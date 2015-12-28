/*************************************************************************
	> File Name: Read.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月28日 星期一 09时53分31秒
 ************************************************************************/

#include<stdio.h>
void main()
{
    int i,j;
    char ch;
    FILE *fp;
    fp=fopen("2.txt","r");
    while(!feof(fp))
    {
        fread(&ch,1,1,fp);
        printf("%d\n",ch); 
        j=(int)ch;
        if(j<0)
        {
            j=256+j;
        }
        for(i=0;i<256;i++)
        {
            if(i==j)
            {
                printf("%d\n",i);
            }
        }
    }
    char a[256];
    for(i=0;i<256;i++)
    {
        a[i]=i;
    }
    for(i=0;i<256;i++)
    {
        printf("%d\n",a[i]);
    }
}
