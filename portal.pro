TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CPortalMsg.cpp \
    CPortal.cpp \
    CPortalAttr.cpp

HEADERS += \
    CPortalMsg.h \
    common/Exception.hpp \
    CPortal.h \
    CPortalAttr.h \
    PortalCommon.h

