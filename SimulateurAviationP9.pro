QT       += core gui widgets

TARGET   = SimulateurAviationP9

CONFIG   += c++17 console

SOURCES += SimulateurAviationP9.cpp \
		   menuPrincipale.cpp \
		   simulation.cpp \
		   gestionnaireScenes.cpp \
		   transitions.cpp \
		   indicateurComponent.cpp \
		   avion.h

HEADERS += menuPrincipale.h \
		   simulation.h \
		   gestionnaireScenes.h \
		   transitions.h \
		   indicateurComponent.h \
		   avion.h