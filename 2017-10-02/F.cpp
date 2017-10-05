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

const int N = 1e5 + 10 , P = 1e9 + 7;
int n , m , inv[N] , ifac[N] = {1} , rd[N];
int par[N] , in[N];
vi g[N];
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
int myrand(){return (ll(rand())<<32^ll(rand())<<16^rand())%P;}
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int sz[N],hs[N],way[N];
int C(int a,int b){
    int r=1;rep(i,0,b) r=1ll*r*(a-i)%P;
    return 1ll*r*ifac[b]%P;
}
void dfs(int c){
    sz[c]=1;hs[c]=1;way[c]=1;
    for(auto t : g[c]) dfs(t),sz[c]+=sz[t],hs[c]=1ll*hs[c]*(rd[sz[t]]+hs[t])%P;
    sort(all(g[c]),[&](int a,int b){return hs[a]<hs[b];});
    for(int i=0,j=0;i<sz(g[c]);i=j){
        for(j=i;j<sz(g[c])&&hs[g[c][i]]==hs[g[c][j]];++j);
        way[c]=1ll*way[c]*C(j-i+1ll*way[g[c][i]]*(m-1)%P-1,j-i)%P;
    }
}
int ne[N];
int Kmp(vi&v){
    ne[0]=-1;
    int n=sz(v);
    for(int i=1,j=-1;i<n;++i){
        while(j!=-1&&hs[v[j+1]]!=hs[v[i]]) j=ne[j];
        ne[i]=hs[v[j+1]]==hs[v[i]]?++j:j;
    }
    if(n%(n-1-ne[n-1])==0) return n-1-ne[n-1];
    return n;
}
int dp[N] = {1};
int main(){
    srand(time(NULL));
    rep(i,1,N) rd[i] = myrand() % P;
    inv[1] = 1;rep(i,2,N) inv[i] = P-ll(P/i)*inv[P%i]%P;
    rep(i,1,N) ifac[i] = 1ll* ifac[i-1] * inv[i] % P;
    while(~scanf("%d%d",&n,&m)) {
        rep(i,0,n) g[i].clear() , in[i] = 0;
        rep(i,0,n) scanf("%d",par+i),--par[i],g[par[i]].pb(i) , in[par[i]]++;
        vi pts;rep(i,0,n) if(in[i]==0) pts.pb(i);
        rep(i,0,sz(pts)) if(!--in[par[pts[i]]]) pts.pb(par[pts[i]]);
        vi cir;int s=0;while(in[s]==0)++s;
        for(int t=par[s];cir.pb(t),t!=s;t=par[t]);
        for(auto c : cir){
            rep(i,0,sz(g[c])) if(in[g[c][i]]){
                g[c].erase(g[c].begin()+i);
                break;
            }
            dfs(c);
        }
        int smallloop = Kmp(cir) , block = sz(cir) / smallloop , waybranch = 1;
        rep(i,0,smallloop) waybranch=1ll*waybranch*way[cir[i]]%P;
        dp[1]=0;dp[2]=1ll*m*(m-1)%P;
        for(int cof=dp[2],i=3;i<=sz(cir);++i) cof=1ll*cof*(m-1)%P,dp[i]=(cof-dp[i-1]+P)%P;
        int ans=0;
        rep(step,1,block+1){
            int orbit=__gcd(step,block);
            pp(ans,1ll*dp[orbit*smallloop]*Pow(waybranch,orbit)%P);
        }
        ans=1ll*ans*inv[block]%P;
        printf("%d\n",ans);
    }
    return 0;
}
