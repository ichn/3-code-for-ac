#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef double TYPE;
#define Abs(x) (((x)>0)?(x):(-(x)))
#define Sgn(x) (((x)<0)?(-1):(1))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)<(b))?(a):(b))
#define EPS 1e-8
#define Infinity 1e+10
#define PI acos(-1.0)//3.14159265358979323846
TYPE Deg2Rad(TYPE deg){return (deg * PI / 180.0);}
TYPE Rad2Deg(TYPE rad){return (rad * 180.0 / PI);}
TYPE Sin(TYPE deg){return sin(Deg2Rad(deg));}
TYPE Cos(TYPE deg){return cos(Deg2Rad(deg));}
TYPE ArcSin(TYPE val){return Rad2Deg(asin(val));}
TYPE ArcCos(TYPE val){return Rad2Deg(acos(val));}
TYPE Sqrt(TYPE val){return sqrt(val);}

//��
struct POINT {
	TYPE x, y;
	POINT(TYPE xx = 0, TYPE yy = 0): x(xx), y(yy) {}
};
// ������ľ���
TYPE Distance(const POINT &a, const POINT &b) {
	return Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
//�߶�
struct SEG {
	POINT a ,b;
	SEG() {};
	SEG(POINT aa, POINT bb): a(aa), b(bb) {}
};
//ֱ��(����ʽ)
struct LINE {
	POINT a, b;
	LINE() {};
	LINE(POINT aa, POINT bb): a(aa), b(bb) {}
};
//ֱ��(һ��ʽ)
struct LINE2 {
	TYPE A,B,C;
	LINE2() {};
	LINE2(TYPE AA, TYPE BB, TYPE CC): A(AA), B(BB), C(CC) {}
};
//����ʽ��һ��ʽ
LINE2 Line2line(const LINE &L) {
	LINE2 L2;
	L2.A = L.b.y - L.a.y;
	L2.B = L.a.x - L.b.x;
	L2.C = L.b.x * L.a.y - L.a.x * L.b.y;
	return L2;
}
// ���÷���ֱ�� Ax + By + C =0 ��ϵ��
void Coefficient(const LINE &L, TYPE &A, TYPE &B, TYPE &C) {
	A = L.b.y - L.a.y;
	B = L.a.x - L.b.x;
	C = L.b.x * L.a.y - L.a.x * L.b.y;
}
void Coefficient(const POINT &p,const TYPE &a,TYPE &A,TYPE &B,TYPE &C) {
	A = Cos(a);
	B = Sin(a);
	C = - (p.y * B + p.x * A);
}
//ֱ���ཻ�Ľ���
POINT Intersection(const LINE &A, const LINE &B) {
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;
	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);
	POINT I;
	I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
	I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
	return I;
}
//�㵽ֱ�ߵľ���
TYPE Ptol(const POINT &p,const LINE2 &L) {
	return fabs(L.A * p.x + L.B * p.y + L.C)/Sqrt(L.A * L.A + L.B * L.B);
}
//���߶β��
TYPE Cross2(const SEG &p, const SEG &q) {
	return (p.b.x - p.a.x) * (q.b.y - q.a.y) - (q.b.x - q.a.x) * (p.b.y - p.a.y);
}
//�й����˵�O���,���й�,����p0->p1->p2������
TYPE Cross(const POINT &a, const POINT &b, const POINT &o) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
//�е�(ֵ���㣬ֱ��)
bool IsEqual(const TYPE &a, const TYPE &b) {
	return (Abs(a - b) < EPS);
}
bool IsEqual(const POINT & a, const POINT & b) {
	return IsEqual(a.x, b.x) && IsEqual(a.y, b.y);
}
bool IsEqual(const LINE & A, const LINE & B) {
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;
	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);
	return IsEqual(A1 * B2, A2 * B1) && IsEqual(A1 * C2, A2 * C1) && IsEqual(B1 * C2, B2 * C1);
}
// �жϵ��Ƿ����߶���
bool IsOnSeg(const SEG &seg, const POINT &p) {
	return (IsEqual(p, seg.a) || IsEqual(p, seg.b)) ||
		(((p.x - seg.a.x) * (p.x - seg.b.x) < 0 ||
		  (p.y - seg.a.y) * (p.y - seg.b.y) < 0) &&
		 (IsEqual(Cross(seg.b, p, seg.a), 0)));
}

//�ж������߶��Ƿ��ཻ���˵��غ����ཻ
bool IsIntersect(const SEG &u, const SEG &v) {
	return (Cross(v.a, u.b, u.a) * Cross(u.b, v.b, u.a) >= 0) &&
		(Cross(u.a, v.b, v.a) * Cross(v.b, u.b, v.a) >= 0) &&
		(Max(u.a.x, u.b.x) >= Min(v.a.x, v.b.x)) &&
		(Max(v.a.x, v.b.x) >= Min(u.a.x, u.b.x)) &&
		(Max(u.a.y, u.b.y) >= Min(v.a.y, v.b.y)) &&
		(Max(v.a.y, v.b.y) >= Min(u.a.y, u.b.y));
}
//�ж��߶�P��ֱ��Q�Ƿ��ཻ���˵��غ����ཻ
bool Isonline(const SEG &p, const LINE &q) {
	SEG p1,p2,q0;
	p1.a = q.a; p1.b = p.a;
	p2.a = q.a; p2.b = p.b;
	q0.a = q.a; q0.b = q.b;
	return (Cross2(p1,q0) * Cross2(q0,p2) >= 0);
}
//�ж������߶��Ƿ�ƽ��
bool IsParallel(const LINE &A, const LINE &B) {
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;
	Coefficient(A, A1, B1, C1);
	Coefficient(B, A2, B2, C2);
	return (A1 * B2 == A2 * B1);
}
//�ж�����ֱ���Ƿ��ཻ
bool IsIntersect(const LINE & A, const LINE & B) {
	return !IsParallel(A, B);
}
// ����
struct RECT {
	POINT a; // ���µ�
	POINT b; // ���ϵ�
	RECT() {}
	RECT(const POINT &aa, const POINT &bb): a(aa), b(bb) {}
};
//���λ���׼
RECT Stdrect(const RECT &q) {
	RECT p = q;
	if(p.a.x > p.b.x) swap(p.a.x , p.b.x);
	if(p.a.y > p.b.y) swap(p.a.y , p.b.y);
	return p;
}
//�����±귵�ؾ��εı�
SEG Edge(const RECT &rect, int idx) {
	SEG edge;
	while (idx < 0) idx += 4;
	switch (idx % 4) {
		case 0: //�±�
			edge.a = rect.a;
			edge.b = POINT(rect.b.x, rect.a.y);
			break;
		case 1: //�ұ�
			edge.a = POINT(rect.b.x, rect.a.y);
			edge.b = rect.b;
			break;
		case 2: //�ϱ�
			edge.a = rect.b;
			edge.b = POINT(rect.a.x, rect.b.y);
			break;
		case 3: //���
			edge.a = POINT(rect.a.x, rect.b.y);
			edge.b = rect.a;
			break;
		default:
			break;
	}
	return edge;
}
//���ε����
TYPE Area(const RECT &rect) {
	return (rect.b.x - rect.a.x) * (rect.b.y - rect.a.y);
}
//�������εĹ������
TYPE CommonArea(const RECT &A, const RECT &B) {
	TYPE area = 0.0;
	POINT LL(Max(A.a.x, B.a.x), Max(A.a.y, B.a.y));
	POINT UR(Min(A.b.x, B.b.x), Min(A.b.y, B.b.y));
	if((LL.x <= UR.x) && (LL.y <= UR.y)) {
		area = Area(RECT(LL, UR));
	}
	return area;
}
// Բ
struct CIRCLE {
	TYPE x, y, r;
	CIRCLE() {}
	CIRCLE(TYPE xx, TYPE yy, TYPE zz): x(xx), y(yy), r(zz) {}
};
//Բ��
POINT Center(const CIRCLE &circle) {
	return POINT(circle.x, circle.y);
}
//Բ�����
TYPE Area(const CIRCLE &circle) {
	return PI * circle.r * circle.r;
}
//����Բ�Ĺ������
TYPE CommonArea(const CIRCLE &A, const CIRCLE &B)
{
	TYPE area = 0.0;
	const CIRCLE & M = (A.r > B.r) ? A : B;
	const CIRCLE & N = (A.r > B.r) ? B : A;
	TYPE D = Distance(Center(M), Center(N));
	if((D < M.r + N.r) && (D > M.r - N.r)) {
		TYPE cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
		TYPE cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
		TYPE alpha = 2.0 * ArcCos(cosM);
		TYPE beta = 2.0 * ArcCos(cosN);
		TYPE TM = 0.5 * M.r * M.r * Sin(alpha);
		TYPE TN = 0.5 * N.r * N.r * Sin(beta);
		TYPE FM = (alpha / 360.0) * Area(M);
		TYPE FN = (beta / 360.0) * Area(N);
		area = FM + FN - TM - TN;
	}
	else if(D <= M.r - N.r) {
		area = Area(N);
	}
	return area;
}
//�ж�Բ�Ƿ��ھ�����(����������)
bool IsInCircle(const CIRCLE &circle, const RECT &rect) {
	return (circle.x - circle.r > rect.a.x) &&
		(circle.x + circle.r < rect.b.x) &&
		(circle.y - circle.r > rect.a.y) &&
		(circle.y + circle.r < rect.b.y);
}
//�жϾ����Ƿ���Բ��(����������)
bool IsInRect(const CIRCLE & circle, const RECT & rect) {
	POINT c,d;
	c.x = rect.a.x; c.y = rect.b.y;
	d.x = rect.b.x; d.y = rect.a.y;
	return (Distance( Center(circle) , rect.a ) < circle.r) &&
		(Distance( Center(circle) , rect.b ) < circle.r) &&
		(Distance( Center(circle) , c ) < circle.r) &&
		(Distance( Center(circle) , d ) < circle.r);
}
//�жϾ����Ƿ���Բ����(����������)
bool Isoutside(const CIRCLE & circle, const RECT & rect) {
	POINT c,d;
	c.x = rect.a.x; c.y=rect.b.y;
	d.x = rect.b.x; d.y=rect.a.y;
	return ((Distance( Center(circle) , rect.a ) > circle.r) &&
			(Distance( Center(circle) , rect.b ) > circle.r) &&
			(Distance( Center(circle) , c ) > circle.r) &&
			(Distance( Center(circle) , d ) > circle.r) &&
			(rect.a.x > circle.x || circle.x > rect.b.x || rect.a.y > circle.y || circle.y > rect.b.y)) ||
		((circle.x - circle.r > rect.b.x) ||
		 (circle.x + circle.r < rect.a.x) ||
		 (circle.y - circle.r > rect.b.y) ||
		 (circle.y + circle.r < rect.a.y));
}
//������
struct TRIANGLE {
	POINT a, b, c;
	TRIANGLE() {};
	TRIANGLE(const POINT & aa, const POINT & bb, const POINT & cc):
		a(aa), b(bb), c(cc) {}
};
//�����α�׼��
TRIANGLE StdTRIANGLE(TYPE len1, TYPE len2, TYPE len3) //��3�߳�ת����������
{
	POINT a, b, c;     //��֪�߳�����ת��������������
	a.x = a.y = 0.0;
	b.x = len1;
	b.y = 0.0;
	c.x = (len2 * len2 - len3 * len3 + len1 * len1)/len1/2.0;
	c.y = Sqrt(len2 * len2 - c.x * c.x);
	TRIANGLE temp(a,b,c);
	return temp;
};
//�����η����(�������ε�������֮����С�ĵ�)
POINT fermentPONT(TRIANGLE &t) {
	POINT u, v;
	double step = fabs(t.a.x) + fabs(t.a.y) + fabs(t.b.x) + fabs(t.b.y) + fabs(t.c.x) + fabs(t.c.y);
	int i, j, k;
	u.x = (t.a.x + t.b.x + t.c.x)/3;
	u.y = (t.a.y + t.b.y + t.c.y)/3;
	while (step > EPS)
		for(k = 0; k < 10; step /= 2, ++k)
			for(i = -1; i <= 1; ++i)
				for(j = -1; j <= 1; ++j) {
					v.x = u.x + step * i;
					v.y = u.y + step * j;
					if(Distance(u,t.a) + Distance(u,t.b) + Distance(u,t.c) > Distance(v,t.a) + Distance(v,t.b) + Distance(v,t.c))
						u = v;
				}
	return u;
};
//����������(���߽���)
POINT InCenter(const TRIANGLE &t) {
	return POINT((t.a.x + t.b.x + t.c.x)/3, (t.a.y + t.b.y + t.c.y)/3);
}
//����������(�д��߽���)
POINT CcCenter(const TRIANGLE &t) {
	POINT u, v;
	LINE A, B;
	A.a = t.a; A.b = t.b; B.a = t.b; B.b = t.c;
	TYPE A1, B1, C1;
	TYPE A2, B2, C2;
	Coefficient(A, B1, A1, C1);
	Coefficient(B, B2, A2, C2);
	B1 = -B1; B2 = -B2;
	C1 = -((A.a.x + A.b.x) * A1 + (A.a.y + B.a.y) * B1)/2;
	C2 = -((B.a.x + B.b.x) * A2 + (B.a.y + B.b.y) * B2)/2;
	POINT I(0, 0);
	I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
	I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
	return I;
}
//����������(��ƽ���߽���)
POINT incenter(const TRIANGLE &t) {
	LINE u, v;
	TYPE m, n;
	u.a = t.a;
	m = atan2(t.b.y - t.a.y, t.b.x - t.a.x);
	n = atan2(t.c.y - t.a.y, t.c.x - t.a.x);
	u.b.x = u.a.x + cos((m + n)/2);
	u.b.y = u.a.y + sin((m + n)/2);
	v.a = t.b;
	m = atan2(t.a.y - t.b.y, t.a.x - t.b.x);
	n = atan2(t.c.y - t.b.y, t.c.x - t.b.x);
	v.b.x = v.a.x + cos((m + n)/2);
	v.b.y = v.a.y + sin((m + n)/2);
	return Intersection(u, v);
};
//����������Բ���
TYPE InArea(const TRIANGLE &t) {
	TYPE p, a, b, c, s;
	a = Distance(t.a, t.b);
	c = Distance(t.a, t.c);
	b = Distance(t.c, t.b);
	s = (a + b + c)/2;
	p = s * (s - a) * (s - b) * (s - c);
	s = p * PI/s/s;
	return s;
}
//���������Բ���
TYPE OutArea(const TRIANGLE & t) {
	TYPE a,b,c;
	a = (t.a.x - t.b.x) * (t.a.x - t.b.x) + (t.a.y - t.b.y) * (t.a.y - t.b.y);
	b = (t.a.x - t.c.x) * (t.a.x - t.c.x) + (t.a.y - t.c.y) * (t.a.y - t.c.y);
	c = (t.c.x - t.b.x) * (t.c.x - t.b.x) + (t.c.y - t.b.y) * (t.c.y - t.b.y);
	a = PI * sqrt(c/(1-(a+b-c)*(a+b-c)/a/b/4));
	return a;
}
// ����� ,��ʱ���˳ʱ�����x,y
struct POLY {
	int n;     //n����
	TYPE *x, *y;   //x,yΪ���ָ�룬��β�����غ�
	POLY(): n(0), x(NULL), y(NULL) {};
	POLY(int nn, const TYPE *xx, const TYPE *yy) {
		n = nn;
		x = new TYPE[n + 1];
		memcpy(x, xx, n*sizeof(TYPE));
		x[n] = xx[0];
		y = new TYPE[n + 1];
		memcpy(y, yy, n*sizeof(TYPE));
		y[n] = yy[0];
	}
};
//����ζ���
POINT Vertex(const POLY &poly, int idx) {
	// idx %= poly.n;
	return POINT(poly.x[idx], poly.y[idx]);
}
//����εı�
SEG Edge(const POLY &poly, int idx) {
	// idx %= poly.n;
	return SEG(POINT(poly.x[idx], poly.y[idx]), POINT(poly.x[idx + 1], poly.y[idx + 1]));
}
//����ε��ܳ�
TYPE Perimeter(const POLY & poly) {
	TYPE p = 0.0;
	for (int i = 0; i < poly.n; ++i)
		p += Distance(Vertex(poly, i), Vertex(poly, i + 1));
	return p;
}
//���������
TYPE Area(const POLY & poly) {
	if (poly.n < 3) return TYPE(0);
	double s = poly.y[0] * (poly.x[poly.n - 1] - poly.x[1]);
	for (int i = 1; i < poly.n; ++i) {
		s += poly.y[i] * (poly.x[i - 1] - poly.x[(i + 1) % poly.n]);
	}
	return s/2;
}
//����ε�����
POINT InCenter(const POLY & poly) {
	TYPE S,Si,Ax,Ay;
	POINT p;
	Si = (poly.x[poly.n - 1] * poly.y[0] - poly.x[0] * poly.y[poly.n - 1]);
	S = Si;
	Ax = Si * (poly.x[0] + poly.x[poly.n - 1]);
	Ay = Si * (poly.y[0] + poly.y[poly.n - 1]);
	for(int i = 1; i < poly.n; ++i){
		Si = (poly.x[i-1] * poly.y[i] - poly.x[i] * poly.y[i-1]);
		Ax += Si * (poly.x[i-1] + poly.x[i]);
		Ay += Si * (poly.y[i-1] + poly.y[i]);
		S += Si;
	}
	S = S * 3;
	return POINT(Ax/S,Ay/S);
}
//�жϵ��Ƿ��ڶ������
bool IsOnPoly(const POLY &poly, const POINT &p) {
	for(int i = 0; i < poly.n; ++i){
		if( IsOnSeg(Edge(poly, i), p) ) return true;
	}
	return false;
}
//�жϵ��Ƿ��ڶ�����ڲ�
bool IsInPoly(const POLY &poly, const POINT &p) {
	SEG L(p, POINT(Infinity, p.y));
	int count = 0;
	for (int i = 0; i < poly.n; i++) {
		SEG S = Edge(poly, i);
		if (IsOnSeg(S, p)) {
			return true; //������� ��poly���򷵻� true,
		}
		if(!IsEqual(S.a.y, S.b.y)) {
			POINT & q = (S.a.y > S.b.y)?(S.a):(S.b);
			if(IsOnSeg(L, q)) ++count;
			else if(!IsOnSeg(L, S.a) && !IsOnSeg(L, S.b) && IsIntersect(S, L)) {
				++count;
			}
		}
	}
	return (count % 2 != 0);
}
//�ж��Ƿ�򵥶����
bool IsSimple(const POLY & poly) {
	if(poly.n < 3) return false;
	SEG L1, L2;
	for(int i = 0; i < poly.n - 1; ++i) {
		L1 = Edge(poly, i);
		for(int j = i + 1; j < poly.n; ++j) {
			L2 = Edge(poly, j);
			if(j == i + 1) {
				if(IsOnSeg(L1, L2.b) || IsOnSeg(L2, L1.a)) return false;
			}
			else if(j == poly.n - i - 1) {
				if (IsOnSeg(L1, L2.a) || IsOnSeg(L2, L1.b)) return false;
			}
			else if(IsIntersect(L1, L2)) return false;
		} // for j
	} // for i
	return true;
}
// �����͹��������һ�������(��һ���Ѳ���)���������ڵ��������������
POLY ConvexHull(const POINT * set, int n) {
	POINT * points = new POINT[n];
	memcpy(points, set, n * sizeof(POINT));
	TYPE * X = new TYPE[n];
	TYPE * Y = new TYPE[n];
	int i, j, k = 0, top = 2;
	for(i = 1; i < n; ++i) {
		if ((points[i].y < points[k].y) || ((points[i].y == points[k].y) && (points[i].x < points[k].x)))
			k = i;
	}
	swap(points[0], points[k]);
	for(i = 1; i < n - 1; ++i) {
		k = i;
		for(j = i + 1; j < n; ++j) {
			if((Cross(points[j], points[k], points[0]) > 0) ||
					((Cross(points[j], points[k], points[0]) == 0) &&
					 (Distance(points[0], points[j]) < Distance(points[0], points[k]))))
				k = j;
		}
		swap(points[i], points[k]);
	}
	X[0] = points[0].x; Y[0] = points[0].y;
	X[1] = points[1].x; Y[1] = points[1].y;
	X[2] = points[2].x; Y[2] = points[2].y;
	for(i = 3; i < n; i++) {
		while(Cross(points[i], POINT(X[top], Y[top]),POINT(X[top - 1], Y[top - 1])) >= 0)
			--top;
		++top;
		X[top] = points[i].x;
		Y[top] = points[i].y;
	}
	delete [] points;
	POLY poly(++top, X, Y);
	delete [] X;
	delete [] Y;
	return poly;
}
// �����͹��������һ������� (�󷨶���δ����)
bool cmp(const POINT& aa, const POINT& bb) {
	if(aa.y != bb.y) return aa.y < bb.y;
	else return aa.x < bb.x;
}
POLY ConvexHull2(const POINT * set, int n) {// �������ڵ��������������
	POINT *a = new POINT[n];
	memcpy(a, set, n * sizeof(POINT));
	sort(a, a + n, cmp);
	TYPE * X = new TYPE[n];
	TYPE * Y = new TYPE[n];
	X[0] = a[0].x;
	Y[0] = a[0].y;
	X[1] = a[1].x;
	Y[1] = a[1].y;
	int i,j;
	for(i = 2, j = 2; i < n; ++i) {
		X[j] = a[i].x;
		Y[j] = a[i].y;
		while(((X[j]-X[j-1]) * (Y[j-1]-Y[j-2]) - (Y[j]-Y[j-1]) * (X[j-1]-X[j-2])) >= 0 && j > 1) {
			X[j-1] = X[j];
			Y[j-1] = Y[j];
			--j;
		}
		++j;
	}
	X[j] = a[n-2].x;
	Y[j] = a[n-2].y;
	++j;
	for(i = n - 3; i >= 0; --i) {
		X[j] = a[i].x;
		Y[j] = a[i].y;
		while(((X[j]-X[j-1]) * (Y[j-1]-Y[j-2]) - (Y[j]-Y[j-1]) * (X[j-1]-X[j-2])) >= 0) {
			X[j-1] = X[j];
			Y[j-1] = Y[j];
			--j;
		}
		++j;
	}
	delete [] a;
	POLY poly(j, X, Y);
	delete [] X;
	delete [] Y;
	return poly;
}

int main() {
	double a,b,c,l1,l2,l3,l4;
	POINT d;
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lf%lf%lf",&a,&b,&c);
		TRIANGLE t=StdTRIANGLE(a,b,c);

		d=fermentPONT(t);//�����
		l1=Distance(d,t.a)+Distance(d,t.b)+Distance(d,t.c);

		d=incenter(t);//����
		l2=Distance(d,t.a)+Distance(d,t.b)+Distance(d,t.c);

		d=InCenter(t);//����
		l3=Distance(d,t.a)+Distance(d,t.b)+Distance(d,t.c);

		d=CcCenter(t);//����
		l4=Distance(d,t.a)+Distance(d,t.b)+Distance(d,t.c);

		printf("%.3lf %.3lf %.3lf %.3lf\n",l1,l2,l3,l4);
	}
	return 0;
}
