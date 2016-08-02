#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2e6;

struct Node
{
	int ch[2];
	int fix,val,size;
}T[maxn];

int &root=T[0].ch[1],node_num;

void push_up(int x)
{
	T[x].size=T[T[x].ch[0]].size+T[T[x].ch[1]].size+1;
}

void rot(int &x,int d)
{
	int son=T[x].ch[d^1];
	T[x].ch[d^1]=T[son].ch[d];
	T[son].ch[d]=x;
	push_up(x);
	push_up(son);
	x=son;
}

void insert(int &x,int val)
{
	if(x==0)
	{
		x=++node_num;
		T[x]=(Node){0,0,rand(),val,1};
	}
	else
	{
		int d=T[x].val<val;
		insert(T[x].ch[d],val);
		if(T[T[x].ch[d]].fix<T[x].fix)
			rot(x,d^1);
	}
	push_up(x);
}

int min_node(int x)
{
	if(T[x].ch[0]==0)
		return x;
	return min_node(T[x].ch[0]);
}

void del_min(int fa,int &x)
{
	if(T[x].ch[0]==0)
	{
		T[fa].ch[0]=T[x].ch[1];
		if(x==root)
			root=T[x].ch[1];
		return;
	}
	else
	{
		del_min(x,T[x].ch[0]);
		push_up(x);
	}
}

int kth(int x,int k)
{
	if(T[T[x].ch[0]].size+1==k)
		return x;
	if(k<T[T[x].ch[0]].size+1)
		return kth(T[x].ch[0],k);
	return kth(T[x].ch[1],k-T[T[x].ch[0]].size-1);
}

void init()
{
	T[0]=(Node){0,0,0,0,0};
}
	
void print_tree(int x)
{
	if(x==0)
		return;
	printf("Node Num: %d : \n",x);
	printf("	val : %d   size : %d  fix : %d\n",T[x].val,T[x].size,T[x].fix);
	printf("		ch[0] (left) : %d  ch[1] (right) : %d\n",T[x].ch[0],T[x].ch[1]);
	print_tree(T[x].ch[0]);
	print_tree(T[x].ch[1]);
}

bool check(int x)
{
	if(x==0 || T[x].ch[1]==0 || T[x].ch[0]==0)
		return true;
	if(T[T[x].ch[0]].val<=T[x].val && T[x].val<=T[T[x].ch[1]].val)
		return check(T[x].ch[0]) && check(T[x].ch[1]);
	else
		return false;
}

int main()
{
	int n,min,delta=0,lenum=0;
	scanf("%d %d\n",&n,&min);
	srand(n*min);
	init();
	for(int i=1;i<=n;++i)
	{
		char c;
		int val;
		scanf("%c",&c);
		scanf("%d\n",&val);
	//	printf("%c %d\n",c,val);
		if(c=='I')
		{
			if(min<=val)
				insert(root,val-delta);
		}
		if(c=='F')
		{
			if(val>T[root].size)
			{
				printf("-1\n");
				continue;
			}
			printf("%d\n",T[kth(root,T[root].size-val+1)].val+delta);
		}
		if(c=='A')
		{
			delta+=val;
		}
		if(c=='S')
		{
			delta-=val;
			int x=min_node(root);
			while(T[x].val+delta<min && T[root].size!=0)
			{
				del_min(0,root);
				x=min_node(root);
				++lenum;
			}
		}
	}
	printf("%d\n",lenum);
	return 0;
}
