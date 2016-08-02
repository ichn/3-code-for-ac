#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxPri = 135000;
int pri[maxPri], show[maxPri];
bool is_pri[maxPri];
int cnt;

LL mult(LL b, LL i, LL m) {
	LL r = 0;
	for (;i;i>>=1, b=b+b%m)
		if (i&1)r=r+b%m;
	return r;
}
LL fpow(LL b, LL i, LL m) {
	LL r = 1;
	for (;i;i>>=1, b=mult(b,b,m))
		if (i&1)r=mult(r,b,m);
	return r%m;
}


void init() {

	memset(is_pri, true, sizeof is_pri);
	for (int i = 2; i < maxPri; ++i) {
		if (is_pri[i]) {
			pri[++cnt] = i;
			for (int j = i+i; j < maxPri; j+=i)
				is_pri[j] = false;
		}
	}
}

LL L, phi, mod;

int seq[maxPri], num;

vector<LL> ans;

void dfs(int dep, LL r) {
	if (dep == num + 1) {
		//cout << r << endl;
		//printf("(%lld %lld %lld)", r, fpow(10, r, mod), mod);
		if (fpow(10, r, mod) == 1)
			ans.push_back(r);
		return ;
	}
	dfs(dep+1, r);
	for (int i = 1; i <= show[dep]; ++i) {
		r = r * seq[dep];
		dfs(dep+1, r);
	}
}

int solve() {
	memset(show, 0, sizeof show);

	int t = 8;
	while (L % 2 == 0) {
		if (t == 1) return 0;
		t /= 2;
		L /= 2;
	}
	if (L % 5 == 0) return 0;
	L *= 9;
	mod = L;
	//cout << mod << endl;

	for (int i = 1; i <= cnt; ++i) {
		while (L % pri[i] == 0)
			++show[pri[i]], L /= pri[i];
	}
	if (L != 1) phi = L - 1;
	else phi = 1;
	for (int i = 2; i < maxPri; ++i)
		if (show[i] != 0) {
			--show[i];
			while (show[i] != 0)
				phi *= i, --show[i];
			phi *= i - 1;
		}
	//printf("%lld\n", phi);

	memset(show, 0, sizeof show);
	for (int i = 1; i <= cnt; ++i) {
		while (phi % pri[i] == 0)
			++show[pri[i]], phi /= pri[i];
	}
	num = 0;
	if (phi > 1) {
		seq[++num] = phi, show[num] = 1;
	}
	for (int i = 2; i < maxPri; ++i)
		if (show[i] != 0)
			seq[++num] = i, show[num] = show[i];
	ans.clear();
	/*
	printf("%d\n", num);
	for (int i = 1; i <= num; ++i)
		printf("%d ", seq[i]);
	puts("");
	for (int i = 1; i <= num; ++i)
		printf("%d ", show[i]);
	puts("");
	*/
	dfs(1, 1);
	//puts("");
	sort(ans.begin(), ans.end());
	if (ans.size() == 0) return 0;
	return ans[0];
}

int main() {

	
	
#ifndef ONLINE_JUDGE
	freopen("g.in", "r", stdin);
	freopen("g.out", "w", stdout);
#endif

	init();

	int tCase = 0;
	while (cin >> L) {
		if (L == 0) break;
		++tCase;
		printf("Case %d: %d\n", tCase, solve());
	}
	
	return 0;
}
