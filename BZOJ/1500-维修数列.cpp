#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 500000 + 10000;
const int INF  = 0x7fffffff/2;

bool check(int x)
{
	return x!=1 && x!=2 && x!=0;
}

struct Splay
{
	struct Splay_Node
	{
		int fa,ch[2];
		int val,size,sum,lmax,rmax,maxs;
		int rev,same;
		void init(int k,int s=1)
		{
			size=s;
			val=sum=lmax=rmax=maxs=k;
			ch[0]=ch[1]=fa=0;
			rev=same=0;
		}
	}T[maxn];
	int root;

	struct Storage
	{
		int top,stack[maxn];
		Storage()
		{
			top=0;
			for(int i=3;i<maxn;++i)
				stack[++top]=i;
		}

		int Ask()
		{
			return stack[top--];
		}

		void Add(int x)
		{
			stack[++top]=x;
		}
	}S;

	void push_down(int x)
	{
		if(T[x].rev)
		{
			T[x].rev=0;
			swap(T[x].ch[0],T[x].ch[1]);
			swap(T[x].lmax,T[x].rmax);
			if(check(T[x].ch[0])) T[T[x].ch[0]].rev^=1;
			if(check(T[x].ch[1])) T[T[x].ch[1]].rev^=1;
		}
		if(T[x].same)
		{
			T[x].same=0;
			if(check(T[x].ch[0])) T[T[x].ch[0]].same=1,T[T[x].ch[0]].val=T[x].val;
			if(check(T[x].ch[1])) T[T[x].ch[1]].same=1,T[T[x].ch[1]].val=T[x].val;
			T[x].sum=T[x].lmax=T[x].rmax=T[x].maxs=T[x].size*T[x].val;
			if(T[x].val<0)
				T[x].lmax=T[x].rmax=T[x].maxs=T[x].val;
		}
	}

	void push_up(int x)
	{
		T[x].size=T[T[x].ch[0]].size+T[T[x].ch[1]].size+1;
		T[x].sum=T[T[x].ch[0]].sum+T[T[x].ch[1]].sum+T[x].val;
		T[x].lmax=max(T[T[x].ch[0]].lmax,T[T[x].ch[0]].sum+T[x].val+max(T[T[x].ch[1]].lmax,0));
		T[x].rmax=max(T[T[x].ch[1]].rmax,T[T[x].ch[1]].sum+T[x].val+max(T[T[x].ch[0]].rmax,0));
		T[x].maxs=max(T[T[x].ch[1]].maxs,T[T[x].ch[0]].maxs);
		T[x].maxs=max(T[x].maxs,T[x].val);
		T[x].maxs=max(T[x].maxs,T[x].val+max(T[T[x].ch[0]].rmax,0)+max(T[T[x].ch[1]].lmax,0));
	}

	void rot(int x,int d)
	{
		int y=T[x].fa,z=T[y].fa;
		push_down(T[y].ch[d]),push_down(T[x].ch[d^1]),push_down(T[x].ch[d]);
		T[y].ch[d^1]=T[x].ch[d];
		T[T[x].ch[d]].fa=y;
		T[x].ch[d]=y;
		T[y].fa=x;
		T[z].ch[T[z].ch[1]==y]=x;
		T[x].fa=z;
		push_up(y);
	}

	void splay(int x,int goal)
	{
		push_down(x);
		if(x==goal)	return ;
		for(;T[x].fa!=goal;)
		{
			int y=T[x].fa,z=T[y].fa;
			int rx=T[y].ch[0]==x,ry=T[z].ch[0]==y;
			if(z==goal) rot(x,rx);
			else
			{
				if(rx==ry) rot(y,ry);
				else rot(x,rx);
				rot(x,ry);
			}
		}
		push_up(x);
		if(goal==0) root=x;
	}

	void select(int k,int goal)
	{
		int u=root;
		for(;;)
		{
			push_down(u);
			if(k<T[T[u].ch[0]].size+1)
				u=T[u].ch[0];
			else if(T[T[u].ch[0]].size+1<k)
			{
				k-=T[T[u].ch[0]].size+1;
				u=T[u].ch[1];
			}
			else break;
		}
		splay(u,goal);
	}

	void Same(int l,int r,int val)
	{
		select(l,0),select(r,root);
		int pos=T[T[root].ch[1]].ch[0];
		T[pos].same=1;
		T[pos].val=val;
		splay(pos,0);
	}

	void Rev(int l,int r)
	{
		select(l,0),select(r,root);
		int pos=T[T[root].ch[1]].ch[0];
		T[pos].rev^=1;
		splay(pos,0);
	}

	int Sum(int l,int r)
	{
		select(l,0),select(r,root);
		int pos=T[T[root].ch[1]].ch[0];
		int ans=T[pos].sum;
		splay(pos,0);
		return ans;
	}

	int Max()
	{
		return T[root].maxs;
	}

	int a[maxn];

	void build(int &pos,int l,int r)
	{
		if(r<l) return ;
		int mid=(l+r)>>1;
		pos=S.Ask();
		T[pos].init(a[mid]);
		build(T[pos].ch[0],l,mid-1);
		if(T[pos].ch[0]!=0) T[T[pos].ch[0]].fa=pos;
		build(T[pos].ch[1],mid+1,r);
		if(T[pos].ch[1]!=0) T[T[pos].ch[1]].fa=pos;
		push_up(pos);
	}

	void Add(int l,int r,int n)
	{
		for(int i=1;i<=n;++i)
			cin>>a[i];
		select(l,0),select(r,root);
		int &pos=T[T[root].ch[1]].ch[0];
		build(pos,1,n);
		if(pos!=0) T[pos].fa=T[root].ch[1];
		splay(pos,0);
	}

	void del_travel(int x)
	{
		if(x==0) return ;
		del_travel(T[x].ch[0]);
		S.Add(x);
		del_travel(T[x].ch[1]);
	}

	void Del(int l,int r)
	{
		select(l,0),select(r,root);
		int &pos=T[T[root].ch[1]].ch[0];
		del_travel(pos);
		pos=0;
		splay(T[root].ch[1],0);
	}

	void init(int n)
	{
		T[0].init(-INF,0),T[1].init(-INF,2),T[2].init(-INF,1);
		root=1;
		T[0].sum=T[1].sum=T[2].sum=0;
		T[1].ch[1]=2;
		T[2].fa=1;
		Add(1,2,n);
	}
}S;

int main()
{
//	freopen("seq2005.in","r",stdin);
//	freopen("seq2005.out","w",stdout);
	ios_base::sync_with_stdio(false);

	int n,m;
	string tmp;
	cin>>n>>m;

	S.init(n);
	for(int i=1;i<=m;++i)
	{
		int pos,tot,val;
		cin>>tmp;
		if(tmp=="INSERT")
		{
			cin>>pos>>tot;
			S.Add(pos+1,pos+2,tot);
		}
		if(tmp=="DELETE")
		{
			cin>>pos>>tot;
			S.Del(pos,pos+tot+1);
		}
		if(tmp=="MAKE-SAME")
		{
			cin>>pos>>tot>>val;
			S.Same(pos,pos+tot+1,val);
		}
		if(tmp=="REVERSE")
		{
			cin>>pos>>tot;
			S.Rev(pos,pos+tot+1);
		}
		if(tmp=="GET-SUM")
		{
			cin>>pos>>tot;
			printf("%d\n",S.Sum(pos,pos+tot+1));
		}
		if(tmp=="MAX-SUM")
		{
			printf("%d\n",S.Max());
		}
	}
	return 0;
}

