#include <bits/stdc++.h>
using namespace std;

int dp[10000 + 10], fa[10000 + 10];
int n, m, X, Y;
int x[1010][2], y[1010][2], a, b;
vector<pair<int, int> > pos[10000 + 10];

int main() {
#ifdef lol
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
#endif

	scanf("%d %d", &X, &Y);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d %d %d %d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
	scanf("%d %d", &a, &b);
	for (int i = 1; i <= n; ++i)
		pos[x[i][1]].push_back(make_pair(x[i][0], i));
	vector<int> ans;
	dp[0] = 1;


	if (x[b][0] < x[a][0]) {
		swap(a, b);
	}

	if (x[a][1] > x[b][0]) {
		goto end;
	}


	dp[x[a][1]] = 1;
	dp[x[b][1]] = 1;
	fa[x[b][1]] = b;
	fa[x[a][1]] = a;

	for (int i = 0; i <= x[a][0]; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}
	if (dp[x[a][0]] == 0) {
		goto end;
	}
	for (int i = x[a][1]; i <= x[b][0]; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (pos[i][j].first >= x[a][1] && dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}

	if (dp[x[b][0]] == 0) {
		goto end;
	}
	for (int i = x[b][1]; i <= X; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (pos[i][j].first >= x[b][1] && dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}

	//for (int i = 0; i <= X; ++i) {
	//	printf("%d ", dp[i]);
	//}
	//puts("");
	//for (int i = 0; i <= X; ++i) {
	//	printf("%d ", fa[i]);
	//}
	//puts("");

	ans.clear();
 	if (dp[X]) {
		int t = X;
		while (t != 0) {
			ans.push_back(fa[t]);
			t = x[fa[t]][0];
		}
		printf("%d\n", (int)ans.size());
		reverse(ans.begin(), ans.end());
		if (ans.size() != 0)
			printf("%d", ans[0]);
		for (int i = 1; i < (int)ans.size(); ++i)
			printf(" %d", ans[i]);
		puts("");
		return 0;
	}

end:

	memset(dp, 0, sizeof dp);
	memset(fa, 0, sizeof fa);

	dp[0] = 1;

	for (int i = 0; i <= Y; ++i)
		pos[i].clear();
	for (int i = 1; i <= n; ++i)
		pos[y[i][1]].push_back(make_pair(y[i][0], i));

	if (y[b][0] < y[a][0]) {
		swap(a, b);
	}

	if (y[a][1] > y[b][0]) {
		puts("-1");
		return 0;
	}

	dp[y[a][1]] = 1;
	dp[y[b][1]] = 1;
	fa[y[b][1]] = b;
	fa[y[a][1]] = a;

	for (int i = 0; i <= y[a][0]; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}
	if (dp[y[a][0]] == 0) {
		puts("-1");
		return 0;
	}
	for (int i = y[a][1]; i <= y[b][0]; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (pos[i][j].first >= y[a][1] && dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}
	if (dp[y[b][0]] == 0) {
		puts("-1");
		return 0;
	}
	for (int i = y[b][1]; i <= Y; ++i) {
		for (int j = 0; j < (int)pos[i].size(); ++j)
			if (pos[i][j].first >= y[b][1] && dp[pos[i][j].first])
				dp[i] = 1, fa[i] = pos[i][j].second;
	}

	ans.clear();
 	if (dp[Y]) {
		int t = Y;
		while (t != 0) {
			ans.push_back(fa[t]);
			t = y[fa[t]][0];
		}
		printf("%d\n", (int)ans.size());
		reverse(ans.begin(), ans.end());
		if (ans.size() != 0)
			printf("%d", ans[0]);
		for (int i = 1; i < (int)ans.size(); ++i)
			printf(" %d", ans[i]);
		puts("");
		return 0;
	}


	puts("-1");

	return 0;
}
