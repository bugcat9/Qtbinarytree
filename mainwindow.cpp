#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<Qdir>
#include<QPainter>
#include<QPen>
#include<QStack>
#include<QPoint>
#include<QMessageBox>

//构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   My_Dialog=new MyDialog(this);
   My_Tree=nullptr;

   //接受从子窗口发射过来的信号
   connect(My_Dialog,&MyDialog::strTransfer,
           [=](QString pre,QString in)
   {
       if(My_Tree!=nullptr)
           My_Tree->clear();
       qDebug()<<pre;
       qDebug()<<in;
       if(pre.size()!=in.size())
       {
            QMessageBox::information(nullptr, "前序、中序构造", "前序、中序构造输入错误", QMessageBox::Yes);
       }
       else
       {
           My_Tree=new BinaryTree(pre,in);
           update();
       }

   }
           );

}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
    delete My_Tree;
    delete My_Dialog;
}

//重构的绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(5);
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    //只有当树部位空的时候才画图
    if(My_Tree!=nullptr&&My_Tree->isright==true)
    {

        for(int i=0;i<My_Tree->size();i++)
        {
            QPoint p=My_Tree->getPoints()[i];//得到各个节点的坐标
            painter.drawEllipse(p,25,25);//圆的半径为25
            painter.drawText(p,QString(My_Tree->getLevelStr()[i]));
            if(i!=0)
               painter.drawLine(My_Tree->getLines()[i-1]);//得到线段的坐标
        }

        //将前序、中序、后序、层次遍历依次输出
       pen.setColor(Qt::darkCyan);
       painter.setPen(pen);
       painter.drawText(10,70,"前序：");
       painter.drawText(10,100,My_Tree->getPreStr());
       qDebug()<<My_Tree->getPreStr();
       painter.drawText(10,150,"中序：");
       painter.drawText(10,200,My_Tree->getInStr());
       qDebug()<<My_Tree->getInStr();
       painter.drawText(10,250,"后序：");
       painter.drawText(10,300,My_Tree->getPostStr());
       qDebug()<<My_Tree->getPostStr();
       painter.drawText(10,350,"层次：");
       painter.drawText(10,400,My_Tree->getLevelStr());
       qDebug()<<My_Tree->getLevelStr();
       //得到查找函数的各个父亲节点
       if(!My_Tree->keyParent.isEmpty())
       {
           painter.drawText(10,450,"父节点:");
           painter.drawText(10,500,My_Tree->keyParent);
       }
    }


}

//前序构造
void MainWindow::on_actionCreat_triggered()
{
    //获得输入的字符串
    bool isOk;
    QString text=QInputDialog::getText(this,QString("构造树"),QString("输入字符串"),
                                       QLineEdit::Normal, QDir::home().dirName(), &isOk);


    if(isOk&&!text.isEmpty())
    {
        //ABC##DE#G##F###
        qDebug()<<text;
        int i=text.count('#');

        //错误判断
        if((2*i-text.size())!=1)
        {
            QMessageBox::information(nullptr, "前序构造", "前序构造输入错误", QMessageBox::Yes);
            return;
        }

        if(My_Tree!=nullptr)
            My_Tree->clear();
         My_Tree=new BinaryTree(text);
         //如果生成树错误,则不刷新屏幕
         if(My_Tree->isright)
             update();
         else
         {
             QMessageBox::information(nullptr, "前序构造", "前序构造输入错误", QMessageBox::Yes);
         }
    }




    /*text.clear();
    text=QString("ABC##DE#G##F###");
    */
}

//层次构造
void MainWindow::on_actionLevel_triggered()
{
    bool isOk;
    QString text=QInputDialog::getText(this,QString("构造树"),QString("输入字符串"),
                                       QLineEdit::Normal, QDir::home().dirName(), &isOk);
    if(isOk&&!text.isEmpty())
    {
        //AB#CD##EF#G####
        qDebug()<<text;

        int i=text.count('#');

        //错误判断
        if((2*i-text.size())!=1)
        {
            QMessageBox::information(nullptr, "层次构造", "层次构造输入错误", QMessageBox::Yes);
            return;
        }

        if(My_Tree!=nullptr)
            My_Tree->clear();
         My_Tree=new BinaryTree(text,1);

         //如果生成树错误,则不刷新屏幕
         if(My_Tree->isright)
             update();
         else
         {
             QMessageBox::information(nullptr, "层次构造", "层次构造输入错误", QMessageBox::Yes);
         }
    }
    /*
     * text.clear();
    text=QString("AB#CD##EF#G####");
    */

}

void MainWindow::on_actionSwap_triggered()
{
    My_Tree->swapTree();
    update();
}

//查找函数
void MainWindow::on_actionFind_triggered()
{
    My_Tree->keyParent.clear();
    bool isOk;
    QString text=QInputDialog::getText(this,QString("查找关键字"),QString("输入关键字"),
                                       QLineEdit::Normal, QDir::home().dirName(), &isOk);
    if(isOk&&!text.isEmpty())
    {

        QChar ch=text[0];
        if(text.size()==1&&My_Tree->Find(ch))
        {
            update();
        }
        else
        {
                QMessageBox::information(this,QString("失败"),QString("查找失败"));
        }

    }

}


void MainWindow::on_actionReCreat_triggered()
{
    My_Dialog->show();
}
