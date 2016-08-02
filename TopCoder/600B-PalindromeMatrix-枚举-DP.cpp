#include <bits/stdc++.h>
using namespace std;

class PalindromeMatrix {

	int n, m, g[14][14];
	int f[8][15];
	void dpd(int &x, int v) {
		if (v < x) x = v;
	}
public:
	int minChange(vector<string> A, int rowCnt, int colCnt) {
		n = (int)A.size();
		m = (int)A[0].length();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				g[i][j] = A[i][j] - '0';
		int ans = 14 * 14;
		for (int s = 0; s < (1<<m); ++s)
			if (__builtin_popcount(s) == colCnt) {
	//			printf("%d\n", s);
				memset(f, 0x3f, sizeof f);
				f[0][0] = 0;
				for (int i = 1; i <= n / 2; ++i) {
					int ra = i - 1, rb = n - i;
					int va, vb, vc;

					va = 0;
					for (int j = 0; j < m; ++j)
						if ((s >> j) & 1)
							va += g[ra][j] ^ g[rb][j];

					vb = 0;
					for (int j = 0; j < m / 2; ++j) {
						int ca = j, cb = m - j - 1;
						bool oa = (s>>ca) & 1, ob = (s>>cb) & 1;
						if (!oa && !ob)
							vb += g[ra][ca] ^ g[ra][cb];
						else if (oa && !ob)
							vb += (!(g[ra][ca] == g[ra][cb] && g[ra][ca] == g[rb][ca]));
						else if (!oa && ob)
							vb += (!(g[ra][cb] == g[ra][ca] && g[ra][cb] == g[rb][cb]));
						else {
							int x = g[ra][ca];
							int y = g[ra][cb];
							int u = g[rb][ca];
							int v = g[rb][cb];
							if (x == y && y == u && u == v)
								vb += 0;
							else if (!(x ^ y ^ u ^ v))
								vb += 2;
							else vb += 1;
						}
					}
					int tmp = vb;
					vb = 0;
					for (int j = 0; j < m / 2; ++j) {
						int ca = j, cb = m - j - 1;
						bool oa = (s>>ca) & 1, ob = (s>>cb) & 1;
						if (!oa && !ob)
							vb += g[rb][ca] ^ g[rb][cb];
						else if (oa && !ob)
							vb += (!(g[rb][ca] == g[rb][cb] && g[ra][ca] == g[rb][ca]));
						else if (!oa && ob)
							vb += (!(g[rb][cb] == g[rb][ca] && g[ra][cb] == g[rb][cb]));
						else {
							int x = g[ra][ca];
							int y = g[ra][cb];
							int u = g[rb][ca];
							int v = g[rb][cb];
							if (x == y && y == u && u == v)
								vb += 0;
							else if (!(x ^ y ^ u ^ v))
								vb += 2;
							else vb += 1;
						}
					}
					vb = min(vb, tmp);

					vc = 0;
					for (int j = 0; j < m / 2; ++j) {
						int ca = j, cb = m - j - 1;
						bool oa = (s>>ca) & 1, ob = (s>>cb) & 1;
						if (!oa && !ob) {
							vc += g[ra][ca] ^ g[ra][cb];
							vc += g[rb][ca] ^ g[rb][cb];
						} else {
							int x = g[ra][ca];
							int y = g[ra][cb];
							int u = g[rb][ca];
							int v = g[rb][cb];
							if (x == y && y == u && u == v)
								vc += 0;
							else if (!(x ^ y ^ u ^ v))
								vc += 2;
							else vc += 1;
						}
					}
				//	printf("%d %d %d %d\n", i, va, vb, vc);

					for (int j = 0; j <= 2 * (i - 1); ++j) {
						dpd(f[i][j], f[i - 1][j] + va);
						dpd(f[i][j + 1], f[i - 1][j] + vb);
						dpd(f[i][j + 2], f[i - 1][j] + vc);
					}
				}
				ans = min(ans, f[n / 2][rowCnt]);
			}
		return ans;
	}
};

vector<string> A;
int colCnt, rowCnt;
int _main() {
	freopen("in", "r", stdin);
	scanf("%d %d", &rowCnt, &colCnt);
	string str;
	while (cin >> str)
		A.push_back(str);
	printf("%d\n", (new PalindromeMatrix)->minChange(A, rowCnt, colCnt));
	return 0;
}
