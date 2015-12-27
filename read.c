/**************************************************************************************************
	> File Name: read.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月27日 星期日 18时54分43秒
 ************************************************************************************************/

#include<stdio.h>
void read()
{
    char ch;
    FILE *fp;
    fp=fopen("1.txt","r");
    ch=fgetc(fp);
    printf("%d",ch);
}
int main()
{
    read();
}
