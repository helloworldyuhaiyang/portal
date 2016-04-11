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

#include "CPortalAttr.h"

namespace Taiji {


EATTR_TYPE CPortalAttr::type() const
{
    return _head._type;
}

void CPortalAttr::setType(const EATTR_TYPE &type)
{
    _head._type = type;
}

uint8_t CPortalAttr::length() const
{
    return _head._length;
}

std::string CPortalAttr::val() const
{
    return _val;
}

void CPortalAttr::setVal(const std::string &val)
{
    _val = val;
    _head._length = val.length();
}

const HexType &CPortalAttr::pack()
{
    _data.clear();

    _data.append( (char*)&_head, sizeof( _head ) );
    _data.append( (char*)&_val, _val.length() );
    return _data;
}




}


