#include "indicateurComponent.h"


IndicateurComponent::IndicateurComponent(QWidget* parent, const QString& cheminImage, float echelleArg, float ratioPivotY, double xActuel, double yActuel)
    : QWidget(parent)
    , angleActuel(0.0)
    , angleCible(0.0)
    , echelle(echelleArg)
    , pivotRatio(ratioPivotY)
    , xActuel(xActuel)
    , xCible(xActuel)
    , yActuel(yActuel)
    , yCible(yActuel)
    , vitesseLerp(0.01)
{
    pixmap = QPixmap(cheminImage);
    setAttribute(Qt::WA_TranslucentBackground);
}

void IndicateurComponent::setAngleCible(double a) { angleCible = a; }

void IndicateurComponent::mettreAJourAnimation() {

    // Animation de l'Angle
    if (qAbs(angleCible - angleActuel) > 0.05) {
        angleActuel += (angleCible - angleActuel) * vitesseLerp;
    }

    // Animation de la Position X
    if (qAbs(xCible - xActuel) > 0.1) {
        xActuel += (xCible - xActuel) * vitesseLerp;
    }

    // Animation de la Position Y
    if (qAbs(yCible - yActuel) > 0.1) {
        yActuel += (yCible - yActuel) * vitesseLerp;
    }

    update();
}

void IndicateurComponent::setPosition(double pixelsX, double pixelsY) {
    xCible = pixelsX;
    yCible = pixelsY;
}

void IndicateurComponent::paintEvent(QPaintEvent*) {
    if (pixmap.isNull()) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    const double baseSize = 400.0;
    double currentSize = qMin(width(), height());
    double ratioScaling = currentSize / baseSize;

    // On découpe un cercle autour du milieu pour pas que les component sortes
    float rayon = (qMin(width(), height()) / 2.0) * 0.9;
    QPainterPath path;
    path.addEllipse(QRectF((width() / 2.0) - rayon, (height() / 2.0) - rayon, rayon * 2, rayon * 2));
    painter.setClipPath(path);


    double xScale = xActuel * ratioScaling;
    double yScale = yActuel * ratioScaling;

    painter.translate((width() / 2.0) + xScale, (height() / 2.0) - yScale);
    painter.rotate(angleActuel);

    int w = width() * echelle;
    int h = height() * echelle;
    painter.drawPixmap(-w / 2, -(h / pivotRatio), w, h, pixmap);
}