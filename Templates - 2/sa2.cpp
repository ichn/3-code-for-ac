
const int maxn = 1e6 + 100;
char str[maxn];
int n, m;
int sum[maxn], rank[maxn], sa[maxn], height[maxn];

// 对c进行排序
void sort(int *a, int *b, int *c, int n, int m) {
	rep(i, 0, m) sum[i] = 0;
	rep(i, 1, n) ++sum[c[i]];
	rep(i, 1, m) sum[i] += sum[i - 1];
	red(i, n, 1) b[sum[c[a[i]]]--] = a[i];
}

void get_sa() {
	static int x[maxn], y[maxn];
	rep(i, 1, n) rank[i] = i, x[i] = str[i];
	sort(rank, sa, x, n, 256);
	rank[sa[1]] = 1;
	rep(i, 2, n)
		rank[sa[i]] = rank[sa[i - 1]] + (x[sa[i - 1]] != x[sa[i]]);
	for(int i = 1; i <= n; i <<= 1) {
		rep(j, 1, n)
			sa[j] = j, x[j] = rank[j], y[j] = j + i <= n ? rank[i + j] : 0;
		sort(sa, rank, y, n, n), sort(rank, sa, x, n, n);
		rank[sa[1]] = 1;
		rep(j, 2, n)
			rank[sa[j]] = rank[sa[j - 1]] + (x[sa[j]] != x[sa[j - 1]] || y[sa[j]] != y[sa[j - 1]]);
		if(rank[sa[n]] == n) break;
	}
}

void get_height() {
	for(int i = 1, j = 0; i <= n; ++i) {
		if(j > 0) --j;
		if(rank[i] != 1)
			while(str[i + j] == str[sa[rank[i] - 1] + j])
				++j;
		height[rank[i]] = j;
	}
}

