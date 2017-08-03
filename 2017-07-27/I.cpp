#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define de(x) cout << #x << " = " << x << endl;
//-------
const int N = 1e5 + 7;
const int MOD = 1e9 + 7;
int n, a[N];
bool vis[N];
vector<int> prime;
ll kpow(ll a, ll b) {
    ll r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return r;
}
void inc(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}
void init() {
    rep(i, 2, N) {
        if (vis[i]) continue;
        prime.pb(i);
        for (ll j = 1ll * i * i; j < N; j += i)
            vis[j] = true;
    }
//    printf("sz = %d\n", sz(prime));
}
int top, st[N];
void fac(int x) {
    top = 0;
    for (int i = 0; i < sz(prime) && prime[i] <= x; ++i)
        if (x % prime[i] == 0) {
            st[top++] = prime[i];
            while (x % prime[i] == 0) x /= prime[i];
        }
}
int mv, ans;
void gao(int val, int sg) {
    int p = 0, ret = 1;
    while (p < n) {
        int l = p, r = n - 1, b = a[p] / val;
        while (l + 1 < r) {
            int z = (l + r) >> 1;
            b == a[z] / val ? l = z : r = z;
        }
        int q = (b == a[r] / val ? r : l);
        ret = 1ll * ret * kpow(b, q - p + 1) % MOD;
        p = q + 1;
    }
    if (sg == 1) {
        inc(ans, ret);
    } else {
        inc(ans, MOD - ret);
    }
}
void dfs(int t, int val, int sg) {
    if (t >= sz(prime)) return ;
    if (val > mv / prime[t]) return ;
    dfs(t + 1, val, sg);
    gao(val * prime[t], -sg);
    dfs(t + 1, val * prime[t], -sg);
}
int main() {
    init();
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d", &n);
        rep(i, 0, n) scanf("%d", a + i);
        sort(a, a + n);
        mv = a[0], ans = 0;
        dfs(0, 1, -1);
        printf("Case #%d: %d\n", cas + 1, ans);
    }
    return 0;
}
