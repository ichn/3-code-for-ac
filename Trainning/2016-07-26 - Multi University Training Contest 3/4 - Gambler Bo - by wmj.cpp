#include <bits/stdc++.h>
using namespace std;
const int maxn=33;
int n,m,a[maxn][maxn];
void init(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) scanf("%d",a[i]+j),a[i][j]%=3;
}
int b[maxn][maxn][maxn],b1[maxn][maxn][maxn];

int ope[33], cnt[33][33], p[33][33];


void cli(int a, int b) {
    //printf("%d %d\n", a, b);
    ++cnt[a][b];
    cnt[a][b] %= 3;
    p[a][b] += 2;
    p[a][b] %= 3;
    ++p[a-1][b];
    ++p[a][b-1];
    ++p[a+1][b];
    ++p[a][b+1];
    p[a-1][b] %= 3;
    p[a][b-1] %= 3;
    p[a+1][b] %= 3;
    p[a][b+1] %= 3;
}

void work(){
    memset(b,0,sizeof(b)); memset(b1,0,sizeof(b1));


    for (int i=1;i<=m;++i) b[1][i][i]=2,b[1][i][i+1]=1,b[1][i][i-1]=1,b[1][i][m+1]=a[1][i],b1[1][i][i]=1;
    b[1][1][0]=0;


    for (int i=2;i<=n;++i){
        for (int j=1;j<=m;++j) for (int k=1;k<=m+1;++k)
            b1[i][j][k]=-b[i-1][j][k];

        for (int j=1;j<=m;++j){
            b[i][j][m+1]+=a[i][j];
            for (int l=max(1,j-1);l<=min(m,j+1);++l) for (int k=1;k<=m+1;++k)
                b[i][l][k]+=b1[i][j][k];
            for (int k=1;k<=m+1;++k) b[i][j][k]+=b1[i][j][k];
            for (int k=1;k<=m+1;++k) b[i][j][k]+=b1[i-1][j][k];
        }

        for (int j=1;j<=m;++j) for (int k=1;k<=m+1;++k)
            b[i][j][k]%=3,b1[i][j][k]%=3;
    }

/*    for (int i=1;i<=n;++i) for (int j=1;j<=m;++j){
        for (int k=1;k<=m+1;++k) cout<<b[i][j][k]<<' ';
        cout<<endl;
    }
    puts("");
    for (int i=1;i<=n;++i) for (int j=1;j<=m;++j){
        for (int k=1;k<=m+1;++k) cout<<b1[i][j][k]<<' ';
        cout<<endl;
    }*/
//    for (;;);
    static int T[maxn][maxn];

    for (int i=1;i<=m;++i){
        for (int k=1;k<=m;++k) T[i][k]=((b[n][i][k]%3)+3)%3;
        T[i][m+1]=((-b[n][i][m+1]%3)+3)%3;
    }

//    for (int i=1;i<=m;++i,cout<<endl) for (int j=1;j<=m+1;++j) cout<<T[i][j]<<' ';

    static int tmp[maxn];
    for (int i=1;i<=m;++i){
        if (!T[i][i]){
            for (int j=i+1;j<=m;++j) if (T[j][i]){
                memcpy(tmp,T[j],sizeof(tmp)); memcpy(T[j],T[i],sizeof(tmp)); memcpy(T[i],tmp,sizeof(tmp)); break;
            }
        }
        if (T[i][i]){
            for (int j=i+1;j<=m;++j){
                int t=0;
                if (T[i][i]==1) t=T[j][i];
                if (T[i][i]==2) if (T[j][i]==1) t=2;else if (T[j][i]==2) t=1;
                if (t) for (int k=i;k<=m+1;++k) T[j][k]=((T[j][k]-T[i][k]*t)%3+3)%3;
            }
        }
    }

//    for (int i=1;i<=m;++i,cout<<endl) for (int j=1;j<=m+1;++j) cout<<T[i][j]<<' ';

    static int ans[maxn];
    for (int i=m;i>=1;--i){
        int xxx=T[i][m+1];
        for (int j=i+1;j<=m;++j) xxx-=ans[j]*T[i][j];
        xxx=((xxx%3)+3)%3;
        if (!T[i][i]) ans[i]=0;
        if (T[i][i]==1) ans[i]=xxx;
        if (T[i][i]==2){
            if (xxx==0) ans[i]=0;
            if (xxx==1) ans[i]=2;
            if (xxx==2) ans[i]=1;
        }
    }
    //for (int i=1;i<=m;++i) cout<<ans[i]<<endl;
    memcpy(p, a, sizeof a);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < ans[i]; ++j)
            cli(1, i);
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            while (p[i-1][j] != 0) {
                cli(i, j);
            }
        }
    }        int ans2 = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                ans2 += cnt[i][j];
        printf("%d\n", ans2);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                while (cnt[i][j] != 0) {
                    printf("%d %d\n", i, j);
                    --cnt[i][j];
                }
            }
}


int main(){
    int T; scanf("%d",&T);
    while (T--) init(),work();
    return 0;
}
