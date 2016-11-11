#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "student.h"
#include <iostream>
#include <fstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setupgraph(ui->customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupgraph(QCustomPlot *customPlot)
{
    const int NUM_STUDENTS = 10;
        int count=0;
        Student s[NUM_STUDENTS];
        //Assignment a[NUM_ASSIGNMENTS]; //TODO
        //for(int k=0; k< NUM_ASSIGNMENTS; k++) {
        ifstream filename("a1.txt");
        if(filename.is_open()){
            for(int k=1;k<=NUM_ASSIGNMENTS;k++){  //NUM_ASSIGNMENTS (for now took it as 2 )is a constant in student.h
                count=0;
                int assignmentType;
                filename>>assignmentType;
                Student::SetAssignmentType(assignmentType);

                //set the name of assignment/test
                //TODO:use name from download team
                if(Student::GetAssignment_type() == 1)
                    Student::Set_numAssignments();
                else if(Student::GetAssignment_type() == 2)
                    Student::Set_numTests();

                for(int i=0;i<NUM_STUDENTS;i++){
                    int id = 0;
                    double marks = 0.0;
                    filename >> id;
                    filename >> marks;
                    if (k==1){
                        //First assignment, no data in student objects yet
                        //Assign directly without any checks
                        s[i].Setstudent_id(id);
                        s[i].Set_Marks(k-1,marks);
                        s[i].allAssignments_avg();
                    }
                    else{
                        for(int j=0; j<NUM_STUDENTS; j++){
                            /*student id's for each assignment will not be in the same
                              order, so check before assigning*/
                            if(s[j].Getstudent_id() == id){
                                s[j].Set_Marks(k-1,marks);
                                s[j].allAssignments_avg();
                            }
                        }
                    }
                    count++;
                }
                filename.close();
                filename.open("a2.txt");
                if(filename.is_open()){

                }
                else {
                   cout<<"not open";
                }
            }

        }
        else
            cout<<"not open";

        //using scatter graph
        customPlot->legend->setVisible(true);
        customPlot->legend->setFont(QFont("Helvetica", 9));
        customPlot->legend->setRowSpacing(-3);
        QVector<QCPScatterStyle::ScatterShape> shapes;
        shapes << QCPScatterStyle::ssCross;
        QPen pen;

        for (int i=0; i<shapes.size(); ++i)
        {
          customPlot->addGraph();
          pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
          // generate data:
          QVector<double> x(10), y(10); // initialize with entries 0...9
          for(int a=0;a<10;a++){
              x[a]=s[a].Getstudent_id();       // ID NUMBER of 10 students
              y[a] = s[a].allAssignments_avg(); //  Avg Scores
          }
          //set axises and line
          customPlot->graph(0)->setData(x, y);
          customPlot->graph(0)->rescaleAxes(true);
          customPlot->graph(0)->setPen(pen);
          customPlot->graph(0)->setName("Avg Score of Assignmet 1");
          customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
          // add title layout element:
          customPlot->plotLayout()->insertRow(0);
          customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Avg Score of each sutdent", QFont("arial", 12, QFont::Bold)));
          //set labels
          customPlot->xAxis->setRange(1200,1280);
          customPlot->yAxis->setRange(0,200);

          // set scatter style and plot data
          if (shapes.at(i) != QCPScatterStyle::ssCustom)
          {
            customPlot->graph(0)->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
          }
          else
          {
            QPainterPath customScatterPath;
            for (int i=0; i<3; ++i)
              customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
            customPlot->graph(0)->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
          }
        }
}
