#include <bits/stdc++.h>
using namespace std;

int n, m;
char str[100000 + 100], p[5001];

int main() {
    int tCase;
    scanf("%d", &tCase);
    while (tCase--) {
        scanf("%d%d\n", &n,&m);
        scanf("%s", str);
        scanf("%s", p);
        int td = n - m + 1;
        for (int i = 0; i < td; ++i) {
            bool ok = true;
            for (int j = 0; j < m; ++j) {
                if (p[j] == str[i+j]) continue;
                if (j+1 == m || p[j+1] != str[i+j]) {
                    ok = false;
                    break;
                }
                if (p[j] != str[i+j+1]) {
                    ok =false;
                    break;
                }
                ++j;
            }
            putchar('0'+ok);
        }
        for (int i = td; i < n; ++i)
            putchar('0');
        puts("");
    }

    return 0;
}
