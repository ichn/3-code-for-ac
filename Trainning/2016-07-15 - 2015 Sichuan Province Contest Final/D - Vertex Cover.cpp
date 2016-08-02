#include <bits/stdc++.h>
using namespace std;
#define N 505
#define M 130000
struct edge
{
	int to,next;
}e[M<<1];
int h[N],tp;
void ae(int u,int v)
{
	e[++tp].to=v;e[tp].next=h[u];h[u]=tp;
}
int n,m;
int match[N],type[N],link[N],fa[N];
int vis[N],tim;
int q[N],t;
int get_lca(int u,int v)
{
	for(tim++;;swap(u,v))
		if(u)
		{
			if(vis[u]==tim) return u;
			vis[u]=tim;u=fa[link[match[u]]];
		}
}
void update(int u,int v,int tar)
{
	while(fa[u]!=tar)
	{
		link[u]=v;
		if(type[match[u]]==1) type[q[++t]=match[u]]=0;
		fa[u]=tar;fa[match[u]]=tar;
		u=link[v=match[u]];
	}
}
bool bfs(int x)
{
	q[t=1]=x;
	for(int i=1;i<=n;i++) type[i]=-1,fa[i]=i;
	type[x]=0;
	for(int k=1;k<=t;k++)
	{
		int u=q[k];
		for(int v,i=h[u];i;i=e[i].next)
		{
			if(type[v=e[i].to]==-1)
			{
				link[v]=u;type[v]=1;
				int nu=match[v];
				if(!nu)
				{
					while(v)
					{
						int nv=match[link[v]];
						match[match[v]=link[v]]=v;
						v=nv;
					}
					return 1;
				}
				type[q[++t]=nu]=0;
			}
			else if(!type[v]&&fa[v]!=fa[u])
			{
				int lca=get_lca(u,v);
				update(u,v,lca);update(v,u,lca);
				for(int j=1;j<=n;j++) fa[j]=fa[fa[j]];
			}
		}
	}
	return 0;
}
int main()
{
	while (scanf("%d %d", &n, &m) != EOF) {
		tp = 0;
		memset(h, 0, sizeof h);
		memset(match, 0, sizeof match);
		memset(link, 0, sizeof link);
		for(int u,v,i=1;i<=m;i++)
		{
			scanf("%d %d", &u, &v);
			ae(u,v);ae(v,u);
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(!match[i]&&bfs(i)) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
