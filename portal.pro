TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    CPortalMsg.cpp \
    CPortal.cpp \
    CPortalAttr.cpp \
    common/Exception.cpp \
    PortalCommon.cpp	\
    gtest/CAttrUnit.cpp \
    gtest/CMsgUnit.cpp \
    gtest/CPortalUnit.cpp

HEADERS += \
    CPortalMsg.h \
    CPortal.h \
    CPortalAttr.h \
    PortalCommon.h \
    common/Exception.h	\
    gtest/CAttrUnit.h \
    gtest/CMsgUnit.h \
    gtest/CPortalUnit.h


LIBS += \
        -lgtest    \
        -lgtest_main   \
        -lpthread	\
        -lPocoNet	\
        -lPocoFoundation	\
        -lcrypto
