#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000000 + 10000;
struct Node {
	Node *go[26], *suf;
	int l, sz;
} pool[maxn], *loc, *root, *last;

Node*newNode(int l) {
	loc->l = l + 1;
	loc->sz = 0;
	memset(loc->go, 0, sizeof loc->go);
	loc->suf = NULL;
	return loc++;
}

void init() {
	loc = pool;
	root = newNode(0);
	last = root;
}

void append(int w) {
	Node*p = last, *np = newNode(p->l + 1);
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p) np->suf = root;
	else {
		Node*q = p->go[w];
		if (q->l == p->l+1) {
			np->suf = q;
		} else {
			Node*nq = newNode(p->l+1);
			memcpy(nq->go, q->go, sizeof q->go);
			nq->suf = q->suf;
			q->suf = np->suf = nq;
			nq->sz = q->sz;
			while (p && p->go[w] == q) {
				p->go[w] = nq, p = p->suf;
			}
		}
	}
	last = np;
	while (np)
		++np->sz, np = np->suf;
}

char str[maxn];

void decode(char s[],int mask) {  
	int i,n=strlen(s);
	for(i=0; i<n; i++) {  
		mask=(mask*131+i)%n;  
		swap(s[i],s[mask]);  
	}  
}  

int main() {

	
//	freopen("2555.in", "r", stdin);
//	freopen("2555.out", "w", stdout);

	int t, n, ans;
	static char ope[10];
	scanf("%d", &t);
	scanf("%s", str);
	n = strlen(str);
	init();
	for (int i = 0; i < n; ++i)
		append(str[i] - 'A');

	int mask = 0;
	while (t--) {
		scanf("%s %s", ope, str);
		decode(str, mask);
		n = strlen(str);
		if (ope[0] == 'Q') {
			Node*c = root;
			int result = 0;
			for (int i = 0; i < n; ++i) {
				c = c->go[str[i] - 'A'];
				if (!c) {
					result = -1;
					break;
				}
			}
			if (result == -1) {
				ans = 0;
			} else {
				ans = c->sz;
			}
			mask ^= ans;
			printf("%d\n", ans);
		} else {
			for (int i = 0; i < n; ++i)
				append(str[i] - 'A');
		}
	}

	return 0;
}
