#include "simulationCockpit.h"

SimulationCockpit::SimulationCockpit(QWidget* parent) : QWidget(parent) {
    this->setStyleSheet("background-color: black;");

    // Scene 3d ??? :)
    view3d = new QQuickWidget(this);
    view3d->setSource(QUrl::fromLocalFile("cockpit3D.qml"));
    view3d->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Important pour voir les instruments 2D par-dessus
    view3d->setAttribute(Qt::WA_AlwaysStackOnTop, false);
    view3d->lower();
    view3d->show();
}

void SimulationCockpit::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    // scène 3D
    if (view3d) {
        view3d->setGeometry(0, 0, this->width(), this->height());
    }
}