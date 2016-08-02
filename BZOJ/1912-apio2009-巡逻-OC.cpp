#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define MAXE 100010
#define MAXV 100010

using namespace std;

int n,m;

struct edge
{
	int u,v,w,next;
}edges[2*MAXE];

int head[MAXV],nCount=1;

void AddEdge(int U,int V,int W)
{
	edges[++nCount].u=U;
	edges[nCount].v=V;
	edges[nCount].w=W;
	edges[nCount].next=head[U];
	head[U]=nCount;
}

int diameter,s; //树的直径为diameter,直径的起点是s
int son1[MAXV],son2[MAXV]; //记录最长路与次长路的路径

int DFS(int u,int fa)
{
	int max1=0,max2=0; //最长路与次长路
	for(int p=head[u];p!=-1;p=edges[p].next)
	{
		int v=edges[p].v;
		if(v==fa) continue;
		int nowh=DFS(v,u)+edges[p].w;
		if(nowh>max1) max2=max1,son2[u]=son1[u],max1=nowh,son1[u]=p;
		else if(nowh>max2) max2=nowh,son2[u]=p;
	}
	if(diameter<max1+max2) diameter=max1+max2,s=u;
	return max1;
}

int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u,v,1);
		AddEdge(v,u,1);
	}
	int ans=(n-1)<<1;
	diameter=0;
	memset(son1,-1,sizeof(son1));
	memset(son2,-1,sizeof(son2));
	DFS(1,-1);
	ans-=diameter-1;
	if(m>1)
	{
		diameter=0;
		for(int i=son1[s];i!=-1;i=son1[edges[i].v]) edges[i].w=edges[i^1].w=-1;
		for(int i=son2[s];i!=-1;i=son1[edges[i].v]) edges[i].w=edges[i^1].w=-1;
		memset(son1,-1,sizeof(son1));
		memset(son2,-1,sizeof(son2));
		DFS(1,-1);
		ans-=diameter-1;
	}
	printf("%d\n",ans);
	return 0;
}
