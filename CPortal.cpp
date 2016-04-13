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



CPortal::CPortal(EPORTAL_VER ver)
{
    _session._ver = ver;
}

void CPortal::setVersion(EPORTAL_VER ver)
{
    _session._ver = ver;
}

void CPortal::userAuth(std::string &userIp, std::string &userName,
                       std::string &userPass, std::string &nasIp, uint16_t nasPort)
{
    //保存回话信息
    _session._serialNo = ::random();
    _session._userIp = userIp;
    Poco::Net::SocketAddress addr( nasIp, nasPort );
    _session._nasAddr = addr;

    std::shared_ptr<CPortalMsgV1> pMsgPack = nullptr;
    if ( EPORTAL_VER::VER1 == _session._ver )
    {
        pMsgPack = std::shared_ptr<CPortalMsgV1>( new CPortalMsgV1 );
    }else if ( EPORTAL_VER::VER2 == _session._ver )
    {

    }else
    {
        throw ExceptErrorVersion("version is not support");
    }

    //发送 challenge

    //接收 challenge

    //发送认证包

    //接收认真响应包
}

void CPortal::sendChallenge( std::shared_ptr<CPortalMsgV1>& p )
{
    p->setUserIp( _session._userIp );
    p->setType( EMSG_TYPE::REQ_CHALLENGE );
    const HexType& data = p->pack();
    _sock.sendTo( data.data(), data.length(), _session._nasAddr );
}


}


