#include <bits/stdc++.h>
using namespace std;
#define foreach(s, i) for (__typeof(i.begin()) s = i.begin(); s != i.end(); ++s)
const int maxn = 8e4 + 100;
const int maxm = maxn * 2;

int e, h[maxn], to[maxm], nxt[maxm];
void addEdge(int u, int v) {
	nxt[e] = h[u], to[e] = v, h[u] = e++;
}
int n, p, q;

vector<int> disc;
int discrete[maxn], disc_rng;
int getDiscrete(int c) {
	return lower_bound(disc.begin(), disc.end(), c) - disc.begin() + 1;
}

class Box {

	public:
	static const int maxNode = (80000 + 200)<<2;
	//multiset<int> moni;

	int tr[maxNode], n;
	void upd(int rt) {
		tr[rt] = tr[rt<<1] + tr[rt<<1|1];
	}

	void insert(int l, int r, int rt, int val) {
		if (l == r) {
			++tr[rt];
			return ;
		}
		int mid = (l + r) >> 1;
		if (val <= mid) insert(l, mid, rt<<1, val);
		else insert(mid+1, r, rt<<1|1, val);
		upd(rt);
	}

	void erase(int l, int r, int rt, int val) {
		if (l == r) {
			--tr[rt];
			return ;
		}
		int mid = (l + r) >> 1;
		if (val <= mid) erase(l, mid, rt<<1, val);
		else erase(mid + 1, r, rt<<1|1, val);
		upd(rt);
	}

	int qKth(int l, int r, int rt, int k) {
		if (l == r) {
			return l;
		}
		int mid = (l + r) >> 1;
		if (tr[rt<<1] >= k) return qKth(l, mid, rt<<1, k);
		else return qKth(mid+1, r, rt<<1|1, k - tr[rt<<1]);
	}

	int qRnk(int l, int r, int rt, int val) {
		if (l == r) {
			return tr[rt];
		}
		int mid = (l + r) >> 1;
		if (val <= mid) return qRnk(l, mid, rt<<1, val);
		return tr[rt<<1] + qRnk(mid+1, r, rt<<1|1, val);
	}


	Box(int __val_rng) {
		n = __val_rng + 10;
		memset(tr, 0, sizeof tr);
	//	moni.clear();
	}

	void insert(int val) {
		insert(1, n, 1, val);
	//	moni.insert(val);
	}

	void erase(int val) {
		erase(1, n, 1, val);
	//	moni.erase(lower_bound(moni.begin(), moni.end(), val));
	}

	int qKth(int k) {
	//	int cnt = 1;
	//	multiset<int>::iterator it = moni.begin();
	//	while (cnt < k) {
	//		++cnt;
	//		++it;
	//	}
	//	return *it;
		return qKth(1, n, 1, k);
	}

	int qRnk(int val) {
		return qRnk(1, n, 1, val);
	}

	int pred(int val) {
		return qKth(qRnk(val)-1);
	}

	int succ(int val) {
		return qKth(qRnk(val)+1);
	}
} *box;

int ans[maxn];

int blk[maxn], nBlk, SZ;
int fa[maxn], dep[maxn], sz[maxn], dfn[maxn], dfs_clock, stk[maxn], top;
int pa[maxn][21];
vector<int> rela[maxn];


void dfs(int u) {
	dfn[u] = ++dfs_clock;
	int tmp = top;
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (v != fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			if (top - tmp >= SZ) {
				++nBlk;
				while (top != tmp)
					blk[stk[top--]] = nBlk;
			}
		}
	}
	stk[++top] = u;
}

struct Panzi {
	int u, v, c;
	void read() {
		scanf("%d %d %d", &u, &v, &c);
		disc.push_back(c);
	}
	bool operator < (const Panzi&rhs) const {
		return c < rhs.c;
	}
} P[maxn];

struct Querys {
	int id;
	int u, v, k;
	void read() {
		scanf("%d %d %d", &u, &v, &k);
		if (dfn[u] > dfn[v]) swap(u, v);
	}
	bool operator < (const Querys&rhs) const {
		return blk[u] < blk[rhs.u] || (blk[u] == blk[rhs.u] && blk[v] < blk[rhs.v]);
	}
} Q[maxn];

void init() {

	nBlk = dfs_clock = top = 0;
	SZ = (int)sqrt(n + .5);

	fa[1] = 0;
	dep[0] = 0;
	dep[1] = 1;
	dfs(1);

	for (int i = 1; i <= p; ++i) {
		rela[P[i].u].push_back(P[i].c);
		rela[P[i].v].push_back(P[i].c);
	}

	box = (new Box(disc_rng + 1));
	for (int i = 1; i <= n; ++i)
		pa[i][0] = fa[i];
	for (int i = 1; i <= 20; ++i)
		for (int j = 1; j <= n; ++j)
			pa[j][i] = pa[pa[j][i - 1]][i - 1];
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; 0 <= i; --i)
		if (dep[pa[u][i]] >= dep[v])
			u = pa[u][i];
	if (u == v) return u;
	for (int i = 20; 0 <= i; --i)
		if (pa[u][i] != pa[v][i])
			u = pa[u][i], v = pa[v][i];
	return pa[u][0];
}


int cnt[maxn];
bool on[maxn];
vector<int> r1, r2;

void move(int a, int b) {
	if (a == b) return ;
	r1.clear(), r2.clear();
	int c = lca(a, b);
	int t = a;
	while (t != c)
		r1.push_back(t), t = fa[t];
	t = b;
	while (true) {
		r2.push_back(t);
		if (t == c) break;
		t = fa[t];
	}

	reverse(r2.begin(), r2.end());
	foreach(i, r2)
		r1.push_back(*i);

	bool flg = true;
	foreach(i, r1) {
		if (flg) {
			vector<int>::iterator j = i;
			++j;
			if (j == r1.end() || !on[*j]) {
				flg = false;
				continue;
			}
		}
		if (flg) {
			foreach(j, rela[*i]) {
				if (cnt[*j] == 2) {
					box->erase(*j);
				}
				--cnt[*j];
			}
			on[*i] = false;
		} else {
			foreach(j, rela[*i]) {
				if (cnt[*j] == 1) {
					box->insert(*j);
				}
				++cnt[*j];
			}
			on[*i] = true;
		}
	}
}

void solve() {
	int a = 1, b = 1;
	foreach(s, rela[1]) {
		if (cnt[*s] == 1) {
			box->insert(*s);
		}
		++cnt[*s];
	}
	on[1] = true;

	for (int i = 1; i <= q; ++i) {
		move(b, Q[i].u);
		b = Q[i].u;
		move(a, Q[i].v);
		a = Q[i].v;
		ans[Q[i].id] = box->qKth(Q[i].k);
	//	cerr << Q[i].k << ' ' << box->tr[1] << endl;
	}
}

int main() {
	freopen("fruit.in", "r", stdin);
	freopen("fruit.out", "w", stdout);

	e = 0;
	memset(h, -1, sizeof h);

	scanf("%d %d %d", &n, &p, &q);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 1; i <= p; ++i) {
		P[i].read();
	}
	sort(disc.begin(), disc.end());
	disc_rng = disc.size();
	for (int i = 0; i < disc_rng; ++i)
		discrete[i + 1] = disc[i];
	sort(P + 1, P + p + 1);
	for (int i = 1; i <= p; ++i) {
		P[i].c = i;
	}

	init();

	for (int i = 1; i <= q; ++i) {
		Q[i].id = i;
		Q[i].read();
	}
	sort(Q + 1, Q + q + 1);

	solve();

	for (int i = 1; i <= q; ++i) {
		printf("%d\n", discrete[ans[i]]);
	}

	return 0;
}
/*
syntax on
color slate
set nocompatible
set ru
set nu
set nobackup
set noswapfile
set autoread
set autochdir
set backspace=indent,eol,start
set softtabstop=4
set shiftwidth=4
set noexpandtab
set ts=4
set guifont=Courier_New
set list
set listchars=tab:>\ 
",eol:<
set showtabline=0
set go=
set cin
set autoindent
set smartindent
set smarttab
let mapleader='-'
map<leader>sv :source $MYVIMRC<CR>
map<leader>nv :tabnew $MYVIMRC<CR>

map<F9> :w<CR>:!g++ -g % -o %<.exe -Wall -lm && %<.exe<CR>
map<F8> :w<CR>:!g++ -g % -o %<.exe -Wall -lm && gdb %<.exe<CR>

 
 */

/*
 作曲 : REVO
作词 : REVO
君の大好きなこの旋律(Melodie)…大空へと响け口风琴(Harmonica)… 你最喜歡的這旋律(Melodie)…在天空中響遍的口琴(Harmonica)…
天使 が抱いた窓枠の画布(Toile)…ねぇ…その风景画(Paysage)…绮丽かしら? 天使擁抱著窗框裡的畫布(Toile)…喂…這幅風景畫(Paysage)…漂亮嗎？
 
其れは(ce)—— 這是(ce)——
风が运んだ…淡い花弁…春の追想... 被風帶來的…淡淡的花瓣…春之追憶
绮丽な音…呗う少女(Monica)…鸟の啭り…针は进んだ → 美麗的音色…詠唱的少女(Monica)…鳥兒的鳴叫…指針的前進 →
其れは(ce)—— 這是(ce)——
苍が系いで…流れる云…夏の追想... 與穹蒼緊連的…流動的雲…夏之追憶
绮丽な音…谣う少女(Monica)…蝉の时雨…针は进んだ → 美麗的音色…放歌的少女(Monica)…蟬們的陣雨…指針的前進 →
绮丽だと…君が言った景色…きっと忘れない… 漂亮呢…你所說的景色…永遠不忘…
『美しきもの』…集める为に…生命(ひと)は遣って来る…… 「美麗之物」…為了將它採擷…生命(人)才降誕到世上…
君が抱きしめた短い季节(Saison)…痛みの雨に打たれながら… 你所擁有的短暫的季節(Saison)…儘管滿是痛苦的雨的敲打…
「心配ないよ」…笑って言った…君の様相(Paysage)忘れないよ…… “别担心哦”…笑著這麼說道…你的樣子(Paysage)永遠不忘……
 
其れは(ce)—— 這是(ce)——
夜の窓辺に…微笑む月…秋の追想… 夜晚的窗邊…微笑的月亮…秋之追憶
绮丽な音…咏う少女(Monica)…虫の羽音…针は进んだ → 美麗的音色…歌唱的少女(Monica)…昆蟲的振翅…指針的前進 →
其れは(ce)—— 這是(ce)——
大地を包み…微眠む雪…冬の追想 包裹大地的…淺\眠的雪花…冬之追憶
绮丽な音…诗う少女(Monica)…时の木枯…针は进んだ → 美麗的音色…歌吟的少女(Monica)…時間的凋零…指針的前進 →
绮丽だね…君が生きた景色…ずっと忘れない… 漂亮呢…你所說的景色…永遠不忘…
『美しきもの』…集める为に…生命(ひと)は过ぎて行く…… 「美麗之物」…為了將它採擷…生命(人)才前進在世上…
君が駈け抜けた昡い季节(Saison)…病の焔に灼かれながら… 你所跑過的短暫的季節(Saison)…儘管滿是疾病之火的灼烤…
「呜呼…绮丽だね」…笑って逝った…君の面影(Image)忘れないよ…… “啊…真漂亮呢”…笑著離開世界…你的面容(Image)永遠不忘……
 
君が生まれた朝…泣き虫だった私は…小さくても姉となった—— 你所誕生的黎明…只是個愛哭鬼的我…變成了小小的姐姐——
嬉しくて…少し照れくさくて…とても夸らしかった…… 真高興啊…雖然有點不好意思…但那真值得驕傲……
苦しみに揺荡う生存の荒野を 在搖蕩著痛苦的，生存的荒野上
『美しきもの』探すように駈け抜けた 為了尋找「美麗之物」而縱橫馳騁
果てしなき地平へ旅立つ君の寝颜 往沒有盡頭的地平線旅行而去的你的睡臉
何より美しいと思ったよ…… 我覺得比任何東西都更加美麗……
君の大好きなこの旋律(Melodie)…大空へと响け口风琴(Harmonica)… 你最喜歡的這旋律(Melodie)…在天空中響遍的口琴(Harmonica)…
天使 が抱いた窓枠の画布(Toile)…ねぇ…その风景画(Paysage)…绮丽かしら? 天使擁抱著窗框裡的畫布(Toile)…喂…這幅風景畫(Paysage)…漂亮嗎？
 
「わたしは 世界に一番美しい光が见った “我呢 看见了这世上第一美丽的光
その花は胸に抱いて Laurantに运う 咏い続けよ」 将那花朵抱在胸前 给Laurant听 继续歌唱”
 
「其処にロマンは在るのかしら?」 「那裡有Roman在嗎？」
 
 */
