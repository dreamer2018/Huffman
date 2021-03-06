/**************************************************************************************************
	> File Name: Huffman3.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月28日 星期一 14时47分41秒
 ************************************************************************************************/

#include<stdio.h>
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
    char code[257];
}Code;

//初始化哈夫曼数的结点
void initHuffTree(Code *code,HufNode *h,int n)
{
    int i;
    int m=2*n-1;
    for(i=0;i<n;i++)
    {
        h[i].Weight=code[i].weight;
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
int countZero(int *Weight)
{
    int i,j;
    for(i=0,j=0;i<256;i++)
    {
        if(Weight[i]!=0)
        {
            j++;
        }
    }
    return j;
}
int countWeight(Code *code,int *Weight)
{
    int i,j;
    for(i=0,j=-1;i<256;i++)
    {
        if(Weight[i]!=0)
        {
            j++;
            code[j].ascii=i;
            code[j].weight=Weight[i];
        }
    }
}
int readFile(int *Weigh,char *filename)
{
    int i,j,k;
    FILE *fp;
    char ch;
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Not Found %s\n",filename);
    }
    for(j=0;!feof(fp);j++)
    {
        fread(&ch,1,1,fp);
        k=(int)ch;
        if(k<0)
        {
            k=k+256;
        }
        for(i=0;i<256;i++)
        {
            if(k==i)
            {
                Weigh[i]++;
                break;
            }
        }
    }
    return j;
}
void writeCode(Code *code,int n,int len,char *filename)
{
    int i,j;
    FILE *fp;
    FILE *fp2;
    char filename1[128];
    memset(filename1,'\0',sizeof(filename1));
    char ch;
    for(i=0;filename[i]!='.' && filename[i]!='\0';i++)
    {
        filename1[i]=filename[i];
    }
    strcat(filename1,".code");
    fp=fopen(filename1,"w");
    fprintf(fp,"%d %d",n,len);
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%c %d %s\n",code[i].ascii,code[i].weight,code[i].code);
    }
    printf("--------\n");
    for(i=0;i<n;i++)
    {
        printf("%c %s\n",code[i].ascii,code[i].code);
    }
    fp2=fopen(filename,"r");
 //   while(!feof(fp2))
    for(j=0;j<len;j++)
    {
        fread(&ch,1,1,fp2);
        for(i=0;i<n;i++)
        {
            if(ch==code[i].ascii)
            {
                fprintf(fp,"%s\n",code[i].code);
            }
        }
    }
    fclose(fp);
    fclose(fp2);
}
int readNum(char *filename)
{
    FILE *fp;
    int n,len;
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Not Found %s",filename);
        return 0;
    }
    fscanf(fp,"%d %d",&n,&len);
    fclose(fp);
    return n;
}
void readCode(Code *code,char *filename)
{
    int i,j,n,len;
    FILE *fp;
    char filename1[128];
    char ch[9];
    memset(filename1,'\0',sizeof(filename1));
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Not Found %s\n",filename);
    }
    fscanf(fp,"%d %d",&n,&len);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%c %d %s\n",&code[i].ascii,&code[i].weight,code[i].code);
    }
    printf("-------wfr-\n");
    for(i=0;i<n;i++)
    {
        printf("%c",code[i].ascii);
    }
    for(i=0;filename[i]!='.' && filename[i]!='\0';i++)
    {
        filename1[i]=filename[i];   
    }
    strcat(filename1,".decode");
    FILE *fp2;
    fp2=fopen(filename1,"w");
    //while(!feof(fp))
    for(j=0;j<len;j++)
    {
        memset(ch,'\0',sizeof(ch));
        fscanf(fp,"%s\n",ch);
        for(i=0;i<n;i++)
        {
            if(!strcmp(code[i].code,ch))
            {
                fwrite(&code[i].ascii,1,1,fp2);
            }
        }
    }
    fclose(fp);
    fclose(fp2);
}
void compressFile(char *filename)
{
    int i,n,m,len;
    int Weight[256];
    bzero(Weight,sizeof(Weight));
    len=readFile(Weight,filename);
    for(i=0;i<256;i++)
    {
        if(Weight[i]!=0)
        {
            printf("%d\n",Weight[i]);
        }
    }
    n=countZero(Weight);
    m=2*n-1;
    printf("n=%d len=%d\n",n,len);
    Code code[n];
    countWeight(code,Weight);
    for(i=0;i<n;i++)
    {
        printf("%d %d\n",code[i].ascii,code[i].weight);
    }
    HufNode h[m];
    initHuffTree(code,h,n);
    createHuffTree(h,n);
    printHufTree(h,n);
    for(i=0;i<n;i++)
    {
        bzero(code[i].code,sizeof(code[i].code));
        HuffmanCode(h,code[i].code,h[i],i);
    }
    for(i=0;i<n;i++)
    {
        printf("%c:%s\n",code[i].ascii,code[i].code);
    }
    writeCode(code,n,len,filename);
}
void uncompressFile(char *filename)
{
    int n;
    n=readNum(filename);
    Code code[n];
    readCode(code,filename);
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
