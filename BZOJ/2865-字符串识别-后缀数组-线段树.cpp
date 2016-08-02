#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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
//#define generator_sbit
 
// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
// 永远不要相信自己的意志力
 
const int maxn = 500000 + 2000;
char s[maxn];
int len, f[maxn];
 
int n, m;
int rank[maxn], sa[maxn], tmp1[maxn], tmp2[maxn], sum[maxn], height[maxn];
 
void sa_build() {
    int *x = tmp1, *y = tmp2;
    reu(i, 0, m)
        sum[i] = 0;
    reu(i, 0, n)
        ++sum[x[i] = (s[i]-'a')];
    reu(i, 1, m)
        sum[i] += sum[i-1];
    red(i, n-1, 0)
        sa[--sum[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        reu(i, n-k, n)
            y[p++] = i;
        reu(i, 0, n)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        reu(i, 0, m)
            sum[i] = 0;
        reu(i, 0, n)
            ++sum[x[y[i]]];
        reu(i, 1, m)
            sum[i] += sum[i-1];
        red(i, n-1, 0)
            sa[--sum[x[y[i]]]] = y[i];
        swap(x, y);
        p=1, x[sa[0]]=0;
        reu(i, 1, n)
            x[sa[i]] = y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        if (p >= n) break;
        m = p;
    }
    for (int i=0; i<n; ++i)
        rank[sa[i]] = i;
    for (int i=0, k=0, j; i<n; ++i) {
        if (0 < k) --k;
        if (0 <= rank[i]-1) {
            j = sa[rank[i]-1];
            while (s[i+k] == s[j+k])
                ++k;
        }
        height[rank[i]] = k;
    }
}
 
bool sa_chk(int l, int r) {
    int ln = (r-l+1);
    int rk = rank[l];
    return ln > height[rk+1] && ln > height[rk];
}
 
int mn[maxn<<2], tg[maxn<<2];
 
bool chk(int l, int r) {
    return sa_chk(l, r);
}
 
void dpd(int &x, int y) {
    if (y < x)
        x = y;
}
 
void mark(int ql, int qr, int v, int l, int r, int rt) {
    if (ql <= l && r <= qr) {
        dpd(mn[rt], v);
        dpd(tg[rt], v);
        return ;
    }
    int mid = (l+r)>>1;
    if (tg[rt] != INF) {
        dpd(mn[rt<<1], tg[rt]);
        dpd(mn[rt<<1|1], tg[rt]);
        dpd(tg[rt<<1], tg[rt]);
        dpd(tg[rt<<1|1], tg[rt]);
        tg[rt] = INF;
    }
    if (ql <= mid) mark(ql, qr, v, l, mid, rt<<1);
    if (mid < qr) mark(ql, qr, v, mid+1, r, rt<<1|1);
    dpd(mn[rt], min(mn[rt<<1], mn[rt<<1|1]));
}
 
int get(int p, int l, int r, int rt) {
    if (l == r) {
        return mn[rt];
    }
    int mid = (l+r)>>1;
    if (tg[rt] != INF) {
        dpd(mn[rt<<1], tg[rt]);
        dpd(mn[rt<<1|1], tg[rt]);
        dpd(tg[rt<<1], tg[rt]);
        dpd(tg[rt<<1|1], tg[rt]);
        tg[rt] = INF;
    }
    if (p <= mid) return get(p, l, mid, rt<<1);
    else return get(p, mid+1, r, rt<<1|1);
}
 
void pre_mark(int ql, int qr, int v) {
    mark(ql, qr, v, 1, len, 1);
}
 
int main() {
    scanf("%s", s);
    len = strlen(s);
    s[len++] = 'z'+1;
    n = len, m = 30;
    sa_build();
    --len;
    s[len] = '\0';
    f[len] = len;
    for (int i = 0; i < (maxn<<2); ++i)
        mn[i] = tg[i] = len;
    for (int i = len-1; 0 <= i; --i) {
        f[i] = f[i+1];
        if (f[i] != len)
            pre_mark(i+1, f[i]+1, f[i]-i+1);
        while (i <= f[i]-1 && chk(i, f[i]-1)) {
            --f[i];
            pre_mark(i+1, f[i]+1, f[i]-i+1);
        }
    }
    for (int i = 1; i <= len; ++i) {
        printf("%d\n", get(i, 1, len, 1));
    }
 
    return 0;
}
