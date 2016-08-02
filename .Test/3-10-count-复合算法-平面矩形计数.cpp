#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 100;

struct Point {
	int x, y;
	void read() {
		scanf("%d%d",&x, &y);
	}
	Point() {}
	Point(int x, int y):x(x), y(y) {}
	bool operator < (const Point &rhs) const {
		return x < rhs.x || (x==rhs.x && y < rhs.y);
	}
} p[maxn];
vector<int> num;


int vis[maxn];

vector<int> X[maxn];

vector<int> a, b;


int n, nX, nY, nA, nB;
int is_b[maxn];

//map<int, int> mp[maxn];

vector<Point> s;
int sCnt[maxn], is[maxn], step[maxn];

int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		p[i].read();

	for (int i = 1; i <= n; ++i)
		num.push_back(p[i].x);
	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end());
	nX = num.size();
	for (int i = 1; i <= n; ++i)
		p[i].x = lower_bound(num.begin(), num.end(), p[i].x) - num.begin() + 1;

	num.clear();

	for (int i = 1; i <= n; ++i)
		num.push_back(p[i].y);

	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end());
	nY = num.size();
	for (int i = 1; i <= n; ++i)
		p[i].y = lower_bound(num.begin(), num.end(), p[i].y) - num.begin() + 1;

	// 跪跪跪
	// 妈呀太神了

	//X.resize(nX+1);
	//Y.resize(nY+1);


	for (int i = 1; i <= n; ++i) {
		X[p[i].x].push_back(p[i].y);
		//[p[i].y].push_back(p[i].x);
	}
	for (int i = 1; i <= nX; ++i)
		sort(X[i].begin(), X[i].end());

	unsigned int D = 1;
	while (D*D < (unsigned)n)
		++D;
	for (int i = 1; i <= nX; ++i) {
		if (X[i].size() >= D)
			a.push_back(i);
	}
	nA = a.size();


	long long ans = 0;
	for (int i = 0; i < nA; ++i) {
		int p = a[i];
		int nT = X[p].size();
		for (int j = 0; j < nT; ++j)
			vis[X[p][j]] = 1;
		for (int j = 1; j <= nX; ++j)
			if (p < j || X[j].size() < D) {
				int nR = X[j].size();
				int cnt = 0;
				for (int k = 0; k < nR; ++k)
					cnt += vis[X[j][k]];
				ans += (long long)cnt*(cnt-1)/2;
			}
		for (int j = 0; j < nT; ++j)
			vis[X[p][j]] = 0;
	}
	/*
	 * 复杂度分析1（错误）：
	 *	恩，最多有n/d个a类对吧，
	 *	两两枚举就是$O(n)$对吧，
	 *	但是。。每扫一次就是$O(n)$的。。此奥
	 *
	 * 复杂度分析2（正确）：
	 *	恩，最多有n/d个a对吧，
	 *	枚举每一个就是$O(n/d)$，
	 *	枚举其他相当于每个点都扫一遍对吧，
	 *	所以复杂度是$O(n^2/d)$对吧，
	 *	取d=sqrt(n)就是最优的！（这句话是错的！要考虑b类才能得出这个结论）
	 * 
	 * 吱吱：我复杂度分析的好。。
	 * */

	/*
	 * 复杂度分析3（错误）：
	 *  恩，b类中每列最多d个元素对吧，
	 *  两两枚举做线段就是$O(n)$个对吧，
	 *  然后枚举所有的列。。卧槽最坏有$O(n)$条！
	 * 
	 * 复杂度分析4（正确）：
	 *  恩，取所有的点分别做线段的左端点，最多有$O(n)$个，
	 *  然后每个点只会在一个列中，然后这个列元素是$O(n/d)$的，取做右端点，
	 *  所以就是$O(n^2/d)$对吧，
	 *  取d=sqrt(n)就是最优的！
	 *
	 * 对于b类的空间优化：
	 *	考虑所有右端点为k的线段，hash其他的端点
	 * */

	//ans /= 2;

	//printf("%lld\n", ans);

	//for (int i = 1; i <= n; ++i) {
	//	if (is_b[p[i].x]) {
	//		int nT = X[p[i].x].size();
	//		for (int j = 0; j < nT; ++j) {
	//			if (X[p[i].x][j] < p[i].y) {
	//				ans += mp[X[p[i].x][j]][p[i].y];
	//				mp[X[p[i].x][j]][p[i].y]++;
	//			}
	//		}
	//	}
	//}
	//for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
	//	ans += it->second*(it->second-1)/2;
	//}
	
	for (int i = 1; i <= n; ++i) {
		if (X[p[i].x].size() < D)
			s.push_back(Point(p[i].y, p[i].x));
	}
	sort(s.begin(), s.end());
	memset(is, -1, sizeof is);
	int nS = s.size();
	for (int i = 0; i < nS; ) {
		int x = s[i].x;
		for (; i<nS && s[i].x==x; ++i) {
			++step[s[i].y];
			for (int j = step[s[i].y]; j < (int)X[s[i].y].size(); ++j) {
				int t = X[s[i].y][j];
				if (is[t] == x) {
					ans += sCnt[t];
					++sCnt[t];
				} else {
					is[t] = x;
					sCnt[t] = 1;
				}
			}
		}
	}
	printf("%lld\n", ans);

	return 0;
}

