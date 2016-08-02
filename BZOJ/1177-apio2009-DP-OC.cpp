#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int max_n = 1510;
const int inf = 2e9;
int n, m, k;
int sum[max_n][max_n], max_s[max_n][max_n][4], l_max_s[max_n][2];
inline int getnum() {
	int ans = 0; char c; bool flag = false;
	while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
	if (c == '-') flag = true; else ans = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ans = ans * 10 + c - '0';
	return ans * (flag ? -1 : 1);
}
inline int calc_s(int _x1, int _y1, int _x2, int _y2) {
	int x1 = min(_x1, _x2);
	int x2 = max(_x1, _x2);
	int y1 = min(_y1, _y2);
	int y2 = max(_y1, _y2);

	if (!(1 <= x1 && x1 <= n)) return 0;
	if (!(1 <= x2 && x2 <= n)) return 0;
	if (!(1 <= y1 && y1 <= m)) return 0;
	if (!(1 <= y2 && y2 <= m)) return 0;
	return (ll)sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
inline void calc_max_s() {
	// 0
	for (int i = k; i <= n; i++)
		for (int j = m - k + 1; j >= 1; j--)
			max_s[i][j][0] = max(max(max_s[i][j + 1][0], max_s[i - 1][j][0]), calc_s(i, j, i - k + 1, j + k - 1));

	// 1
	for (int i = k; i <= n; i++)
		for (int j = k; j <= m; j++)
			max_s[i][j][1] = max(max(max_s[i][j - 1][1], max_s[i - 1][j][1]), calc_s(i, j, i - k + 1, j - k + 1));

	// 2
	for (int i = n - k + 1; i >= 1; i--)
		for (int j = k; j <= m; j++)
			max_s[i][j][2] = max(max(max_s[i][j - 1][2], max_s[i + 1][j][2]), calc_s(i, j, i + k - 1, j - k + 1));

	// 3
	for (int i = n - k + 1; i >= 1; i--)
		for (int j = m - k + 1; j >= 1; j--)
			max_s[i][j][3] = max(max(max_s[i][j + 1][3], max_s[i + 1][j][3]), calc_s(i, j, i + k - 1, j + k - 1));

	for (int i = k; i <= n; i++)
		for (int j = k; j <= m; j++) {
			l_max_s[i][0] = max(l_max_s[i][0], calc_s(i, j, i - k + 1, j - k + 1));
			l_max_s[j][1] = max(l_max_s[j][1], calc_s(i, j, i - k + 1, j - k + 1));
		}
}
inline void update(int &a, int b) {
	a = max(a, b);
}
int main() {
	n = getnum(); m = getnum(); k = getnum();
	int k2 = k * 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int x = getnum();
			sum[i][j] = (ll)sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + x;
		}
	}

	calc_max_s();

	int max_ans = 0;

	//  |  |
	//  |  |
	//  |  |
	for (int i = k; i <= m - k2; i++) {
		int max_mid = 0;
		for (int j = i + k; j <= m - k; j++) {
			update(max_mid, l_max_s[j][1]);
			update(max_ans, max_s[n][i][1] + max_mid + max_s[n][j + 1][0]);
		}
	}

	//  ----
	// 
	//  ----
	for (int i = k; i <= n - k2; i++) {
		int max_mid = 0;
		for (int j = i + k; j <= n - k; j++) {
			update(max_mid, l_max_s[j][0]);
			update(max_ans, max_s[i][m][1] + max_mid + max_s[j + 1][m][2]);
		}
	}

	// 1| 0
	//  |---
	//  | 3
	for (int i = k; i <= m - k; i++)
		for (int j = k; j <= n - k; j++)
			update(max_ans, max_s[n][i][1] + max_s[j][i + 1][0] + max_s[j + 1][i + 1][3]);

	// 1 |0
	// --|
	// 2 |
	for (int i = k; i <= m - k; i++)
		for (int j = k; j <= n - k; j++)
			update(max_ans, max_s[j][i][1] + max_s[j + 1][i][2] + max_s[n][i + 1][0]);

	// 1 |0
	// ----
	//   2
	for (int i = k; i <= n - k; i++)
		for (int j = k; j <= m - k; j++)
			update(max_ans, max_s[i][j][1] + max_s[i][j + 1][0] + max_s[i + 1][m][2]);

	// 1
	// ----
	// 2 |3
	for (int i = k; i <= n - k; i++)
		for (int j = k; j <= m - k; j++)
			update(max_ans, max_s[i][m][1] + max_s[i + 1][j][2] + max_s[i + 1][j + 1][3]);

	cout << max_ans << endl;
}
