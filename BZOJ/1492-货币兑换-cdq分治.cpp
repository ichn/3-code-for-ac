#include <cstdio>
#include <cstring>
#include <algorithm>
#define max(a, b) ((a) < (b) ? (b) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))
using std::sort;
using std::merge;
using std::swap;
using std::make_pair;
typedef double DB;
const int maxn = 200000 + 20;
#define x first
#define y second
typedef std::pair<DB, DB> point;
point f[maxn], tmp[maxn];
DB a[maxn], b[maxn], c[maxn], rate[maxn], profit[maxn], ans;

int n, pos[maxn], stack[maxn];

bool cmp(int x, int y) {
	return c[x] > c[y];
}
DB cross(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
DB getprofit(int l, int i) {
	return f[l].x * a[i] + f[l].y * b[i];
}
void solve(int l, int r) {
	if(l == r) {
		ans = max(ans, profit[l]);
		f[l].y = ans / (a[l] * rate[l] + b[l]);
		f[l].x = f[l].y * rate[l];
		return ;
	}
	int mid = (l + r) >> 1;
	memcpy(stack + l, pos + l, sizeof (int) * (r - l + 1));
	for(int k = l, i = l, j = mid + 1; k <= r; ++k) {
		if(stack[k] <= mid) {
			pos[i++] = stack[k];
		} else {
			pos[j++] = stack[k];
		}
	}
	solve(l, mid);
	int top = 0;
	for(int i = l; i <= mid; ++i) {
		while(2 <= top && cross(f[stack[top - 1]], f[stack[top]], f[i]) >= 0) {
			--top;
		}
		stack[++top] = i;
	}
	for(int k = 1, i = mid + 1; i <= r; ++i) {
		for(; k < top && getprofit(stack[k], pos[i]) < getprofit(stack[k + 1], pos[i]); ++k);
		profit[pos[i]] = max(profit[pos[i]], getprofit(stack[k], pos[i]));
	}
	solve(mid + 1, r);
	merge(f + l, f + mid + 1, f + mid + 1, f + r + 1, tmp + l);
	memcpy(f + l, tmp + l, sizeof (point) * (r - l + 1));
}

int main() {
	scanf("%d%lf", &n, &ans);
	for(int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &a[i], &b[i], &rate[i]);
		c[i] = -a[i] / b[i];
		pos[i] = i;
	}
	sort(pos + 1, pos + n + 1, cmp);
	solve(1, n);
	printf("%.3lf\n", ans);

	return 0;
}

