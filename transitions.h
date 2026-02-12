#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class Transitions {
public:
    static void apparition(QWidget* cible, int dureeMs = 1000);

    static void disparition(QWidget* cible, int dureeMs = 1000);
};

#endif