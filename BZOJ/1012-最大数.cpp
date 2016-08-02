//{HEADS
#define FILE_IN_OUT
#define debug
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <string>
#define REP(i, j) for (int i = 1; i <= j; ++i)
#define REPI(i, j, k) for (int i = j; i <= k; ++i)
#define REPD(i, j) for (int i = j; 0 < i; --i)
#define STLR(i, con) for (int i = 0, sz = con.size(); i < sz; ++i)
#define STLRD(i, con) for (int i = con.size() - 1; 0 <= i; --i)
#define CLR(s) memset(s, 0, sizeof s)
#define SET(s, v) memset(s, v, sizeof s)
#define mp make_pair
#define pb push_back
#define PL(k, n) for (int i = 1; i <= n; ++i) { cout << k[i] << ' '; } cout << endl
#define PS(k) STLR(i, k) { cout << k[i] << ' '; } cout << endl
using namespace std;
#ifdef debug
#ifndef ONLINE_JUDGE
	const int OUT_PUT_DEBUG_INFO = 1;
#endif
#endif
#ifdef ONLINE_JUDGE
	const int OUT_PUT_DEBUG_INFO = 0;
#endif
#define DG if(OUT_PUT_DEBUG_INFO)
void FILE_INIT(string FILE_NAME) {
#ifdef FILE_IN_OUT
#ifndef ONLINE_JUDGE 
	freopen((FILE_NAME + ".in").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);

#endif
#endif
}
typedef long long LL;
typedef double DB;
typedef pair<int, int> i_pair;
const int INF = 0x3f3f3f3f;
//}

const int maxn = 200000 + 10;

int m, d;

struct Things {
	int pos, val;
	Things() {}
	Things(int pos, int val):pos(pos), val(val) {}
	void print() {
		printf("%d %d\n", pos, val);
	}
}S[maxn];
int tail = 0;
/*{ 获取字符*/
char gchar() {
	char ret = getchar();
	for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
	return ret;
}
/*}*/

int main() {
	FILE_INIT("BZOJ1012");

	scanf("%d%d", &m, &d);
	char ope;
	int t, rec = 0, cnt = 0;
	REP(i, m) {
		ope = gchar();
		scanf("%d", &t);
		if(ope == 'A') {
			S[++tail] = Things(++cnt, (rec + t) % d);
			DG S[tail].print();
			for(; 1 < tail && S[tail - 1].val <= S[tail].val; S[tail - 1] = S[tail], --tail);
			DG S[tail].print();
		} else {
			int l = 1, r = tail;
			DG printf("l = %d r = %d\n", l, r);
			while(l < r) {
				int mid = (l + r) >> 1;
				if(cnt - S[mid].pos + 1 <= t) {
					r = mid;
				} else {
					l = mid + 1;
				}
			}
			rec = S[l].val;
			printf("%d\n", rec);
		}
	}

	return 0;
}

