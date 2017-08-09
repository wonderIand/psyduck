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

const int N = 4e4 + 10, M = 4;
int n,m,K;
const ll INF = 8e18;
ll Hcost[N][M],Wcost[N][M];
pair<ll,int> dp[1<<M],pd[1<<M];

inline void Update(pair<ll,int>&a,pair<ll,int> b){
    a=min(a,b);
}
pair<ll,int> check(ll d){
    rep(i,0,n-1) rep(j,0,m) Hcost[i][j]-=d;
    rep(i,0,n) rep(j,0,m-1) Wcost[i][j]-=d;
    rep(i,0,1<<m) dp[i]=mp(INF,0);
    dp[0]=mp(0,0);
    rep(i,0,n) rep(j,0,m){
        rep(i,0,1<<m) pd[i]=mp(INF,0);
        rep(k,0,1<<m) if(dp[k].fi!=INF){
            if(k>>j&1) Update(pd[k^1<<j],mp(dp[k].fi+Hcost[i-1][j],dp[k].se+1));
            int nk=k|1<<j;
            Update(pd[nk],dp[k]);
            if(j&&((nk>>(j-1)&3)==3)) Update(pd[nk^3<<(j-1)],mp(dp[k].fi+Wcost[i][j-1],dp[k].se+1));
        }
        rep(i,0,1<<m) dp[i]=pd[i];
    }
    rep(i,0,n-1) rep(j,0,m) Hcost[i][j]+=d;
    rep(i,0,n) rep(j,0,m-1) Wcost[i][j]+=d;
    return *min_element(dp,dp+(1<<m));
}

void solve(){
    scanf("%d%d%d",&n,&m,&K);
    rep(i,0,n-1) rep(j,0,m) scanf("%lld",Hcost[i] + j);
    rep(i,0,n) rep(j,0,m-1) scanf("%lld",Wcost[i] + j);
    ll l=1,r=1e14;
    while(l + 1 < r){
        ll mid=(l+r)>>1;
        auto e = check(mid);
        if(e.se <= K) l=mid;
        else r=mid;
    }
    auto e = check(l);
    printf("%lld\n",e.fi+K*l);
}

int main(){
    int T;scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
