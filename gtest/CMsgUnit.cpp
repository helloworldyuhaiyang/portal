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

#include "CMsgUnit.h"

using std::string;

void CMsgUnit::SetUpTestCase()
{
    std::cout << "开始 Msg 包测试" << std::endl;
}

void CMsgUnit::TearDownTestCase()
{
   std::cout << "结束 Msg　包测试" << std::endl;
}



TEST_F( CMsgUnit, pack_Ok )
{
    _msg.setType( EMSG_TYPE::REQ_AUTH );
    _msg.setSerialNo( 123 );
    _msg.setReqId( 456 );
    _msg.setUserIp( "192.168.10.179" );
    _msg.setUserPort( 8081 );
    //添加属性
    _msg.addAttr( CPortalAttr( EATTR_TYPE::USER_NAME, "yuhaiyang" ) );
    _msg.addAttr( CPortalAttr( EATTR_TYPE::PASSWORD, "123456" ) );
    //打包数据
    HexType data = _msg.pack();

    HexType obj = {
        0x01, 0x03, 0x00, 0x00, 0x00, 0x7b, 0x01, 0xc8, 0xc0, 0xa8,
        0x0a, 0xb3, 0x1f, 0x91, 0x00, 0x02, 0x01, 0x0b, 0x79, 0x75,
        0x68, 0x61, 0x69, 0x79, 0x61, 0x6e, 0x67, 0x02, 0x08, 0x31,
        0x32, 0x33, 0x34, 0x35, 0x36
    };

    PrintHex( data.data(), data.length() );
    PrintHex( obj.data(), obj.length() );

    //对比数据
    ASSERT_EQ( data, obj );
}


TEST_F( CMsgUnit, unpack_Ok )
{
    HexType obj = {
        0x01, 0x03, 0x00, 0x00, 0x00, 0x7b, 0x01, 0xc8, 0xc0, 0xa8,
        0x0a, 0xb3, 0x1f, 0x91, 0x00, 0x02, 0x01, 0x0b, 0x79, 0x75,
        0x68, 0x61, 0x69, 0x79, 0x61, 0x6e, 0x67, 0x02, 0x08, 0x31,
        0x32, 0x33, 0x34, 0x35, 0x36
    };
    //解包数据
    _msg.unpack( obj );
    //获取解包的数据
    string typeStr = _msg.getTypeStr();
    std::cout << "MsgType:" << typeStr << std::endl;

    uint16_t serialNo =_msg.serialNo();
    uint16_t reqId = _msg.reqId();
    string userIp = _msg.userIp();
    uint16_t port = _msg.userPort();


    ASSERT_EQ( typeStr, "auth req" );
    ASSERT_EQ( serialNo, 123 );
    ASSERT_EQ( reqId, 456 );
    ASSERT_EQ( userIp, "192.168.10.179" );
    ASSERT_EQ( port, 8081 );
    std::cout << "userIp: " << userIp << std::endl;
}




