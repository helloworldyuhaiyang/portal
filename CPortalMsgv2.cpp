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
//#include "PortalCommon.h"
#include <memory.h>

namespace Taiji {




CPortalMsgv2::CPortalMsgv2(const std::string &secret)
{
    _secret = secret;
    _head._ver = EPORTAL_VER::VER2;	//协议版本2
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

void CPortalMsgv2::getAckAuthenticator(void )
{
    //添加 authenticator 到数据包
    HexType authenIn( (uint8_t*)&_head, sizeof(_head) );
    authenIn.append( _reqAuthenticator );
    printf("_reqAuthenticator:\n");
    PrintHex(_reqAuthenticator.data(),16);
    //增加属性包到 authenIn
    packAttrs( authenIn );
    //增加共享密钥
    authenIn.append( (uint8_t*)_secret.data(), _secret.length() );
    printf("portal server计算ackAuthenticator，加密前数据:\n");
    PrintHex( authenIn.data(),authenIn.size());
    //生成认证字
    _ackAuthenticator = md5(authenIn);
    printf("加密后得到的_ackAuthenticator:\n");
    PrintHex( _ackAuthenticator.data(),16);

}


}
