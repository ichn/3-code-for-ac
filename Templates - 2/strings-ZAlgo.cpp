// 线性计算字符串每个后缀与原串的LCP，用于匹配时W&P一下
static const int maxLen = 10000 + 100;
int z[maxLen];
void getZ(char*str) {
	int n = strlen(str);
	int L = 0, R = 0;
	z[0] = n;
	for （int i = 1; i < n; ++i) {
		if (R < i) {
			L = R = i;
			while (R < n && str[R-L] == str[R]) ++R;
			z[i] = R-L;
			--R;
		} else {
			int k = i-L;
			if (z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while (R < n && str[R-L] == str[R]) ++R;
				z[i] = R-L;
				--R;
			}
		}
	}
}
