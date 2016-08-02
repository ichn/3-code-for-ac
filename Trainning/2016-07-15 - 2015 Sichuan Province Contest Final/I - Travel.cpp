#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 100;
const int maxm = 5e5 + 100;

int h[maxn], to[maxm*2], nxt[maxm*2];
int ec;

set<pair<int, int> > rd;
void addedge(int u, int v) {
    to[ec] = v, nxt[ec] = h[u], h[u] = ec++;
    to[ec] = u, nxt[ec] = h[v], h[v] = ec++;
    rd.insert(make_pair(u, v));
    rd.insert(make_pair(v, u));
}


int n, m, a, b;

int dis[maxn], inq[maxn];

queue<int> que;

long long  ans;

bool flag;
void solve() {
    if (flag) {
        bool ok = false;
        for (int i = 2; i < n; ++i) {
            if (rd.find(make_pair(i, 1)) == rd.end() && 
                    rd.find(make_pair(i, n)) == rd.end()) {
                ok = true;
                break;
            }
        }
        if (ok) ans = min(ans, b * 2LL);
        cout << ans << endl;
        return ;
    }
    memset(dis, 0x3f, sizeof dis);
    memset(inq, false, sizeof inq);
    dis[1] = 0;
    inq[1] = 1;
    que.push(1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = h[u]; i != -1; i = nxt[i]) {
            int v = to[i];
            if (dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                if (!inq[v])
                    que.push(v), inq[v] = true;
            }
        }
    }
    if (dis[n] != 0x3f3f3f3f)
        ans = min(ans, (long long)dis[n] * a);
    cout << ans << endl;
}

int main() {
#ifdef lol
    freopen("i.in", "r", stdin);
    freopen("i.out", "w", stdout);
#endif

    while (scanf("%d %d %d %d", &n, &m, &a, &b) != EOF) {
        memset(h, -1, sizeof h);
        ans = 0x3f3f3f3f;
        ec = 0;
        flag = false;
        rd.clear();
        for (int i = 1; i <= m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            addedge(u, v);
            if (u == 1 && v == n)
                ans = a, flag = true;
            if (u == n && v == 1)
                ans = a, flag = true;
        }
        if (!flag)
            ans = b;
        solve();
    }
    return 0;
}
