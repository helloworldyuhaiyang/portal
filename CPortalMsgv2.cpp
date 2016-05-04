/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/15
*/

#include "CPortalMsgv2.h"

#include <memory.h>

namespace Taiji {




CPortalMsgv2::CPortalMsgv2(const std::string &secret)
{
    _head._ver = EPORTAL_VER::VER2;
    _secret = secret;
}

const HexType& CPortalMsgv2::pack()
{
    _data.clear();

    //设置属性个数
    setAttrNum( _attrs.size() );
    //添加头信息
    _data.append( ( uint8_t*)&_head, sizeof(_head) );
    //添加 authenticator 到数据包
    getReqAuthenticator();
    //增加认证字段到数据包
    _data.append( _reqAuthenticator );
    //打包所有的属性数据到 _data里
    packAttrs( _data );

    return _data;
}

void CPortalMsgv2::unpack(const HexType &data)
{
    if ( data.length() < sizeof(SMsgHead) +16 )
    {
        throw ExceptInvildLength("length of portal pack is too small");
    }
    //解析头信息
    ::mempcpy( &_head, data.data(), sizeof(SMsgHead) );
    //取出发送过来的 authenticator
    HexType authenRecv;
    authenRecv.append( data.data()+sizeof(SMsgHead), 16 );
    //解析属性包
    auto attrsStart = data.begin() + sizeof(SMsgHead)+16;
    auto attrsEnd = data.end();
    unpackAttrs( attrsStart, attrsEnd );

    //获取本数据包应该的 authenticator
    getAckAuthenticator();
    //核对 authenticator 的值
    if ( authenRecv != _ackAuthenticator )
    {
        throw ExceptUnexceptedPack( "authenticator is not correct" );
    }
}

void CPortalMsgv2::clear()
{
    _head._ver = EPORTAL_VER::VER2;	//协议版本
    _head._type = EMSG_TYPE::NONE;		//报文类型
    _head._auth = EAUTH_TYPE::CHAP;	//用户的认证方式,现在只需要支持chap模式
    _head._rsv = 0;		//预留字段,全部填0
    _head._serialNo = 0; //报文序列号 portal 随机生成
    _head._reqId = 0;	//nas 设备随机生成
    _head._userIp = 0; 	//用户的 mac
    _head._userPort = 0;	//用户的 port 没有用到
    _head._errCode = 0;	//错误码
    _head._attrNum = 0;	//属性个数

    _reqAuthenticator.clear();
    _ackAuthenticator.clear();
    //清空属性
    _attrs.clear();
}


void CPortalMsgv2::getReqAuthenticator(void )
{
    //添加 authenticator 到数据包
    HexType authenIn( (uint8_t*)&_head, sizeof(_head) );
    authenIn.append( 16, 0x00 );
    //增加属性包到 authenIn
    packAttrs( authenIn );
    //增加共享密钥
    authenIn.append( (uint8_t*)_secret.data(), _secret.length() );
    //生成认证字
    _reqAuthenticator = md5( authenIn );
}

 void CPortalMsgv2::getAckAuthenticator()
{
    //添加 authenticator 到数据包
    HexType authenIn( (uint8_t*)&_head, sizeof(_head) );
    authenIn.append( _reqAuthenticator );
    //增加属性包到 authenIn
    packAttrs( authenIn );
    //增加共享密钥
    authenIn.append( (uint8_t*)_secret.data(), _secret.length() );
    //生成认证字
    _ackAuthenticator = md5( authenIn );
}



}
