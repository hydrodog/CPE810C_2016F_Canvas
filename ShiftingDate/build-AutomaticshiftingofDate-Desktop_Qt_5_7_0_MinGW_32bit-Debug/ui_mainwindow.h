/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd;
    QAction *actionEdit;
    QAction *actionRemove;
    QAction *actionNew;
    QAction *actionOpen;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *listpage;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QWidget *detailpage;
    QGridLayout *gridLayout_3;
    QLabel *classeslabel;
    QLineEdit *themeEdit;
    QDateEdit *expirationdateEdit;
    QPlainTextEdit *assignmentEdit;
    QLineEdit *nameEdit;
    QLabel *assignmentlabel;
    QLabel *datelabel;
    QPushButton *Button1;
    QLabel *themelabel;
    QPushButton *Button3;
    QPushButton *Button4;
    QPushButton *Button2;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;
    QCalendarWidget *calendarWidget;
    QMenuBar *menuBar;
    QMenu *menuEntries;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(741, 557);
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(-10, -10, 411, 471));
        listpage = new QWidget();
        listpage->setObjectName(QStringLiteral("listpage"));
        gridLayout = new QGridLayout(listpage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget = new QListWidget(listpage);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(listpage);
        detailpage = new QWidget();
        detailpage->setObjectName(QStringLiteral("detailpage"));
        gridLayout_3 = new QGridLayout(detailpage);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        classeslabel = new QLabel(detailpage);
        classeslabel->setObjectName(QStringLiteral("classeslabel"));

        gridLayout_3->addWidget(classeslabel, 0, 1, 1, 1);

        themeEdit = new QLineEdit(detailpage);
        themeEdit->setObjectName(QStringLiteral("themeEdit"));

        gridLayout_3->addWidget(themeEdit, 1, 2, 1, 1);

        expirationdateEdit = new QDateEdit(detailpage);
        expirationdateEdit->setObjectName(QStringLiteral("expirationdateEdit"));

        gridLayout_3->addWidget(expirationdateEdit, 3, 2, 1, 1);

        assignmentEdit = new QPlainTextEdit(detailpage);
        assignmentEdit->setObjectName(QStringLiteral("assignmentEdit"));

        gridLayout_3->addWidget(assignmentEdit, 12, 2, 1, 1);

        nameEdit = new QLineEdit(detailpage);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout_3->addWidget(nameEdit, 0, 2, 1, 1);

        assignmentlabel = new QLabel(detailpage);
        assignmentlabel->setObjectName(QStringLiteral("assignmentlabel"));

        gridLayout_3->addWidget(assignmentlabel, 12, 0, 1, 2);

        datelabel = new QLabel(detailpage);
        datelabel->setObjectName(QStringLiteral("datelabel"));

        gridLayout_3->addWidget(datelabel, 3, 1, 1, 1);

        Button1 = new QPushButton(detailpage);
        Button1->setObjectName(QStringLiteral("Button1"));
        Button1->setMaximumSize(QSize(302, 16777215));

        gridLayout_3->addWidget(Button1, 8, 2, 1, 1);

        themelabel = new QLabel(detailpage);
        themelabel->setObjectName(QStringLiteral("themelabel"));

        gridLayout_3->addWidget(themelabel, 1, 1, 1, 1);

        Button3 = new QPushButton(detailpage);
        Button3->setObjectName(QStringLiteral("Button3"));

        gridLayout_3->addWidget(Button3, 10, 2, 1, 1);

        Button4 = new QPushButton(detailpage);
        Button4->setObjectName(QStringLiteral("Button4"));

        gridLayout_3->addWidget(Button4, 9, 2, 1, 1);

        Button2 = new QPushButton(detailpage);
        Button2->setObjectName(QStringLiteral("Button2"));
        Button2->setMaximumSize(QSize(302, 16777215));

        gridLayout_3->addWidget(Button2, 7, 2, 1, 1);

        stackedWidget->addWidget(detailpage);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(420, 10, 311, 221));
        buttonBox = new QDialogButtonBox(centralWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 450, 391, 31));
        buttonBox->setStandardButtons(QDialogButtonBox::Discard|QDialogButtonBox::Reset|QDialogButtonBox::Save);
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(430, 240, 296, 236));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 26));
        menuEntries = new QMenu(menuBar);
        menuEntries->setObjectName(QStringLiteral("menuEntries"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuEntries->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuEntries->addAction(actionAdd);
        menuEntries->addAction(actionEdit);
        menuEntries->addAction(actionRemove);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAdd->setText(QApplication::translate("MainWindow", "Add", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "Edit", 0));
        actionRemove->setText(QApplication::translate("MainWindow", "Remove", 0));
        actionNew->setText(QApplication::translate("MainWindow", "new", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "open", 0));
        classeslabel->setText(QApplication::translate("MainWindow", " Name", 0));
        assignmentlabel->setText(QApplication::translate("MainWindow", "Assignment", 0));
        datelabel->setText(QApplication::translate("MainWindow", " Date", 0));
        Button1->setText(QApplication::translate("MainWindow", "Add a week", 0));
        themelabel->setText(QApplication::translate("MainWindow", " Theme", 0));
        Button3->setText(QApplication::translate("MainWindow", "Back a week", 0));
        Button4->setText(QApplication::translate("MainWindow", "Back a day", 0));
        Button2->setText(QApplication::translate("MainWindow", "Add a day ", 0));
        menuEntries->setTitle(QApplication::translate("MainWindow", "Entries", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
