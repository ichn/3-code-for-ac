#include <bits/stdc++.h>
using namespace std;

class ORSolitaire {
	int n;
	int d[51], c;
public:
	int getMinimum(vector<int> num, int goal) {
		n = (int)num.size();
		c = 0;
		for (int i = 0; i < n; ++i) {
			if ((num[i] & goal) == num[i])
				d[++c] = num[i];
		}
		int ans = n;
		for (int i = 0; i < 31; ++i) {
			if ((goal >> i) & 1) {
				int t = 0;
				for (int j = 1; j <= c; ++j)
					if ((d[j] >> i) & 1)
						++t;
				ans = min(ans, t);
			}
		}
		return ans;
	}
};
