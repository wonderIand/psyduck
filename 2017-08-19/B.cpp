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

const int N = 20;
char s[N+10];
int T,n,m,Q,a[N],b[N],g[1<<N],rg[1<<N],cnt[1<<N];

bool ok[1<<N];int _;
int solve(int *g,int n,int A,int B){
    _=0;
    rep(i,0,1<<n) if((i|A)==A) ok[_++]=cnt[g[i]&B]>=cnt[i];
    n=__builtin_popcount(A);
    rep(i,0,n) rep(j,0,1<<n) if(j>>i&1)
        ok[j]&=ok[j^(1<<i)];
    int ans=0;
    rep(i,0,1<<n) ans+=ok[i];
    return ans;
}

int main(){
    rep(i,1,1<<N) cnt[i]=cnt[i>>1]+(i&1);
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d%d",&n,&m,&Q);
        rep(i,0,1<<n) g[i]=0;
        rep(i,0,1<<m) rg[i]=0;
        rep(i,0,n) {
            scanf("%s",s);
            rep(j,0,m) if(s[j]=='1')
                g[1<<i]|=1<<j,rg[1<<j]|=1<<i;
        }
        rep(i,1,1<<n) g[i]|=g[i&(i-1)]|g[1<<__builtin_ctz(i)];
        rep(i,1,1<<m) rg[i]|=rg[i&(i-1)]|rg[1<<__builtin_ctz(i)];
        rep(i,0,n) scanf("%d",a+i);
        rep(i,0,m) scanf("%d",b+i);
        printf("Case #%d:",i+1);
        rep(i,0,Q){
            int d=0;scanf("%d",&d);
            int maskg=0,maskrg=0;
            rep(i,0,n) if(a[i]%d==0) maskg|=1<<i;
            rep(i,0,m) if(b[i]%d==0) maskrg|=1<<i;
            printf(" %lld",1ll*solve(g,n,maskg,maskrg)*solve(rg,m,maskrg,maskg)-1);
        }
        puts("");
    }
    return 0;
}
