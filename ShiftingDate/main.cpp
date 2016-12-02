/*Author:Jing Li,Yang Bai

  show mainwindow

*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createassignment createAssignment;
    createassignmentcontroller controller(&createAssignment);
    MainWindow w(&controller);
    w.show();

    return a.exec();
}
