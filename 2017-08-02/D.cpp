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
const int M = 30;
int n, a[N], b[M];
struct Trie {
    int rt, tot;
    int c[N * 30], ch[N * 30][2];
    inline void clr(int id) {
        c[id] = 0, ch[id][0] = ch[id][1] = -1;
    }
    void init() {
        rt = 0, tot = 1;
        clr(rt);
    }
    void upd(int a[], int v) {
        int p = rt;
        rep(i, 0, M) {
            c[p] += v;
            if (ch[p][a[i]] == -1) {
                clr(tot);
                ch[p][a[i]] = tot++;
            }
            p = ch[p][a[i]];
        }
        c[p] += v;
    }
} seg[2];
void gao(int x) {
    rep(i, 0, M) b[i] = x & 1, x >>= 1;
    reverse(b, b + M);
//    rep(i, 0, M) printf("%d", b[i]);puts("");
}
ll cnt[M][2];
void upd(int a[], ll f) {
    int pl = seg[0].rt, pr = seg[1].rt;
    rep(i, 0, M) {
        if (pl < 0 || pr < 0) break;
        if (~seg[0].ch[pl][0] && ~seg[1].ch[pr][1]) {
            cnt[i][0] += f * seg[0].c[seg[0].ch[pl][0]] * seg[1].c[seg[1].ch[pr][1]];
        }
        if (~seg[0].ch[pl][1] && ~seg[1].ch[pr][0]) {
            cnt[i][1] += f * seg[0].c[seg[0].ch[pl][1]] * seg[1].c[seg[1].ch[pr][0]];
        }
        pl = seg[0].ch[pl][a[i]];
        pr = seg[1].ch[pr][a[i]];
    }
}
ll br() {
    ll ret = 0;
    rep(k, 0, n) {
        ll tmp = 0;
        rep(j, 0, k)
            rep(i, 0, j) {
                tmp += (a[i] ^ a[j]) < (a[j] ^ a[k]);
//                if ((a[i] ^ a[j]) < (a[j] ^ a[k]))
//                    printf("%d %d %d\n", i, j, k);
            }
//        printf("k = %d, tmp = %lld\n", k, tmp);
        ret += tmp;
    }
    return ret;
}
void dfs(int i, int pl, int pr) {
    if (pl < 0 || pr < 0) return ;
    if (~seg[0].ch[pl][0] && ~seg[1].ch[pr][1])
        cnt[i][0] += seg[0].c[seg[0].ch[pl][0]] * seg[1].c[seg[1].ch[pr][1]];
    if (~seg[0].ch[pl][1] && ~seg[1].ch[pr][0])
        cnt[i][1] += seg[0].c[seg[0].ch[pl][1]] * seg[1].c[seg[1].ch[pr][0]];
    rep(j, 0, 2) dfs(i + 1, seg[0].ch[pl][j], seg[1].ch[pr][j]);
}
ll solve() {
    if (n < 3) return 0;
    rep(i, 0, 2) seg[i].init();
    rep(i, 0, M) rep(j, 0, 2) cnt[i][j] = 0;
    gao(a[0]), seg[0].upd(b, 1);
    for (int i = n - 1; i > 1; --i) gao(a[i]), seg[1].upd(b, 1);
    dfs(0, seg[0].rt, seg[1].rt);
    ll ret = 0;
    rep(j, 1, n - 1) {
        gao(a[j]);
        rep(i, 0, M) ret += cnt[i][b[i]];
//        printf("j = %d, ret = %lld\n", j, ret);
        // L
        upd(b, -1);
        seg[0].upd(b, 1);
        upd(b, 1);
        // R
        gao(a[j + 1]);
        upd(b, -1);
        seg[1].upd(b, -1);
        upd(b, 1);
    }
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d", &n);
        rep(i, 0, n) scanf("%d", a + i);
        cout << solve() << endl;
//        cout << br() << endl;
    }
    return 0;
}
