#include <QApplication>
#include "gestionnaireScenes.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    GestionnaireScenes w;
    w.show();

    return a.exec();
}