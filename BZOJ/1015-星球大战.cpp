#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=400000;
const int maxm=200000;
vector<int> g[maxn+50];
int q[maxn+50],a[maxn+50],f[maxn+50],n,m,len;
bool p[maxn+50],visit[maxn+50];
int find(int x)
{
    if(f[x]==x) return f[x];
    return f[x]=find(f[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) g[i].clear();
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    scanf("%d",&len);
    for(int i=1;i<=len;++i) scanf("%d",&q[i]);
    memset(visit,0,sizeof(visit));
    for(int i=1;i<=len;++i) visit[q[i]]=1;
    for(int i=0;i<n;++i) f[i]=i;
    for(int i=0;i<n;++i)
        if(visit[i]==0)
            for(int j=0;j<g[i].size();++j)
                if(visit[g[i][j]]==0)
                {
                    int x=find(i),y=find(g[i][j]);
                    if(x!=y) f[y]=x;
                }
    a[len]=0;
    memset(p,0,sizeof(p));
    for(int i=0;i<n;++i)
        if(visit[i]==0) p[find(i)]=1;
    for(int i=0;i<n;++i) if(p[i]==1) ++a[len];
    for(int k=len-1;k>=0;--k)
    {
        visit[q[k+1]]=0;
        a[k]=a[k+1]+1;
        for(int i=0;i<g[q[k+1]].size();++i)
            if(visit[g[q[k+1]][i]]==0)
            {
                int x=find(q[k+1]),y=find(g[q[k+1]][i]);
                if(x!=y) f[y]=x,a[k]--;
            }
    }
    for(int i=0;i<=len;++i) printf("%d\n",a[i]);
    return 0;
}
