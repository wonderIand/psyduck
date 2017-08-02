#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define de(x) cout << #x << " = " << x << endl;
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
//-------
const int N = 5e5 + 7;
int n, k, a[N], p[N];
struct Node {
    int v, pre, nxt;
    Node() {
    }
    Node(int _v, int _pre, int _nxt) {
        v = _v, pre = _pre, nxt = _nxt;
    }
} d[N];
void del(int p) {
    int pre = d[p].pre, nxt = d[p].nxt;
    d[pre].nxt = nxt;
    d[nxt].pre = pre;
}
ll solve() {
    if (k <= 0) return 0;
    --k;
    rep(i, 1, n + 1)
        d[i] = Node(i, i - 1, i + 1);
    d[0] = Node(0, 0, 1);
    d[n + 1] = Node(n + 1, n, n + 1);
    ll ret = 0;
    for (int i = 1; i <= n; ++i) {
        int id = p[i];
        pii L = mp(p[i], 0), R = mp(p[i], 0);
        rep(j, 0, k) {
            if (d[L.fi].pre == 0) break;
            L = mp(d[L.fi].pre, L.se + 1);
        }
        rep(j, 0, k - L.se) {
            if (d[R.fi].nxt > n) break;
            R = mp(d[R.fi].nxt, R.se + 1);
        }
        while (L.se + R.se >= k) {
            ret += (ll) i * (ll) (d[L.fi].v - d[d[L.fi].pre].v) * (ll) (d[d[R.fi].nxt].v - d[R.fi].v);
//            printf("i = %d, l = %d, r = %d\n", i, d[L.fi].v, d[R.fi].v);
            L.fi = d[L.fi].nxt;
            R.fi = d[R.fi].nxt;
            if (d[L.fi].v > p[i] || d[R.fi].v > n) break;
        }
        del(p[i]);
    }
    ++k;
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &k);
        rep(i, 1, n + 1) scanf("%d", a + i), p[a[i]] = i;
        cout << solve() << endl;
//        n = 5e5, k = 1;
//        rep(i, 1, n + 1) a[i] = i, p[a[i]] = i;
//        de(br());
    }
    return 0;
}
