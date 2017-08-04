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

const int N = 6e4 + 10;
map<pii,int> dp;

int T,n,K,a[N],b[N],posb[N];
vi del[N<<1];
int Dp(int x,int y){
    if(x<=0||y<=0) return x+y;
    if(dp.count({x,y})) return dp[{x,y}];
    int &res=dp[{x,y}] , step=0;
    auto e=upper_bound(all(del[x-y+n]),x);
    if(e==del[x-y+n].begin()) step=min(x,y);
    else step=x-(*--e);
    if(step==0) res=min(Dp(x-1,y),Dp(x,y-1))+1;
    else res=Dp(x-step,y-step)+step;
    return res;
}

void solve(){
    scanf("%d%d",&n,&K);
    rep(i,1,n+1) scanf("%d",a + i);
    rep(i,1,n+1) scanf("%d",b + i),posb[b[i]]=i;
    rep(i,0,n<<1) del[i].clear();
    rep(i,1,n+1) for(int j=max(1,a[i]-K);j<=n&&j<=a[i]+K;++j)
        del[i-posb[j]+n].pb(i);
    dp.clear();
    printf("%d\n",Dp(n , n));
}

int main(){
    scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
