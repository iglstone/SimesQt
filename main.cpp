#include "mainwindow.h"
#include <QApplication>
#include "consiemensplcs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    ConSiemensPlcs p;
    p.show();

    return a.exec();
}
