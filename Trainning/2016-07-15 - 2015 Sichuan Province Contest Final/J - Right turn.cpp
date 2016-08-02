#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct sta {
	int x, y, dir;
/*
 dir
 0 (0, 1)
 1 (1, 0)
 2 (0, -1)
 3 (-1, 0)
 */
	bool operator < (const struct sta&lhr) const {
		return x < lhr.x || (x == lhr.x && (y < lhr.y || (y == lhr.y && dir < lhr.dir)));
	}
	bool operator == (const struct sta&lhr) const {
		return x == lhr.x && y == lhr.y && dir == lhr.dir;
	}
	sta() {}
	sta(int x, int y, int dir):x(x), y(y), dir(dir) {}
};


set<sta> S;
sta cur_sta;

int n;

pair<int, int> obs[1000 + 10], tmp;

void solve() {
	int cnt = 0;
	while (true) {
		if (cur_sta.dir == 0) {
			tmp = make_pair(cur_sta.x, INF);
			for (int i = 0; i < n; ++i) {
				if (obs[i].first == cur_sta.x && obs[i].second < tmp.second && obs[i].second > cur_sta.y)
					tmp = obs[i];
			}
			if (tmp.second == INF) {
				printf("%d\n", cnt);
				return ;
			}
			++cnt;
			S.insert(cur_sta);
			cur_sta.x = tmp.first, cur_sta.y = tmp.second-1, ++cur_sta.dir, cur_sta.dir %= 4;
			if (S.find(cur_sta) != S.end()) {
				puts("-1");
				return ;
			}
		} else if (cur_sta.dir == 2)  {
			tmp = make_pair(cur_sta.x, -INF);
			for (int i = 0; i < n; ++i) {
				if (obs[i].first == cur_sta.x && obs[i].second > tmp.second && obs[i].second < cur_sta.y)
					tmp = obs[i];
			}
			if (tmp.second == -INF) {
				printf("%d\n", cnt);
				return ;
			}
			++cnt;
			S.insert(cur_sta);
			cur_sta.x = tmp.first, cur_sta.y = tmp.second+1, ++cur_sta.dir, cur_sta.dir %= 4;
			if (S.find(cur_sta) != S.end()) {
				puts("-1");
				return ;
			}
		} else if (cur_sta.dir == 1) {
			tmp = make_pair(INF, cur_sta.y);
			for (int i = 0; i < n; ++i) {
				if (obs[i].second == cur_sta.y && obs[i].first < tmp.first && obs[i].first > cur_sta.x)
					tmp = obs[i];
			}
			if (tmp.first == INF) {
				printf("%d\n", cnt);
				return ;
			}
			++cnt;
			S.insert(cur_sta);
			cur_sta.x = tmp.first-1, cur_sta.y = tmp.second, ++cur_sta.dir, cur_sta.dir %= 4;
			if (S.find(cur_sta) != S.end()) {
				puts("-1");
				return ;
			}
		} else if (cur_sta.dir == 3) {
			tmp = make_pair(-INF, cur_sta.y);
			for (int i = 0; i < n; ++i) {
				if (obs[i].second == cur_sta.y && obs[i].first > tmp.first && obs[i].first < cur_sta.x)
					tmp = obs[i];
			}
			if (tmp.first == -INF) {
				printf("%d\n", cnt);
				return ;
			}
			++cnt;
			S.insert(cur_sta);
			cur_sta.x = tmp.first+1, cur_sta.y = tmp.second, ++cur_sta.dir, cur_sta.dir %= 4;
			if (S.find(cur_sta) != S.end()) {
				puts("-1");
				return ;
			}
		}
	}
}

int main() {
#ifdef lol
	freopen("j.in", "r", stdin);
	freopen("j.out", "w", stdout);
#endif

	while (scanf("%d", &n) != EOF) {
		S.clear();
		cur_sta = sta(0, 0, 1);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &obs[i].first, &obs[i].second);
		}
		solve();
	}

	return 0;
}
