#include <bits/stdc++.h>
using namespace std;

const int maxNode = 100000;
const int Dim = 3;
#define X x[0]
#define Y x[1]
#define Z x[2]
struct Point {
	int x[Dim];
};

struct kd_node : public Point {
	kd_node *fa, *ch[2];
	Point mn, mx;
	kd_node() {
		fa = NULL;
		ch[0] = NULL;
		ch[1] = NULL;
	}
} pool[maxNode];

int _dim;
bool cmp(kd_node a, kd_node b) {
	return a.x[_dim] < b.x[_dim];
}

double dist(Point a, Point b) {
	double ret = 0.0;
	for (int i = 0; i < Dim; ++i) {
		ret += 1.0 * (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
	}
	return sqrt(ret);
}

kd_node ptns[maxNode];

void build(int l, int r, kd_node*&rt) {
	++_dim;
	if (_dim >= Dim) _dim -= Dim;
	int mid = (l + r) >> 1;
	nth_element(ptns + l, ptns + mid, ptns + r + 1, cmp);
	rt = ptns[mid];
	build(l, mid-1, rt->ch[0]);
	build(mid+1, r, rt->ch[1]);

}




int main() {
	freopen("kd.in", "r", stdin);
	freopen("kd.out", "w", stdout);

	return 0;
}
