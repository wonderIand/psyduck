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
#define de(x) cout << #x << " = " << x << endl
//-------
const int MOD = 1e9 + 7;
ll kpow(ll a, ll b) {
    ll r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return r;
}
struct Mat {
    static const int M = 2;
    int a[M][M];
    void clr(int x) {
        rep(i, 0, M) rep(j, 0, M)
            a[i][j] = (i == j ? x : 0);
    }
    Mat operator*(const Mat &p) const {
        Mat r;r.clr(0);
        rep(k, 0, M) rep(i, 0, M) rep(j, 0, M)
            r.a[i][j] += 1ll * a[i][k] * p.a[k][j] % MOD;
        rep(i, 0, M) rep(j, 0, M) r.a[i][j] %= MOD;
        return r;
    }
    Mat operator^(ll b) const {
        Mat r, a = *this;r.clr(1);
        while (b > 0) {
            if (b & 1) r = r * a;
            a = a * a, b >>= 1;
        }
        return r;
    }
    void out() {
        rep(i, 0, M) {
            rep(j, 0, M) cout << a[i][j] << " ";
            puts("");
        }
    }
} A;
ll n, m;
int solve() {
    if (m == 1) return 1;
    ll a = 1, b = 0;
    if (n > 2) {
        A.a[0][0] = 0, A.a[0][1] = 1;
        A.a[1][0] = 2, A.a[1][1] = 1;
        A = A ^ (n - 2);
//        A.out();
        a = (A.a[1][0] + A.a[1][1]) % MOD;
    }
    if (n & 1)
        b = (a - kpow(2, n) + 1 % MOD) % MOD;
//    de(a), de(b);
    if (m > 2) {
        A.a[0][0] = (kpow(2, n) - 1 + MOD) % MOD;
        A.a[0][1] = 1;
        A.a[1][0] = 0, A.a[1][1] = 1;
        A = A ^ (m - 2);
//        A.out();
        a = a * A.a[0][0] + b * A.a[0][1];
        a = (a % MOD + MOD) % MOD;
    }
    return (a + a - (n & 1) + MOD) % MOD;
}
int main() {
    int T;
    cin >> T;
    rep(cas, 0, T) {
        cin >> n >> m;
        cout << solve() << endl;
    }
    return 0;
}
