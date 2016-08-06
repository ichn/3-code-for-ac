#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int hs = 29;
const int mod = 1e9 + 7;
int pd[20001];
struct Node {
	char s[20001];
	int h[20001];
	int len[20001], len2[20001];
	int l;
	
	int getHs(int l, int r) {
		if (l == 0) return h[r];
		int d = (1LL * h[l-1] * pd[r - l + 1]) % mod;
		return (h[r] - d + mod) % mod;
	}
	void read() {
		scanf("%s\n", s);
		l = strlen(s);
		h[0] = s[0] - 'a';
		for (int i = 1; i < l; ++i)
			h[i] = (1LL * h[i-1] * hs % mod + s[i] - 'a') % mod;
		memset(len, 0, sizeof len);
		memset(len2, 0, sizeof len2);
		for (int i = 1; i <= l; ++i) {
			for (int j = 0; j < l; j += i)
				if (getHs(j, j+i-1) == getHs(0, i-1))
					++len[i];
				else break;
			for (int j = l-1; 0 <= j; j -= i)
				if (getHs(j-i+1, j) == getHs(l-i, l-1))
					++len2[i];
				else break;
		}
		//for (int i = 1; i <= l; ++i)
		//	printf("%d ", len[i]);
		//puts("");
		//for (int i = 1; i <= l; ++i)
		//	printf("%d ", len2[i]);
		//puts("");
	}
} s[200];

map<int, int> ss;

int n;

void upd(int x, int v) {
	//printf("upd %d %d\n", x, v);
	if (ss.find(x) == ss.end())
		ss[x] = v;
	else ss[x] = max(ss[x], v);
}

int main() {
#ifdef lol
	freopen("hd.in", "r", stdin);
	freopen("hd.out", "w", stdout);
#endif

	pd[0] = 1;
	for (int i = 1; i < 20001; ++i)
		pd[i] = (1LL * pd[i-1] * hs) % mod;

	int T;
	int u, v;
	scanf("%d", &T);
	while (T--) {
		scanf("%d\n", &n);
		for (int i = 0; i < n; ++i)
			s[i].read();
		ss.clear();
		int ans = 0;
		u = 0, v = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= s[i].l; ++j)
				if (s[i].len2[j] > 1) {
					int val = s[i].getHs(s[i].l-j, s[i].l-1);
					if (ss.find(val) != ss.end()) {
						int xu = ss[val];
						int xv = s[i].len2[j];
						if ((xu+xv-(xu==xv))*j > ans) {
							ans = (xu+xv-(xu==xv))*j;
							u = xu*j, v = xv*j;
						}
					}
				}
			for (int j = 1; j <= s[i].l; ++j) {
				if (s[i].len[j] > 0)
					upd(s[i].getHs(0, j-1), s[i].len[j]);
			}
		}
		ss.clear();
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= s[i].l; ++j)
				if (s[i].len[j] > 1) {
					int val = s[i].getHs(0, j-1);
					if (ss.find(val) != ss.end()) {
						int xu = ss[val];
						int xv = s[i].len[j];
						if ((xu+xv-(xu==xv))*j > ans) {
							ans = (xu+xv-(xu==xv))*j;
							u = xu*j, v = xv*j;
						}
					}
				}
			for (int j = 1; j <= s[i].l; ++j) {
				if (s[i].len2[j] > 0)
					upd(s[i].getHs(s[i].l-j, s[i].l-1), s[i].len2[j]);
			}
		}

		if (v < u) swap(u, v);
		printf("%d %d\n", u, v);
	}

	return 0;
}
