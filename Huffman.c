/**************************************************************************************************
	> File Name: Huffman.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月26日 星期六 12时10分47秒
 ************************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>

//定义数据类型
#define DataType int
#define MAX 10000
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
void InitHuffTree(int *W,HufNode *h,int n)
{
    int i;
    int m=2*n-1;
    for(i=0;i<n;i++)
    {
        h[i].Weight=W[i];
        h[i].Parent=0;
        h[i].LChild=0;
        h[i].RChild=0;
    }
    for(;i<m;i++)
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
void CreateHuffTree(HufNode *h,int n)
{
    int i;
    int m=2*n-1;
    int  n1,n2;
    for(i=n;i<m;i++)
    {
        FindMin(i,h,&n1,&n2);
        h[i].Weight=h[n1].Weight+h[n2].Weight;
        h[i].LChild=n1;
        h[i].RChild=n2;
        h[n1].Parent=h[n2].Parent=i;
    }
}
//打印出哈夫曼树
void PrintHufTree(HufNode *h,int n)
{
    int i;
    for(i=0;i<(2*n-1);i++)
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
void ReadFile(char *str)
{
    int i;
    FILE *fp;
    char ch;
    fp=fopen("1.txt","r");
    if(fp==NULL)
    {
        printf("Not Found 1.txt");
    }
    for(i=0;i<20;i++)
    {
        ch=getc(fp);
        if(ch==EOF)
        {
            str[i]='\0';
            break;
        }
        str[i]=ch;
    }
    fclose(fp);
}
void WriteFile(char *str)
{
    int i;
    FILE *fp;
    fp=fopen("1.txt.tmp","w");
    for(i=0;str[i]!='\0';i++)
    {
        fputc(str[i],fp);
    }
    fclose(fp);
}
int CountNum(char *str,int *cout)
{
    int i,c=0;
    for(i=0;str[i]!='\0';i++)
    {
        cout[str[i]-1]++;
    }
    for(i=0;i<127;i++)
    {
        if(cout[i]!=0)
        {
            c++;
        }
    }
    return c;
}
int main()
{
    int n,m;
    int count[127];
    char ch[n];
    char 
    char str[MAX];
    int w[]={1,1,6,9};
    ReadFile(str);
    n=CountNum(str,count);
    m=2*n-1;
    HufNode h[m];
    InitHuffTree(w,h,n);
    CreateHuffTree(h,n);   
    int i;
    for(i=0;i<n;i++)
    {
        memset(ch,'\0',sizeof(ch));
        HuffmanCode(h,ch,h[i],i);
        printf("%c,%s\n",ch);
    }
}
