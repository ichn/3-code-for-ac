#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

#define rep(i, j, k) for (int i = j; i < k; ++i)
#define rgo(i, j, k) for (int i = j; i <= k; ++i)

queue<int> que;
queue<int> que2;
const int maxN = 10000 + 100;
const int maxM = 1000000 + 100;
int n, m;

int cnt[maxN];
bool vis[maxN];

set<pair<int, int> > dis;

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = 0;
	while (scanf("%d %d", &n, &m) != EOF) {
		if (n + m == 0)
			break;
		dis.clear();
		rep(i, 0, m) {
			int u, v;
			scanf("%d %d", &u, &v);
			dis.insert(make_pair(u, v));
			dis.insert(make_pair(v, u));
		}
		while (!que.empty())
			que.pop();
		memset(vis, false, sizeof vis);
		que.push(1);
		vis[1] = true;
		while (!que2.empty())
			que2.pop();

		static int ttt[maxN];
		for (int i = 2; i <= n; ++i)
			ttt[i] = i;
		random_shuffle(ttt+2, ttt+n);
		for (int i = 2; i <= n; ++i)
			que2.push(ttt[i]);


		while (!que.empty()) {
			int u = que.front();
			que.pop();
			int cnt = 0;
			int ssss = que2.size();
			int cnt2 = 0;
			while (!que2.empty()) {
				++cnt;
				int i = que2.front();
				que2.pop();
				if (!vis[i] && dis.find(make_pair(u, i)) == dis.end()) {
					vis[i] = true;
					que.push(i);
					++cnt2;
					if (cnt2 > 10) {
						que.push(u); break;
					}
				}
				if (!vis[i])
				que2.push(i);
				if (cnt > ssss)
					break;
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += vis[i];

		printf("Case %d: %d\n", ++tCase, ans-1);
	}



	return 0;
}
