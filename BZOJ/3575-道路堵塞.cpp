#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x7f7f7f7f
#define INF 21000000000000ll
#define ls(x) ((x)<<1)
#define rs(x) (((x)<<1)|1)
using namespace std;
   
   
struct E
{
    int u,v,w,pre;
    E(int U=0,int V=0,int W=0,int P=0){u=U;v=V;pre=P;w=W;}
}edge[200005];
int dis[100005],pos[200005],pe[200005];
int L,fs[100005];
int ft[100005],adj[100005],deg[100005];
int rt[200005],inr[200005],n,m;
int pre[200005],suf[200005];
int p;
struct Node
{
    int x,dis;
    bool operator <(const Node &e)const
    {
        return dis>e.dis;
    }
}q[500005];
  
  
#define CH getchar()
inline void read(int &x)
{
    x=0;
    char ch=CH;
    while(!(ch>='0'&&ch<='9'))ch=CH;
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=CH;
    }
}
   
  
  
int queue[1500005],vis[100005];
int occur[100005],id,stack[100005];
int val[100005],top;
inline void spfa(int ds,int S,int lim)
{
    memset(vis,0,sizeof(vis));
    ++id;dis[S]=ds;
    int l=1,r=1;
    queue[1]=S;vis[S]=1;
    for(;l<=r;l++)
    {
        int u=queue[l];
        for(int i=adj[u];i;i=edge[i].pre)
        if(!inr[i])
        {
            int v=edge[i].v;
            if(pos[v]>lim)
            {
                if(occur[v]!=id)
                {
                    occur[v]=id;
                    stack[++top]=v;
                    val[v]=dis[u]+edge[i].w+suf[pos[v]];
                }else
                {
                    val[v]=min(val[v],dis[u]+edge[i].w+suf[pos[v]]);
                }
            }else
            if(dis[u]+edge[i].w<dis[v])
            {
                dis[v]=dis[u]+edge[i].w;
                if(vis[v])continue;
                queue[++r]=v;
                vis[v]=1;
            }
        }
        vis[u]=0;
    }
    for(;top;top--)
    {
        ++p;
        q[p].x=stack[top];
        q[p].dis=val[stack[top]];
        push_heap(q+1,q+p+1);
    }
}
  
   
inline void work()
{
    memset(dis,0x7f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=L;i++)
    {
        inr[rt[i]]=1;
        spfa(pre[i],pe[i],i);
        inr[rt[i]]=0;
        while(p&&pos[q[1].x]<=i)
        {
            pop_heap(q+1,q+p+1);
            p--;
        }
        if(!p)puts("-1");else printf("%d\n",q[1].dis);
    }
}
   
   
int main()
{
    read(n);read(m);read(L);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        read(u);read(v);read(w);
        edge[i]=E(u,v,w,adj[u]);
        adj[u]=i;
    }
    pos[1]=1;pe[1]=1;    
    for(int i=1;i<=L;i++)
    {
        read(rt[i]);
        pe[i+1]=edge[rt[i]].v;
        pos[edge[rt[i]].v]=i+1;
    }
    for(int i=1;i<=L;i++)
        pre[i+1]=pre[i]+edge[rt[i]].w;
    for(int i=L;i;i--)
        suf[i]=suf[i+1]+edge[rt[i]].w;
    work();
    return 0;
}
