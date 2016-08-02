#include <bits/stdc++.h>
using namespace std;

class LotsOfLines {
	int sum[1200][1200];
public:
	long long countDivisions(int A, int B) {
		for (int i = 1; i < A; ++i)
			for (int j = 1; j < B; ++j)
				sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + (__gcd(i, j)==1);
		long long ans = 1;
		for (int i = 0; i < A; ++i)
			for (int j = 0; j < B; ++j) {
				++ans;
				ans += (!!i) * (sum[i][j] + 1 + sum[i][B-j-1]);
			}
		return ans;
	}
};

#ifdef love_lhy
int main() {
	cout << (new LotsOfLines)->countDivisions(2, 2) << endl;
}
#endif
/*
比较厉害的想法：
加入一条线产生的影响，量化
求互质数对可以直接预处理
*/
