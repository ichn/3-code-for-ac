#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;

char s1[3333], s2[3333];

struct TreeNode {
	vector<TreeNode*> son;
} pool[6666], *loc, *r1, *r2;

int main() {

	scanf("%d", &n);
	while (n--) {
		scanf("%s", s1);
		scanf("%s", s2);
		loc = pool;
		r1 = NULL, r2 = NULL;
		bui
	}

	return 0;
}

