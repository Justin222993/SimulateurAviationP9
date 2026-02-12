#include "transitions.h"

void Transitions::apparition(QWidget* cible, int dureeMs) {
    if (!cible) return; // Safety first kids

    // On applique un effet d'opacité à la cible
    QGraphicsOpacityEffect* effet = new QGraphicsOpacityEffect(cible);
    cible->setGraphicsEffect(effet);

    // Animation de l'opacité
    QPropertyAnimation* animation = new QPropertyAnimation(effet, "opacity");
    animation->setDuration(dureeMs);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Transition quadratique slow-fast-slow

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Transitions::disparition(QWidget* cible, int dureeMs) {
    if (!cible) return;

    QGraphicsOpacityEffect* effet = new QGraphicsOpacityEffect(cible);
    cible->setGraphicsEffect(effet);

    QPropertyAnimation* animation = new QPropertyAnimation(effet, "opacity");
    animation->setDuration(dureeMs);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Transition quadratique slow-fast-slow

    QObject::connect(animation, &QPropertyAnimation::finished, [cible]() {
        cible->hide();
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}