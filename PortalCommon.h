/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/8
*/

#ifndef PORTALCOMMON_H
#define PORTALCOMMON_H

#include "Taiji/TExcept/Except.h"
#include <vector>
#include <map>

namespace Taiji {


//portal 协议模块的基本异常
TAIJI_NEW_EXCEPTION( ExceptPortal,ExceptProtocal );

//错误的 协议版本
TAIJI_NEW_EXCEPTION( ExceptErrorVersion,ExceptPortal);

//错误的长度
TAIJI_NEW_EXCEPTION( ExceptInvildLength,ExceptPortal );

//报文格式不对。根据协议要求不能解析
TAIJI_NEW_EXCEPTION( ExceptErrorFormat,ExceptPortal );


//不是预期的包
TAIJI_NEW_EXCEPTION( ExceptUnexceptedPack,ExceptPortal );

//重复的请求
TAIJI_NEW_EXCEPTION( ExceptDuplicateReq, ExceptPortal);


//Timeout exception
TAIJI_NEW_EXCEPTION( ExceptTimeout, ExceptPortal );
//portal 协议的版本号
enum class EPORTAL_VER : uint8_t
{
    VER1 = 0x01,
    VER2 = 0x02
};

//portal 协议认证类型
enum class EAUTH_TYPE : uint8_t
{
    CHAP = 0x00,
    PAP = 0x01
};


//portal 包类型
enum class EMSG_TYPE : uint8_t
{
    NONE = 0x00,
    REQ_CHALLENGE = 0x01,
    ACK_CHALLENGE = 0x02,
    REQ_AUTH = 0x03,
    ACK_AUTH = 0x04,
    REQ_LOGOUT = 0x05,
    ACK_LOGOUT = 0x06,
    AFF_ACK_AUTH = 0x07,
    NTF_LOGOUT = 0x08,
    REQ_INFO = 0x09,
    ACK_INFO = 0x0a,
};


enum class EATTR_TYPE : uint8_t
{
    NONE = 0x00,
    USER_NAME = 0x01,
    PASSWORD = 0x02,
    CHALLENGE = 0x03,
    CHAP_PASS_WORD = 0x04

    //其它的不需要先不弄
};

//存放网络数据包的数据类型
typedef std::basic_string<uint8_t> HexType;


void PrintHex( const void *data, size_t len );


HexType md5(const HexType &in);
//#define DEBUGOUT( argv, value )  	std::cout << "DEBUG INFO:" << argv << ":" << value << std::endl;

}

#endif // PORTALCOMMON_H

