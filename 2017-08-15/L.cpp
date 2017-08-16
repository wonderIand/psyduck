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

const int N = 15;
int T,m,n,P,down[N],up[N],f[N+1][1<<N],downsum[1<<N],upsum[1<<N];
inline void pp(int&x,int d){if((x+=d)>=P)x-=P;}
int C(int a,int b){
    if(a < b) return 0;
    map<int,int> times;
    auto update = [&](int x,int k){
        for(int i=2;i*i<=x;++i) if(x%i==0){
            while(x%i==0) x/=i,times[i]+=k;
        }
        if(x>1) times[x]+=k;
    };
    rep(i,0,b) update(a-i,1),update(i+1,-1);
    int res=1;
    for(auto e : times) rep(j,0,e.se)
        res=1ll*res*e.fi%P;
    return res;
}

int main(){
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d%d",&n,&m,&P);
        rep(i,0,n){
            auto read = [&]{
                int m,res=0,x;scanf("%d",&m);
                rep(i,0,m) scanf("%d",&x) , res|=1<<(x-1);
                return res;
            };
            down[i]=read();
            up[i]=read();
        }
        rep(i,1,1<<n) downsum[i]=downsum[i&(i-1)]|down[__builtin_ctz(i)];
        rep(i,1,1<<n) upsum[i]=upsum[i&(i-1)]|up[__builtin_ctz(i)];
        rep(i,0,n+1) rep(j,0,1<<n) f[i][j]=0;
        f[0][0]=1;
        int all=(1<<n)-1;
        int mask=all^(1<<2);
        rep(i,0,n) rep(j,0,1<<n) if(f[i][j]){
            for(int x=all^j,y=x;y;y=(y-1)&x){
                if((j&upsum[y])==0&&(y&downsum[j])==0)
                    pp(f[i+1][j|y],f[i][j]);
            }
        }
        int ans=0;
        rep(i,1,n+1) pp(ans,1ll*C(m,i)*f[i][all]%P);
        printf("%d\n",ans);
    }
    return 0;
}
