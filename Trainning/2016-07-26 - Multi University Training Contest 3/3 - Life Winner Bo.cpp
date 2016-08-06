/*
 * wmj完成
 * 威**博弈？
 * */

#include<bits/stdc++.h>
using namespace std;
const int maxn=1011;
int a[4][maxn][maxn];
void preset(int n){
    memset(a,255,sizeof(a));
    a[0][n][n]=0;
    for (int i=n;i>=1;--i) for (int j=n;j>=1;--j) if (i!=n || j!=n){
        int flag=0;
        if (!a[0][i][j+1]) flag=1;
        if (!a[0][i+1][j]) flag=1;
        if (!a[0][i+1][j+1]) flag=1;
        a[0][i][j]=flag;
    }
    static bool r[maxn],c[maxn];
    memset(r,0,sizeof(r)); memset(c,0,sizeof(c));
    a[1][n][n]=0; r[n]=1; c[n]=1;
    for (int i=n;i>=1;--i) for (int j=n;j>=1;--j) if (i!=n || j!=n){
        if (r[i] || c[j]) a[1][i][j]=1;
        else a[1][i][j]=0,r[i]=1,c[j]=1;
    }
    a[2][n][n]=0;
    for (int i=n;i>=1;--i) for (int j=n;j>=1;--j) if (i!=n || j!=n){
        if (!a[2][i+1][j+2] || !a[2][i+2][j+1]){a[2][i][j]=1; continue;}
        if ( !(i+1<=n && j+2<=n) && !(i+2<=n && j+1<=n) ){a[2][i][j]=-1; continue;}
        if ( (!(i+1<=n && j+2<=n) || a[2][i+1][j+2]==1) && ( !(i+2<=n && j+1<=n) || a[2][i+2][j+1]==1) ) a[2][i][j]=0;
    }
//    cout<<a[2][996][996]<<' '<<a[2][997][998]<<' '<<a[2][998][997]<<endl;
//    cout<<a[2][997][998]<<' '<<a[2][998][1000]<<' '<<a[2][999][999]<<endl;
    static bool XXX[maxn<<1]; bool *r_c=XXX+1011;
    memset(r,0,sizeof(r)); memset(c,0,sizeof(c)); memset(XXX,0,sizeof(XXX));
    a[3][n][n]=0; r[n]=1; c[n]=1; r_c[0]=1;
    for (int i=n;i>=1;--i) for (int j=n;j>=1;--j) if (i!=n || j!=n){
        if (r[i] || c[j] || r_c[i-j]) a[3][i][j]=1;
        else a[3][i][j]=0,r[i]=1,c[j]=1,r_c[i-j]=1;
    }
}
int op,n,m;
void init(){
    scanf("%d%d%d",&op,&n,&m);
}
void work(){
    --op;
    if (a[op][1000-n+1][1000-m+1]==1) puts("B");
    else if (a[op][1000-n+1][1000-m+1]==-1) puts("D");
    else puts("G");
}
int main(){
    preset(1000); int T; scanf("%d",&T);
    while (T--) init(),work();
    return 0;
}
