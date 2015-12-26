/*************************************************************************
	> File Name: HuffmanTree.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Declared: Signed on behalf of not only belongs , but also represent a responsibility!
	> Created Time: 2015年11月11日 星期三 19时11分43秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define N 4
#ifdef N
#define H 2*N-1
#endif

//定义数据类型
#define DataType int

//定义二叉树结构体
typedef struct BinaryTree
{
    DataType data;
    struct BinaryTree *LChild;
    struct BinaryTree *RChild;
}BiNode,* Bitree;
//定义哈夫曼树的结构体
typedef struct
{
    int Weight;
    int Parent;
    int LChild;
    int RChild;
}HufNode;

//初始化哈夫曼数的结点
void InitHuffTree(int *W,HufNode *h)
{
    int i;
    for(i=0;i<N;i++)
    {
        h[i].Weight=W[i];
        h[i].Parent=0;
        h[i].LChild=0;
        h[i].RChild=0;
    }
    for(;i<H;i++)
    {
        h[i].Weight=0;
        h[i].Parent=0;
        h[i].LChild=0;
        h[i].RChild=0;   
    }
}
//找出权值最小的两个
void FindMin(int n,HufNode *h,int *n1,int *n2)
{
    int i,j,k=0;
    HufNode h1,h2;
    for(i=1;i<n;i++)
    {
        if(h[i].Parent==0)
        {
            if(h[i].Weight==h[i-1].Weight)
            {
                k++;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(h[i].Parent==0)
        {
            h1=h2=h[i];
            *n1=*n2=i;
            break;
        }
    }
    j=i;
    for(i=j;i<n;i++)
    {
        if(h[i].Parent==0 && h[i].Weight< h1.Weight)
        {
            h1=h[i];
            *n1=i;
        }
        //这里使用大于等于的目的是防止所有的元素都相等时，n1和n2的值相等
        if(h[i].Parent==0 && h[i].Weight>=h2.Weight)
        {
            h2=h[i];
            *n2=i;
        }
    }
    //最小的元素已找到，再次找到次小的元素
    for(i=j;i<n;i++)
    {
        if(h[i].Parent==0 && h[i].Weight<h2.Weight && *n1!=i)
        {
            h2=h[i];
            *n2=i;
        }
    }
}
//创建哈夫曼数
void CreateHuffTree(HufNode *h)
{
    int i;
    int  n1,n2;
    for(i=N;i<H;i++)
    {
        FindMin(i,h,&n1,&n2);
        h[i].Weight=h[n1].Weight+h[n2].Weight;
        h[i].LChild=n1;
        h[i].RChild=n2;
        h[n1].Parent=h[n2].Parent=i;
    }
}
//打印出哈夫曼树
void PrintHufTree(HufNode *h)
{
    int i;
    for(i=0;i<H;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",i+1,h[i].Weight,h[i].Parent,h[i].LChild,h[i].RChild);
    }
}
void HuffmanCode(HufNode *h,char *c,HufNode a,int n)
{
    int i,j,k,m;
    char temp;
    HufNode b=a;
    k=n;

    //获取哈弗曼编码
    for(i=0;;i++)
    {
        if(b.Parent==0)
        {
            c[i]='\0';
            break;
        }
        if(k==h[b.Parent].LChild)
        {
            c[i]='0';
        }
        else
        {
            c[i]='1';
        }
        k=b.Parent;
        b=h[b.Parent];
    }

    //将c字符串逆置
    for(j=i-1,m=0;j>m;j--,m++)
    {
        temp=c[j];
        c[j]=c[m];
        c[m]=temp;
    }
}
int main()
{
    HufNode h[H];
    char ch[N];
    int w[N]={1,1,6,9};
    char sign[N]={'A','B','C','D'};
    InitHuffTree(w,h);
    CreateHuffTree(h);
    PrintHufTree(h);
    int i;
    for(i=0;i<N;i++)
    {
        memset(ch,'\0',sizeof(ch));
        HuffmanCode(h,ch,h[i],i);
        printf("%c:%s\n",sign[i],ch);
    }
}
