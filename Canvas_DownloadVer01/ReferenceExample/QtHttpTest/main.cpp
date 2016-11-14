#include "MainDialog.h"
#include <QApplication>
#include "httpfun.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.show();

    return a.exec();
}
