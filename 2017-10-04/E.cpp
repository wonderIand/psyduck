#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define de(x) cout << #x << " = " << x << endl
using namespace std;

#define pb push_back
typedef vector<int> vi;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

const int N = 1e2 + 7;
int n;
vi dig;
vector<pii> ans, ans2;
///-------
int tmp[N];
void RotateLeft(vi &v, int dis) {
    ans.pb(mp(2, dis));
    rep(i, 0, n) tmp[i] = v[(i + dis) % sz(v)];
    rep(i, 0, n) v[i] = tmp[i];
}
void Swap4(vi &v, int pos, bool cord = true) {
    if (cord) ans.pb(mp(1, pos + 1));
    swap(v[pos], v[(pos + 3) % sz(v)]);
    swap(v[(pos + 1) % sz(v)], v[(pos + 2) % sz(v)]);
}
///-------
void gao(int des) {
    int cur = 0; while (dig[cur] != des) cur++;
    while (cur - des >= 3) Swap4(dig, cur -= 3);
    if (cur - des == 1) Swap4(dig, cur++ - 1);
    if (cur - des == 2) Swap4(dig, cur++ - 1);
    while (cur - des >= 3) Swap4(dig, cur -= 3);
}
map<int, bool> M;
bool ok(vi &vu) {
    rep(i, 0, sz(vu) - 1) if (vu[i] > vu[i + 1]) return false;
    return true;
}
int toInt(vi &vu) {
    int ret = 0;
    rep(i, 0, sz(vu)) ret = ret * 10 + vu[i];
    return ret;
}
void show(vi &vu) {
    //if (vu[0] != 1 || vu[1] != 2) return;
    rep(i, 0, sz(vu)) printf("%d ", vu[i]); puts("");
}
bool dfs(vi &vu) {
    if (M.count(toInt(vu))) return false;
        else M[toInt(vu)] = true;
    //show(vu);
    if (ok(vu)) return true;
    rep(i, 0, sz(vu) - 3) {
        Swap4(vu, i, false);
        if (dfs(vu)) {
            ans2.pb(mp(1, i + max(0, n - 6) + 1));
            return true;
        }
        Swap4(vu, i, false);
    }
    return false;
}
int main() {

    //freopen("xx.in", "r", stdin);
    //freopen("xx.out", "w", stdout);

    //vi v; rep(i, 1, 7)v.pb(i);
    //dfs(v);

    for (; ~scanf("%d", &n); ) {

        ///init
        ans.clear();
        ans2.clear();

        ///read
        n = n << 1; dig.resize(n);
        rep(i, 0, n) scanf("%d", &dig[i]), dig[i]--;

        ///prework
        int nxd = 0;
        rep(i, 0, n) rep(j, i, n) nxd += dig[i] > dig[j];
        if (nxd & 1) RotateLeft(dig, 1);

        ///work
        M.clear();
        if (n > 4) rep(i, 0, n - 4) gao(i); else {
            while (dig[0] != 0) RotateLeft(dig, 1);
            if (dig[1] != 1) RotateLeft(dig, 1);
        }
        vi vu; rep(i, max(0, n - 6), n) vu.pb(dig[i]);
        //rep(i, 0, n) printf("%d ", dig[i]); puts("");
        if (dfs(vu) == false) while(1);

        ///print
        printf("%d\n", sz(ans) + sz(ans2));
        assert(sz(ans) +sz(ans2) < 400000);
        rep(i, 0, sz(ans)) printf("%d %d\n", ans[i].fi, ans[i].se);
        per(i, 0, sz(ans2)) printf("%d %d\n", ans2[i].fi, ans2[i].se);
        //rep(i, 0, n) printf("%d ", dig[i]); puts("");
        per(i, 0, sz(ans2)) Swap4(dig, ans2[i].se - 1);
        rep(i, 0, n) assert(dig[i] == i);
        //rep(i, 0, n) printf("%d ", dig[i]); puts("");
        //de(sz(ans2));
    }

    return 0;
}
