#include <bits/stdc++.h>
using namespace std;

struct ACAutomata {
	static const int maxNode = 1000000;
	static const int maxStat = 26;

	short ch[maxNode][maxStat];
	int val[maxNode], fail[maxNode];
	int lst[maxNode];
	int sz;

	void init() {
		sz = 0;
	}

	int id(char c) {
		return c - 'a';
	}

	void insert(char *s, int v) {
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; ++i) {
			int c = id(s[i]);
			if (ch[u][c] == 0) {
				memset(ch[sz], 0, sizeof ch[sz]);
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	queue<int> q;
	void getFail() {
		while (!q.empty()) q.pop();
		fail[0] = 0;
		for (int c = 0; c < 4; ++c) {
			int u = ch[0][c];
			if (u) {
				fail[u] = 0, q.push(u), lst[u] = 0;
			}
		}
		while (!q.empty()) {
			int r = q.front(); q.pop();
			for (int c = 0; c < 4; ++c) {
				int u = ch[r][c];
				if (!u) {
					ch[r][c] = ch[fail[r]][c];
					continue;
				}
				q.push(u);
				int v = fail[r];
				while (v && !ch[v][c]) v = fail[v];
				fail[u] = ch[v][c];
				lst[u] = val[fail[u]] ? fail[u] : lst[fail[u]];
			}
		}
	}
};

