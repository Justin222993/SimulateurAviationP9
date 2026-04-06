#ifndef SIMULATIONCOCKPIT_H
#define SIMULATIONCOCKPIT_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <iostream>
#include <thread>
#include <conio.h>
#include <iomanip>
#include <QQuickWidget>
#include <QMetaObject>
#include <QQuickItem>
#include "indicateurComponent.h"
#include "avion.h"

class SimulationCockpit : public QWidget {
    Q_OBJECT

    public:
        SimulationCockpit(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

    private:
        // 3D
        QQuickWidget* view3d;
};

#endif