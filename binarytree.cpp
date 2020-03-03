#include "binarytree.h"
#include<QDebug>
#include<QStack>
#include<QQueue>
//默认构造函数
BinaryTree::BinaryTree()
{
    root=nullptr;
    Treesize=0;
    Mypoints=nullptr;
    isright=true;
}

//构造函数
BinaryTree::BinaryTree(QString str,int i)
{

    if(i==0)     //前序构造
    {

        Treesize=0;
        this->CreateBinTree(str,root,i);
        if(str.size()!=i)//没有用到所有节点说明树生成错误
        {
            isright=false;
            return;
        }else
        {
            isright=true;
        }


    }
    else            //层次构造
    {
        int j=0;
        Treesize=0;
        QQueue<BinTreeNode *>Q;
        BinTreeNode *p=nullptr;
        if(str[j]=='#')   //先创建根节点
        {
            Treesize=0;
            return;
        }
        root=new BinTreeNode(str[j]);
        Treesize++;
        Q.enqueue(root);
        j++;

        while(j<(str.size()-1))
        {
            if(Q.isEmpty())
                break;
             else
                p=Q.dequeue();

            if(str[j]!='#')   //如果字符不为‘#’，创建左结点
            {
                p->left=new BinTreeNode(str[j]);
                Treesize++;
                Q.enqueue(p->left);
            }

             j++;

            if(str[j]!='#')   //如果字符不为‘#’，创建右结点
            {
                p->right=new BinTreeNode(str[j]);
                Treesize++;
                Q.enqueue(p->right);

            }

             j++;
        }

        if(str.size()!=j)//没有用到所有节点说明树生成错误
        {
            isright=false;
            return;
        }
        else
        {
            isright=true;
        }

    }

    //进行遍历
    this->setMyPoints();
    this->preOrder();
    this->inOrder();
    this->postOrder();
    this->LevelOrder();
}

//前序和中序构造
BinaryTree::BinaryTree(QString pre, QString in)
{

    Treesize=pre.size();
    preStr=pre;
    inStr=in;
    root=this->creatBinaryTree(pre,in,Treesize);
    this->postOrder();
    this->LevelOrder();
    this->setMyPoints();
}

//析构函数
BinaryTree::~BinaryTree()
{
   this->clear();
}

 //前序、中序、后序遍历
void BinaryTree::preOrder()
{
    this->preOrder(root);
}

void BinaryTree::inOrder()
{
    this->inOrder(root);
}

void BinaryTree::postOrder()
{
    this->postOrder(root);
}


void BinaryTree::LevelOrder()
{
    QQueue<BinTreeNode *>Q;         //调用队列
    BinTreeNode *p=root;
    Q.enqueue(root);
    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        levelStr.append(p->data);
        if(p->left!=nullptr)
            Q.enqueue(p->left);
        if(p->right!=nullptr)
            Q.enqueue(p->right);
    }
}

//为坐标组设置应的坐标,以及得到相应的线段
void BinaryTree::setMyPoints()
{
      //设置父节点和子节点间横坐标相差的距离

    int i=0;
//    int H=height();
    Mypoints=new QPoint[Treesize];  //动态分配空间
    My_lines=new QLine[Treesize-1];

    QQueue<BinTreeNode *>Q;         //调用队列
    BinTreeNode *p=root;
    root->setpoint(QPoint(500,75));  //为根节点设置坐标
    Q.enqueue(root);
    Mypoints[i]=root->point;

    //通过层次遍历，完成各个坐标的匹配
    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        if(p->left!=nullptr)
        {
            i++;
            int h=height(p);
            p->left->setpoint(p->point-QPoint(45*h,-100));
            Mypoints[i]=p->left->point;
            My_lines[i-1].setP1(p->point+QPoint(0,25));
            My_lines[i-1].setP2(p->left->point-QPoint(0,25));
            Q.enqueue(p->left);
        }

        if(p->right!=nullptr)
        {
            i++;
            int h=height(p);
            p->right->setpoint(p->point+QPoint(45*h,100));
            Mypoints[i]=p->right->point;
            My_lines[i-1].setP1(p->point+QPoint(0,25));
            My_lines[i-1].setP2(p->right->point-QPoint(0,25));
            Q.enqueue(p->right);
            h--;
        }

    }

}

//返回节点个数
int BinaryTree::size()
{
    return Treesize;
}

//交换结点
void BinaryTree::swapTree()
{
    delete[]  Mypoints;
    delete[]  My_lines;
    preStr.clear();
    inStr.clear();
    postStr.clear();
    levelStr.clear();
    keyParent.clear();

    this->swapTree(root);
    this->setMyPoints();

    this->preOrder();
    this->inOrder();
    this->postOrder();
    this->LevelOrder();

}

//查找函数
bool BinaryTree::Find(QChar ch)
{
   if(this->Find(ch,root))
   {
       return true;
   }
   return false;
}

void BinaryTree::clear()
{
    this->destroy(root);
    Treesize=0;
    delete[]  Mypoints;
    delete[]  My_lines;
    preStr.clear();
    inStr.clear();
    postStr.clear();
    levelStr.clear();
    keyParent.clear();
}

 //获得前序、中序、后、层次遍历的字符串
QString BinaryTree::getPreStr()
{
    return preStr;
}

QString BinaryTree::getInStr()
{
    return inStr;
}

QString BinaryTree::getPostStr()
{
    return postStr;
}

QString BinaryTree::getLevelStr()
{
    return levelStr;
}

QPoint *BinaryTree::getPoints()
{
    return Mypoints;
}

QLine *BinaryTree::getLines()
{
    return My_lines;
}

BinTreeNode *BinaryTree::getRoot()
{
    return root;
}

int BinaryTree::height(BinTreeNode *Node)
{
      if(Node==nullptr)
          return 0;
      else
      {
          int i=height(Node->left);
          int j=height(Node->right);
          return (i<j)? j+1:i+1;
      }
}


//前序创造节点
//i代表第几个字母
void BinaryTree::CreateBinTree(QString &str, BinTreeNode *&Node,int &i)
{
  //  qDebug()<<str;
    if(str[i]!='#')//说明不是空节点
    {
        Node=new BinTreeNode(str[i]);
        Treesize++;
        i++;
        this->CreateBinTree(str,Node->left,i);
        this->CreateBinTree(str,Node->right,i);
    }
    else
    {
        i++;
        Node=nullptr;
    }

}

//删除函数
void BinaryTree::destroy(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        this->destroy(Node->left);
        this->destroy(Node->right);
        delete Node;
    }

}

void BinaryTree::swapTree(BinTreeNode *Node)
{
    if(Node==nullptr)
        return;
    BinTreeNode *p=Node->left;
    Node->left=Node->right;
    Node->right=p;
    this->swapTree(Node->left);
    this->swapTree(Node->right);
}

//查找
bool BinaryTree::Find(QChar ch, BinTreeNode *Node)
{
    if(Node==nullptr)
        return false;
    if(Node->data==ch)
        return true;
    if(Find(ch,Node->left)||Find(ch,Node->right))
    {
        keyParent.push_front(Node->data);
        return true;
    }
    return false;
}

//前序、中序、后序遍历
void BinaryTree::preOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        preStr.append(Node->data);
        preOrder(Node->left);
        preOrder(Node->right);
    }
}

void BinaryTree::inOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        inOrder(Node->left);
        qDebug()<<Node->data;
        inStr.append(Node->data);
        inOrder(Node->right);
    }
    qDebug()<<inStr;
}

void BinaryTree::postOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        postOrder(Node->left);
        postOrder(Node->right);
        qDebug()<<Node->data;
        postStr.append(Node->data);
    }
}

//前序和中序建树
//pre代表前序字符串
//in代表中序字符串
//n代表pre可以到的位置
BinTreeNode *BinaryTree::creatBinaryTree(QString pre, QString in, int n)
{
    qDebug()<<pre;
    qDebug()<<in;
    if(n==0) return nullptr;
    int k=0;
    while(pre[0]!=in[k]&&k<in.length())k++;
    if(k>=in.length()) return nullptr;  //理论上应该需要抛出异常的，
    BinTreeNode *t=new BinTreeNode(pre[0]);
    t->left=creatBinaryTree(pre.mid(1),in,k);
    t->right=creatBinaryTree(pre.mid(k+1),in.mid(k+1),n-k-1);
    return t;

}


