#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
};
using namespace my_useful_tools;

const int maxv = 11000 + 100, maxe = maxv * 8;

const int maxn = 100;

class MCMF {
	public:

	int edge, head[maxv], to[maxe], next[maxe];
	int cap[maxe], cost[maxe];
	void addedge(int u, int v, int c, int w) {
		to[edge] = v, next[edge] = head[u];
		cap[edge] = c, cost[edge] = w;
		head[u] = edge++;
	}
	void addEdge(int u, int v, int c, int w) {
		addedge(u, v, c, w);
		addedge(v, u, 0, -w);
	}

	int s, t, loc;
	
	MCMF() {
		edge = 0;
		loc = 0;
		memset(head, -1, sizeof head);
	}

	int inq[maxv], que[maxv], dis[maxv], pre[maxv], front, back;
	int Flow, Cost, arg[maxv];

	bool spfa() {
		rep(i, 0, loc) dis[i] = INF;
		dis[s] = 0;
		que[front=back=0]=s, inq[s] = true;
		arg[s] = INF;
		while (front <= back) {
			int u = que[front++];
			inq[u] = false;
			for (int i=head[u]; i!=-1; i=next[i]) {
				int v = to[i], c = cost[i], f = cap[i];
				if (dis[u]+c < dis[v]  &&  f > 0) {
					dis[v] = dis[u]+c;
					arg[v] = min(f, arg[u]);
					pre[v] = i;
					if (!inq[v]) {
						que[++back] = v;
						inq[v] = true;
					}
				}
			}
		}
		return dis[t]!=INF;
	}

	pair<int, int> mcmf() {
		Flow = Cost = 0;
		while (spfa()) {
			int u = t;
			Flow += arg[t];
			Cost += dis[t]*arg[t];
			while (u != s) {
				int i = pre[u];
				cap[i] -= arg[t];
				cap[i^1] += arg[t];
				u = to[i^1];
			}
		}
		return make_pair(Flow, Cost);
	}

};


MCMF sv;
int n, g[maxn][maxn];

int hash[maxn*maxn], ind[maxn];
int getID(int x, int y) {
	int p = (x-1)*n+y;
	if (hash[(x-1)*n+y])
		return hash[p];
	return hash[p] = ++sv.loc;
}
 
int main() {
//#ifdef love_sbit
	file(2597);
//#endif

	fr(n);
	int b = n*(n-1)/2;
	sv.s = 0;
	rep(i, 1, n)
		rep(j, 1, n) {
			g[i][j] = fr();
			if (i <= j)
				continue;
			if (g[i][j]==0) {
				sv.addEdge(getID(i, j), b+j, 1, 0);
				++ind[j];
			} else if (g[i][j]==1) {
				sv.addEdge(getID(i, j), b+i, 1, 0);
				++ind[i];
			} else if (g[i][j] == 2) {
				sv.addEdge(getID(i, j), b+j, 1, 0);
				++ind[j];
				sv.addEdge(getID(i, j), b+i, 1, 0);
				++ind[i];
			}
		}
	rep(i, 1, b) {
		sv.addEdge(sv.s, i, 1, 0);
	}

	sv.t = b+n+1;
	rep(i, 1, n) {
		int u = b+i;
		rep(j, 0, ind[i]-1)
			sv.addEdge(u, sv.t, 1, 2*j+1);
	}

	sv.loc = b+n+1;
	pair<int, int> res = sv.mcmf();
	
	int ans = n*(n-1)*(n-2)/2/3+n*(n-1)/2/2-res.second/2;

	printf("%d\n", ans);
	//printf("%d\n", res.second);
 
	rep(i, 1, n)
		rep(j, 1, n) {
			if (i<=j || g[i][j]!=2)
				continue;
			int u = getID(i, j);
			for (int s=sv.head[u]; s!=-1; s=sv.next[s]) {
				if (sv.to[s] > u && sv.cap[s] > 0) {
					if (sv.to[s] == b+i)
						g[i][j]=0, g[j][i]=1;
					else g[i][j]=1, g[j][i]=0;
				}
			}
		}
	rep(i, 1, n)
		rep(j, 1, n)
			printf("%d%c", g[i][j], " \n"[j==n]);

	return 0;
}


/*
【NOI2008志愿者招募 WC2007剪刀石头布 POI2002滑雪者】网络流总结

先讲讲这几道题的题解和心得：

 

1.志愿者招募：

   题意：见原题

   根据流量平衡方程来构图非常方便，而且简单易懂，以后可能成为做网络流的神法之一

   简单记一下流量平衡方程构图法的步骤：

      a.列出需求不等式

      b.通过设置松弛变量，将不等式变成等式

      c.两两相减，得到流量平衡方程

      d.观察方程，>0表示得到的流量，<0表示输出的流量，如果是跟需求量有关的变量，则跟源点和汇点连，如果是跟费用有关的变量则把相关的方程对应连边

      e.使用最小费用最大流算法求解

   具体连边方法：令oo=maxlongint，连(i,j,k,l)表示i向j连容量为k，费用为l的边

      a.令a[0]=a[n+1]=0，对于a[i]-a[i-1]>0连(s,i,a[i]-a[i-1],0)，而a[i]-a[i-1]<0，则连(i,t,a[i-1]-a[i],0)

      b.连(i+1,i,oo,0)

      c.对于每类志愿者(x,y,z)，连(x,y+1,oo,z)

 

2.剪刀石头布：

   题意：给你一个有向完全图，其中有一些边已经确定，要求你给未定向的边定向，使得图中的三元环尽量多

   本题需要转化几次模型，而每一步都非常神奇！

   首先单独考虑每个三元组，这3个点不成环的充要条件是存在1个点入度（或出度）=2，证明是显然的

   利用补集转化的思想，可以得到原图所成的三元环个数=C(n,3)-不成环的三元组个数

   有了这一点，问题便清晰了不少，可以列出目标式：

      ans=C(n,3)-∑C(di,2) (di为i的入度)

   变形得到

      ans=C(n,3)-(∑di^2)/2+∑di/2

   而∑di=n*(n-1)/2为常数，所以我们要最大化ans，即要最小化∑di^2

   由此可以得到一个二分图网络流模型，以原图中的未定向的边为点集A，原图中的点当成点集B

   未定向的边的定向过程相当于将流量分配给它的端点，即给其中一个端点的入度+1

   而我们只要由源点向A集中的点连容量为1的边，A集中的点向它对应的两个端点连容量为1的边，B集中的点向汇点连费用边就差不多解决这道题了

   然而这题还没完，通常的费用流都只能解决线性费用，这里的费用显然不是线性的！（其实就是2次式）

   怎么办？

   观察：1=1^2,1+3=2^2,1+3+5=3^2,1+3+5+7=4^2...

   方法来了：我们将一条容量为+oo，费用为流量的平方的费用边拆成若干条容量为1，费用依次为1^2,2^2-1^2,3^2-2^2...

   这样子连出来，由于我们求的是最小费用最大流，所以算法会自动从小到大找费用边，也就是说，我们流i的流量所产生的费用就会是i^2了！

   就这样，本题被完美解决，不仅如此，还留下了一个解决非线性费用边的处理神法，拆边！只要是多项式函数的费用，都可以这样拆边来实现！

   这道题太牛B了！

 

3.滑雪者

   题意：给你一个有向拓扑图（其实条件中还说它一个平面图，这种做法没有用到这个性质），而且只有一个源点，一个汇点，要求你用最少的源点到汇点的路径覆盖所有的边

   虽然mt用了一个怪怪的贪心A了9个点，但我们还是想寻求正解的

   会不会是网络流？经验告诉我们，一般怪怪的题可以用网络流做的可能性是非常大的，这个题呢？

   硬往网络流上想，好像题目就是求一个所谓的“带有下界的最小流”，每条边的容量下界为1，我们相当于要求个最小流

   哪有这种算法？

   世事难料，（看了题解之后），竟然真的有这种算法，求“带有下界的最小流”，无语。。

   无语归无语，算法还得学，这个神奇算法其实非常简单

   就像一般的上下界网络流一样设置s',t'，对于原图中下界为k的边(i,j)，让s'向j连k，i向t'连k，由s'向t'求个最大流，我们就可以得到原图中一个满足所有边的下界的可行流

   可是题目还要这个流最小，怎么办？

   很简单，就从原图中的汇点向源点做一次最大流来“退流”就可以了，由于我们已经满足了原图中的所有条件（下界和流量平衡方程），而这个退流的过程也是不会破坏条件的，所以这样退一次流就可以得到题目要求的“带有下界的最小流”了！

   竟然是这样的暴力，这样的裸，还竟然真的这样搞出来了！不得不佩服网络流的神奇功能，也佩服想出这个方法的大牛

 

小结：

   网络流的本质其实就是贪心

   网络流和不等式，流量平衡方程密不可分，在某种意义上，他们甚至可以说是等价的

   网络流往往能处理一些依赖关系非常强的最优化问题

   网络流的一些经典模型要熟悉，如最大权闭合图一类的最小割模型的应用，平面图网络流转最短路（反过来也不无可能的说）

   如果要用网络流来搞题目，一定要列出目标式，明确要最优化的方向，通过对式子的变形来让看起来没法做的变得可以做；或是直接列流量平衡方程来构图

   费用流相当于是给最大流增了一维，功能更强大的代价是速度慢了

   对于网络流算法的选择，自己要熟悉并完全能搞定1种，我用的是dinic，其实sap也不错，只是近期我不会换了，关于费用流，我和盾盾借鉴了zkw大牛的算法，研究出了一种我们命名为“距离标号连续最短增广路算法”的算法，效果非常好，具体的内容下一篇文章再写

   最后一点，网络流真是好东西
   
   */
