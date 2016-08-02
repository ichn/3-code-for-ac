/*
 * 用量纲和v1=0,v2=0,v1=v2的特殊情况猜结论。其实是个推倒题的说。。。
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
const int INF = 0x3f3f3f3f;


int main() {
#ifdef lol
    freopen("hd.in", "r", stdin);
    freopen("hd.out", "w", stdout);
#endif

    int a, v1, v2;
    while (cin >> a >> v1 >> v2) {
        if (a == 0) {
            puts("0");
            continue;
        }
        if (v1 <= v2) {
            puts("Infinity");
        } else {
            printf("%.12lf\n", (double) a * v1 / (v1 + v2) / (v1 - v2));
        }
    }
    return 0;
}
