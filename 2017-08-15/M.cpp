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

const int P = 1e9 + 7 , M = 501;
ll H;
int X,Y,p,way[M],vis[M][M],_,pw[M]={1};
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int Pow(int x,ll t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
int inv(int x){return Pow(x,P-2);}
int dp[M][11];

int main(){
    rep(i,1,M) pw[i]=pw[i-1]*2%P;
    int T;scanf("%d",&T);
    rep(i,0,T){
        scanf("%lld%d%d%d",&H,&X,&Y,&p);
        rep(i,0,p) rep(j,0,p) vis[i][j]=0;
        _=0;
        int a=X%p,b=Y%p;
        do{
            vis[a][b]=1;
            ++_;
            b=b*X%p;
            a=(2*a+b)%p;
        }while(!vis[a][b]);
        memset(way,0,sizeof(way));
        int down=inv(Pow(2,_)-1);
        ll prez=-1,preup=0;
        for(int a=X%p,b=X%p,i=0;i<_&&i<H;++i){
            ll x=H-1-i,y=x%_,z=x/_;
            ll up=0;
            if(z==prez) up=preup;
            else prez=z,preup=up=(Pow(2,(z+1)%(P-1)*_%(P-1))-1+P)%P;
            pp(way[a] , 1ll*pw[y]*up%P*down%P);
            b=b*X%p;
            a=(2*a+b)%p;
        }
        rep(i,0,p) rep(j,0,Y+1) dp[i][j]=0;
        dp[0][0]=1;
        static int s[20]={0};
        rep(i,0,p) if(way[i]) {
            s[1]=way[i];
            for(int j=1,d=i;j<=Y;++j,s[j]=1ll*s[j-1]*(way[i]+j-1)%P*inv(j)%P,d=(d+i)%p) ;
            per(y,0,Y) rep(x,0,p) if(dp[x][y]){
                for(int dy=1,dx=i;dy+y<=Y;++dy,dx+=i)
                    pp(dp[(x+dx)%p][dy+y] , 1ll*s[dy]*dp[x][y]%P);
            }
        }
        int ans=0;
        rep(i,0,Y+1) pp(ans,dp[0][i]);
        printf("%d\n",ans);
    }
    return 0;
}
