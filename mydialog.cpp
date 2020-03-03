#include "mydialog.h"
#include "ui_mydialog.h"
#include<QAbstractButton>
#include<QDebug>

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
    preString.clear();
    inString.clear();
}


void MyDialog::on_buttonBox_clicked(QAbstractButton *)
{
    //前序字符串
    preString=ui->prelineEdit->displayText();
   // preString=QString("ABHFDECKG");

    //中序字符串
    inString=ui->levellineEdit->displayText();
  //  inString=QString("HBDFAEKCG");

    this->close();
    emit strTransfer(preString,inString);//发射信号

}

