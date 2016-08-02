#include <bits/stdc++.h>
using namespace std;

const int maxm = 5200;
const int maxn = 20000;
class DLX {
	public:
		int n, o;
		int col[maxn], row[maxn], s[maxm];
		int L[maxn], R[maxn], U[maxn], D[maxn];
		int ans[maxn], cnt;
		void init(int n) {
			this->n = n;
			for (int i = 0; i <= n; ++i)
				U[i] = i, D[i] = i, L[i] = i-1, R[i] = i+1;
			L[0] = n, R[n] = 0;
			o = n+1;
			memset(s, 0, sizeof s);
		}

		void add_row(int r, int *C) {
			int rec = o;
			for (int i = 1; i <= C[0]; ++i) {
				int c = C[i];
				L[o] = o-1, R[o] = o+1, D[o] = c, U[o] = U[c], D[U[c]] = o, U[c] = o;
				col[o] = c, row[o] = r;
				++s[c], ++o;
			}
			R[o-1] = rec, L[rec] = o-1;
		}

#define FOR(i, A, s) for (int i = A[s]; i != s; i = A[i])
		void remove(int c) {
			L[R[c]] = L[c];
			R[L[c]] = R[c];
			FOR(i, D, c) {
				FOR(j, R, i)
					U[D[j]] = U[j],
					D[U[j]] = D[j],
					--s[col[j]];
			}
		}
		void restore(int c) {
			FOR(i, U, c) {
				FOR(j, L, i)
					++s[col[j]],
					U[D[j]] = j,
					D[U[j]] = j;
			}
			R[L[c]] = c;
			L[R[c]] = c;
		}


		inline bool dfs(int d) {
			if (R[0] == 0) {
				cnt = d;
				return true;
			}
			int p = R[0];
			FOR(j, R, 0)
				if (s[j] < s[p])
					p = j;
			remove(p);
			FOR(i, D, p) {
				ans[d] = row[i];
				FOR(j, R, i)
					remove(col[j]);
				if (dfs(d+1)) return true;
				FOR(j, L, i)
					restore(col[j]);
			}
			restore(p);
			return false;
		}

		bool solve() {
			cnt = 0;
			if (!dfs(0))
				return false;
			return true;
		}
};



const int d = 4;
const int s = d*d;

class Sudoku {
	DLX solver;
	int encode(int a, int b, int c) {
		return ((a<<8)|(b<<4)|c)+1;
	}
	void decode(int d, int &a, int &b, int &c) {
		--d;
		c = d % 16, d >>= 4;
		b = d % 16, d >>= 4;
		a = d;
	}

	public:
	int sd[s+1][s+1], ans[s+1][s+1];
	int c[maxn];
	void solve() {
		solver.init(1024);
		for (int i = 0; i < s; ++i)
			for (int j = 0; j < s; ++j)
				for (int k = 0; k < s; ++k) 
					if (sd[i][j] == 0 || sd[i][j] == k+1) {
						c[0] = 0;
						c[++c[0]] = encode(0, i, j);
						c[++c[0]] = encode(1, i, k);
						c[++c[0]] = encode(2, j, k);
						c[++c[0]] = encode(3, ((i>>2)<<2)+(j>>2), k);
						solver.add_row(encode(i, j, k), c);
					}
		solver.solve();
		for (int i = 0; i < solver.cnt; ++i) {
			int a, b, c;
			decode(solver.ans[i], a, b, c);
			sd[a][b] = c;
		}
		for (int i = 0; i < s; ++i) {
			for (int j = 0; j < s; ++j)
				printf("%c", sd[i][j]+'A');
			puts("");
		}
	}
} sd;

int gc() {
	char c = getchar();
	while (c == ' ' || c == '\n' || c == '\r')
		c = getchar();
	return c == '-' ? 0 : c - 'A' + 1;
}

int main() {
	freopen("sudoku.in", "r", stdin);
	freopen("sudoku.out", "w", stdout);
	for (int i = 0; i < s; ++i)
		for (int j = 0; j < s; ++j)
			sd.sd[i][j] = gc();
	sd.solve();

	return 0;
}

