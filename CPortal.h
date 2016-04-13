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
namespace Taiji {



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
