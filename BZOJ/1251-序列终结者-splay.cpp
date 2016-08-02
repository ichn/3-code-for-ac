#include <cstdio>
#include <cstring>
//#include <debugger.h>
const int maxn = 100000 + 50;
const int INF = 0x3f3f3f3f;

inline int max(int a,int b){return a<b?b:a;}
inline void swap(int &a,int &b) {int t=a;a=b;b=t;}
struct Splay_Tree
{
	struct SN
	{
		int Val,Add,Max,Size,son[2];
		bool Rev;
		void init(int _val)
		{
			Max=Val=_val;
			Size=1;
			Rev=false;
			Add=son[0]=son[1]=0;
		}
	}T[maxn];
	int fa[maxn],root;
	
	void Push_Up(int x)
	{
		T[x].Max=T[x].Val;T[x].Size=1;
		if(T[x].son[0])
		{
			T[x].Max=max(T[x].Max,T[T[x].son[0]].Max);
			T[x].Size+=T[T[x].son[0]].Size;
		}
		if(T[x].son[1])
		{
			T[x].Max=max(T[x].Max,T[T[x].son[1]].Max);
			T[x].Size+=T[T[x].son[1]].Size;
		}
	}

	void Push_Down(int x)
	{
		if(x==0) return;
		if(T[x].Add)
		{
			if(T[x].son[0])
			{
				T[T[x].son[0]].Add+=T[x].Add;
				T[T[x].son[0]].Val+=T[x].Add;
				T[T[x].son[0]].Max+=T[x].Add;
			}
			if(T[x].son[1])
			{
				T[T[x].son[1]].Add+=T[x].Add;
				T[T[x].son[1]].Val+=T[x].Add;
				T[T[x].son[1]].Max+=T[x].Add;
			}
			T[x].Add=0;
		}
		if(T[x].Rev)
		{
			T[x].Rev=false;
			if(T[x].son[0]) T[T[x].son[0]].Rev^=1;
			if(T[x].son[1]) T[T[x].son[1]].Rev^=1;
			swap(T[x].son[0],T[x].son[1]);
		}
	}

	void Rotate(int x,int kind)
	{
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind];
		fa[T[x].son[kind]]=y;
		T[x].son[kind]=y;
		fa[y]=x;
		T[z].son[T[z].son[1]==y]=x;  //这个很巧妙啊。
		fa[x]=z;
		Push_Up(y);
	}
	
	void splay(int x,int goal)
	{
		if(x==goal) return;
		while(fa[x]!=goal)
		{
			int y=fa[x],z=fa[y];
			Push_Down(z),Push_Down(y),Push_Down(x);
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if(z==goal) Rotate(x,rx);
			else
			{
			
				if(rx==ry) Rotate(y,ry);
				else Rotate(x,rx);
				Rotate(x,ry);
			}
		}
		Push_Up(x);
		if(goal==0) root=x;
	}
	
	int Select(int pos)
	{
		int u=root;
		Push_Down(u);
		while(T[T[u].son[0]].Size!=pos)
		{
			if(T[T[u].son[0]].Size>pos) u=T[u].son[0];
			else
			{
				pos-=T[T[u].son[0]].Size+1;
				u=T[u].son[1];
			}
			Push_Down(u);
		}
		return u;
	}
	
	void update(int L,int R,int val)
	{
		int l=Select(L-1),r=Select(R+1);
		splay(l,0);
		splay(r,l);
		T[T[r].son[0]].Max+=val;
		T[T[r].son[0]].Add+=val;
		T[T[r].son[0]].Val+=val;
	}

	void Reverse(int L,int R)
	{
		int l=Select(L-1),r=Select(R+1);
		splay(l,0);
		splay(r,l);
		T[T[r].son[0]].Rev^=1;
	}

	int query_Max(int L,int R)
	{
		int l=Select(L-1),r=Select(R+1);
		splay(l,0);
		splay(r,l);
		return T[T[r].son[0]].Max;
	}
    
	int build(int l,int r)
	{
		if(l>r) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1;
		T[mid].son[0]=build(l,mid-1);
		T[mid].son[1]=build(mid+1,r);
		fa[T[mid].son[0]]=mid;
		fa[T[mid].son[1]]=mid;
		Push_Up(mid);
		return mid;
	}
	
	void init(int n)
	{
		T[0].init(-INF),T[1].init(-INF),T[n+2].init(-INF);
		for(int i=2;i<=n+1;++i) T[i].init(0);
		root=build(1,n+2); fa[root]=0;
		fa[0]=0; T[0].son[1]=root; T[0].Size=0;
	}
};
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
Splay_Tree solve;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
//	freopen("out","w",stdout);
#endif
	int n,m;
	scanf("%d%d",&n,&m);
	solve.init(n);
	for(int i=1;i<=m;++i)
	{
		int K,L,R;
		K=read();
		L=read();
		R=read();
		if(K==1)
		{
			int val=read();
			solve.update(L,R,val);
		}
		if(K==2)
			solve.Reverse(L,R);
		if(K==3)
			printf("%d\n",solve.query_Max(L,R));
	}
	return 0;
}
