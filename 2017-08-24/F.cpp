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

const int P = 1e9 + 7;
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int n,K,loop2;
vi dp;
vector<pii> loop;

const int N = 60;
struct MM{
    int a[N][N],n;
    MM(int n,int x):n(n){
        rep(i,0,n) rep(j,0,n) a[i][j]=i==j?x:0;
    }
};
MM operator * (const MM&a,const MM&b){
    int n=a.n;
    MM r(n,0);
    rep(i,0,n) rep(j,0,n) rep(k,0,n) pp(r.a[i][j],1ll*a.a[i][k]*b.a[k][j]%P);
    return r;
}
MM operator ^ (MM a,int t){
    int n=a.n;
    MM r(n,1);
    for(;t;t>>=1,a=a*a)if(t&1)r=r*a;
    return r;
}

int Kbig(int n){
    dp = vi(n + 1,0);
    dp[0] = 1;
    rep(i,1,n+1){
        for(auto e : loop) if(i >= e.fi)
            pp(dp[i] , 1ll * dp[i - e.fi] * e.se % P);
        if(i >= 4 && loop2) pp(dp[i] , dp[i-4] * 4ll % P);
    }
    return dp[n];
}

int Ksmall(){
    int m = loop.back().fi;
    if(m == 2) m = 4;
    Kbig(m);
    if(n <= m) return dp[n];
    MM a(m,0);
    for(auto e : loop) a.a[0][e.fi-1]=e.se;
    if(loop2) a.a[0][3]=4;
    rep(i,1,m) a.a[i][i-1]=1;
    a = a ^ (n - m + 1);
    int res=0;
    rep(i,0,m) pp(res,1ll*a.a[0][i]*dp[m-1-i]%P);
    return res;
}

void solve(){
    scanf("%d%d",&n,&K);
    loop.clear();
    for(int i=1;i*i<=K;++i) if(K%i==0){
        auto check = [&](int x){
            return (K/x) & 1;
        };
        auto waycal = [&](int x){
            return x <= 2 ? x : Pow(2,x);
        };
        if(check(i)) loop.pb({i,waycal(i)});
        if(i*i!=K&&check(K/i)) loop.pb({K/i,waycal(K/i)});
    }
    sort(all(loop));
    loop2 = find(all(loop),mp(2,2)) != loop.end();
    printf("%d\n",K <= 60 ? Ksmall() : Kbig(n));
}

int main(){
    int T;scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
