/**************************************************************************************************
	> File Name: filereadtest.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:文件读取测试
	> Created Time: 2015年12月26日 星期六 10时39分43秒
 ************************************************************************************************/

#include<stdio.h>
#include<string.h>
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
        //printf("%c",ch);
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
void CountNum(char *str,int *cout)
{
    int i;
    for(i=0;str[i]!='\0';i++)
    {
        cout[str[i]-1]++;
    }
}
int main()
{
    int i=0;
    int cout[127];
    bzero(cout,sizeof(cout));
    char str[100];
    ReadFile(str);
    CountNum(str,cout);
    WriteFile(str);
    for(i=0;i<127;i++)
    {
        if(cout[i]!=0)
            printf("%c : %d \n",i+1,cout[i]);
    }
}
