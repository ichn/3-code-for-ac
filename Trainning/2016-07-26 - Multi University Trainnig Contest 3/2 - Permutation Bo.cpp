#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
const int INF = 0x3f3f3f3f;

int n, c[1001];
double d;

int main() {
#ifdef lol
    freopen("hd.in", "r", stdin);
    freopen("hd.out", "w", stdout);
#endif

    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i)
            scanf("%d ", &c[i]);
        d = 0;
        d += c[1] * 0.5 + c[n] * 0.5;
        for (int i =2; i < n; ++i)
            d += c[i] / 3.0;

        printf("%.6lf\n", d);
    }


    return 0;
}
