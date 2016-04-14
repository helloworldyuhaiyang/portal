/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/4/13
*/

#ifndef CPORTALUNIT_H
#define CPORTALUNIT_H

#include <gtest/gtest.h>
#include "CPortal.h"

using namespace Taiji;

class CPortalUnit : public testing::Test
{
public:
    CPortalUnit() = default;
    ~CPortalUnit() = default;
    static void SetUpTestCase( void );
    static void TearDownTestCase( void );
};

#endif // CPORTALUNIT_H
