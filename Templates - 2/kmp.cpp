#include <bits/stdc++.h>
using namespace std;

int n, m;
char s[10000], t[10000];
int next[10000];

void get_next() {
	next[0] = -1;
	for (int i = 0, j = -1; i < n; ) {
		if (j == -1 || s[j] == s[i]) {
			++j, ++i;
			next[i] = s[j] == s[i] ? next[j] : j;
		} else j = next[j];
	}
}

void get() {
	for (int i = 0, j = 0; i < m; ) {
		if (j == -1 || s[j] == t[i]) {
			++i, ++j;
			if (j == n) {
				printf("%d ", i - j);
			}
		} else j = next[j];
	}
}

int main() {
	scanf("%s\n%s", s, t);
	n = strlen(s), m = strlen(t);
	get_next();
	get();
	return 0;
}
