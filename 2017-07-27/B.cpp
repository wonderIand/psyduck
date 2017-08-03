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
#define cnt(x) __builtin_popcount(x)
//#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e3;
const int L = 7;
const int LM = (1 << L) - 1;
int n, K, a[N][N], v[N][N];
set<pair<ll, pair<int, int> > > S;
set<pair<ll, pair<int, int> > >::iterator it;
inline unsigned sfr(unsigned h, unsigned x) {
    return h >> x;
}
int f(ll i, ll j) {
  ll w = i * 1000000ll + j;
  int h = 0;
  for(int k = 0; k < 5; ++k) {
    h += (int) ((w >> (8 * k)) & 255);
    h += (h << 10);
    h ^= sfr(h, 6);
  }
  h += h << 3;
  h ^= sfr(h, 11);
  h += h << 15;
  return sfr(h, 27) & 1;
}
bool check(int x, int y) {
    if (x < 1 || y < 1) return false;
    rep(i, 0, n) rep(j, 0, n)
        if (f(x + i, y + j) != a[i][j])
            return false;
    return true;
}
pair<int, int> solve() {
    K = n - 2 * L;
    for (int i = 1; i + L - 1 <= 1e6; i += K)
        for (int j = 1; j + L - 1 <= 1e6; j += K) {
            ll hs = 0;
            rep(di, 0, L) rep(dj, 0, L)
                hs = hs << 1 | f(i + di, j + dj);
            it = S.lower_bound(mp(hs, mp(0, 0)));
            while (it != S.end() && it->fi == hs) {
                if (check(i - it->se.fi, j - it->se.se))
                    return mp(i - it->se.fi, j - it->se.se);
                ++it;
            }
        }
    return mp(-1, -1);
}
int read() {
    char ch = getchar();
    while (!('0' <= ch && ch <= '1')) ch = getchar();
    return ch - '0';
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        n = 1000;
        rep(i, 0, n) rep(j, 0, n) a[i][j] = read();
        rep(i, 0, n) {
            v[i][0] = 0;
            rep(j, 0, L) v[i][0] = v[i][0] << 1 | a[i][j];
            rep(j, 1, n + 1 - L)
                v[i][j] = (v[i][j - 1] << 1 | a[i][j + L - 1]) & LM;
        }
        S.clear();
        rep(j, 0, n + 1 - L) {
            ll hs = 0;
            rep(i, 0, L) hs = hs << L | v[i][j];
            S.insert(mp(hs, mp(0, j)));
            rep(i, 1, n + 1 - L) {
                hs ^= (hs >> (L * (L - 1))) << (L * (L - 1));
                hs = hs << L | v[i + L - 1][j];
                S.insert(mp(hs, mp(i, j)));
            }
        }
        pair<int, int> ans = solve();
        printf("Case #%d :%d %d\n", cas + 1, ans.fi, ans.se);
    }
    return 0;
}
