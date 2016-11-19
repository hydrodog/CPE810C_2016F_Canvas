#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "student.h"
#include "category.h"
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
       // int numberoffiles;
       // cout <<"Enter total number of  files\n";
       // cin >> numberoffiles;   // files include assignments,midterm (or) tests
        //cout<<"file numbers entered\n";
        vector <category> Category;
        ifstream filename("a1.txt");
        for(int k=1;k<=2;k++){
        int assignmenttype;
        if (filename.is_open()){
          filename>> assignmenttype;
          category::Set_AssignmentType(assignmenttype);
          int i=1;
          while(!filename.eof()){
              category c;
              int id;
              double grade=0;
              filename >> id;
              if(filename.eof())
                  break;
              c.Setstudent_id(id);
              filename >> grade;

              /* check for assignment type and then reading grades inthe same
                 order as in the txt file  */

              if(assignmenttype==1){
                  if(c.Get_numAssignments() == 0){
                      c.SetAssignment_Marks(grade);
                  }

              /* as data in 2 different files is not in same order
                  following check is done*/

                  else{
                      for(unsigned int j=0; j< Category.size(); j++){
                          category& c2 = Category.at(j);
                          if(c2.Getstudent_id() == id){
                              c2.SetAssignment_Marks(grade);
                              break;
                          }
                      }
                  }
              }

              else if (assignmenttype == 2){
                  if(c.Get_numTests() == 0)
                      c.SetTest_Marks(grade);
                  else
                      for(unsigned int j=0; j<Category.size(); j++){
                          category& c2 = Category.at(j);
                          if(c2.Getstudent_id() == id){
                              c2.SetAssignment_Marks(grade);
                              break;
                          }
                      }
              }
              if(k == 1)
                  Category.push_back(c);
              i++;
          }
        }
        else
          cout<<"not open\n";
        filename.close();
        if(assignmenttype==1)
          category::Set_numAssignments();
        else if(assignmenttype==2)
          category::Set_numTests();
        filename.open("a2.txt");
        }
        cout<<Category.size()<<"\n";

        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(90, 90, 90));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        customPlot->setBackground(QBrush(gradient));

        // create empty bar chart objects:
        QCPBars *Mean = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        Mean->setAntialiased(false); // gives more crisp, pixel aligned bar borders
        Mean->setStackingGap(1);
        // set names and colors:
        Mean->setName("Mean");
        Mean->setPen(QPen(QColor(0, 168, 140).lighter(130)));
        Mean->setBrush(QColor(0, 168, 140));

        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2;
        labels << "Assignment 1" << "Assignment 2";
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        customPlot->xAxis->setTicker(textTicker);
        customPlot->xAxis->setTickLabelRotation(60);
        customPlot->xAxis->setSubTicks(false);
        customPlot->xAxis->setTickLength(0, 4);
        customPlot->xAxis->setRange(0, 4);
        customPlot->xAxis->setBasePen(QPen(Qt::white));
        customPlot->xAxis->setTickPen(QPen(Qt::white));
        customPlot->xAxis->grid()->setVisible(true);
        customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        customPlot->xAxis->setTickLabelColor(Qt::white);
        customPlot->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        customPlot->yAxis->setRange(0, 100);
        customPlot->yAxis->setPadding(5); // a bit more space to the left border
        customPlot->yAxis->setLabel("Score");
        customPlot->yAxis->setBasePen(QPen(Qt::white));
        customPlot->yAxis->setTickPen(QPen(Qt::white));
        customPlot->yAxis->setSubTickPen(QPen(Qt::white));
        customPlot->yAxis->grid()->setSubGridVisible(true);
        customPlot->yAxis->setTickLabelColor(Qt::white);
        customPlot->yAxis->setLabelColor(Qt::white);
        customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:
        QVector<double> MeanData;
        for(unsigned int a=0; a<Category.size(); a++){
            category C=Category.at(a);
        MeanData.push_back(C.Assignment_Mean());}
        Mean->setData(ticks, MeanData);

        // setup legend:
        customPlot->legend->setVisible(true);
        customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        customPlot->legend->setBrush(QColor(255, 255, 255, 100));
        customPlot->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        customPlot->legend->setFont(legendFont);
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
