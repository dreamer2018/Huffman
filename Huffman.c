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
#define MAX 10000  //文件里的最多的字符个数
//定义二叉树结构体
typedef struct BinaryTree
{
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
/*
//实际需要编码的哈夫曼节点
typedef struct
{
    int ascii;
    int weight;
}HuffMan;
*/
//定义哈夫曼编码结构体
typedef struct
{
    int ascii;
    int weight;
    char ascii_code[8];  //ASCII码为127个，最多用7个字符就可以全部编码，故用长度为8的字符数组保存
}Code;

//初始化哈夫曼数的结点
void InitHuffTree(Code *W,HufNode *h,int n)
{
    int i;
    int m=2*n-1;
    for(i=0;i<n;i++)
    {
        h[i].Weight=W[i].weight;
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
        printf("%d\t%d\t%d\t%d\t%d\n",i,h[i].Weight,h[i].Parent,h[i].LChild,h[i].RChild);
    }
}
//通过建立的哈夫曼树，得到每个子节点的编码
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

//读取出文件内容
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
//将内容写入到文件中
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
//计算出每个ASCII字符出现的次数，并返回出现的ASCII字符个数
int CountNum(char *str,int *count)
{
    int i,c=0;
    for(i=0;str[i]!='\0';i++)
    {
        count[str[i]-1]++;
    }
    for(i=0;i<127;i++)
    {
        if(count[i]!=0)
        {
            c++;
        }
    }
    return c;
}
//将权值不为0的，及需要编码的内容保存到code里面
void CountNull(int *count,Code *code,int n)
{
    int i,j;
    for(i=0,j=-1;i<127 && j<=n ;i++)
    {
        if(count[i]!=0)
        {
            j++;
            code[j].ascii=i+1;
            code[j].weight=count[i];
        }
    }
    /*
    for(i=0;i<n;i++)
    {
        printf("%c %d\n",code[i].ascii,code[i].weight);
    }*/
}
//获取到每个ASCII的哈夫曼编码
void getCode(HufNode *h,Code *code,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        HuffmanCode(h,code[i].ascii_code,h[i],i);
    }
}
/*将压缩后的内容写入到文件中，文件分为三个部分：
 *  第一部分（文件第一行）：记录编码的个数
 *  第二部分
 *
 */
void WriteCode()
{

}
int main()
{
    //n为需要编码的字符个数，m为哈夫曼树的节点个数,满足：m=2*n-1的关系
    int i,n,m;
    //数组下标加一就代表对应得ASCII字符，数组内存储的是那个ASCII字符出现的次数
    int count[127];
    //定义一个字符数组，用于保存从文件中读取的字符个数
    char str[MAX];
    //将数组全部内容置为0
    bzero(count,sizeof(count));  //或者 memset(count,0,sizeof(count));
    //从文件中读取字符
    ReadFile(str);
    //记录文件中的ASCII种类数
    n=CountNum(str,count);
    //printf("%d\n",n);
    m=2*n-1;
    //创建结构体数组保存编码好的码值
    Code code[n];
    //将不为空的ASCII码值存入数组中
    CountNull(count,code,n);
    //创建一个哈夫曼树
    HufNode h[m];
    //初始化哈夫曼树
    InitHuffTree(code,h,n);
    //创建哈夫曼树
    CreateHuffTree(h,n);
    PrintHufTree(h,n);
    getCode(h,code,n);
    for(i=0;i<n;i++)
    {
        printf("%c: %s\t\t %d\n",code[i].ascii,code[i].ascii_code,code[i].weight);
    }
}
