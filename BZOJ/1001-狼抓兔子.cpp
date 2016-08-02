#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 2e6 + 100;
const int maxe = maxn*3;
const int INF = 0x3f3f3f3f;
int n,m,M,N,s,t,edge;
int head[maxn],wei[maxe],to[maxe],next[maxe];
int ans;
void add(int i,int j,int k)
{
	++edge;
	next[edge]=head[i];
	head[i]=edge;
	to[edge]=j;
	wei[edge]=k;
}
inline int read()  
{  
    char ch;
	bool flag=false;
    int a=0;  
    while(!((((ch=getchar())>='0') && (ch<='9')) || (ch=='-')));  
    if(ch!='-')
		a=ch-'0';
	else
		flag=true;
    while(((ch=getchar())>='0') && (ch<='9'))
	{
		a*=10;
		a+=ch-'0';
	}
	if(flag)
		a=-a;
    return a;  
} 
void addedge(int a,int b)
{
	int w=read();
	add(a,b,w);add(b,a,w);
}
#define FOR(_i,_n,_m) for(int _i=_n;_i<=_m;++_i)
void init()
{
	scanf("%d%d",&n,&m);
	if(n==1 || m==1)
	{
		ans=INF;
		if(n==1) n=m;
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&m);
			if(m<ans)
				ans=m;
		}
		printf("%d\n",ans);
		exit(0);
	}
	N=n-1,M=m-1;
	s=N*M*2+1;t=s+1;
	//加入横边
	FOR(i,1,n) FOR(j,1,M)
	{
		if(i==1) addedge(t,j);
		else if(i==n) addedge(s,N*M*2-M+j);
		else addedge((2*(i-1)-1)*M+j,(2*(i-1)-1)*M+j+M);
	}
	//加入纵边
	FOR(i,1,N) FOR(j,1,m)
	{
		if(j==1) addedge(s,(i*2-1)*M+j);
		else if(j==M+1) addedge(t,(i*2-1)*M);
		else addedge((i*2-1)*M+j,(i*2-1)*M+j-M-1);
	}
	//加入斜边
	FOR(i,1,N) FOR(j,1,M)
		addedge(M*(i*2-1)-M+j,M*(i*2-1)+j);
}

int SPFA()
{
	int dis[maxn];
	memset(dis,INF,sizeof dis);
	dis[s]=0;
	queue<int> Q;
	while(!Q.empty()) Q.pop();
	Q.push(s);
	while(!Q.empty())
	{
		int now=Q.front();Q.pop();
		for(int i=head[now];i!=0;i=next[i])
		{
			if(dis[now]+wei[i]<dis[to[i]])
			{
				dis[to[i]]=dis[now]+wei[i];
				Q.push(to[i]);
			}
		}
	}
	return dis[t];
}
struct HN
{
	int d,u;
	HN(int d,int u):d(d),u(u) {}
	bool operator < (const HN &t) const
	{
		return d>t.d;
	}
};
int dis[maxn];
bool vis[maxn];
int Dijkstra()
{
	priority_queue<HN> H;
	while(!H.empty()) H.pop();
	memset(dis,INF,sizeof dis);
	memset(vis,false,sizeof vis);
	dis[s]=0;
	H.push(HN(0,s));
	for(int i=1;i<=t;++i)
	{
		int u=H.top().u; H.pop();
		if(vis[u]) continue;
		if(u==t)
			return dis[t];
		vis[u]=true;
		for(int i=head[u];i!=0;i=next[i])
		{
			if(vis[to[i]]) continue;
			if(dis[u]+wei[i]<dis[to[i]])
			{
				dis[to[i]]=dis[u]+wei[i];
				H.push(HN(dis[to[i]],to[i]));
			}
		}
	}
	return dis[t];
}

int main()
{
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	init();
	printf("%d\n",Dijkstra());
	return 0;
}
