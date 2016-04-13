/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/12
*/

#ifndef CMSGUNIT_H
#define CMSGUNIT_H
#include <gtest/gtest.h>
#include "CPortalMsg.h"

using namespace Taiji;


class CMsgUnit : public testing::Test
{
public:
    CMsgUnit() = default;
    ~CMsgUnit() = default;

    static void SetUpTestCase( void );
    static void TearDownTestCase( void );

    Taiji::CPortalMsgV1 _msg;
};

#endif // CMSGUNIT_H
