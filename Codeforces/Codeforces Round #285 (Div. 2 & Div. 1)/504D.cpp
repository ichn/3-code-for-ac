#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2000 + 100;
bitset<maxn> h[maxn], use[maxn];
int len[maxn], s[maxn];
char str[maxn];
int num[maxn];
int n, loc;
vector<int> out;

int main() {
#ifdef love_sbit
	freopen("504D.in", "r", stdin), freopen("504D.out", "w", stdout);
#endif
	scanf("%d", &n);
	for (int i=1; i<=n; ++loc, ++i) {
		scanf("%s", str);
		int l = strlen(str);
		for (int j=0; j<l; ++j)
			num[l-j] = str[j]-'0';
		len[i] = 0;
		h[i].reset(), use[i].reset();
		while (l) {
			++len[i];
			int j, r;
			for (j=l, r=0; j; --j) {
				num[j] += r*10;
				r = num[j]&1;
				num[j] >>= 1;
			}
			l -= !num[l];
			h[i][len[i]] = r;
		}
		l = len[i];
		for (int j=1; j<i; ++j) {
			if (len[j]==l && h[j][l]&h[i][l]) {
				h[i] ^= h[j];
				use[i] ^= use[j];
				while (l && h[i][l]==0) --l;
			}
		}
		if (l==0) {
			printf("%d", (int)use[i].count());
			for (int j=0; j<=loc; ++j)
				if (use[i][j])
					printf(" %d", j);
			puts("");
			--n, --i;
		} else {
			puts("0");
			use[i][loc].flip();
			len[i] = l;
			for (int j=i; 1<j; --j) {
				if (len[j-1] < len[j]) {
					swap(len[j-1], len[j]);
					swap(h[j], h[j-1]);
					swap(use[j], use[j-1]);
				}
			}
		}
	}
 
	return 0;
}
