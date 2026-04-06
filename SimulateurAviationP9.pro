QT       += core gui widgets quick quickwidgets quick3d quickcontrols2

TARGET   = SimulateurAviationP9

CONFIG   += c++17 console

SOURCES += SimulateurAviationP9.cpp \
		   menuPrincipale.cpp \
		   simulation.cpp \
		   gestionnaireScenes.cpp \
		   transitions.cpp \
		   indicateurComponent.cpp \
		   avion.cpp \
		   simulationCockpit.cpp

HEADERS += menuPrincipale.h \
		   simulation.h \
		   gestionnaireScenes.h \
		   transitions.h \
		   indicateurComponent.h \
		   avion.h \
		   simulationCockpit.h