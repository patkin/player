#include "mainwindow.h"
#include "mainwindow.h"
#include <QStyleFactory>



#include <QApplication>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyle(QStyleFactory::create("Fusion"));
    qDebug() << QStyleFactory::keys().join(" ");
    w.show();




    return a.exec();
}
