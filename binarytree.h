#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<QChar>
#include<QString>
#include<QPoint>
#include<QLine>

struct BinTreeNode
{
   QChar data;                 //数据
   BinTreeNode *left,*right;   //左孩子、右孩子
   QPoint point;               //结点的坐标

   BinTreeNode()               //默认构造函数
   {
       left=NULL;
       right=NULL;
       point=QPoint(0,0);
   }

   //构造函数
   BinTreeNode(QChar data,QPoint point=QPoint(0,0),BinTreeNode *left=NULL,BinTreeNode *right=NULL)
   {
       this->data=data;
       this->left=left;
       this->right=right;
       this->point=point;
   }

    //修改坐标的值
   void setpoint(QPoint p)
   {
         point=p;
   }
};


class BinaryTree
{
public:

    //构造函数、析构函数
    BinaryTree();
    BinaryTree(QString str,int i=0);
    BinaryTree(QString pre,QString in);         //重新构建函数
    ~BinaryTree();

    //前序、中序、后、层次遍历
    void preOrder();
    void inOrder();
    void postOrder();
    void LevelOrder();

    void setMyPoints();      //为坐标组设置应的坐标,以及得到相应的线段
    int size();              //返回树结点的个数
    int height()
    {
        return height(root);
    }
    void swapTree();         //交换结点
    bool Find(QChar ch);     //查找值为key的结点
    void clear();

    //获得前序、中序、后、层次遍历的字符串
    QString getPreStr();
    QString getInStr();
    QString getPostStr();
    QString getLevelStr();

    QPoint *getPoints();       //得到坐标
    QLine *getLines();         //得到线段

    BinTreeNode  *getRoot(); //获得根节点
    QString keyParent;      //关键值的父节点
    bool isright;           //用于判断是否能够成功建树
protected:
    BinTreeNode *root;      //树的根节点
    int Treesize;           //树的结点个数
    QPoint *Mypoints;       //树各个结点坐标的集合
    QLine *My_lines;        //线的条数

    QString preStr;         //前序遍历得到的字符串
    QString inStr;          //中序遍历得到的字符串
    QString postStr;        //后序遍历得到的字符串
    QString levelStr;       //层次遍历得到的字符串

    int height(BinTreeNode *Node);  //得到树的高度

    void CreateBinTree(QString &str,BinTreeNode *&Node,int &i);   //通过字符串，前序遍历建立树
    void destroy(BinTreeNode *Node);                       //删除
    void swapTree(BinTreeNode *Node);                      //交换
    bool Find(QChar ch,BinTreeNode *Node);                 //查找函数

    //前序、中序、后序遍历
    void preOrder(BinTreeNode *Node);
    void inOrder(BinTreeNode *Node);
    void postOrder(BinTreeNode *Node);

    //通过前序和中序建树
    BinTreeNode *creatBinaryTree(QString pre,QString in,int n);
};

#endif // BINARYTREE_H
