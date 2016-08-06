#include <bits/stdc++.h>
using namespace std;
int G[110][110];
int main() {
    int T = 0; scanf("%d",&T);
    while(T --) {
        int n = 0,m = 0;
        scanf("%d%d",&m,&n);
        for(int i = 1;i <= m;++ i)
            for(int j = 1;j <= n;++ j)
                scanf("%d",&G[i][j]);
        int ans = 0;
        for(int i = 1;i <= n;++ i) {
            int cnt = m;
            for(int j = m;j >= 1;-- j) {
                if(G[j][i]) {
                    ans += cnt - j; cnt --;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
