#ifndef INDICATEURCOMPONENT_H
#define INDICATEURCOMPONENT_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QtMath>
#include <QPainterPath>

class IndicateurComponent : public QWidget {
    Q_OBJECT

    public:
        IndicateurComponent(QWidget* parent, const QString& cheminImage, float echelleArg = 0.6f, float ratioPivotY = 1.5f, double xActuel = 0, double yActuel = 0);

        void setAngleCible(double a);
        void mettreAJourAnimation();
        void setPosition(double pixelsX, double pixelsY);

    protected:
        void paintEvent(QPaintEvent*) override;

    private:
        QPixmap pixmap;
        double angleActuel;
        double angleCible;
        float echelle;
        float pivotRatio;
        double xActuel, xCible;
        double yActuel, yCible;
        double vitesseLerp;
};

#endif