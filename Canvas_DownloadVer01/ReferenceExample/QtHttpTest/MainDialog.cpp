#include "MainDialog.h"
#include "ui_MainDialog.h"
#include "HttpFun.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    connect(ui->requestBtn,SIGNAL(clicked()),this,SLOT(slot_requestBtnClicked()));//请求按钮点击信号
}

MainDialog::~MainDialog()
{
    delete ui;
}

//请求按钮点击
void MainDialog::slot_requestBtnClicked()
{
    HttpFun* pHttpFun = new HttpFun();
    QString strUrl = ui->addressEdit->text().trimmed();
    connect(pHttpFun,SIGNAL(signal_requestFinished(bool,const QString&)), //http请求结束信号
            this,SLOT(slot_requestFinished(bool,const QString&)));
    pHttpFun->sendRequest(strUrl);
}

//请求结束
void MainDialog::slot_requestFinished(bool bSuccess, const QString &strResult)
{
    if(bSuccess)
    {
        ui->resultEdit->setPlainText(strResult); //纯文本显示
    }
    else
    {
        ui->resultEdit->setPlainText(tr("请求失败！"));
    }

}
