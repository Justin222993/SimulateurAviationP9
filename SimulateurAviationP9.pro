QT       += core gui widgets quick quickwidgets quick3d

TARGET   = SimulateurAviationP9
CONFIG   += c++17 console

SOURCES += \
    SimulateurAviationP9.cpp \
    menuPrincipale.cpp \
    simulation.cpp \
    gestionnaireScenes.cpp \
    transitions.cpp \
    indicateurComponent.cpp \
    SerialConnectionGateway.cpp \
    SerialManager.cpp \
    avion.cpp \
    $$PWD/include/serial/SerialPort.cpp

HEADERS += \
    menuPrincipale.h \
    simulation.h \
    gestionnaireScenes.h \
    transitions.h \
    indicateurComponent.h \
    avion.h \
    SerialConnectionGateway.h \
    SerialManager.h \
    ./include/json.hpp \
    ./include/serial/SerialPort.hpp

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/serial
