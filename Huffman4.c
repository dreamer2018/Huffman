/**************************************************************************************************
	> File Name: Test.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月27日 星期日 21时23分16秒
 ************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>

//定义数据类型
#define DataType int

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

void Int_Binary(int ascii_code[],int k)
{
    int i,j,h;
    int temp;
    for(i=0;i<8;i++)
    {
        ascii_code[i]=0;
    }
    for(i=7;i>=0;i--)
    {
        ascii_code[i]=(char)(k%2);
        k=k/2;
        if(k==0)
        {
            break;
        }
    }
}
int Binary_Int(int ascii_code[])
{
    int i=7,j=0;
    for(i=0;i<8;i++)
    {
        j+=ascii_code[i]*pow(2,7-i);
    }
    return j;
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
int Code_Index(Code *code,char ch,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(ch==code[i].ascii)
        {
            return i;
        }
    }
}
void writeCode(Code *code,char ascii_code[][256],int n,int len,char *filename)
{
    int i,j,bytenum=-1,c[8],k,h;
    FILE *fp,*fp2;

    char temp,filename1[128],ch;

    //根据原文件名，创建出中间文件名
    memset(filename1,'\0',sizeof(filename1));
    
    for(i=0;filename[i]!='.' && filename[i]!='\0';i++)
    {
        filename1[i]=filename[i];
    }
    strcat(filename1,".code");

    fp=fopen(filename1,"w");    //编码文件
    fp2=fopen(filename,"r");    //源文件
    
    if(fp2==NULL)
    {
        printf("Not Found %s",filename);
    }

    //先写入文件头部信息
    fprintf(fp,"%d %d",n,len);
    
    //再写入code相关信息
    for(i=0;i<n;i++)
    {
        fwrite(&code[i],sizeof(Code),1,fp);
    }

    //将源文件压缩后写入
    for(i=0;i<len;i++)
    {
        //从源文件里面读出部分内容
        fread(&ch,1,1,fp2);
        //与源编码表进行匹配
        int index=Code_Index(code,ch,n);
        //将文件的编码后的码值得到之后，8个为一段，然后转成十进制，然后将十进制整形强转成字符类型，然后存入文件
        
        int m;
        
        for(j=0;ascii_code[index][j]!='\0';j++)
        {
            bytenum++;
            c[bytenum]=(int)ascii_code[index][j]-48;
            if(bytenum == 7)
            {
                k=Binary_Int(c);
                h=(char)k;
                fwrite(&h,1,1,fp);
                bytenum=-1;
            }
        }
    }
    if(bytenum>-1 && bytenum < 7)
    {
        for(i=bytenum+1;i<8;i++)
        {
            c[i]=0;    
        }
        k=Binary_Int(c);
        h=(char)k;
        fwrite(&h,1,1,fp);
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
int readCode(Code *code,char *filename)
{
    int i,j,n,len,k,sign=0,index;
    //记录二进制编码，用于转换成二进制
    int binary[8];
    FILE *fp;
    FILE *fp2;
    char filename1[128];
    char ch;
    
    //根据原文件名，导出新文件名
    memset(filename1,'\0',sizeof(filename1));
    
    for(i=0;filename[i]!='.' && filename[i]!='\0';i++)
    {
        filename1[i]=filename[i];   
    }
    strcat(filename1,".decode");
    
    fp=fopen(filename,"r"); //源文件
    fp2=fopen(filename1,"w"); //要写的编码文件
    if(fp==NULL)
    {
        printf("Not Found %s\n",filename);
        return 0;
    }
    
    //先读出文件头部信息
    fscanf(fp,"%d %d",&n,&len);
    
    //后读取code里面的内容，包括源ASCII编码和权值内容
    for(i=0;i<n;i++)
    {
        fread(&code[i],sizeof(Code),1,fp);
    }
    
    //建立哈夫曼树
    HufNode h[2*n-1];
    initHuffTree(code,h,n);
    createHuffTree(h,n);
    //临时的节点
    HufNode t;
    //判断文件到末尾没
    if(feof(fp))
    {
        return 0;   
    }
    //从源文件里面读出内容
    fread(&ch,1,1,fp);
    k=(int)ch;
    if(k<0)
    {
        k=k+256;
    }
    Int_Binary(binary,k);
    t=h[2*n-2];
    sign++;
    index=2*n-2;
    for(j=0;;j++)
    {
        if(t.LChild ==0 && t.RChild ==0)
        {
            //判断文件到末尾没
            if(feof(fp))
            {
                break;   
            }
            fwrite(&code[index].ascii,1,1,fp2);
            t=h[2*n-2];
            sign++;
            j--;
        }
        else
        {
            if(binary[j]==0)
            {
                index=t.LChild;
                t=h[t.LChild];
            }
            else 
            {
                index=t.RChild;
                t=h[t.RChild];
            }
        }
        if(sign>=len)
        {
            break;
        }
        if(j==7)
        {
            fread(&ch,1,1,fp);
            k=(int)ch;
            if(k<0)
            {
                k=k+256;
            }
            Int_Binary(binary,k);
            j=-1;
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
    n=countZero(Weight);
    m=2*n-1;
    Code code[n];
    char ascii_code[n][256];
    for(i=0;i<n;i++)
    {
        memset(ascii_code,'\0',sizeof(ascii_code));
    }
    countWeight(code,Weight);
    HufNode h[m];
    initHuffTree(code,h,n);
    createHuffTree(h,n);
    for(i=0;i<n;i++)
    {
        bzero(ascii_code[i],sizeof(ascii_code[i]));
        HuffmanCode(h,ascii_code[i],h[i],i);
    }
    writeCode(code,ascii_code,n,len,filename);
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
            printf("zp version 0.5.0 20151229\n");
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
