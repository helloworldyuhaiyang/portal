/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/7
*/

#include "CPortal.h"
#include <memory>

#include <stdlib.h>

namespace Taiji {

using namespace std;


CPortal::CPortal(EPORTAL_VER ver,const string& secret )
{
    _session._ver = ver;
    if ( EPORTAL_VER::VER1 == _session._ver )
    {
        _pMsgPack = std::shared_ptr<CPortalMsgV1>( new CPortalMsgV1 );
    }else if ( EPORTAL_VER::VER2 == _session._ver )
    {
        _pMsgPack = std::shared_ptr<CPortalMsgv2>( new CPortalMsgv2( secret) );
    }else
    {
        throw ExceptErrorVersion("version is not support");
    }
}

void CPortal::setVersion(EPORTAL_VER ver)
{
    _session._ver = ver;
}

void CPortal::sendData(const HexType &data)
{
    //发送数据
    _sock.sendTo( data.data(), data.length(), _session._nasAddr );
}

HexType CPortal::recvData()
{
    Poco::Net::SocketAddress from;
    uint8_t buf[2048];
    int n = _sock.receiveFrom( buf,sizeof(buf), from );
   // int n = _sock.receiveFrom( buf,sizeof(buf), _session._nasAddr );
    PrintHex( buf, n );

    return HexType ( buf,n );
}

void CPortal::userAuth(const std::string &userIp, const std::string &userName,
                       const std::string &userPass, const Poco::Net::SocketAddress &addr,
                       const Poco::Timespan& timeout )
{
    //保存会话信息
    _session._serialNo = ::random();
    _session._userIp = userIp;
    _session._nasAddr = addr;
    _session._userName = userName;
    _session._userPass = userPass;
    //设置超时时间
    _sock.setReceiveTimeout( timeout );

    //发送 challenge
    sendChallenge();
    //发送认证包
    sendAuthReq();
    //发送认证响应包
    sendAffAuthAck();
}

void CPortal::userLogout(const string &userIp,
                         const Poco::Net::SocketAddress &addr,
                         const Poco::Timespan &timeout )
{
    //保存回话信息
    _session._serialNo = ::random();
    _session._userIp = userIp;
    _session._nasAddr = addr;
    //设置超时时间
    _sock.setReceiveTimeout( timeout );



    _pMsgPack->setType( EMSG_TYPE::REQ_LOGOUT );
    _pMsgPack->setSerialNo( _session._serialNo );
    _pMsgPack->setUserIp( _session._userIp );
    //发送数据
    sendData( _pMsgPack->pack() );
    HexType rData = recvData();
    _pMsgPack->clearAttr();
    _pMsgPack->unpack( rData );
    //类型判断
    if ( _pMsgPack->type() != EMSG_TYPE::ACK_LOGOUT )
    {
        throw ExceptUnexceptedPack( "type is not logout ack" );
    }
    //判断序列号
    if ( _pMsgPack->serialNo() != _session._serialNo )
    {
        char buf[1024];
        snprintf( buf, sizeof(buf),"serialNo is not eq.except(%d),actually is(%d)",
                  _session._serialNo, _pMsgPack->serialNo());
        throw ExceptUnexceptedPack( buf );
    }
    //errcode != 0
    uint8_t errCode = _pMsgPack->errCode();
    if ( 0 != errCode )
    {
        switch ( errCode )
        {
            case 1: throw ExceptUnexceptedPack("user logout is refused"); break;
            case 2: throw ExceptUnexceptedPack( "user logout failed" ); break;
            default : throw ExceptUnexceptedPack( "unknow errCode" );
        }
    }
}


void CPortal::sendChallenge( void )
{
    _pMsgPack->setType( EMSG_TYPE::REQ_CHALLENGE );
    _pMsgPack->setSerialNo( _session._serialNo );
    _pMsgPack->setUserIp( _session._userIp );
    //发送数据
    _pMsgPack->clearAttr();
    sendData( _pMsgPack->pack() );
    HexType rData = recvData();
    _pMsgPack->clearAttr();
    _pMsgPack->unpack( rData );

    //类型判断
    if ( _pMsgPack->type() != EMSG_TYPE::ACK_CHALLENGE )
    {
        throw ExceptUnexceptedPack( "type is not challenge ack" );
    }
    //判断序列号
    if ( _pMsgPack->serialNo() != _session._serialNo )
    {
        char buf[1024];
        snprintf( buf, sizeof(buf),"serialNo is not eq.except(%d),actually is(%d)",
                  _session._serialNo, _pMsgPack->serialNo());
        throw ExceptUnexceptedPack( buf );
    }

    //errcode != 0
    uint8_t errCode = _pMsgPack->errCode();
    if ( 0 != errCode )
    {
        switch ( errCode )
        {
            case 1: throw ExceptUnexceptedPack("challenge refused"); break;
            case 2:  break;	//链接已经建立
            case 3: throw ExceptUnexceptedPack( "user is authing, try again later,when challenge"); break;//稍后再试
            case 4: throw ExceptUnexceptedPack( "challenge failed (errcode:4)" );break;
            default : throw ExceptUnexceptedPack( "unknow errCode" );
        }
    }

    //取属性
    const AttrVer& attrs = _pMsgPack->attrs();
    //获取 challenge 值,及 reqid 的值
    for ( auto& it : attrs )
    {
        if( it.type() == EATTR_TYPE::CHALLENGE ){
           _session._challenge = it.val();
        }
    }
    _session._reqId = _pMsgPack->reqId();
}




void CPortal::sendAuthReq()
{
    uint8_t chapId = _session._reqId & 0xff;
    HexType in;
    in.append( &chapId,1 );
    in.append( (uint8_t*)_session._userPass.data(), _session._userPass.length() );
    in.append( (uint8_t*)_session._challenge.data(), _session._challenge.length() );
    HexType out = md5( in );
    CPortalAttr chapPass( EATTR_TYPE::CHAP_PASS_WORD, out );
    CPortalAttr userName( EATTR_TYPE::USER_NAME, _session._userName );
    //添加认证信息
    _pMsgPack->clearAttr();
    _pMsgPack->addAttr( userName );
    _pMsgPack->addAttr( chapPass );
    //发送数据
    _pMsgPack->setType( EMSG_TYPE::REQ_AUTH );
    _pMsgPack->setSerialNo( _session._serialNo );
    _pMsgPack->setReqId( _session._reqId );
    _pMsgPack->setUserIp( _session._userIp );
    sendData( _pMsgPack->pack() );


    //接收数据
    HexType rData = recvData();
    _pMsgPack->clearAttr();
    //解包数据
    _pMsgPack->unpack( rData );
    // serialNo 和 类型
    //类型判断
    if ( _pMsgPack->type() != EMSG_TYPE::ACK_AUTH )
    {
        throw ExceptUnexceptedPack( "type is not auth ack" );
    }
    //判断序列号
    if ( _pMsgPack->serialNo() != _session._serialNo )
    {
        char buf[1024];
        snprintf( buf, sizeof(buf),"serialNo is not eq.except(%d),actually is(%d)",
                  _session._serialNo, _pMsgPack->serialNo());
        throw ExceptUnexceptedPack( buf );
    }

    // errcode != 0
    uint8_t errCode = _pMsgPack->errCode();
    if ( 0 != errCode )
    {
        switch ( errCode )
        {
            case 1: throw ExceptUnexceptedPack("auth req is refused"); break;
            case 2:  break;	//链接已经建立
            case 3: throw ExceptUnexceptedPack( "user is authing, try again later,when auth req"); break;//稍后再试
            case 4: throw ExceptUnexceptedPack( "auth failed (errcode:4)" );break;
            default : throw ExceptUnexceptedPack( "unknow errCode" );
        }
    }

}

void CPortal::sendAffAuthAck()
{
    //发送数据
    _pMsgPack->setType( EMSG_TYPE::AFF_ACK_AUTH );
    _pMsgPack->setSerialNo( _session._serialNo );
    _pMsgPack->setReqId( _session._reqId );
    _pMsgPack->setUserIp( _session._userIp );
    _pMsgPack->clearAttr();
    sendData( _pMsgPack->pack() );
}



}


