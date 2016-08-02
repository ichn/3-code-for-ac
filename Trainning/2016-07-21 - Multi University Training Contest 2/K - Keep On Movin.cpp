#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 10;
int a[maxN];
int cnt, n;

long long Cnt = 0;

int main() {

    int tCase;
    scanf("%d", &tCase);
    while (tCase--) {
        scanf("%d", &n);
        cnt = 0;
        Cnt = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            cnt += (a[i] & 1);
            Cnt += a[i] - (a[i]&1);
        }
        if (cnt == 0) {
            cout << Cnt <<endl;
        } else {
            Cnt >>= 1;
            Cnt /= cnt;
            cout << (Cnt<<1|1) << endl;
        }    
    }

    return 0;
}
