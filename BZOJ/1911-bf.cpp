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
string FILE_NAME = "BZOJ1911_force";
typedef long long LL;
typedef double DB;
typedef pair<int,int> i_pair;
const int INF = 0x3f3f3f3f;
const long long INFL = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 10;

int ability[maxn],sum[maxn],f[maxn],n,a,b,c;

int rec_decision[maxn];

int amend(int s) {
	return s*s*a+s*b+c;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen((FILE_NAME+".in").c_str(),"r",stdin);
	freopen((FILE_NAME+".out").c_str(),"w",stdout);
#endif

	scanf("%d%d%d%d",&n,&a,&b,&c);
	for(int i=1;i<=n;++i) {
		scanf("%d",&ability[i]);
		sum[i]=sum[i-1]+ability[i];
	}
	rec_decision[0]=1;
	for(int i=1;i<=n;++i) {
		f[i]=-INF;
		for(int j=rec_decision[i-1];j<=i;++j) {
			int tmp=f[j-1]+amend(sum[i]-sum[j-1]);
			if(f[i]<tmp) {
				f[i]=tmp;
				rec_decision[i]=j;
			}
		}
	}
	for(int i=1;i<=n;++i) {
		printf("%d ",rec_decision[i]);
	}
	puts("");

	printf("%d\n",f[n]);

	return 0;
}

