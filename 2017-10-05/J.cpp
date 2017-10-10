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

const int N = 55;
int T , n , range[N] , par[N] , sz[N];
ll dp[N][2][N][N] , f[2][N][N] , g[2][N][N];
vi G[N];

void dfs(int c,int fa,int dep){
    for(auto t : G[c]) if(t != fa){
        dfs(t , c , dep+1);
    }
    sz[c] = 1;
    rep(i,0,2) rep(j,0,sz[c]+1) rep(k,0,n+1) f[i][j][k]=0;
    f[0][0][n]=f[1][0][dep]=1;
    for(auto t : G[c]) if(t != fa){
        int newsz=sz[c]+sz[t];
        rep(i,0,2) rep(j,0,newsz+1) rep(k,0,n+1) g[i][j][k]=0;
        rep(i,0,2) rep(j,0,sz[c]+1) rep(k,0,n+1) if(f[i][j][k])
            rep(ii,0,2) rep(jj,0,sz[t]+1) rep(kk,0,n+1) if(dp[t][ii][jj][kk]){
                g[i^ii][j+jj][min(k,kk)] += f[i][j][k] * dp[t][ii][jj][kk];
            }
        rep(i,0,2) rep(j,0,newsz+1) rep(k,0,n+1) f[i][j][k]=g[i][j][k];
        sz[c]=newsz;
    }
    rep(i,0,2) rep(j,0,sz[c]+1) rep(k,0,n+1) dp[c][i][j][k]=0;
    rep(i,0,2) rep(j,0,sz[c]+1) rep(k,0,n+1) if(f[i][j][k])
        dp[c][i][j+(k<n&&dep+range[c]>=k)][k]+=f[i][j][k];
}

int main(){
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d",&n);
        rep(i,0,n) G[i].clear();
        rep(i,0,n) scanf("%d",range+i);
        rep(i,1,n) scanf("%d",par+i),--par[i],G[par[i]].pb(i);
        dfs(0,-1,0);
        ll left=0;
        long double right=0.;
        rep(j,1,n+1) {
            ll sum=0;
            rep(k,0,n+1) sum+=dp[0][1][j][k]-dp[0][0][j][k];
            sum*=n;
            if(sum>=0) left+=sum/j,right+=(sum%j)/(long double)(j);
            else left-=-sum/j,right-=(-sum%j)/(long double)(j);
        }
        printf("Case #%d: %.12f\n",i+1,(double)(left+right));
    }
    return 0;
}
