#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
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
//-------
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
int n, ans, price[N], s[N], t[N];
vector<pii> e[N];
void dfs(int u, int p) {
    s[u] = price[u], t[u] = -price[u];
    rep(i, 0, sz(e[u])) {
        int v = e[u][i].fi, w = e[u][i].se;
        if (v == p) continue;
        dfs(v, u);
        s[u] = max(s[u], s[v] - w);
        t[u] = max(t[u], t[v] - w);
    }
    ans = max(ans, s[u] + t[u]);
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d", &n);
        rep(i, 1, n + 1) e[i].clear();
        rep(i, 1, n + 1) scanf("%d", price + i);
        rep(i, 1, n) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            e[x].pb(mp(y, z));
            e[y].pb(mp(x, z));
        }
        ans = 0;
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
