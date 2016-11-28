#include "Distribution.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "student.h"
#include "Student.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
        vector <Student> S;
        Student c;
        ifstream filename("a1.txt");
        for(int k=1;k<=2;k++){
        int assignmenttype;
        if (filename.is_open()){
          filename>> assignmenttype;
          Student::Set_AssignmentType(assignmenttype);
          int i=1;
          while(!filename.eof()){
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
                      for(unsigned int j=0; j< S.size(); j++){
                          Student& c2 = S.at(j);
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
                      for(unsigned int j=0; j<S.size(); j++){
                          Student& c2 = S.at(j);
                          if(c2.Getstudent_id() == id){
                              c2.SetAssignment_Marks(grade);
                              break;
                          }
                      }
              }
              if(k == 1)
                  S.push_back(c);
              i++;
          }
        }
        else
          cout<<"not open\n";
        filename.close();
        /*if(assignmenttype==1)
          Student::Set_numAssignments();
        else if(assignmenttype==2)
          Student::Set_numTests();
        filename.open("a2.txt");
        }
        cout<<Student.size()<<"\n";*/
        }
        c.Assignment_Arrange_LtoH();
        c.setAssignment_Interval();

        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(90, 90, 90));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        customPlot->setBackground(QBrush(gradient));

        // create empty bar chart objects:
        QCPBars *Interval = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        Interval->setAntialiased(false); // gives more crisp, pixel aligned bar borders
        Interval->setStackingGap(1);
        // set names and colors:
        Interval->setName("Num of Students in the Interval");
        Interval->setPen(QPen(QColor(0, 168, 140).lighter(130)));
        Interval->setBrush(QColor(0, 168, 140));

        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21;
        labels << "0~5" << "5~10"<< "10~15"<< "15~20"<< "20~25"<< "25~30"<< "30~35"<< "35~40"<< "40~45"<< "45~50"<< "50~55"<< "55~60"<< "60~65"
               << "65~70"<< "70~75"<< "75~80"<< "80~85"<< "85~90"<< "90~95"<< "95~100" << ">=100";
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        customPlot->xAxis->setLabel("Score Intervals");
        customPlot->xAxis->setTicker(textTicker);
        customPlot->xAxis->setTickLabelRotation(60);
        customPlot->xAxis->setSubTicks(false);
        customPlot->xAxis->setTickLength(0, 4);
        customPlot->xAxis->setRange(0.5, 22);
        customPlot->xAxis->setBasePen(QPen(Qt::white));
        customPlot->xAxis->setTickPen(QPen(Qt::white));
        customPlot->xAxis->grid()->setVisible(true);
        customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        customPlot->xAxis->setTickLabelColor(Qt::white);
        customPlot->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        customPlot->yAxis->setRange(0, 5);
        customPlot->yAxis->setPadding(5); // a bit more space to the left border
        customPlot->yAxis->setLabel("Num of Student");
        customPlot->yAxis->setBasePen(QPen(Qt::white));
        customPlot->yAxis->setTickPen(QPen(Qt::white));
        customPlot->yAxis->setSubTickPen(QPen(Qt::white));
        customPlot->yAxis->grid()->setSubGridVisible(true);
        customPlot->yAxis->setTickLabelColor(Qt::white);
        customPlot->yAxis->setLabelColor(Qt::white);
        customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // add title layout element:
        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Distribution of Homework" , QFont("Arial", 16, QFont::Bold)));

        // Add data:
        QVector<double> IntervalData;
        for(int i=0;i<21;i++){
            IntervalData.push_back(c.getAssignment_Interval(i));
        }
        Interval->setData(ticks, IntervalData);

        //place value above the bar
        // add the text label at the top:
        for(int i=0;i<21;i++){
        QCPItemText *textLabel = new QCPItemText(customPlot);
        textLabel->position->setCoords(i+1, c.getAssignment_Interval(i)+0.1); // place position at center/top of axis rect
        QString s = QString::number(c.getAssignment_Interval(i));
        textLabel->setText(s);
        textLabel->setFont(QFont("Arial", 12)); // make font a bit larger
        textLabel->setColor(Qt::white);
        textLabel->setPen(QPen(Qt::NoPen)); // show black border around text
        }

        // setup legend:
        customPlot->legend->setVisible(true);
        customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
        customPlot->legend->setBrush(QColor(255, 255, 255, 100));
        customPlot->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        customPlot->legend->setFont(legendFont);
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
