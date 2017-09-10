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
int n, k, a[N];
struct Fenwick {
    int n, c[N];
    void init(int _n) {
        n = _n;
        memset(c, 0, sizeof(*c) * (n + 1));
    }
    void upd(int i, int v) {
        while (i <= n) {
            c[i] = max(c[i], v);
            i += i & -i;
        }
    }
    int qry(int i) {
        int r = 0;
        while (i > 0) {
            r = max(r, c[i]);
            i -= i & -i;
        }
        return r;
    }
} fw;
int solve() {
    int ret = 0;
    fw.init(*max_element(a, a + n));
    rep(i, 0, n) {
        int fi = fw.qry(a[i]) + 1;
        fw.upd(a[i], fi);
        ret = max(ret, fi);
    }
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &k);
        rep(i, 0, n) scanf("%d", a + i);
        int len = solve();
        reverse(a, a + n);
        len = max(len, solve());
        puts(len >= n - k ? "A is a magic array." : "A is not a magic array.");
    }

    return 0;
}
