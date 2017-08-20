#include<bits/stdc++.h>
using namespace std;
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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 7;
const int P = 1e9 + 7;
int n, q;
char s[N];
inline void inc(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}
struct Node {
    int a, b, c, x, y, z;
    void clr() {
        a = b = c = x = y = z = 0;
    }
    void out() {
        dd(a), dd(b), dd(c), dd(x), dd(y), de(z);
    }
    // f(i, 0) = f(i - 1, 0) or f(i - 1, 0) + f(i - 1, 1) + (s[i] == 0)
    // f(i, 1) = f(i - 1, 0) or f(i - 1, 0) + f(i - 1, 1) + (s[i] == 1)
	// (f0, f1) -> (nf0, nf1) = (af0 + bf1 + c, xf0 + yf1 + z) 
    Node operator+(const Node &nd) const {
        Node r;
        r.a = (1ll * a * nd.a + 1ll * x * nd.b) % P;
        r.b = (1ll * b * nd.a + 1ll * y * nd.b) % P;
        r.c = (1ll * c * nd.a + 1ll * z * nd.b + nd.c) % P;
        r.x = (1ll * a * nd.x + 1ll * x * nd.y) % P;
        r.y = (1ll * b * nd.x + 1ll * y * nd.y) % P;
        r.z = (1ll * c * nd.x + 1ll * z * nd.y + nd.z) % P;
        return r;
    }
};
struct SegTree {
#define ls ((t)<<1)
#define rs ((t)<<1|1)
    bool rev[N << 2];
    Node a[2][N << 2];
    void down(int t) {
        if (rev[t]) {
            rev[ls] ^= 1, swap(a[0][ls], a[1][ls]);
            rev[rs] ^= 1, swap(a[0][rs], a[1][rs]);
            rev[t] = 0;
        }
    }
    void build(int t, int l, int r) {
        rev[t] = 0;
        if (l == r) {
            a[0][t].a = 1, a[0][t].b = a[0][t].c = s[l] == '0';
            a[0][t].y = 1, a[0][t].x = a[0][t].z = s[l] == '1';
            a[1][t].a = 1, a[1][t].b = a[1][t].c = s[l] == '1';
            a[1][t].y = 1, a[1][t].x = a[1][t].z = s[l] == '0';
        } else {
            int z = (l + r) >> 1;
            build(ls, l, z), build(rs, z + 1, r);
            a[0][t] = a[0][ls] + a[0][rs];
            a[1][t] = a[1][ls] + a[1][rs];
        }
    }
    void upd(int t, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            rev[t] ^= 1, swap(a[0][t], a[1][t]);
            return ;
        }
        down(t);
        int z = (l + r) >> 1;
        if (L <= z) upd(ls, l, z, L, R);
        if (R > z) upd(rs, z + 1, r, L, R);
        a[0][t] = a[0][ls] + a[0][rs];
        a[1][t] = a[1][ls] + a[1][rs];
    }
    Node qry(int t, int l, int r, int L, int R) {
        if (L <= l && r <= R) return a[0][t];
        down(t);
        int z = (l + r) >> 1;
        if (R <= z) return qry(ls, l, z, L, R);
        if (L > z) return qry(rs, z + 1, r, L, R);
        return qry(ls, l, z, L, R) + qry(rs, z + 1, r, L, R);
    }
} seg;
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d %s", &n, &q, s + 1);
        seg.build(1, 1, n);
        rep(_q, 0, q) {
            int op, l, r;
            scanf("%d%d%d", &op, &l, &r);
            if (op == 1) {
                seg.upd(1, 1, n, l, r);
            } else {
                Node ans = seg.qry(1, 1, n, l, r);
                printf("%d\n", (ans.c + ans.z) % P);
            }
        }
    }
    return 0;
}
