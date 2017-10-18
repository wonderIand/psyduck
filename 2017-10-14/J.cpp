#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl

const int N = 3e2 + 7;
vector<pii> G[N];
bool vis[N];
int dis[N], dig[N][N], n, m;
void error() { puts("Impossible"); exit(0); }
void dfs(int u) {
    vis[u] = true;
    rep(_v, 0, sz(G[u])) {
        int v = G[u][_v].fi;
        int c = G[u][_v].se;
        if (vis[v] && dis[v] != dis[u] + c) error();
        dis[v] = dis[u] + c;
        if (!vis[v]) dfs(v);
    }
}
int main() {

    freopen("xx.in", "r", stdin);

    //read
    scanf("%d", &n);
    rep(i, 0, n) rep(j, 0, n) scanf("%d", &dig[i][j]);
    scanf("%d", &m);
    rep(i, 0, m) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c); a--; b--;
        G[a].pb(mp(b, c));
        G[b].pb(mp(a, -c));
    }

    //work
    rep(i, 0, n) if (!vis[i]) dfs(i);
    rep(i, 0, n) rep(j, 0, n) printf("%d%c", dis[j] - dis[i] + dig[i][j], " \n"[j == n - 1]);

    return 0;
}

