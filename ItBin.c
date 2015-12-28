/**************************************************************************************************
	> File Name: ItBin.c
	> Author: ZhouPan / github:dreamer2018 
	> Mail: zhoupans_mail@163.com
	> Blog: blog.csdn.net/it_dream_er
	> Function:
	> Created Time: 2015年12月28日 星期一 17时32分46秒
 ************************************************************************************************/

#include<stdio.h>
#include<math.h>
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
    printf("\n");
    int i=7,j=0;
    for(i=0;i<8;i++)
    {
        j+=ascii_code[i]*pow(2,7-i);
    }
    return j;
}
int main()
{
    int i,k=0;
    int ascii_code[8];
    Int_Binary(ascii_code,54);
    for(i=0;i<8;i++)
    {
        printf("%d",ascii_code[i]);
    }
    k=Binary_Int(ascii_code);
    printf("%d",k);
}
