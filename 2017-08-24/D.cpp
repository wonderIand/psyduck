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
int inv[N],to[N],sz[N],du[N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

void solve(){
    int n;scanf("%d",&n);
    rep(i,1,n+1) sz[i]=1,du[i]=0;
    rep(i,1,n+1) scanf("%d",to+i),du[to[i]]++;
    vi v;rep(i,1,n+1) if(du[i]==0) v.pb(i);
    rep(i,0,sz(v)){
        int c=v[i],p=to[c];
        sz[p]+=sz[c];
        if(!--du[p]) v.pb(p);
    }
    rep(i,1,n+1) if(du[i]){
        vi v;v.pb(i);int s=0;
        rep(i,0,sz(v)) {
            int c=v[i];s+=sz[c];
            du[c]=0;
            if(to[c]!=v[0]) v.pb(to[c]);
        }
        rep(i,0,sz(v)) sz[v[i]]=s;
    }
    int ans=n+1;
    rep(i,1,n+1) pp(ans,P-inv[1+sz[i]]);
    printf("%d\n",ans);
}

int main(){
    inv[1] = 1;
    rep(i,2,N) inv[i]=P-1ll*(P/i)*inv[P%i]%P;
    int T;scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
