//{
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <string>
#define REP(i,j) for(int i=1;i<=j;++i)
#define REPI(i,j,k) for(int i=j;i<=k;++i)
#define REPD(i,j) for(int i=j;0<i;--i)
#define STLR(i,con) for(int i=0,sz=con.size();i<sz;++i)
#define STLRD(i,con) for(int i=con.size()-1;0<=i;--i)
#define CLR(s) memset(s,0,sizeof s)
#define SET(s,v) memset(s,v,sizeof s)
#define mp make_pair
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef double DB;
typedef pair<int,int> i_pair;
const int INF = 0x3f3f3f3f;
const long long INFL = 0x3f3f3f3f3f3f3f3f;          //}

const int maxn = 1e6 + 10;

LL ability,sum[maxn],f[maxn];

int q[maxn],tail,head,n,a,b,c;

LL amend(LL s) {
	return s*s*a+s*b+c;
}
LL sqr(LL x) {
	return x*x;
}
LL P(int x) {
	return f[x]-b*sum[x]+a*sqr(sum[x]);
}
DB G(int x,int y) {
	return (DB)(P(y)-P(x))/(sum[y]-sum[x]);
}

int main() {
#ifndef ONLINE_JUDGE
	string FILE_NAME = "BZOJ1911";
	freopen((FILE_NAME+".in").c_str(),"r",stdin);
	freopen((FILE_NAME+".out").c_str(),"w",stdout);
#endif

	scanf("%d%d%d%d",&n,&a,&b,&c);
	for(int i=1;i<=n;++i) {
		scanf("%lld",&ability);
		sum[i]=sum[i-1]+ability;
	}

	q[tail=head=0]=0;
	for(int i=1;i<=n;++i) {
		int right_val=2*a*sum[i];
		while(head<tail && G(q[head],q[head+1])>(DB)right_val) {
			++head;
		}
		int k=q[head];
		f[i]=amend(sum[i]-sum[k])+f[k];
	//	printf("%d %lld\n",k,f[i]);
		while(head<tail && G(q[tail-1],q[tail])<G(q[tail],i)) {
			--tail;
		}
		q[++tail]=i;
	}

	printf("%lld\n",f[n]);

	return 0;
}

