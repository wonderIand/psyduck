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
        while (c <= 32)
            c = xchar();
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
//-------
const int N = 1e5 + 7;
int n, m, tot, L[N], R[N];
pii E[N];
vector<int> e[N];
bool vis[N], used[N];
#define lb(x) ((x)&-(x))
struct Fenwick {
    int a[N],n;
    void ini(int _n){n = _n;rep(i,0,n+1) a[i]=0;}
    void add(int c,int d){for(int i=c;i<=n;i+=lb(i))a[i]+=d;}
    int sum(int c){int r=0;for(int i=c;i>=1;i-=lb(i))r+=a[i];return r;}
}fen;

int _ , dep[N] , par[N][18];
void dfs(int u , int fa) {
    L[u] = ++_;
    par[u][0] = fa;
    dep[u] = dep[fa] + 1;
    rep(i,1,18) par[u][i] = par[par[u][i-1]][i-1];
    vis[u] = true;
    rep(i, 0, sz(e[u])) {
        int v = E[e[u][i]].fi ^ E[e[u][i]].se ^ u;
        if (vis[v]) continue;
        used[e[u][i]] = true;
        dfs(v, u);
    }
    R[u] = _;
}
int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u , v);
    rep(i,0,18) if((dep[u] - dep[v]) >> i & 1) u = par[u][i];
    if(u == v) return u;
    per(i,0,18) if(par[u][i] != par[v][i]) u = par[u][i] , v = par[v][i];
    return par[u][0];
}
int fa[N];
int F(int x){return fa[x] == x ? x : fa[x] = F(fa[x]);}
void M(int a,int b){
    a = F(a) , b = F(b);
    if(a != b) fa[a] = b;
}
void link(int a,int b){
    a = F(a);
    while(a != 1 && dep[a] > dep[b]){
        fen.add(L[a] , -1);
        fen.add(R[a] + 1 , 1);
        M(a , par[a][0]);
        a = F(a);
    }
}
void add(int u, int v) {
    int c = lca(u , v);
    link(u , c);
    link(v , c);
}
int query(int x){
    return fen.sum(L[x]) + (dep[x] - 1);
}
int query(int u,int v) {
    return query(u) + query(v) - 2 * query(lca(u,v));
}
int main() {
    int T;
    T = io.xuint();
    rep(cas, 0, T) {
        printf("Case #%d:\n",cas+1);
        n = io.xuint();
        m = io.xuint();
        rep(i, 1, n + 1) vis[i] = false, e[i].clear();
        rep(i, 0, m) {
            int u, v;
            u = io.xuint();
            v = io.xuint();
            used[i] = false;
            E[i] = mp(u, v);
            e[u].pb(i), e[v].pb(i);
        }
        rep(i,1,n+1) fa[i] = i;
        fen.ini(n);
        _ = 0;
        dfs(1 , 0);
        rep(i,0,m) if(!used[i]) add(E[i].fi , E[i].se);
        int Q;
        Q = io.xuint();
        rep(i,0,Q){
            int op , u , v;
            op = io.xuint();
            u = io.xuint();
            v = io.xuint();
            if(op == 1) add(u , v);
            else printf("%d\n",query(u , v));
        }
    }
    return 0;
}
