#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <string>
#define REP(i,j) for(int i=1;i<=j;++i)
#define REPI(i,j,k) for(int i=j;i<=k;++i)
#define REPD(i,j) for(int i=j;0<i;--i)
#define STLR(i,con) for(int i=0,sz=con.size();i<sz;++i)
#define STLRD(i,con) for(int i=con.size()-1;0<=i;--i)
#define CLR(s) memset(s,0,sizeof s)
#define SET(s,v) memset(s,v,sizeof s)
#define mp make_pair
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef double DB;
const int INF = 0x3f3f3f3f;
 
struct Data
{
    vector<int> str;
    void clear()
    {
        str.clear();
    }
    int size()
    {
        return str.size();
    }
    void push_back(int t)
    {
        str.push_back(t);
    }
    void print()
    {
        STLR(i,str)
            printf("%c",char(str[i]));
        puts("");
    }
    int &operator [] (int i)
    {
        return str[i];
    }
};
vector<Data> S;
Data tmp;
 
int n;
bool check(int t)
{
    return t==(int)'*';
}
 
vector<int> next;
 
void get_next(int l,int r,int s)
{
    next.clear();
    next.pb(-1);
    int i=l,j=-1;
    while(i<=r)
    {
        if(j==-1 || S[s][i]==S[s][j+l])
        {
            ++i,next.pb(++j);
        }
        else
            j=next[j];
    }
}
 
bool kmp(int s,int l,int r,int p,int &i)
{
    get_next(l,r,s);
 
    int j=l-1;
    --i;
    int len=S[p].size();
    while(i<len)
    {
        if(j==l-1 || S[s][j]==S[p][i])
        {
            ++i,++j;
            if(j==r+1)
            {
                --i;
                return true;
            }
        }
        else
            j=next[j-l]+l;
    }
    return false;
}
 
vector<int> stop;
vector<pair<int,int> > block;
bool same_with_kmp(int s,int p)
{
    stop.clear();
    block.clear();
    stop.pb(-1);
    STLR(i,S[s])
    {
        if(check(S[s][i]))
            stop.pb(i);
    }
    stop.pb(S[s].size());
    int a,b;
    for(int i=1,sz=stop.size();i<sz;++i)
    {
        a=stop[i-1]+1,b=stop[i]-1;
        if(b<a) continue;
        block.pb(mp(a,b));
    }
     
    int run=0;
    STLR(i,block)
    {
        if(!kmp(s,block[i].x,block[i].y,p,run))
            return false;
    }
 
    return true;
}
 
bool check_with_kmp()
{
    int a=-1,mark=INF;
    bool flag;
    STLR(i,S)
    {
        flag=false;
        STLR(j,S[i])
        {
            if(check(S[i][j]))
            {
                flag=true;
                break;
            }
        }
//      printf("%d %d %d\n",flag,S[i].size(),mark);
        if(!flag && S[i].size()<mark)
        {
            mark=S[i].size();
            a=i;
        }
    }
 
 
    if(a==-1)
        return true;
 
    STLR(i,S)
    {
        if(!same_with_kmp(i,a))
            return false;
    }
 
    return true;
}
 
 
bool same_with_tp(int s,int a,int b)
{
    STLR(i,S[s])
    {
        if(check(S[a][i]) || check(S[s][i]))
            break;
        if(S[a][i]!=S[s][i])
            return false;
    }
    STLR(i,S[s])
    {
        if(check(S[s][S[s].size()-i-1]) || check(S[b][S[b].size()-i-1]))
            break;
        if(S[s][S[s].size()-i-1]!=S[b][S[b].size()-i-1])
            return false;
    }
    return true;
}
 
bool check_with_tp()
{
    int a=0,b=0;
    int mark1=-1,mark2=-1;
    STLR(i,S)
    {
        STLR(j,S[i])
        {
            if(check(S[i][j]))
            {
                if(j>mark1)
                {
                    mark1=j;
                    a=i;
                }
                break;
            }
        }
        STLRD(j,S[i])
        {
            if(check(S[i][j]))
            {
                if(S[i].size()-j>mark2)
                {
                    mark2=S[i].size()-j;
                    b=i;
                }
                break;
            }
        }
    }
 
    //printf("%d %d\n",a,b);
     
    STLR(i,S)
    {
        if(!same_with_tp(i,a,b))
            return false;
    }
 
    return true;
}
 
char s[20000000];
int main()
{
 
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        S.clear();
        for(int i=0;i<n;++i)
        {
            scanf("%s",s);
        //  printf("%s\n",s);
            tmp.clear();
            for(int j=0;s[j]!='\0';++j)
                tmp.pb((int)s[j]);
            S.pb(tmp);
        }
        bool flag1=check_with_tp();
        bool flag2=check_with_kmp();
        if(flag1 && flag2) puts("Y");
        else puts("N");
    }
    fclose(stdin);
    fclose(stdout);
 
    return 0;
}
