#include "Distribution.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "student.h"
#include "Student.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "canvasconnection.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <map>

using namespace std;

vector<QString> userid;
vector<double> assignmentid;
vector<double> assignmentscore;
map<double, vector<double> > everyAss;
vector<double> AssId;
vector<QString> submissionName;
vector<QString> downloadAdd;
vector<QString> fileAddress {"1.json","2.json","3.json","4.json" ,"5.json","6.json" ,"7.json","8.json" ,"9.json","0.json"  };
vector<QString> filenames { "20089.json" ,"20168.json","20285.json","19880.json","22347.json","19850.json","20383.json"};
vector<QString> student{"https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020089/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020168/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020285/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019880/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000022347/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000019850/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/analytics/users/10300000000020383/assignments?access_token=1030~y2v695pyuP5tf7SbJVuosakVODI0LyqrA5MXFWgJYscYmgOSL3VqXezUdOSyMYxL"
                       };
vector<QString> fileApi{"https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000000860/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046024/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061939/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046025/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000046026/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061017/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061018/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061019/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061020/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO",
                        "https://sit.instructure.com/api/v1/courses/10300000000000133/assignments/10300000000061022/submissions?access_token=1030~ITJlnLeBaoqbzneuPAfdNLG5e9jAZqVHMiZWxF3FbvTG31U6l5adkBJcqOf8lCIO"
                       };

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
        QCoreApplication a();
        canvasConnection A;
        A.doDownload();
        A.extract();
        A.showdata();
        A.everyAssScore();
            Student c;
            vector<double>temp;

            for(int i = 0; i<7;i++){
                temp.push_back(everyAss[assignmentid[3]][i]);
                cout<<temp[i]<<'\n';
            }

            c.Assignment_Marks=temp;
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
                   << "65~70"<< "70~75"<< "75~80"<< "80~85"<< "85~90"<< "90~95"<< "95~100" << ">=100" ;
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
            customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Distribution of assignment",QFont("Arial", 16, QFont::Bold)));

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
            QCPItemText *textLabel = new QCPItemText(customPlot);
            textLabel->position->setCoords(19.5, 4.2+0.1); // place position at center/top of axis rect
            textLabel->setText("Mean value: ");
            textLabel->setFont(QFont("Arial", 12)); // make font a bit larger
            textLabel->setColor(Qt::white);
            textLabel->setPen(QPen(Qt::NoPen)); // show black border around text

            QCPItemText *textLabel_1 = new QCPItemText(customPlot);
            textLabel_1->position->setCoords(21, 4.2+0.1);
            QString s = QString::number(c.Assignment_Mean());
            textLabel_1->setText(s);
            textLabel_1->setFont(QFont("Arial", 12)); // make font a bit larger
            textLabel_1->setColor(Qt::white);
            textLabel_1->setPen(QPen(Qt::NoPen)); // show black border around text

            QCPItemText *textLabel_2 = new QCPItemText(customPlot);
            textLabel_2->position->setCoords(19.6, 4+0.1); // place position at center/top of axis rect
            textLabel_2->setText("Median value: ");
            textLabel_2->setFont(QFont("Arial", 12)); // make font a bit larger
            textLabel_2->setColor(Qt::white);
            textLabel_2->setPen(QPen(Qt::NoPen)); // show black border around text

            QCPItemText *textLabel_3 = new QCPItemText(customPlot);
            textLabel_3->position->setCoords(21, 4+0.1);
            QString l = QString::number(c.Assignment_Median());
            textLabel_3->setText(l);
            textLabel_3->setFont(QFont("Arial", 12)); // make font a bit larger
            textLabel_3->setColor(Qt::white);
            textLabel_3->setPen(QPen(Qt::NoPen)); // show black border around text


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
