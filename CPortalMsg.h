/**
* Copyright (c) 2015, 爱wifi（版权声明）
*
* @file xxxxxxx
* @brief 文件的简单介绍
*
* 文件的详细介绍
*
* @author: yuhaiyang
* @date: 2016/3/24
*/

#ifndef CPORTALMSG_H
#define CPORTALMSG_H

#include <stdint.h>
#include <map>
#include <vector>

//portal 协议的版本号
enum class EPORTAL_VER : uint8_t
{
    VER1 = 0x01,
    VER2 = 0x02
};

//portal 协议认证类型
enum class EAUTH_TYPE : uint8_t
{
    CHAP = 0x00,
    PAP = 0x01
};


//包类型
enum class EMSG_TYPE : uint8_t
{
    NONE = 0x00,
    REQ_CHALLENGE = 0x01,
    ACK_CHALLENGE = 0x02,
    REQ_AUTH = 0x03,
    ACK_AUTH = 0x04,
    REQ_LOGOUT = 0x05,
    ACK_LOGOUT = 0x06,
    AFF_ACK_AUTH = 0x07,
    NTF_LOGOUT = 0x08,
    REQ_INFO = 0x09,
    ACK_INFO = 0x0a,
};



//存放网络数据包的数据类型
typedef std::string HexType;


//portal 协议类
class CPortalMsgV1
{
public:
    typedef std::map<EMSG_TYPE,std::string> MsgType2Str;
public:
    CPortalMsgV1() = default;
    ~CPortalMsgV1() = default;

    EMSG_TYPE type() const;
    void setType(const EMSG_TYPE &type);
    std::string getTypeStr( void );

    EAUTH_TYPE auth() const;
    void setAuth(const EAUTH_TYPE &auth);

    uint8_t rsv() const;
    void setRsv(const uint8_t &rsv);

    uint16_t serialNo() const;
    void setSerialNo(const uint16_t &serialNo);

    uint16_t reqId() const;
    void setReqId(const uint16_t &reqId);

    uint32_t userMac() const;
    void setUserMac(const uint32_t &userMac);

    uint16_t userPort() const;
    void setUserPort(const uint16_t &userPort);

    uint8_t errCode() const;
    void setErrCode(const uint8_t &errCode);

    uint8_t attrNum() const;
    void setAttrNum(const uint8_t &attrNum);

    HexType pack( void );
    /**
     * @brief unpack
     * @warning throw Taiji::InvaildPortalPack()
     */
    void unpack( void );
private:
    static MsgType2Str _typeStr;			//数据包类型与对应的字符串
    //数据包的头

#pragma pack(push)
#pragma pack(1)
    struct  SMsgHead
    {
        EPORTAL_VER _ver = EPORTAL_VER::VER1;	//协议版本
        EMSG_TYPE _type = EMSG_TYPE::NONE;		//报文类型
        EAUTH_TYPE _auth = EAUTH_TYPE::CHAP;	//用户的认证方式,现在只需要支持chap模式
        uint8_t _rsv = 0;		//预留字段,全部填0
        uint16_t _serialNo = 0; //报文序列号 portal 随机生成
        uint16_t _reqId = 0;	//nas 设备随机生成
        uint32_t _userMac = 0; 	//用户的 mac
        uint16_t _userPort = 0;	//用户的 port 没有用到
        uint8_t _errCode = 0;	//错误码
        uint8_t _attrNum = 0;	//属性个数
    } _head;
#pragma pack(pop)
    //属性数组
   //std::vector<attr> _attr;
   HexType _data;			//存放网络数据包
};

#endif // CPORTALMSG_H
