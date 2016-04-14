/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file PortalCommon.cpp
* @brief portal 公共文件
*
*
* @author: yuhaiyang
* @date: 2016/4/11
*/

#include "PortalCommon.h"

namespace Taiji {

//portal 协议模块的基本异常
TAIJI_NEW_EXCEPTION_CPP( ExceptPortal,ExceptProtocal, 20 )

//错误的 协议版本
TAIJI_NEW_EXCEPTION_CPP( ExceptErrorVersion,ExceptPortal, 1 )

//错误的长度
TAIJI_NEW_EXCEPTION_CPP( ExceptInvildLength,ExceptPortal, 2 )


//报文格式不对。根据协议要求不能解析
TAIJI_NEW_EXCEPTION_CPP( ExceptErrorFormat,ExceptPortal, 3 )

//不是预期的报文
TAIJI_NEW_EXCEPTION_CPP( ExceptUnexceptedPack,ExceptPortal ,4 )


void PrintHex( const void *data, size_t len )
{
    const uint8_t* p = (const uint8_t*)data;

    for ( size_t i = 0; i < len; ++i )
    {
        printf("%02x ", *(p+i) );
    }
    printf("\n");
}

}
