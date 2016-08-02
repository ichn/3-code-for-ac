#include <bits/stdc++.h>
#define rep(_i, _j) for(int _i = 1; _i <= _j; ++_i)
const int inf = 0x3f3f3f3f;
typedef long long LL;
typedef double DB;
using namespace std;
const int maxn = 10000 + 100;
struct splay_node {
	int fa, ch[2];
	bool rev;
	splay_node() {
		rev = 0;
		fa = ch[0] = ch[1] = 0;
	}
} T[maxn];
bool is_root(int x) {
	return !T[x].fa || (T[T[x].fa].ch[0] != x && T[T[x].fa].ch[1] != x);
}
void push_down(int x) {
	if(T[x].rev) {
		T[x].rev = false;
		if(T[x].ch[0]) T[T[x].ch[0]].rev ^= 1;
		if(T[x].ch[1]) T[T[x].ch[1]].rev ^= 1;
		swap(T[x].ch[0], T[x].ch[1]);
	}
}
void rot(int x, int d) {
	int y = T[x].fa, z = T[y].fa;
	T[y].ch[d ^ 1] = T[x].ch[d];
	if(T[x].ch[d] != 0) T[T[x].ch[d]].fa = y;
	T[x].ch[d] = y;
	if(!is_root(y)) {
		T[z].ch[T[z].ch[1] == y] = x;
	}
	T[x].fa = z;
	T[y].fa = x;
}
void splay(int x) {
	push_down(x);
	while(!is_root(x)) {
		int y = T[x].fa, z = T[y].fa;
		push_down(z), push_down(y), push_down(x);
		int rx = T[y].ch[0] == x, ry = T[z].ch[0] == y;
		if(is_root(y)) {
			rot(x, rx);
		} else {
			rot(rx == ry ? y : x, rx);
			rot(x, ry);
		}
	}
}
void access(int x) {
	for(int p = x, x = 0; p != 0; x = p, p = T[p].fa) {
		splay(p);
		T[p].ch[1] = x;
	}
}
int find(int a) {
	for(access(a), splay(a); T[a].ch[0] != 0; a = T[a].ch[0], push_down(a));
	return a;
}
int n, m;
char s[10];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		int a, b;
		scanf("%s%d%d", s, &a, &b);
		if(!strcmp(s, "Query")) {
			puts(find(a) == find(b) ? "Yes" : "No");
		} else if(!strcmp(s, "Destroy")) {
			access(a), splay(a), T[a].rev = 1;
			access(b), splay(b), T[a].fa = T[b].ch[0] = 0;
		} else {
			access(a), splay(a), T[a].rev = 1;
			T[a].fa = b;
		}
	}
 
	return 0;
}
