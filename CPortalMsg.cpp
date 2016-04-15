/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/3/24
*/

#include "CPortalMsg.h"
#include "memory.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using std::string;


namespace Taiji {


CPortalMsgV1::MsgType2Str CPortalMsgV1::_typeStr =
{
    { EMSG_TYPE::NONE, "no type"},
    { EMSG_TYPE::REQ_CHALLENGE, "challenge req"},
    { EMSG_TYPE::ACK_CHALLENGE, "challenge ack"},
    { EMSG_TYPE::REQ_AUTH, "auth req"},
    { EMSG_TYPE::ACK_AUTH, "auth ack"},
    { EMSG_TYPE::REQ_LOGOUT, "logout req"},
    { EMSG_TYPE::ACK_LOGOUT, "logout ack"},
    { EMSG_TYPE::AFF_ACK_AUTH, "auth sucessful is received"},
    { EMSG_TYPE::NTF_LOGOUT, "forcing users offine"},
    { EMSG_TYPE::REQ_INFO, "info req"},
    { EMSG_TYPE::ACK_INFO, "info ack"}
};

EMSG_TYPE CPortalMsgV1::type() const
{
     return _head._type;
}

void CPortalMsgV1::setType(const EMSG_TYPE &type)
{
    _head._type = type;
}

std::string CPortalMsgV1::getTypeStr()
{
   return _typeStr.find( _head._type )->second;
}

EAUTH_TYPE CPortalMsgV1::auth() const
{
    return _head._auth;
}

void CPortalMsgV1::setAuth(const EAUTH_TYPE &auth)
{
    _head._auth = auth;
}

uint8_t CPortalMsgV1::rsv() const
{
    return _head._rsv;
}

void CPortalMsgV1::setRsv(const uint8_t &rsv)
{
    _head._rsv = rsv;
}

uint16_t CPortalMsgV1::serialNo() const
{
    return ::htons( _head._serialNo );
}

void CPortalMsgV1::setSerialNo(const uint16_t &serialNo)
{
    _head._serialNo = ::htons( serialNo );
}

uint16_t CPortalMsgV1::reqId() const
{
    return ::htons( _head._reqId );
}

void CPortalMsgV1::setReqId(const uint16_t &reqId)
{
    _head._reqId = ::htons( reqId );
}

const std::string CPortalMsgV1::userIp()
{
    string userIp = ::inet_ntoa( *(struct in_addr*)&_head._userIp );
    return userIp;
}

void CPortalMsgV1::setUserIp(const std::string &userIp )
{
    _head._userIp = ::inet_addr( userIp.c_str() );
}

uint16_t CPortalMsgV1::userPort() const
{
    return ::ntohs(_head._userPort );
}

void CPortalMsgV1::setUserPort(const uint16_t &userPort)
{
    _head._userPort = ::htons( userPort );
}

uint8_t CPortalMsgV1::errCode() const
{
    return _head._errCode;
}

void CPortalMsgV1::setErrCode(const uint8_t &errCode)
{
    _head._errCode = errCode;
}

uint8_t CPortalMsgV1::attrNum() const
{
    return _head._attrNum;
}

void CPortalMsgV1::setAttrNum(const uint8_t &attrNum)
{
    _head._attrNum = attrNum;
}



const HexType &CPortalMsgV1::pack()
{
    _data.clear();

    //设置属性个数
    setAttrNum( _attrs.size() );
    //添加头信息
    _data.append( ( uint8_t*)&_head, sizeof(_head) );
    //打包所有的属性数据到 _data里
    packAttrs( _data );

    return _data;
}

void CPortalMsgV1::unpack( const HexType& data )
{
    if ( data.length() < sizeof(SMsgHead) )
    {
        throw ExceptInvildLength("length of portal pack is too small");
    }
    //解析头信息
    ::mempcpy( &_head, data.data(), sizeof(SMsgHead) );

    //解析属性包
    auto attrsStart = data.begin() + sizeof(SMsgHead);
    auto attrsEnd = data.end();
    unpackAttrs( attrsStart, attrsEnd );
}

void CPortalMsgV1::addAttr(const CPortalAttr &attr)
{
    _attrs.push_back( attr );
}

const AttrVer &CPortalMsgV1::attrs() const
{
    return _attrs;
}

void CPortalMsgV1::setAttrs(const AttrVer &attr)
{
    _attrs = attr;
}


//解包属性数据到 _attrs
void CPortalMsgV1::unpackAttrs(HexType::const_iterator &start,
                                 HexType::const_iterator &end )
{
    if ( start > end )
    {
        throw ExceptInvildLength( "length of attrpack is invaild");
    }

    uint8_t atNum = attrNum();
    if( start == end && atNum )
    {
        throw ExceptInvildLength( "length of attrpack is invaild");
    }

    HexType::const_iterator it = start;
    CPortalAttr attr;
    for ( int i=0; i < atNum; ++i )
    {
        //解包属性
        attr.unpack( HexType( it, end) );
        //存入数组
        _attrs.push_back( attr );
        //跳过一个属性包
        it += attr.length();
        //判断长度防止越界
        if ( it > end )
        {
            throw ExceptErrorFormat( "Format of attrs is error");
        }
    }
}

void CPortalMsgV1::packAttrs( HexType& data )
{
    //添加属性信息
    for ( auto& it : _attrs )
    {
        const HexType& dataTmp = it.pack();
        data.append( dataTmp.data(), dataTmp.length() );
    }
}





}

