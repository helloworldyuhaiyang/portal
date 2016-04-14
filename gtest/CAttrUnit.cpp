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

#include "CAttrUnit.h"
#include <string>

using namespace Taiji;
using namespace std;

void CAttrUnit::SetUpTestCase()
{
   std::cout << "===========开始包属性测试=============" << std::endl;
}

void CAttrUnit::TearDownTestCase()
{
   std::cout << "===========结束包属性测试=============" << std::endl;
}


TEST_F( CAttrUnit,pack_OK )
{
    _attr.setType( EATTR_TYPE::USER_NAME );
    _attr.setVal("yuhaiyang");
    HexType data = _attr.pack();
    HexType obj = { 0x01, 0x0b, 0x79, 0x75, 0x68, 0x61, 0x69, 0x79, 0x61, 0x6e, 0x67 };
    PrintHex( obj.data(), obj.length() );
    PrintHex( obj.data(), obj.length() );
    ASSERT_EQ( data, obj );
}

TEST_F( CAttrUnit,unpack_OK )
{
    HexType obj = { 0x01, 0x0b, 0x79, 0x75, 0x68, 0x61, 0x69, 0x79, 0x61, 0x6e, 0x67 };
    _attr.unpack( obj );
    EATTR_TYPE type = _attr.type();
    int len = _attr.length();
    string val = _attr.val();

    std::cout << "len: " << (int)_attr.length() << std::endl;
    std::cout << "val: " << _attr.val() << std::endl;
    ASSERT_EQ( EATTR_TYPE::USER_NAME, type );
    ASSERT_EQ( len, 11 );
    ASSERT_EQ( val, string("yuhaiyang") );
}

TEST_F( CAttrUnit, attr_type2Str )
{
    CPortalAttr attr;
    attr.setType( EATTR_TYPE::CHALLENGE );
    string typeStr = attr.getTypeStr();
    std::cout << "typeStr: " <<  typeStr << std::endl;

    ASSERT_EQ( "challenge", typeStr );
}
