/**************************************************************************************************
	> File Name: Huffman2.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月27日 星期日 20时20分02秒
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

//定义哈夫曼编码结构体
typedef struct
{
    char ascii;
    int weight;
    char ascii_code[257];
}Code;

//初始化哈夫曼数的结点
void initHuffTree(Code *W,HufNode *h,int n)
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
void findMin(int n,HufNode *h,int *n1,int *n2)
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
void createHuffTree(HufNode *h,int n)
{
    int i;
    int m=2*n-1;
    int  n1,n2;
    for(i=n;i<m;i++)
    {
        findMin(i,h,&n1,&n2);
        h[i].Weight=h[n1].Weight+h[n2].Weight;
        h[i].LChild=n1;
        h[i].RChild=n2;
        h[n1].Parent=h[n2].Parent=i;
    }
}

//打印出哈夫曼树
void printHufTree(HufNode *h,int n)
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

void countWeigh(int *weight,char ch)
{
    int i;
    for(i=0;i<256;i++)
    {
        if(ch==weight[i])
        {
            weight[i]++;
        }
    }
}
//读取出文件内容,返回值为文件的字符个数

void readFile(int *Weigh)
{
    int i;
    FILE *fp;
    char ch;
    fp=fopen("1.txt","r");
    while(!feof(fp))
    {
        fread(&ch,1,1,fp);
        for(i=0;i<256;i++)
        {
            if(ch==i)
            {
                Weigh[i]++;
                break;
            }
        }
    }
}

//将内容写入到文件中
void writeFile(char *str,char *filename,int len)
{
    int i;
    FILE *fp;
    fp=fopen(filename,"w");
    for(i=0;i<len;i++)
    {
        fputc(str[i],fp);
    }
    fclose(fp);
}
//计算出每个ASCII字符出现的次数，并返回出现的ASCII字符个数
int countNum(char *str,int *count)
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
void countNull(int *count,Code *code,int n)
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

//解析字符，即就是将字符解析成编码
char *resolveChar(Code *code,char *c,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(code[i].ascii==*c)
        {
            return code[i].ascii_code;
        }
    }
    return c;
}

//解析
char solveChar(Code *code,char *c,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(!strcmp(code[i].ascii_code,c))
        {
            return code[i].ascii;
        }
    }
}
/*
 *  将压缩后的内容写入到文件中，文件分为三个部分：
 *  第一部分（文件第一行）：记录编码的个数和源文件名，使用fscanf()写入，取出是用fprintf读取出
 *  第二部分（文件第二行到n+1行）:记录编码表的内容使用fscanf()函数写入，使用fprintf读取出
 *  第三部分（第n+2行到末尾）：记录编码后的内容
*/
void writeCode(Code *code,int n,int len,char *filename1,char *filename2,char *str)
{
    int i;
    FILE *fp;
    fp=fopen(filename2,"w");
    fprintf(fp,"%d %d %s",n,len,filename1);
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%c %s\n",code[i].ascii,code[i].ascii_code);
    }
    for(i=0;i<len;i++)
    {
        fprintf(fp,"%s\n",resolveChar(code,&str[i],n));
    }
    fclose(fp);
}
//读取出文件里的文件名和n值
void readCount(int *n,int *len,char *filename1,char *filename2)
{
    FILE *fp;
    fp=fopen(filename2,"r");
    if(fp==NULL)
    {
        printf("Not Found %s",filename2);
        *n=0;
    }
    fscanf(fp,"%d %d %s",n,len,filename1);
    fclose(fp);
}
//读取压缩后的文件内容，并将编码解析，写入文件
int readCode(Code *code,char *str,char *filename1)
{
    int i,n,len;
    char temp[8];
    bzero(temp,sizeof(temp));
    char filename[256];
    FILE *fp;
    fp=fopen(filename1,"r");
    if(fp==NULL)
    {
        return 0;
    }
    fscanf(fp,"%d %d %s",&n,&len,filename);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%c %s\n",&code[i].ascii,code[i].ascii_code);
    }
    for(i=0;i<len;i++)
    {
        fscanf(fp,"%s\n",temp);
        str[i]=solveChar(code,temp,n);
    }
    fclose(fp);
    return 1;
}
void compressFile(char *filename)
{
    int weight[256];
    bzero(weight,sizeof(weight));
}
void uncompressFile(char *filename2)
{
    int i,n,len;
    char filename1[128],filename3[128];
    memset(filename3,'\0',sizeof(filename1));
    readCount(&n,&len,filename1,filename2);
    char str[len];
    memset(str,'\0',sizeof(str));
    Code code[n];
    readCode(code,str,filename2);
    for(i=0;filename2[i]!='.' && filename2[i]!='\0';i++)
    {
        filename3[i]=filename2[i];
    }
    strcat(filename3,".decode");
    writeFile(str,filename3,len);
}
void errorInput()
{
    printf("Usage:zp -c/d/v/n filename\n");
    printf(" -c 压缩   \n");
    printf(" -d 解压缩 \n");
    printf(" -v 版本号 \n");
    printf(" -h 帮助   \n");
}
int main(int argc,char *argv[])
{
    if(argc==3)
    {
        if(!strncmp(argv[1],"-d",2))
        {
            uncompressFile(argv[2]);   
        }
        else if(!strncmp(argv[1],"-c",2))
        {   
            compressFile(argv[2]);
        }
        else
        {
            errorInput();
        }
    }
    else if(argc==2)
    {
        if(!strncmp(argv[1],"-v",2))
        {
            printf("zp version 0.3.1 20151227\n");
        }
        else if(!strncmp(argv[1],"-h",2))
        {
            errorInput();
        }
        else
        {
            errorInput();
        }
    }
    else
    {
        errorInput();
    }
}
