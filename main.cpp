#include "mainwindow.h"
#include <QApplication>


/*! \brief Funkcja main programu
 *
 *  Funkcja main, w której zostały stworzone obiekty
 *  QApplication oraz MainWindow, w ktorym odbywa sie
 *  cala praca programu.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
