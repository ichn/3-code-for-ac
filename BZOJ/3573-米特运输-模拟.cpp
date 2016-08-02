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
#define CLR(s) memset(s,0,sizeof s)
#define SET(s,v) memset(s,v,sizeof s)
#define mp make_pair
#define pb push_back
#define x first
#define y second
using namespace std;
string FILE_NAME = "meat";
typedef long long LL;
typedef double DB;
const int INF = 0x3f3f3f3f;

const int maxn = 2000 + 100;

int fa[maxn],son[maxn],n;
DB A[maxn];
struct Edge
{
	int head[maxn],next[maxn],to[maxn];
	int edge;
	void init()
	{
		edge=0;
		SET(head,-1);
	}
	void addedge(int a,int b)
	{
		next[edge]=head[a];
		to[edge]=b;
		head[a]=edge++;
	}
}E;

int cnt;

int dcmp(DB d)
{
	if(fabs(d)<1e-4)
		return 0;
	return d<0?-1:1;
}


void get_son(int f,DB wei)
{
	if(son[f]==0)
		return ;
	DB ave=wei/son[f];
	for(int i=E.head[f];i!=-1;i=E.next[i])
	{
		if(dcmp(A[E.to[i]]-ave)!=0)
		{
			++cnt;
		}
		get_son(E.to[i],ave);
	}
}

int get_num(int ex)
{
	cnt=0;
	DB wei=A[ex];
	while(ex!=1)
	{
		wei=wei*son[fa[ex]];
		ex=fa[ex];
	}
	if(dcmp(wei-A[ex])!=0) cnt=1;
	get_son(1,wei);
//	printf("%d %lf %d\n",ex,wei,cnt);
	return cnt;
}

int main()
{
	scanf("%d",&n);
	E.init();
	for(int i=1;i<=n;++i)
	{
		scanf("%lf",&A[i]);
	}
	for(int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		fa[b]=a;
		++son[a];
		E.addedge(a,b);
	}

	int ans=INF;
	for(int i=n;0<i;--i)
	{
		int d=get_num(i);
		if(d<ans) ans=d;
	}
	printf("%d\n",ans);
	return 0;
}
