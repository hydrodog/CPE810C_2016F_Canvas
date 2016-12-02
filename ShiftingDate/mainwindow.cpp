/*Author:Jing Li
 * realize the openFileSlot();newFileSlot();AddaWeek();AddaDay() functions.link this functions and buttons

 *Author:Yang Bai

  link functions and buttons, tell buttons what they should do when they are clicked.

*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "holiday.h"


MainWindow::MainWindow(createassignmentcontroller *controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(controller)
{ /*
     * We use Q_ASSERT to check the dependencies we received.
     */
    Q_ASSERT(controller!=nullptr);
    ui->setupUi(this);

    setupConnections();

    ui->actionAdd->setShortcut( QKeySequence::New );
    ui->actionEdit->setShortcut( tr( "Ctrl+E" ) );
    ui->actionRemove->setShortcut( QKeySequence::Delete );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createEntry()
{
    auto entry=m_controller->createEntry();
    if(entry){
        ui->listWidget->addItem(entry->name());
        auto listItem=ui->listWidget->item(ui->listWidget->count()-1);
        m_entryMap.insert(listItem,entry);

    }
}

void MainWindow::deleteEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          if(m_controller->deleteEntry(entry)){
              m_entryMap.remove(listItem);
              delete listItem;
          }
        }
    }

}

void MainWindow::editEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          ui->stackedWidget->setCurrentWidget(ui->detailpage);
          ui->menuEntries->setEnabled(false);
          resetEntry();
        }
    }
}

void MainWindow::saveEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          entry->setName(ui->nameEdit->text());
          entry->setTheme(ui->themeEdit->text());
          entry->setExpirationdate(ui->expirationdateEdit->date());
          entry->setAssignment(ui->assignmentEdit->toPlainText());
          ui->nameEdit->setText(entry->name());
          ui->themeEdit->setText(entry->theme());
          ui->expirationdateEdit->setDate(entry->expirationdate());
          ui->assignmentEdit->setPlainText(entry->assignment());
          listItem->setText(entry->name());
          discardEntry();
        }
    }
}

void MainWindow::discardEntry()
{
   ui->stackedWidget->setCurrentWidget(ui->listpage);
   ui->menuEntries->setEnabled(true);

}

void MainWindow::resetEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          ui->nameEdit->setText(entry->name());
          ui->themeEdit->setText(entry->theme());
          ui->expirationdateEdit->setDate(entry->expirationdate());
          ui->assignmentEdit->setPlainText(entry->assignment());
        }
    }

}

void MainWindow::newFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"current file modified";

    }
    else
    {

        ui->textEdit->clear();
       this->setWindowTitle("time.txt");
    }

}

void MainWindow::openFileSlot()
{
    /*
     * read a txt file.
     */

  QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());

  if(fileName.isEmpty())
  {
      QMessageBox::information(this,"error" ,"please select a text file");
      return;
  }
  QFile*file=new QFile;
  file->setFileName(fileName);
  bool ok=file->open(QIODevice::ReadOnly);
  if(ok)
  {
     QTextStream in(file);
     ui->textEdit->setText(in.readAll());//read all messages
     file->close();
     delete file;
  }
  else
  {
      QMessageBox::information(this,"error","file open error"+file->errorString());

      return;
  }
}
void MainWindow:: AddaWeek()
{/*
when button is pressed ,judge if it is holiday first.
  */
   QDate datetimes = ui->expirationdateEdit->date();
    datetimes =datetimes.addDays(7);
    Holiday x(datetimes);
    QString y=x.festival();
    if(y=="")
     ui->expirationdateEdit->setDate(datetimes);
    else
    {
        QMessageBox a;
        a.setText(y);
        a.exec();
        return;
    }

}
void MainWindow:: AddaDay()
{
   QDate datetimes = ui->expirationdateEdit->date();
        datetimes =datetimes.addDays(1);
        Holiday x(datetimes);
        QString y=x.festival();
        if(y=="")
         ui->expirationdateEdit->setDate(datetimes);
        else
        {
            QMessageBox a;
            a.setText(y);
            a.exec();
            return;
        }

}
void MainWindow:: MinusaWeek()
{
   QDate datetimes = ui->expirationdateEdit->date();
    datetimes =datetimes.addDays(-7);
    Holiday x(datetimes);
    QString y=x.festival();
    if(y=="")
     ui->expirationdateEdit->setDate(datetimes);
    else
    {
        QMessageBox a;
        a.setText(y);
        a.exec();
        return;
    }

}
void MainWindow:: MinusaDay()
{
   QDate datetimes = ui->expirationdateEdit->date();
        datetimes =datetimes.addDays(-1);
        Holiday x(datetimes);
        QString y=x.festival();
        if(y=="")
         ui->expirationdateEdit->setDate(datetimes);
        else
        {
            QMessageBox a;
            a.setText(y);
            a.exec();
            return;
        }

}

void MainWindow::setupConnections()
{/*
     * This connects various signals in the UI to slots we defined accordingly.
     */
   connect(ui->actionAdd,SIGNAL(triggered(bool)),
           this,SLOT(createEntry()));
   connect(ui->actionRemove,&QAction::triggered,
           this,&MainWindow::deleteEntry);
   connect(ui->actionEdit,&QAction::triggered,
           this,&MainWindow::editEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Save),&QPushButton::clicked,
           this,&MainWindow::saveEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Discard),&QPushButton::clicked,
           this,&MainWindow::discardEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Reset),&QPushButton::clicked,
           this,&MainWindow::resetEntry);
   connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFileSlot()));
   connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   connect(ui->Button1,&QPushButton::clicked,
           this,&MainWindow::AddaWeek);
   connect(ui->Button2,&QPushButton::clicked,
           this,&MainWindow::AddaDay);
   connect(ui->Button3,&QPushButton::clicked,
           this,&MainWindow::MinusaWeek);
   connect(ui->Button4,&QPushButton::clicked,
           this,&MainWindow::MinusaDay);

}
