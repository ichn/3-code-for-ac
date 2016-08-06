#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

long long f[1011][1011];

int a[1011], b[1111], pos1[1111], pos2[1111];
int n, m;

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int j = 1; j <= m; ++j)
            scanf("%d", &b[j]);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1];
                f[i][j] %= mod;
                f[i][j] += mod;
                f[i][j] %= mod;
                if (a[i] == b[j]) {
                    f[i][j] += f[i-1][j-1] + 1;
                    f[i][j] %= mod;
                }
            }
        //    memset(pos1, 0, sizeof pos1);
        //    f[0][0] = 1;
        //    for (int i = 1; i <= n; ++i) {
        //        memset(pos2, 0, sizeof pos2);
        //        pos1[a[i]] = i-1;
        //        for (int j = 1; j <= m; ++j) {
        //            pos2[b[j]] = j-1;
        //            f[i][j] = (f[pos1[b[j]]][j-1] + f[i-1][pos2[a[i]]]) % mod;
        //        }
        //    }
        cout << f[n][m] % mod << endl;
    }
    return 0;
}
