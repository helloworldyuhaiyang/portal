/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/11
*/

#ifndef CATTRUNIT_H
#define CATTRUNIT_H

#include <gtest/gtest.h>
#include "CPortalAttr.h"

using namespace Taiji;

class CAttrUnit : public testing::Test
{
public:
    CAttrUnit() = default;
    ~CAttrUnit() = default;

    static void SetUpTestCase( void );
    static void TearDownTestCase( void );

    Taiji::CPortalAttr _attr;

};

#endif // CATTRUNIT_H
