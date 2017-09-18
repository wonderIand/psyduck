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

typedef long double db;
const int N = 404;
const db pi = acos(-1.) , eps = 1e-10;
db A[N * N];int rk[N][N] , f[N];
vi id;
int sgn(db x){return (x > eps) - (x < -eps);}
db area(int a,int b,int n){
    return sin(2 * pi * a / n) + sin(2 * pi * b / n) - sin(2 * pi * (a + b) / n);
}

void Prepare(int n){
    id.clear();
    memset(rk , -1 , sizeof(rk));
    rep(i,1,n+1) rep(j,i,n+1) if(n-i-j>=j) {
        A[i * n + j] = area(i , j , n);
        id.pb(i * n + j);
    }
    sort(all(id) , [&](int a,int b){return A[a] < A[b];});
    int _ = 0;
    rep(i,0,sz(id)) rk[id[i]/n][id[i]%n] = i && sgn(A[id[i]] - A[id[i-1]]) != 0 ? ++_ : _;
    rep(i,1,n+1) rep(j,1,n+1-i) if(n-i-j>=1&&!~rk[i][j]){
        vi v{i,j,n-i-j};sort(all(v));
        rk[i][j]=rk[v[0]][v[1]];
    }
}

ll solve(int n,int P){
    int res=0;
    rep(i,0,sz(id)){
        int a = id[i] / n , b = id[i] % n , c = n - a - b;
        rep(j,0,c+1) f[j]=0;
        f[1] = 1;
        rep(j,2,c+1) {
            ll x = 0;int times=0;
            for(int k=1;k+k<j;++k) if(rk[k][j-k]<rk[a][b]){
                ++times;x+=ll(f[k])*f[j-k];
                if(times>>3) times=0,x%=P;
            }
            x = x * 2 % P;
            if((~j & 1) && rk[j>>1][j>>1]<rk[a][b])
                (x+=ll(f[j>>1])*f[j>>1])%=P;
            f[j]=x;
        }
        int same=0+(a==b)+(a==c)+(b==c);
        int way=(same==3?n/3:(same==0?2*n:n));
        (res+=ll(f[c])*f[a]%P*f[b]%P*way%P)%=P;
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    rep(i,0,T) {
        int n,x,y;
        scanf("%d%d%d",&n,&x,&y);
        Prepare(n);
        printf("%lld\n",solve(n , x) * solve(n , y));
    }
    return 0;
}
