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
#include<memory>

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>


namespace Taiji {



class CPortal
{
public:
    CPortal( EPORTAL_VER ver = EPORTAL_VER::VER1 );

    //设置版本号
    void setVersion( EPORTAL_VER ver );

    void userAuth( std::string& userIp,
                   std::string& userName,
                   std::string&userPass,
                   std::string& nasIp, uint16_t nasPort );

    void sendChallenge(std::shared_ptr<CPortalMsgV1> &p);
private:
    struct SSession
    {
        EPORTAL_VER _ver;
        uint16_t _serialNo = 0;	//portal 生成的同一流程相同
        uint16_t _reqId = 0;		//由 nas 响应 challenge 时候生成。后面的流程都是相同的。
        std::string _userIp = 0; 	//大端的4字节的 userIp
        Poco::Net::SocketAddress _nasAddr;
    }_session;

    Poco::Net::DatagramSocket _sock;	//发送报文的 socket

};

}

#endif // CPORTAL_H
