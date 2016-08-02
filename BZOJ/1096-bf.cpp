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

const int maxn = 1000000 + 100;

LL P[maxn],C[maxn],n;
LL f[maxn],sw[maxn],sd[maxn],cost[maxn];

int main() {
#define FILE_IN_OUT
string FILE_NAME = "BZOJ1096_force";
/*FILE{*/
#ifdef FILE_IN_OUT
#ifndef ONLINE_JUDGE
	freopen((FILE_NAME+".in").c_str(),"r",stdin);
	freopen((FILE_NAME+".out").c_str(),"w",stdout);
#endif
#endif/*}*/

	scanf("%lld",&n);
	for(int i=1;i<=n;++i) {
		scanf("%lld%lld%lld",sd+i,P+i,C+i);
	}
	for(int i=1;i<=n;++i) {
		sw[i]=sw[i-1]+P[i];
		cost[i]=cost[i-1]+sw[i-1]*(sd[i]-sd[i-1]);
//		cout<<sw[i]<<' '<<sd[i]<<' '<<cost[i]<<endl;
	}
	memset(f,0x3f,sizeof f);
	f[0]=0;
	int rec_pos=0;
	for(int i=1;i<=n;++i) {
		for(int j=rec_pos;j<i;++j) {
			LL tmp=f[j]+cost[i]-cost[j]-sw[j]*(sd[i]-sd[j])+C[i];
			if(f[i]>tmp) {
				f[i]=tmp;
				rec_pos=j;
			}
		}
		printf("%d\n",rec_pos);
//		cout<<f[i]<<'\n';
	}
	printf("%lld\n",f[n]);

	return 0;
}

