// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

const int N = 2e5 + 10;
#define lb(x) ((x)&(-x))
struct Fenwick{
    pii a[N];int n;
    void ini(int _n){fill_n(a,(n=_n)+1,mp(-1,-1));}
    pii query(int c){pii r(-1,-1);for(;c>0;c^=lb(c))r=max(r,a[c]);return r;}
    void update(int c,pii x){for(;c<=n;c+=lb(c))a[c]=max(a[c],x);}
}fen;
int n , m , start[N] , len[N] , pre[N] , f[N] , lensum[N];
int go[N] , du[N];

int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) {
        int u,v;
        scanf("%d%d",&u,&v);
        if(u!=-1){
            if(v==1) start[u]=i;
            len[u]++;
        }
    }
    len[0]=0,start[0]=1,len[m+1]=0,start[m+1]=n+1;
    ++m;
    rep(i,1,m+1) lensum[i]=lensum[i-1]+len[i];
    fen.ini(n);
    fen.update(1,mp(0,0));
    memset(pre,-1,sizeof(pre));
    rep(i,1,m+1) {
        pii t=fen.query(start[i]-lensum[i-1]);
        if(t.se!=-1) {
            pre[i]=t.se;
            f[i]=t.fi+len[i];
            fen.update(start[i]-lensum[i-1],mp(f[i],i));
        }
    }
    int c=m;
    vi fix;for(;c>=0;c=pre[c]) fix.pb(c);
    reverse(all(fix));
    memset(go , -1 , sizeof(go));
    rep(i,1,sz(fix)){
        int u=fix[i-1],v=fix[i];
        for(int i=u+1,pos=start[u]+len[u];i<v;++i)
            rep(j,0,len[i]) du[go[start[i]+j]=pos++]++;
    }
    vector<vi> ans;
    auto bfs = [&](int c){
        vi path;
        for(;c!=-1;) {
            path.pb(c);
            int t=go[c];
            go[c]=-1;
            c=t;
        }
        return path;
    };
    rep(i,1,n+1) if(go[i]!=-1&&du[i]==0) ans.pb(bfs(i));
    rep(i,1,n+1) if(go[i]!=-1&&du[i]==1) ans.pb(bfs(i));
    printf("%d %d\n",lensum[m]-f[m],sz(ans));
    rep(i,0,sz(ans)){
        printf("%d",sz(ans[i]));
        rep(j,0,sz(ans[i])) printf(" %d",ans[i][j]);
        puts("");
    }
    return 0;
}

