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

namespace Taiji {


TAIJI_NEW_EXCEPTION_CPP( 200, ExceptPortal )

TAIJI_NEW_EXCEPTION_CPP( 201, ExceptErrorVersion )

CPortal::CPortal(EPORTAL_VER ver)
{
    _ver = ver;
}

void CPortal::userAuth(std::string &userIp, std::string &userName,
                       std::string &userPass, std::string &nasIp, uint16_t port)
{
    std::shared_ptr<CPortalMsgV1> p = nullptr;
    if ( EPORTAL_VER::VER1 == _ver )
    {
        p = std::shared_ptr<CPortalMsgV1>( new CPortalMsgV1 );
    }else if ( EPORTAL_VER::VER2 == _ver )
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


}


