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

protected:
    /**
     * @brief getAuthenticator
     * @param authenticator
     */
    HexType getAuthenticator( void );

private:
    std::string _secret;	///< 共享密钥
};




}


#endif // CPORTALMSGV2_H
