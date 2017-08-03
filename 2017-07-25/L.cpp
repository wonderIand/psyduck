#pragma comment(linker, "/STACK:1024000000,1024000000") 
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
struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    FastIO() :
            wpos(0) {
    }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len)
            return -1;
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;    
        if (c == -1) return -1;
        while (c <= 32) {
            c = xchar();
            if (c == -1) return -1;
        }
        for (; '0' <= c && c <= '9'; c = xchar())
            x = x * 10 + c - '0';
        return x;
    }
    inline int xint() {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32)
            c = xchar();
        if (c == '-')
            s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar())
            x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s) {
        int c = xchar();
        while (c <= 32)
            c = xchar();
        for (; c > 32; c = xchar())
            *s++ = c;
        *s = 0;
    }
    inline void wchar(int x) {
        if (wpos == S)
            fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(int x) {
        if (x < 0)
            wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n)
            s[n++] = '0' + x % 10, x /= 10;
        while (n--)
            wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s)
            wchar(*s++);
    }
    ~FastIO() {
        if (wpos)
            fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
const int N = 1e6 + 7;
const int MOD = 1e9 + 7;
int n, l[N], r[N], f[N], rf[N], v[N], w[N], fa[N];
vector<int> p[N];
inline ll kpow(ll a, ll b) {
    ll r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return r;
}
inline int C(int n, int m) {
    if (n < m) return 0;
    return 1ll * f[n] * rf[m] % MOD * rf[n - m] % MOD;
}
ll dfs(int L, int R) {
    if (!sz(p[R - L + 1])) return 0;
    int i = p[R - L + 1].back();
    p[R - L + 1].pop_back();
    if (l[i] != L && r[i] != R) return 0;
    if (L == R) return 1;
    if (i == L) return dfs(L + 1, R);
    if (i == R) return dfs(L, R - 1);
    ll ans = C(R - L, R - i);    
    ans = ans * dfs(i + 1, R) % MOD;
    ans = ans * dfs(L, i - 1) % MOD;
    return ans;
}
int main() {
    f[0] = 1;
    rep(i, 1, N) f[i] = 1ll * f[i - 1] * i % MOD;
    rf[N - 1] = kpow(f[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; --i)
        rf[i] = 1ll * rf[i + 1] * (i + 1) % MOD;
    int cas = 0;
    while (~(n = io.xuint())) {
        rep(i, 1, n + 1) l[i] = io.xint();
        rep(i, 1, n + 1) r[i] = io.xint();            
        rep(i, 1, n + 1) p[i].clear();
        rep(i, 1, n + 1) p[r[i] - l[i] + 1].pb(i);
        int ans = dfs(1, n);    
        printf("Case #%d: %d\n", ++cas, ans);
    }

    return 0;
}
