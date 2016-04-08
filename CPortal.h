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

#ifndef CPORTAL_H
#define CPORTAL_H

#include"CPortalMsg.h"
#include "common/Exception.hpp"
namespace Taiji {

//portal 协议模块的基本错误
TAIJI_NEW_EXCEPTION_INCLUDE( ExceptPortal,Exception, 200 )

//错误的 协议版本
TAIJI_NEW_EXCEPTION_INCLUDE( ExceptErrorVersion,ExceptPortal, 201 )

class CPortal
{
public:
    CPortal( EPORTAL_VER ver = EPORTAL_VER::VER1 );

    void userAuth( std::string& userIp,
                   std::string& userName,
                   std::string&userPass,
                   std::string& nasIp, uint16_t port );

private:
    EPORTAL_VER _ver;
};


}


#endif // CPORTAL_H
