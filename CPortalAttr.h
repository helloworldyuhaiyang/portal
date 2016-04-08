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

class CPortalAttr
{
public:
    CPortalAttr() = default;
    ~CPortalAttr() = default;



private:
    EAttrType _type = EAttrType::NONE_TYPE; ///< 包类型
    uint8_t _length = sizeof( SAttrPack );              ///< 长度
    std::string _val = "";              ///< 数据段
};

#endif // CPORTALATTR_H
