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

#include "CPortalMsg.h"


CPortalMsgV1::MsgType2Str CPortalMsgV1::_typeStr =
{
    { EMSG_TYPE::NONE, "no type"},
    { EMSG_TYPE::REQ_CHALLENGE, "challenge req"},
    { EMSG_TYPE::ACK_CHALLENGE, "challenge ack"},
    { EMSG_TYPE::REQ_AUTH, "auth req"},
    { EMSG_TYPE::ACK_AUTH, "auth ack"},
    { EMSG_TYPE::REQ_LOGOUT, "logout req"},
    { EMSG_TYPE::ACK_LOGOUT, "logout ack"},
    { EMSG_TYPE::AFF_ACK_AUTH, "auth sucessful is received"},
    { EMSG_TYPE::NTF_LOGOUT, "forcing users offine"},
    { EMSG_TYPE::REQ_INFO, "info req"},
    { EMSG_TYPE::ACK_INFO, "info ack"}
};

EMSG_TYPE CPortalMsgV1::type() const
{
     return _head._type;
}

void CPortalMsgV1::setType(const EMSG_TYPE &type)
{
    _head._type = type;
}

std::string CPortalMsgV1::getTypeStr()
{
   return _typeStr.find( _head._type )->second;
}

EAUTH_TYPE CPortalMsgV1::auth() const
{
    return _head._auth;
}

void CPortalMsgV1::setAuth(const EAUTH_TYPE &auth)
{
    _head._auth = auth;
}

uint8_t CPortalMsgV1::rsv() const
{
    return _head._rsv;
}

void CPortalMsgV1::setRsv(const uint8_t &rsv)
{
    _head._rsv = rsv;
}

uint16_t CPortalMsgV1::serialNo() const
{
    return _head._serialNo;
}

void CPortalMsgV1::setSerialNo(const uint16_t &serialNo)
{
    _head._serialNo = serialNo;
}

uint16_t CPortalMsgV1::reqId() const
{
    return _head._reqId;
}

void CPortalMsgV1::setReqId(const uint16_t &reqId)
{
    _head._reqId = reqId;
}

uint32_t CPortalMsgV1::userMac() const
{
    return _head._userMac;
}

void CPortalMsgV1::setUserMac(const uint32_t &userMac)
{
    _head._userMac = userMac;
}

uint16_t CPortalMsgV1::userPort() const
{
    return _head._userPort;
}

void CPortalMsgV1::setUserPort(const uint16_t &userPort)
{
    _head._userPort = userPort;
}

uint8_t CPortalMsgV1::errCode() const
{
    return _head._errCode;
}

void CPortalMsgV1::setErrCode(const uint8_t &errCode)
{
    _head._errCode = errCode;
}

uint8_t CPortalMsgV1::attrNum() const
{
    return _head._attrNum;
}



HexType CPortalMsgV1::pack()
{
    _data.clear();

    /*
     * todo 要增加设备的属性个先
     */
    _data.append( (char*)&_head, sizeof(_head) );


    return _data;
}

