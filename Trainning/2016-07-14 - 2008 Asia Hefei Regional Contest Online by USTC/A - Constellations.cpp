#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int maxSize = 1000 + 10;
const int maxCons = 50 + 10;
const int maxN = 100 + 10;
const int base = 45061;
const int mod1 = 45053;
const int mod = 1e9 + 7;

LL bs[maxCons * maxCons];

char gchar() {
    char ret = getchar();
    for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
    return ret;
}


int N, M, T, P, Q;


int sky[maxSize][maxSize];
int con[maxCons * maxCons];


LL h_c[maxN];
LL h_s[maxSize][maxSize];
bool show[maxN];
int ans;

map<int, int> ste;


int main() {

#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif // ONLINE_JUDGE

    bs[0] = 1;
    for (int i = 1; i < maxCons * maxCons; ++i)
        bs[i] = (bs[i - 1] * (LL)base) % mod;


    int tCase = 0;

    while (scanf("%d %d %d %d %d", &N, &M, &T, &P, &Q) != EOF) {
        if (N + M + T + P + Q == 0) break;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                sky[i][j] = (gchar() == '*');
		ste.clear();
        for (int i = 0; i < T; ++i) {
			LL val = 0;
			for (int j = 1; j <= P; ++j) {
				LL temp = 0;
				for (int k = 0; k < Q; ++k) {
					LL t2 = gchar() == '*';
					temp |= t2<<(Q-k-1);
				}
				int t3 = temp % mod1;
				val = (val * base % mod + t3) % mod;
			}
			h_c[i] = val;
			ste[val] = 0;
        }
        memset(h_s, 0, sizeof h_s);
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j + Q - 1 <= M; ++j) {
				LL temp = 0;
				for (int k = 0; k < Q; ++k) {
					LL t2 = sky[i-1][j+k-1];
					temp |= t2<<(Q-k-1);
				}
				h_s[i][j] = temp % mod1;
			}

        for (int i = 1; i <= N-P+1; ++i)
            for (int j = 1; j <= M-Q+1; ++j) {
				LL val = 0;
                for (int k = 0; k < P; ++k) {
					val = (val * base % mod + h_s[i+k][j]) % mod;
                }
				if (ste.find(val) != ste.end()) {
					ste.find(val)->second = 1;
				}
            }
        ans = 0;
		for (int i = 0; i < T; ++i) {
			if (ste[h_c[i]] != 0)
				++ans;
		}
        printf("Case %d: %d\n", ++tCase, ans);
    }

    return 0;

}
