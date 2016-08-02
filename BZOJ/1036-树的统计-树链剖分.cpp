#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

using namespace std;


const int maxn = 30000 + 500;
const int maxe = maxn * 2;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int edge;
	int next[maxe],to[maxe],head[maxn];
	void init()
	{
		edge=0;
		memset(head,-1,sizeof head);
	}
	Edge() { init(); }
	void addedge(int u,int v)
	{
		next[edge]=head[u];
		to[edge]=v;
		head[u]=edge++;
	}
}E;

int tree[maxn*4],sum[maxn*4];
int size[maxn],son[maxn],dep[maxn],fa[maxn],to[maxn],d[maxn][2],val[maxn],top[maxn],w[maxn];
int n,root,z;

void dfs(int v)
{
	size[v]=1,son[v]=0;
	for(int i=E.head[v];i!=-1;i=E.next[i])
		if(E.to[i]!=fa[v])
		{
			dep[E.to[i]]=dep[v]+1;
			fa[E.to[i]]=v;
			dfs(E.to[i]);
			if(size[son[v]]<size[E.to[i]])
				son[v]=E.to[i];
			size[v]+=size[E.to[i]];
		}
}

void build_tree(int v,int tp)
{
	w[v]=++z; top[v]=tp;
	if(son[v]!=0) build_tree(son[v],tp);
	for(int i=E.head[v];i!=-1;i=E.next[i])
		if(E.to[i]!=son[v] && E.to[i]!=fa[v])
			build_tree(E.to[i],E.to[i]);
}

void change(int l,int r,int rt,int pos,int val)
{
	if(l==r)
	{
		tree[rt]=sum[rt]=val;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) change(l,mid,rt<<1,pos,val);
	else if(mid<pos) change(mid+1,r,rt<<1|1,pos,val);
	tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void init()
{
	E.init();
	memset(dep,0,sizeof dep);
	memset(size,0,sizeof size);
	scanf("%d",&n);
	root=1;
	fa[root]=z=dep[root]=0;
	for(int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		d[i][0]=a,d[i][1]=b;
		E.addedge(a,b);
		E.addedge(b,a);
	}
	dfs(root);
	build_tree(root,root);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&val[i]);
		change(1,z,1,w[i],val[i]);
	}
}

int Max(int l,int r,int rt,int ql,int qr)
{
	if(ql<=l && r<=qr)
	{
		return tree[rt];
	}
	int mid=(l+r)>>1;
	int ret=-INF;
	if(ql<=mid) ret=max(ret,Max(l,mid,rt<<1,ql,qr));
	if(mid<qr) ret=max(ret,Max(mid+1,r,rt<<1|1,ql,qr));
	return ret;
}

int get_max(int a,int b)
{
	int f1=top[a],f2=top[b];
	int ans=-INF;
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2])
		{
			swap(f1,f2);
			swap(a,b);
		}
		ans=max(ans,Max(1,z,1,w[f1],w[a]));
		a=fa[f1],f1=top[a];
	}
	if(a==b) return max(ans,Max(1,z,1,w[a],w[a]));
	if(dep[a]>dep[b]) swap(a,b);
	ans=max(ans,Max(1,z,1,w[a],w[b]));
	return ans;
}

int Sum(int l,int r,int rt,int ql,int qr)
{
	if(ql<=l && r<=qr)
		return sum[rt];
	int mid=(l+r)>>1;
	int ret=0;
	if(ql<=mid)
		ret+=Sum(l,mid,rt<<1,ql,qr);
	if(mid<qr)
		ret+=Sum(mid+1,r,rt<<1|1,ql,qr);
	return ret;
}

int get_sum(int a,int b)
{
	int f1=top[a],f2=top[b];
	int ans=0;
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2])
		{
			swap(f1,f2);
			swap(a,b);
		}
		ans+=Sum(1,z,1,w[f1],w[a]);
		a=fa[f1],f1=top[a];
	}
	if(a==b) return ans+=Sum(1,z,1,w[a],w[a]);
	if(dep[a]>dep[b]) swap(a,b);
	ans+=Sum(1,z,1,w[a],w[b]);
	return ans;
}


char str[10];
void solve()
{
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int a,b;
		scanf("%s %d %d",str,&a,&b);
		if(str[0]=='C')
			change(1,z,1,w[a],b);
		else if(str[0]=='Q')
		{
			int ans;
			if(str[1]=='M')
				ans=get_max(a,b);
			else if(str[1]=='S')
				ans=get_sum(a,b);
			printf("%d\n",ans);
		}
	}
}

int main()
{

	init();
	solve();

	return 0;
}

