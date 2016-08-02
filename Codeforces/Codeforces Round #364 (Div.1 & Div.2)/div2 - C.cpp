#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

int n;
char str[100002];

int Id(char c) {
	if ('a' <= c && c <= 'z')
		return c - 'a';
	else return c - 'A' + 27;
}

int cnt[60], cnt2[60];

bool chk() {
	for (int i = 0; i < 59; ++i)
		if (cnt2[i] != 0 && cnt[i] == 0)
			return false;
	return true;
}

int main() {

#ifdef lol
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif

	scanf("%d\n", &n);
	scanf("%s", str);

	for (int i = 0; i < n; ++i)
		++cnt2[Id(str[i])];
	int ans = n;
	for (int i = 0, j = 0; i < n; ++i) {
		cnt[Id(str[i])]++;
		while (j <= i && chk()) {
			ans = min(ans, i - j + 1);
			cnt[Id(str[j])]--;
			++j;
		}
	}

	printf("%d\n", ans);


	return 0;
}
