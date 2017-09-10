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
const int N = 1e4 + 10;
int n;
vi g[N];
#define lb(x) ((x)&-(x))
struct Fenwick {
    int a[N],n;
    void ini(int _n){n = _n;rep(i,0,n+1) a[i]=0;}
    void add(int c,int d){for(int i=c;i<=n;i+=lb(i))a[i]+=d;}
    int sum(int c){int r=0;for(int i=c;i>=1;i-=lb(i))r+=a[i];return r;}
}fen;

int lft[N] , rgt[N] , _ , par[N][14] , dep[N];
void dfs(int c,int fa){
    dep[c] = dep[fa] + 1 ;
    par[c][0] = fa;
    rep(i,1,14) par[c][i] = par[par[c][i-1]][i-1];
    lft[c] = ++_;
    for(auto t : g[c]) if(t != fa) dfs(t , c);
    rgt[c] = _;
}

int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u , v);
    rep(i,0,14) if((dep[u] - dep[v]) >> i & 1) u = par[u][i];
    if(u == v) return u;
    per(i,0,14) if(par[u][i] != par[v][i]) u = par[u][i] , v = par[v][i];
    return par[u][0];
}
vector<pii> ask[N];
int ans;

void dfs2(int c,int fa){
    for(auto t : g[c]) if(t != fa) dfs2(t , c);
    bool ok = true;
    for(auto e : ask[c]){
        int u = e.fi , v = e.se;
        if(fen.sum(lft[u]) > 0 || fen.sum(lft[v]) > 0)
            ok = true;
        else {
            ok = false;
            break;
        }
    }
    if(!ok){
        ans++;
        fen.add(lft[c] , 1);
        fen.add(rgt[c] + 1 , -1);
    }
}

int main() {
    while(~scanf("%d",&n)){
        ++n;
        rep(i,1,n+1) g[i].clear() , ask[i].clear();
        rep(i,1,n){
            int u,v;
            scanf("%d%d",&u,&v);
            ++u;++v;
            g[u].pb(v);
            g[v].pb(u);
        }
        _ = 0;
        dfs(1 , 0);
        int m;
        scanf("%d",&m);
        rep(i,0,m){
            int u,v;
            scanf("%d%d",&u,&v);
            ++u;++v;
            ask[lca(u , v)].pb({u , v});
        }
        ans = 0;
        fen.ini(n);
        dfs2(1 , 0);
        printf("%d\n",ans);
    }
    return 0;
}
