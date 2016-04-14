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
    CPortal() = delete;
    CPortal( EPORTAL_VER ver = EPORTAL_VER::VER1 );

    //设置协议版本号
    void setVersion( EPORTAL_VER ver );

    //发送数据
    void sendData( const HexType& data );

    //接收数据
    HexType recvData();

    void userAuth( const std::string& userIp,
                   const std::string& userName,
                   const std::string& userPass,
                   const Poco::Net::SocketAddress& addr,
                   const Poco::Timespan &timeout);

    void userLogout( const std::string& userIp,
                     const Poco::Net::SocketAddress& addr, Poco::Timespan& timeout );
    /**
     * @brief sendChallenge
     *
     * 发送 challenge 请求
     */
    void sendChallenge( void );

    /**
     * @brief sendAuthReq
     *
     * 发送 登陆请求
     */
    void sendAuthReq( void );


    /**
     * @brief sendAuthAck
     *
     * 发送认证成功响应报文
     */
    void sendAffAuthAck( void );

    static HexType md5( const HexType& in );
private:
    struct SSession
    {
        EPORTAL_VER _ver;
        uint16_t _serialNo = 0;	//portal 生成的同一流程相同
        uint16_t _reqId = 0;		//由 nas 响应 challenge 时候生成。后面的流程都是相同的。
        std::string _userIp = ""; 	//大端的4字节的 userIp
        std::string _challenge = "";	//一次交互的 challenge
        std::string _userName = "";		//用户名
        std::string _userPass = "";		//用户密码
        Poco::Net::SocketAddress _nasAddr;
    }_session;

    Poco::Net::DatagramSocket _sock;	//发送报文的 socket
    std::shared_ptr<CPortalMsgV1> _pMsgPack;
};

}

#endif // CPORTAL_H
