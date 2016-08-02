#include <bits/stdc++.h>
using namespace std;

class WinterAndPresents {
	int n;
	long long calc(int num, vector<int>&a, vector<int>&o) {
		long long ret = n * num;
		long long ca = 0;
		for (int i = 0; i < n; ++i) {
			ca += min(num, a[i]);
		}
		long long co = 0;
		for (int i = 0; i < n; ++i) {
			co += min(num, o[i]);
		}
		return ca - (ret - co) + 1;
	}

public:
	long long getNumber(vector<int> a, vector<int> o) {
		n = (int)a.size();
		int rk = INT_MAX;
		for (int i = 0; i < n; ++i)
			rk = min(rk, a[i] + o[i]);
		long long ret = 0;
		for (int i = 1; i <= rk; ++i) {
			ret += calc(i, a, o);
		}
		return ret;
	}
};
