#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include<QString>
#include<QAbstractButton>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();



QString preString;
QString inString;

signals:
    void strTransfer(QString pre,QString in);

private slots:
void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
