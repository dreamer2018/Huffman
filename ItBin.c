/**************************************************************************************************
	> File Name: ItBin.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月28日 星期一 17时32分46秒
 ************************************************************************************************/

#include<stdio.h>
void Int_Binary(int ascii_code[8],int k)
{
    int i,j,h;
    int temp;
    for(i=0;i<8;i++)
    {
        ascii_code[i]=0;
    }
    for(i=8;i>=0;i--)
    {
        ascii_code[i]=(char)(k%2);
        k=k/2;
        if(k==0)
        {
            break;
        }
    }
}

int main()
{
    int i;
    int ascii_code[8];
    Int_Binary(ascii_code,64);
    for(i=0;i<=8;i++)
    {
        printf("%d",ascii_code[i]);
    }
}
