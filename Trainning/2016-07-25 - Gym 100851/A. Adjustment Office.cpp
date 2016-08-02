#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
void init(){
    scanf("%d%d",&n,&m);
}
void work(){
    ll a1=n,a2=n,s1=(1LL+n)*n/2,s2=s1;
    static bool b1[1000011],b2[1000011];
    memset(b1,1,sizeof(b1)); memset(b2,1,sizeof(b2));
    for (int i=1;i<=m;++i){
        char op[3]; int x;
        scanf("%s%d",op,&x);
        if (op[0]=='R'){
            ll ans=0;
            if (b1[x]){ans=1LL*x*a2+s2; b1[x]=0; --a1; s1-=x;}
            cout<<ans<<endl;
        }else{
            ll ans=0;
            if (b2[x]){ans=1LL*x*a1+s1; b2[x]=0; --a2; s2-=x;}
            cout<<ans<<endl;
        }
    }
}
int main(){
    freopen("adjustment.in","r",stdin); freopen("adjustment.out","w",stdout);
    init(); work();
    return 0;
}
