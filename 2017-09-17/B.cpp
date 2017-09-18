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

const int N = 101 , M = 10 , K = 8;
db f[M*N][K*N] , g[M*N][K*N];
int lft[M*N] , rgt[M*N];

int main(){
    int T,n;
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d",&n);
        rep(i,0,M*n) lft[i] = 3 - (i % (2 * n) == 1) , rgt[i] = 3 - (i % (2 * n) == 2 * n - 1);
        rep(i,0,M*n) rep(j,0,K*n) f[i][j] = g[i][j] = 0;
        per(i,0,M*n) {
            db s=0.;
            for(int j=i;j<M*n&&j-i<K*n;++j) {
                if(j-lft[j]>=i) s+=f[i][j-lft[j]-i];
                g[j][j-i]=(j-i-1>=0?g[j][j-i-1]:0.)+(j-i-rgt[i]>=0?f[i+rgt[i]][j-i-rgt[i]]:0.);
                f[i][j-i]=(s+g[j][j-i])/(j-i+1)+1;
            }
        }
        db ans=0.;
        rep(i,0,2*n) ans+=f[i+rgt[i]][K*n-lft[i]-rgt[i]]+1;
        ans/=2*n;
        printf("%.6f\n",ans);
        rep(j,0,8*n){
            int i=j%(2*n);
            printf("%.6f ",f[i+rgt[i]][K*n-lft[i]-rgt[i]]+1);
        }
        puts("");
    }
    return 0;
}
