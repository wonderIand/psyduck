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

const int P = 41 * 797 , p1 = 41 , p2 = 797 , Q = 1<<30;
int T,n,mu[P];
ll a[p1][p2],remain[p1][p2];
struct root{
    int r,p;
    vi ex,lg;
    void ini(int _p){
        r=2;p=_p;
        ex=lg=vi(p);
        for(int c,i=-1;;++r){
            for(c=1,i=0;!(i&&c==1);++i,c=1ll*c*r%p) ex[lg[c]=i]=c;
            if(i==p-1) break;
        }
    }
}r1,r2;

typedef long double ld;
typedef complex<ld> vir;
const long double pi = acos(ld(-1.));
namespace FFT{
    void fft(vir *F,int len,int o){
        int j = 0 , k , h;
        rep(i,0,len-1){
            if(i < j) swap(F[i] , F[j]);
            for(k=len;j>=(k>>=1);j&=~k);  j|=k;
        }
        for(h=1;h<len;h<<=1){
            vir wn(cos(pi*o/h),sin(pi*o/h));
            for(j=0;j<len;j+=h<<1){
                vir w(1.);
                for(k=j;k<j+h;++k,w=w*wn){
                    vir b = w*F[k+h];
                    F[k+h] = F[k]-b , F[k] = F[k]+b;
                }
            }
        }
        if(o == -1) rep(i,0,len) F[i] = F[i]/(ld)len;
    }
}
const int L = 131072 , M = 233637;
ll f[L],cnt[L];vir A[L];
int x[M],y[M],du[P],mcnt;vector<pii> g[P];

int main(){
    r1.ini(p1);r2.ini(p2);
    rep(i,0,P) remain[i%p1][i%p2]=i;
    mu[1]=1;rep(i,1,P) for(int j=i+i;j<P;j+=i) mu[j]-=mu[i];
    rep(g,1,P) for(int i=g;i<P;i+=g) for(int j=i;(ll)i/g*j<P;j+=g) if(mu[i]&&mu[j]&&__gcd(i,j)==g)
        x[mcnt]=i,y[mcnt++]=j,du[i]++,du[j]++;
    rep(i,0,mcnt){
        int &a=x[i],&b=y[i];
        if(du[a]>du[b]) swap(a,b);
        g[a].pb({b,a/__gcd(a,b)*b});
    }
    rep(i,0,P) sort(all(g[i]));
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d",&n);
        memset(a,0,sizeof(a));
        memset(cnt,0,sizeof(cnt));
        rep(i,0,n){
            int x;scanf("%d",&x);
            a[x%p1][x%p2]++;
        }
        rep(i,0,p1){
            ll t=a[i][0];
            rep(j,1,p2) t+=a[i][j]*2;
            rep(j,0,p1) (cnt[remain[i*j%p1][0]]+=a[j][0]*t)%=Q;
        }
        rep(i,1,p2){
            ll t=a[0][i];
            rep(j,1,p1) t+=a[j][i]*2;
            rep(j,1,p2) (cnt[remain[0][i*j%p2]]+=a[0][j]*t)%=Q;
        }
        int len=1;while(len<2*(p1*p2*2)) len<<=1;
        memset(f,0,sizeof(f));
#define id(x,y) x*p2*2+y
        rep(i,1,p1) rep(j,1,p2) if(a[i][j]) f[id(r1.lg[i],r2.lg[j])]+=a[i][j];
        rep(i,0,len) A[i]=f[i];
        FFT::fft(A,len,1);
        rep(i,0,len) A[i]*=A[i];
        FFT::fft(A,len,-1);
        rep(i,0,len) f[i]=(ll)(A[i].real()+0.5);
        rep(i,0,len) if(f[i]) (cnt[remain[r1.ex[i/(p2*2)%(p1-1)]][r2.ex[i%(p2*2)%(p2-1)]]]+=f[i])%=Q;
        ll ans=3*cnt[0]*cnt[1]%Q*cnt[1]%Q;
        auto pp = [&](ll &x,ll d){
            x+=d;
            if(x<0) x+=Q;
            if(x>=Q) x-=Q;
        };
        rep(i,1,P) for(int j=i+i;j<P;j+=i) pp(cnt[i],cnt[j]);
        rep(i,0,mcnt){
            int way[]={0,1,3,6};
            int a=x[i],b=y[i],cof=3-(a==b);
            vector<pii>&A=g[a],&B=g[b];
            int lab=a/__gcd(a,b)*b;
            if(!cnt[lab]) continue;
            for(int i=0,j=0;i<sz(A)&&j<sz(B);){
                if(A[i].fi<B[j].fi) ++i;
                else if(A[i].fi>B[j].fi) ++j;
                else {
                    int c=A[i].fi;
                    pp(ans,mu[a]*mu[b]*mu[c]*cnt[lab]*cnt[A[i].se]%Q*cnt[B[j].se]%Q*way[cof-(a==c||b==c)]%Q);
                    ++i,++j;
                }
            }
        }
        printf("%d\n",(int)ans);
    }
    return 0;
}
