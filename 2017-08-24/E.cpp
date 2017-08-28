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

const int M = 4 , N = 1e5 + 10 , S = 400 , P = 998244353;
void inline pp(int &x,int d){if((x+=d)>=P)x-=P;}
int Striling[M][M],fac[M]={1},cof[M]={1},inv[M];
int ans[N],g[N][M],f[N];

int main(){
    Striling[0][0] = 1;
    rep(i,1,M) rep(j,1,i+1) Striling[i][j] = Striling[i-1][j-1] + j * Striling[i-1][j];
    rep(i,1,M) fac[i]=1ll*fac[i-1]*i;
    inv[1]=1;rep(i,2,M) inv[i]=P-1ll*(P/i)*inv[P%i]%P;
    int T;scanf("%d",&T);
    f[0]=1;g[0][0]=1;
    for(int i=1;i*(S+1)<N;++i){
        per(j,1,N) f[j]=f[j-1];f[0]=0;
        rep(j,i,N) pp(f[j],f[j-i]);
        rep(j,1,M) cof[j]=1ll*cof[j-1]*(i-j+1)%P*inv[j]%P;
        for(int d=S*i,j=(S+1)*i;j<N;++j) rep(k,0,M){
            pp(g[j][k],1ll*f[j-d]*cof[k]%P);
        }
    }
    rep(i,1,S+1) rep(j,i,N) rep(k,0,M){
        pp(g[j][k],g[j-i][k]);
        if(k>=1) pp(g[j][k],g[j-i][k-1]);
    }
    rep(i,1,N) rep(j,0,4) pp(ans[i],1ll*g[i][j]*(Striling[3][j]*fac[j])%P);
    rep(i,0,T){
        int n;scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
    return 0;
}
