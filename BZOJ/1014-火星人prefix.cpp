#include <cstdio>
#include <cstring>
const int maxn = 100000 + 200;
const int base = 27;
void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}
struct splay_node {
    int fa, ch[2], size, c;
    unsigned int hash;
    splay_node() {
        fa = ch[0] = ch[1] = size = 0;
    }
    splay_node(int c): c(c) {
        fa = ch[0] = ch[1] = 0;
        size = 1;
    }
} T[maxn];
int root, lside, rside, node_num;
unsigned int wei[maxn];
#define ls (T[rt].ch[0])
#define rs (T[rt].ch[1])
void push_up(int rt) {
    T[rt].size = T[ls].size + T[rs].size + 1;
    T[rt].hash = T[ls].hash + T[rt].c * wei[T[ls].size] + T[rs].hash * wei[T[ls].size + 1];
}
void rot(int x, int d) {
    int y = T[x].fa, z = T[y].fa;
    T[y].ch[d ^ 1] = T[x].ch[d];
    if(T[x].ch[d] != 0) T[T[x].ch[d]].fa = y;
    T[x].ch[d] = y;
    T[z].ch[T[z].ch[1] == y] = x;
    T[x].fa = z;
    T[y].fa = x;
    push_up(y);
}
void print_tree(int rt) {
    if(rt == 0) return ;
    print_tree(ls);
    printf("num :%d size :%d ls :%d rs :%d fa :%d c :%c hash :%u\n", rt, T[rt].size, ls, rs, T[rt].fa, T[rt].c + 'a' - 1, T[rt].hash);
    print_tree(rs);
}
void splay(int x, int goal = 0) {
    if(x == goal) return;
    while(T[x].fa != goal) {
        int y = T[x].fa, z = T[y].fa;
        int rx = T[y].ch[0] == x, ry = T[z].ch[0] == y;
        if(z == goal) {
            rot(x, rx);
        } else {
            if(rx == ry) {
                rot(y, ry);
            } else {
                rot(x, rx);
            }
            rot(x, ry);
        }
    }
    push_up(x);
    if(goal == 0) {
        root = x;
    }
}
int select(int rt, int k) {
    for(; ;) {
        if(k <= T[ls].size) {
            rt = ls;
        } else if(T[ls].size + 1 < k) {
            k -= T[ls].size + 1;
            rt = rs;
        } else {
            return rt;
        }
    }
}
int &make_range(int l, int r) {
    splay(select(root, l - 1));
    //printf("%d %d\n", root, r + 1);
    //printf("%d\n", select(root, r + 1)); 
    splay(select(root, r + 1), root);
    return T[T[root].ch[1]].ch[0];
}
 
void insert(int pos, int c) {
    int &rt = make_range(pos + 2, pos + 1);
    //printf("%d\n", root);
//  print_tree(root);
    rt = node_num++;
    T[rt] = splay_node(c); T[rt].hash = T[rt].c; T[rt].fa = T[root].ch[1];
    push_up(T[root].ch[1]), push_up(root);
}
void modify(int pos, int c) {
    int rt = make_range(pos + 1, pos + 1);
    //printf("%d\n", root);
    //print_tree(root);
    //puts("");
    T[rt] = splay_node(c); T[rt].hash = T[rt].c; T[rt].fa = T[root].ch[1];
    push_up(T[root].ch[1]), push_up(root);
}
 
int query(int l, int r) {
    int lower = 0, upper = node_num - 3 - r + 1;
    if(upper <= 0) return 0;
    while(lower < upper) {
        int mid = (lower + upper + 1) >> 1;
        int hash1 = T[make_range(l + 1, l + mid)].hash;
        int hash2 = T[make_range(r + 1, r + mid)].hash;
        if(hash1 == hash2) {
            lower = mid;
        } else {
            upper = mid - 1;
        }
    }
    return lower;
}
 
char str[maxn];
int n, m;
void build_tree(int l, int r, int &rt) {
    if(r < l) return ;
    rt = node_num++;
    int mid = (l + r) >> 1;
    build_tree(l, mid - 1, T[rt].ch[0]);
    T[T[rt].ch[0]].fa = rt;
    //printf("%d %d\n", node_num, mid);
    T[rt].c = str[mid - 1] - 'a' + 1;
    build_tree(mid + 1, r, T[rt].ch[1]);
    T[T[rt].ch[1]].fa = rt;
    push_up(rt);
}
char gchar() {
    char ret = getchar();
    for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar());
    return ret;
}
 
 
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("1014.in", "r", stdin), freopen("1014.out", "w", stdout);
#endif
    wei[0] = 1;
    for(int i = 1; i < maxn; ++i) {
        wei[i] = wei[i - 1] * base;
    }
    node_num++;
    lside = node_num++;
    rside = node_num++;
    T[lside].ch[1] = rside;
    T[rside].fa = lside;
    T[lside].size = 2, T[rside].size = 1;
    root = lside;
    scanf("%s", str);
    n = strlen(str);
    build_tree(1, n, T[rside].ch[0]);
    T[T[rside].ch[0]].fa = rside;
    push_up(rside), push_up(lside);
    /*
    print_tree(root);
    printf("%d\n", query(1, 7));
 
    return 0;*/
    int m;
    scanf("%d", &m);
    while(m--) {
        char ope, ch;
        int l, r;
        ope = gchar();
        if(ope == 'Q') {
            scanf("%d%d", &l, &r);
            if(r < l) {
                swap(r, l);
            }
            printf("%d\n", query(l, r));
        } else if(ope == 'R') {
            scanf("%d", &l);
            ch = gchar();
            modify(l, ch - 'a' + 1);
    //      print_tree(root);
        } else {
            scanf("%d", &l);
            ch = gchar();
            insert(l, ch - 'a' + 1);
    //      printf("%d\n", T[root].size);
        }
    }
    return 0;
}
