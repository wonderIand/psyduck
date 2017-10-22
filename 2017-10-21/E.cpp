#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e6 + 7;
const int M = 1e6 + 7;
int n, m, K, W, f[N], col[N];
struct Edge {
    int a, b, c;
    void in() {
        scanf("%d%d%d", &a, &b, &c);
    }
} e[N];
vector<pii> same, diff;
inline int get(int x) {
    return x == f[x] ? x : f[x] = get(f[x]);
}
bool le(const pii &a, const pii &b) {
    return a.fi <= b.fi;
}
void merge(const vector<pii> &a, const vector<pii> &b, vector<pii> &c) {
    int i = 0, j = 0;
    while (i < sz(a) || j < sz(b)) {
        while (i < sz(a) && (j >= sz(b) || le(a[i], b[j])))
            c.pb(a[i++]);
        while (j < sz(b) && (i >= sz(a) || !le(a[i], b[j])))
            c.pb(b[j++]);
    }
}
pair<int, ll> gao(int dc) {
    vector<pii> ret;
    rep(i, 0, sz(diff)) diff[i].fi = e[diff[i].se].c + dc;
    merge(same, diff, ret);
    rep(i, 1, n + 1) f[i] = i;
    ll cost = 0, cnt = 0;
    rep(i, 0, sz(ret)) {
        int a = e[ret[i].se].a, b = e[ret[i].se].b,
            c = ret[i].fi;
        if (get(a) == get(b)) continue;
        f[get(a)] = get(b);
        cost += c, cnt += col[a] != col[b];
    }
    return mp(cnt, cost);
}
ll solve() {
    int l = -N, r = N; pair<int, ll> ret;
    ret = gao(l);
    rep(i,1,n+1) if(get(i) != get(1)) return -1;
    if(ret.fi < W) return -1;
    ret = gao(r);
    if(ret.fi > W) return -1;
    while (l + 1 < r) {
        int m=(l+r)>>1;
        ret = gao(m);
        if(ret.fi <= W) r = m;
        else l = m;
    }
    ret = gao(r);
    return ret.se - 1ll * r * W;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &K, &W);
    rep(i, 0, K) {
        int x; scanf("%d", &x);
        col[x] = 1;
    }
    rep(i, 0, m) {
        e[i].in();
        if (col[e[i].a] == col[e[i].b]) {
            same.pb(mp(e[i].c, i));
        } else {
            diff.pb(mp(e[i].c, i));
        }
    }
    sort(all(same)), sort(all(diff));
    cout << solve() << endl;
    return 0;
}
