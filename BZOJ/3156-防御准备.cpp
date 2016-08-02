//{HEADS
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
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
#define PL(k,n) for(int i=1;i<=n;++i) { cout<<k[i]<<' '; } cout<<endl
#define PS(k) STLR(i,k) { cout<<k[i]<<' '; } cout<<endl
using namespace std;
typedef long long LL;
typedef double DB;
typedef pair<int,int> i_pair;
const int INF = 0x3f3f3f3f;
const long long INFL = 0x3f3f3f3f3f3f3f3f;
//}

const int maxn = 1e6 + 100;

int n;
LL a[maxn],f[maxn];

inline DB slope(LL x,LL y) {
	return (DB)((DB)(2*f[x]+x*x+x)-(DB)(2*f[y]+y*y+y))/(DB)(2*x-2*y);
}
int que[maxn],head,tail;
int main() {
#define FILE_IN_OUT
string FILE_NAME = "BZOJ3156";
/*FILE{*/
#ifdef FILE_IN_OUT
#ifndef ONLINE_JUDGE
	freopen((FILE_NAME+".in").c_str(),"r",stdin);
	freopen((FILE_NAME+".out").c_str(),"w",stdout);
#endif
#endif/*}*/

	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
	}
	reverse(a+1,a+1+n);
	f[1]=a[1];
	head=0,tail=-1;
	que[++tail]=1;
	for(int i=2;i<=n+1;++i) {
		while(head<tail && slope(que[head],que[head+1])<(DB)i) {
			++head;
		}
		int j=que[head];
		f[i]=f[j]+((i-j-1)*(i-j))/2+a[i];
//		printf("%lld %d\n",f[i],j);
		while(head<tail && slope(que[tail-1],que[tail])>slope(que[tail],i)) {
			--tail;
		}
		que[++tail]=i;
	}
	printf("%lld\n",f[n+1]);

	return 0;
}

