Edge e;
int cnt, pre[MaxN], bl[MaxN], low[MaxN], stk[MaxN], top, cl;
void dfs(int u) {
    pre[u] = low[u] = ++cl, stk[++top] = u;
    for(int i = e.head[u], v; i != -1; i = e.next[i])
        if(!pre[v = e.to[i]])
            dfs(v), low[u] = min(low[v], low[u]);
        else if(!bl[v]) low[u] = min(pre[v], low[u]);
    // 注意!bl[v]，否则v不在u所在的SCC内。
    if(low[u] == pre[u])
        for(++cnt, stk[top + 1] = -1; stk[top + 1] != u; --top)
            bl[stk[top]] = cnt;
}
void find_scc() {
    cnt = top = cl = 0;
    memset(low, 0, sizeof low);
    memset(bl, 0, sizeof bl);
    for(int i = 1; i <= n; ++i)
        if(!pre[i]) dfs(i);
}
