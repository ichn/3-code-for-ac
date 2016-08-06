/*
 * 注意点的坐标范围，当c(n,2)<=2m时暴力，否则鸽巢原理。
 *
 * */
#include<bits/stdc++.h>
using namespace std;
const int maxn=100011;
int n,m; int a[maxn],b[maxn];
void init(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d%d",a+i,b+i);
}
void work(){
    if (1LL*n*(n-1)/2>2*m){puts("YES"); return;}
    static bool B[maxn*2]; memset(B,0,sizeof(B));
    for (int i=1;i<=n;++i) for (int j=i+1;j<=n;++j){
        int dis=abs(a[i]-a[j])+abs(b[i]-b[j]);
        if (B[dis]){puts("YES"); return;} B[dis]=1;
    }
    puts("NO");
}
int main(){
    int T; scanf("%d",&T);
    while (T--) init(),work();
    return 0;
}
