#include<bits/stdc++.h>
using namespace std;
const int maxn=100011;
int n,a[maxn];
void init(){
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",a+i);
}
inline int f(int a,int x){return (a>>x)&1;}
inline int g(int a,int x){return ((a>>x)&1)?1:-1;}
long long c[25][25];
void work(){
    memset(c,0,sizeof(c)); long long ans=0;
    for (int i=1;i<n;++i){
        int t=-1;
        for (int bit=19;bit>=0;--bit) if (f(a[i],bit) ^ f(a[i+1],bit))
            if (t==-1) t=bit,ans+=1<<t;else if (f(a[i],bit)^f(a[i],t)) c[bit][t]--;else c[bit][t]++;
    }

    static long long A[1500],B[1500];
    memset(A,0,sizeof(A));
    for (int i=0;i<1024;++i){
        for (int j=0;j<10;++j) for (int k=j+1;k<10;++k){
            A[i]+=g(i,j)*g(i,k)*(1<<j)*c[j][k];
        }
    }


    memset(B,0,sizeof(B));
    for (int i=0;i<1024;++i){
        for (int j=0;j<10;++j) for (int k=j+1;k<10;++k)
            B[i]+=g(i,j)*g(i,k)*(1LL<<(10+j))*c[10+j][10+k];
    }

    static long long dp[1500][20];
    memset(dp,0,sizeof(dp));
    for (int i=0;i<1024;++i) for (int j=0;j<10;++j){
        for (int k=0;k<10;++k) dp[i][j]+=g(i,k)*c[k][j+10]*(1<<k);
    }

    long long ans1=LLONG_MAX,ans2=-1;
    for (int j=0;j<1024;++j) for (int i=0;i<1024;++i){
        long long tmp=A[i]+B[j];
        for (int k=0;k<10;++k) tmp+=g(j,k)*dp[i][k];
        if (tmp<ans1) ans1=tmp,ans2=i+j*1024;
    }
    cout<<ans2<<' '<<ans+ans1<<endl;
}
int main(){
	freopen("5798.in", "r", stdin);
	freopen("std.out", "w", stdout);
    int T; scanf("%d",&T);
    while (T--) init(),work();
    return 0;
}
