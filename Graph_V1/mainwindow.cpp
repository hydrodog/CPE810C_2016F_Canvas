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
        int numberoffiles;
        cout <<"enter number of assignment files\n";
        cin >> numberoffiles;
        vector<Student> student;
        // for(int i=1; i<= numberoffiles; i++){
        ifstream filename("a1.txt");
        for(int k=1;k<=numberoffiles;k++){
          int assignmenttype;
          if (filename.is_open()){
              filename>> assignmenttype;
              Student::Set_AssignmentType(assignmenttype);
              int i=1;
              while( i<=10){
                  Student s;
                  int id;
                  double grade=0;
                  filename >> id;
                  s.Setstudent_id(id);
                  filename >> grade;
                  if(assignmenttype==1){
                      if(s.Get_numAssignments() == 0){
                          s.SetAssignment_Marks(grade);
                      }
                      else{
                          for(unsigned int j=0; j< student.size(); j++){
                              Student& s2 = student.at(j);
                              if(s2.Getstudent_id() == id){
                                  s2.SetAssignment_Marks(grade);
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
          std::cout<<"opening a2.txt"<<endl;
          filename.open("a2.txt");
        }

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
          for(unsigned int a=0; a<student.size(); a++){
              Student S=student.at(a);
              x[a] =S.Getstudent_id();       // ID NUMBER of 10 students
              y[a] =S.allAssignments_avg(); //  Avg Scores
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
