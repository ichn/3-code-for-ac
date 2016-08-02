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

int get() {
	return rand()%10+1;
}


int main() {
#define FILE_IN_OUT
string FILE_NAME = "BZOJ1096";
/*FILE{*/
#ifdef FILE_IN_OUT
#ifndef ONLINE_JUDGE
	freopen((FILE_NAME+".in").c_str(),"w",stdout);
#endif
#endif/*}*/

	int n=10;
	srand((int)time(NULL));
	printf("%d\n",n);
	printf("%d %d %d\n",0,get(),get());
	for(int i=2;i<=n;++i) {
		printf("%d %d %d\n",get(),get(),get());
	}
	
	return 0;
}

