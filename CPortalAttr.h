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

#ifndef CPORTALATTR_H
#define CPORTALATTR_H

#include <string>
#include "PortalCommon.h"

namespace Taiji {


class CPortalAttr
{
public:
    CPortalAttr() = default;
    ~CPortalAttr() = default;



    EATTR_TYPE type() const;
    void setType(const EATTR_TYPE &type);

    uint8_t length() const;

    std::string val() const;
    void setVal(const std::string &val);

    const HexType& pack( void );

private:
    struct SAttrHead
    {
        EATTR_TYPE _type = EATTR_TYPE::NONE; 	///< 包类型
        uint8_t _length = 0;              		///< 长度
    } _head;
    std::string _val = "";              	///< 数据段
    HexType _data;							///< 网络数据包
};



}

#endif // CPORTALATTR_H



