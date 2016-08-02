#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
int sgn(double x) {
	return x < -eps ? -1 : eps < x;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y):x(x), y(y) {
	}
	bool operator < (const Point&rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	bool operator == (const Point&rhs) const {
		return !sgn(x - rhs.x) && !sgn(y - rhs.y);
	}
	Point operator - (Point rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator + (Point rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator * (double p) const {
		return Point(x * p, y * p);
	}
	Point operator / (double p) const {
		return Point(x / p, y / p);
	}
	Point operator & (double rad) {
		return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
	}
	double operator ^ (Point rhs) {
		return x * rhs.y - y * rhs.x;
	}
	double operator * (Point rhs) {
		return x * rhs.x + y * rhs.y;
	}
	double Length2() {
		return (*this) * (*this);
	}
	double Length() {
		return sqrt((*this) * (*this));
	}
	double Angle(Point rhs) {
		return acos((*this) * rhs / Length() / rhs.Length());
	}
	double Distance(Point rhs) {
		return (rhs - (*this)).Length();
	}
	Point operator ~ () {
		double l = Length();
		return Point(-y / l, x / l);
	}
} P;

struct Line {
	Point p, q, v;
	Line() {}
	Line(Point p, Point q):p(p), q(q) {
		v = q - p;
	}
	Point operator * (Line rhs) {
		Point u = p - rhs.p;
		double t = (rhs.v ^ u) / (v ^ rhs.v);
		return p + v * t;
	}
	Point operator ^ (Point rhs) {
		return p + v * (v * (rhs - p) / (v * v));
	}
	bool on
	double dist2p(Point rhs) {
		return fabs((rhs - p) ^ v) / v.Length();
	}
	double xdist2p(Point rhs) {
		if (p == q) return (rhs - p).Length();
		if (sgn((rhs - p) * (v)) < 0) return (rhs - p).Length();
		else if (sgn((rhs - q) * v) > 0) return (rhs - q).Length();
		else return dist2p(rhs);
	}
};




int main() {

	P = Point(2, 1);
	P = ~P;
	printf("%lf %lf\n", P.x, P.y);

	return 0;
}
