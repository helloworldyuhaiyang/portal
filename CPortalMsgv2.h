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

#ifndef CPORTALMSGV2_H
#define CPORTALMSGV2_H

#include "CPortalMsg.h"
#include <string>

namespace Taiji{


class CPortalMsgv2 : public CPortalMsgV1
{
public:
    CPortalMsgv2( const std::string& secret );
    CPortalMsgv2() = delete;
    virtual ~CPortalMsgv2() = default;


    virtual const HexType& pack();

    /**
     * @brief unpack
     * @warnin
     */
    virtual void unpack( const HexType& data );


    virtual void clear( void );
protected:
    /**
     * @brief getAuthenticator
     * @param authenticator
     */
    void getReqAuthenticator( void );


    void getAckAuthenticator( void );


private:
    HexType _reqAuthenticator;	///请求包的 authenticator
    HexType _ackAuthenticator;	///响应包的 authenticator
    std::string _secret;		///< 共享密钥
};




}


#endif // CPORTALMSGV2_H
