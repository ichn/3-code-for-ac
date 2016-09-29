#include <cstdio>

int f(int n) {
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;
	return f(n-1)+f(n-2);
}


int sort(数组a) {
	把数组a平均分成两个小数组b和c
	sort(b)
	sort(c)
	合并b和c得到数组d
	返回数组d
}
int main() {
	for (int i = 1; i <= 10; ++i)
		printf("%d ", f(i));
	return 0;
}
