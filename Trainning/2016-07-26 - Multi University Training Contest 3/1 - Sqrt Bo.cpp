#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char s[200];
long long x;
int l;
long long getnum()
{
    long long ret=0;
    for(int i=0;i<l;i++)ret=ret*10+s[i]-'0';
    return ret;
}
int main()
{
    int i,j,k;
    
    while(scanf("%s",s)!=EOF)
    {
        l=strlen(s);
        if(l>12||(l==0&&getnum()==0))puts("TAT");
        else {
            x=getnum();
            int tms=0;
            while(x!=1 && tms<=5)
            {
                x=(long long)sqrt(x);
                tms++;
            }
            if(tms>5)puts("TAT");
            else printf("%d\n",tms);
        }
    }
    return 0;
}
