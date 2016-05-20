TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    gtest \
    common

SOURCES += \
    CPortalMsg.cpp \
    CPortal.cpp \
    CPortalAttr.cpp \
    PortalCommon.cpp	\
    gtest/CAttrUnit.cpp \
    gtest/CMsgUnit.cpp \
    gtest/CPortalUnit.cpp \
    CPortalMsgv2.cpp \
    common/PortalException.cpp

HEADERS += \
    CPortalMsg.h \
    CPortal.h \
    CPortalAttr.h \
    PortalCommon.h \
    gtest/CAttrUnit.h \
    gtest/CMsgUnit.h \
    gtest/CPortalUnit.h \
    CPortalMsgv2.h \
    common/PortalException.h


LIBS += \
        -lgtest    \
        -lgtest_main   \
        -lpthread	\
        -lPocoNet	\
        -lPocoFoundation	\
        -lcrypto
