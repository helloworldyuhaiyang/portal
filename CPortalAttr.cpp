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

CPortalAttr::AttrType2Str CPortalAttr::_typeStr = {
    { EATTR_TYPE::NONE, "init attr" },
    { EATTR_TYPE::USER_NAME, "user name" },
    { EATTR_TYPE::PASSWORD, "passWord" },
    { EATTR_TYPE::CHALLENGE, "challenge"},
    { EATTR_TYPE::CHAP_PASS_WORD, "chap password" }
};


CPortalAttr::CPortalAttr(const CPortalAttr &other)
{
    setType( other.type() );
    setVal( other.val() );
}

CPortalAttr::CPortalAttr(EATTR_TYPE type, const std::string &val)
{
    setType( type );
    setVal( val );
}

CPortalAttr::CPortalAttr(EATTR_TYPE type, const HexType &val)
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

std::string CPortalAttr::getTypeStr()
{
    return _typeStr.find( _head._type )->second;
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
    _head._length = val.length() + sizeof(SAttrHead);
}

void CPortalAttr::setVal(const HexType &val)
{
    _val.assign( (char*)val.data(), val.length() );
    _head._length = val.length() + sizeof(SAttrHead);
}

const HexType &CPortalAttr::pack()
{
    _data.clear();

    _data.append( (uint8_t*)&_head, sizeof( _head ) );
    _data.append( (uint8_t*)_val.data(), _val.length() );
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
        throw ExceptInvildLength("length of attr is bigger then length of data");
    }
    auto begin = data.begin()+sizeof(SAttrHead);
    _val.assign( begin, begin+length()-sizeof(SAttrHead) );
}

//void CPortalAttr::printHex()
//{
//    const uint8_t* p = (const uint8_t*)_data.data();
//    size_t len = _data.length();

//    for ( size_t i = 0; i < len; ++i )
//    {
//        printf("%02x ", *(p+i) );
//    }
//    printf("\n");
//}


}


