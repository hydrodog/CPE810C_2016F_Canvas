#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "student.h"
#include <vector>
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
void MainWindow::setupgraph(QCustomPlot *customPlot){
        //int numberoffiles;
       // cout <<"Enter total number of  files\n";
       // cin >> numberoffiles;   // files include assignments,midterm (or) tests
        //cout<<"file numbers entered\n";
        vector<Student> student;
        ifstream filename("a1.txt");
        for(int k=1;k<=2;k++){
        int assignmenttype;
        if (filename.is_open()){
          filename>> assignmenttype;
          Student::Set_AssignmentType(assignmenttype);
          int i=1;
          while(!filename.eof()){
              Student s;
              int id;
              double grade=0;
              filename >> id;
              if(filename.eof())
                  break;
              s.Setstudent_id(id);
              filename >> grade;

              /* check for assignment type and then reading grades inthe same
                 order as in the txt file  */

              if(assignmenttype==1){
                  if(s.Get_numAssignments() == 0){
                      s.SetAssignment_Marks(grade);
                  }

              /* as data in 2 different files is not in same order
                  following check is done*/

                  else{
                      for(unsigned int j=0; j< student.size(); j++){
                          Student& s2 = student.at(j);
                          if(s2.Getstudent_id() == id){
                              s2.SetAssignment_Marks(grade);
                              break;
                          }
                      }
                  }
              }

              else if (assignmenttype == 2){
                  if(s.Get_numTests() == 0)
                      s.SetTest_Marks(grade);
                  else
                      for(unsigned int j=0; j< student.size(); j++){
                          Student& s2 = student.at(j);
                          if(s2.Getstudent_id() == id){
                              s2.SetAssignment_Marks(grade);
                              break;
                          }
                      }
              }
              if(k == 1)
                  student.push_back(s);
              i++;
          }
        }
        else
          cout<<"not open\n";
        filename.close();
        if(assignmenttype==1)
          Student::Set_numAssignments();
        else if(assignmenttype==2)
          Student::Set_numTests();
        filename.open("a2.txt");
        }
        cout<<student.size()<<"\n";

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
          QVector<double> x, y; // initialize with entries 0...9
          for(unsigned int a=0; a<student.size(); a++){
              Student S=student.at(a);
              x.push_back(S.Getstudent_id());       // ID NUMBER of 10 students
              y.push_back(S.allAssignments_avg()); //  Avg Scores
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
          customPlot->xAxis->setRange(990,1280);
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
