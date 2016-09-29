#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

struct ACA {

	static const int maxAlpha = 4;
	static const int maxNode = 1e5 + 100;

	int ch[maxNode][maxAlpha], pa[maxNode], val[maxNode], len[maxNode], suf[maxNode];
	int que[maxNode], rt, loc, cnt, qh, qt;

	vector<pair<int, int> > pos;

	void iniNode(int p) {
		memset(ch[p], 0, sizeof ch[p]);
		val[p] = -1;
		suf[p] = 0;
	}

	int insStr(int *s, int l) {
		int u = 0;
		for (int i = 0; i < l; ++i) {
			if (!ch[u][s[i]]) {
				ch[u][s[i]] = ++loc;
				iniNode(loc);
			}
			u = ch[u][s[i]];
		}
		val[u] = cnt++;
		len[u] = l;
		return val[u];
	}

	void Bld() {
		qh = 0;
		qt = -1;
		for (int i = 0; i < maxAlpha; ++i)
			if (ch[rt][i]) {
				que[++qt] = ch[rt][i];
				pa[ch[rt][i]] = rt;
				suf[ch[rt][i]] = 0;
			}
		suf[0] = 0;
		pa[0] = 0;
		while (qh <= qt) {
			int u = que[qh++];
			for (int i = 0; i < maxAlpha; ++i) {
				if (!ch[u][i]) {
					ch[u][i] = ch[pa[u]][i];
					continue;
				}
				int s = ch[u][i];
				que[++qt] = s;
				int v = pa[u];
				while (v && !ch[v][i])
					v = pa[v];
				pa[s] = ch[v][i];
				suf[s] = (val[pa[s]] != -1) ? pa[s] : suf[pa[s]];
			}
		}
	}

	void Ini() {
		cnt = 0;
		loc = 0;
		rt = 0;
		iniNode(rt);
	}

	void print(int u, int p) {
		if (!u || u==-1) return ;
		pos.push_back(make_pair(val[u], p-len[u]+1));
		print(suf[u], p);
	}

	void Run(int *s, int l, vector<pair<int, int> > &res) {
		pos.clear();
		int u = 0;
		for (int i = 0; i < l; ++i) {
			u = ch[u][s[i]];
			if (val[u] != -1)
				print(u, i);
			else if (suf[u])
				print(suf[u], i);
		}
		res.resize(pos.size());
		for (int i = 0; i < (int)pos.size(); ++i)
			res[i] = pos[i];
	}

};

char str[5555];
string word[555];
int n;

int ww[5555];

void modify(char*s) {
	int l = strlen(s);
	for (int i = 0; i < l; ++i) {
		if (s[i] == 'A')
			ww[i] = 0;
		else if (s[i] == 'G')
			ww[i] = 1;
		else if (s[i] == 'T')
			ww[i] = 2;
		else if (s[i] == 'C')
			ww[i] = 3;
	}
}

int f[1111][1111];
void dpd(int &x, int b) {
	if (b < x) x = b;
}

int main() {

	ACA*a = (new ACA);

	int casNum = 0;
	while (scanf("%d", &n) != EOF && n != 0) {
		a->Ini();
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			word[i] = str;
			int l = strlen(str);
			modify(str);
			a->insStr(ww, l);
		}
		scanf("%s", str);
		int l = strlen(str);
		modify(str);
		a->Bld();
		memset(f, 0x3f, sizeof f);
		f[0][0] = 0;
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j <= a->loc; ++j) {
				for (int k = 0; k < 4; ++k) {
					if (a->val[a->ch[j][k]] == -1 && a->suf[a->ch[j][k]] == 0)
						dpd(f[i+1][a->ch[j][k]], f[i][j] + (k != ww[i]));
				}
			}
		}
		int ans = 0x3f3f3f3f;
		for (int i = 0; i <= a->loc; ++i)
			dpd(ans, f[l][i]);
		++casNum;
		printf("Case %d: %d\n", casNum, ans==0x3f3f3f3f?-1 : ans);
	}


	return 0;
}
