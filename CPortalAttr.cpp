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

#include <memory.h>

namespace Taiji {


CPortalAttr::CPortalAttr(EATTR_TYPE type, const std::__cxx11::string &val)
{
    setType( type );
    setVal( val );
}

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
    _head._length = val.length() + 2;
}

const HexType &CPortalAttr::pack()
{
    _data.clear();

    _data.append( (char*)&_head, sizeof( _head ) );
    _data.append( (char*)_val.data(), _val.length() );
    return _data;
}

void CPortalAttr::unpack( const HexType& data )
{
    if ( data.length() < sizeof( SAttrHead ) )
    {
        throw ExceptInvildLength("length of attr pack is too small");
    }
    //解析头
    ::memcpy( &_head, data.data(),sizeof(SAttrHead) );
    //数据的长度小于 head 的 length
    if ( length() > data.length() )
    {
        throw ExceptInvildLength("length of attr is error");
    }
    _val.assign( data.begin()+sizeof(SAttrHead), data.end() );
}

void CPortalAttr::printHex()
{
    const uint8_t* p = (const uint8_t*)_data.data();
    size_t len = _data.length();

    for ( size_t i = 0; i < len; ++i )
    {
        printf("%02x ", *(p+i) );
    }
    printf("\n");
}




}


