#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 1e3 + 7;
const int V = 1e5 + 7;
int n, m, k, f[N][N];
vector< pair<int, int> > e[N];
int tot, top, dfn[N], low[N], sta[N];
int *a, *c, la, lb, lc, A[V], C[V], B[V];
struct Node {
    int w, i, j;
    Node() {
    }
    Node(int _w, int _i, int _j) {
        w = _w, i = _i, j = _j;
    }
    bool operator<(const Node &nd) const {
        return w < nd.w;
    }
};
void merge(int m, int b[]) {
    priority_queue<Node> que;
    lc = 0;
    rep(i, 0, m)
        que.push(Node(a[0] + b[i], 0, i));
    while (lc < k && !que.empty()) {
        c[lc++] = que.top().w;
        int i = que.top().i, j = que.top().j;
        que.pop();
        if (i + 1 < la)
            que.push(Node(a[i + 1] + b[j], i + 1, j));
    }
    la = lc, swap(a, c);
}
void dfs(int u, int dep) {
    int cc = 0;
    sta[top++] = u, dfn[u] = low[u] = dep;
    rep(i, 0, sz(e[u])) {
        int v = e[u][i].fi;
        if (!dfn[v]) {
            dfs(v, dep + 1);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                lb = 0;
                while (sta[--top] != v) B[lb++] = sta[top];
                B[lb++] = v, B[lb++] = u;
                if (lb > 2) {
                    sta[top] = B[0];
                    rep(i, 0, lb - 1)
                        B[i] = f[B[i]][B[i + 1]];
                    B[lb - 1] = f[sta[top]][u];
                    merge(lb, B);
                }
            }
        } else if (dfn[v] != dfn[u] - 1 || cc++) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int main() {
//    freopen("1009.in", "r", stdin);
    a = A, c = C;
    while (~scanf("%d%d", &n, &m)) {
        ui all = 0;
        rep(i, 1, n + 1) dfn[i] = 0, e[i].clear();
        rep(i, 0, m) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].pb(mp(v, w));
            e[v].pb(mp(u, w));
            all += w, f[u][v] = f[v][u] = w;
        }
        scanf("%d", &k);
        tot = 0, top = 0, la = 1, a[0] = 0;;
        dfs(1, 1);
        ui ans = 0;
        rep(i, 0, la)
            ans += (ui) (i + 1) * (all - a[i]);
        static int cas = 0;
        printf("Case #%d: %u\n", ++cas, ans);
    }
    return 0;
}
