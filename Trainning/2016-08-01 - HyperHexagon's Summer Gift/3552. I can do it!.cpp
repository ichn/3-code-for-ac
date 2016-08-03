#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
pair<int, int> ss[100011];

int N, M[100011];

int main() {

#ifdef lol
    freopen("1008.in", "r", stdin);
    freopen("1008.out", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    for (int tt = 1; tt <= T; ++tt) {
        scanf("%d", &N);
        for (int i= 1; i <= N; ++i) {
            scanf("%d %d", &ss[i].x, &ss[i].y);
        }
        sort(ss + 1, ss + N + 1);
        M[N+1] = 0;
        for (int i = N; 0 < i; --i)
            M[i] = max(M[i+1], ss[i].y);
        int ans = INT_MAX;
        ss[0].x = 0;
        for (int i = 0; i <= N; ++i) {
            ans = min(ans, ss[i].x + M[i+1]);
        }
        printf("Case %d: %d\n", tt, ans);
    }

    return 0;
}
