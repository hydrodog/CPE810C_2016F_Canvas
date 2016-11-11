/*Author:Jing Li,Yang Bai
  This class represents our user interface. It pulls in generated code from the *.ui file
 * to show the GUI as designed in Qt Creator/Designer.

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"createassignmentcontroller.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include<QHash>


namespace Ui {
class MainWindow;
}
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(createassignmentcontroller *controller,QWidget *parent = 0);
    ~MainWindow();
public slots:
    void createEntry();
    void deleteEntry();
    void editEntry();
    void saveEntry();
    void discardEntry();
    void resetEntry();
    void openFileSlot();
    void newFileSlot();
    void AddaWeek();
    void AddaDay();
private:
    Ui::MainWindow *ui;
    createassignmentcontroller *m_controller;
    QHash<QListWidgetItem*,createassignmententry*>m_entryMap;
    void setupConnections();


};

#endif // MAINWINDOW_H
