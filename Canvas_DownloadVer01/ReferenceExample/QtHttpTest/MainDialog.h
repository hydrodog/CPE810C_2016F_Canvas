#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

//主窗口
class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
private slots:
    void slot_requestBtnClicked();//请求按钮点击
    void slot_requestFinished(bool bSuccess, const QString& strResult); //http请求结束
private:
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
