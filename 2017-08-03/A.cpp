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

const int P = 3*(1<<18)+1 , N = 1<<18 , G = 11 , B = 2;
ll Pow(ll x, ll t){ll r=1;for(;t;t>>=1,x=x*x%P)if(t&1)r=r*x%P;return r;}
namespace NTT {
    int w[2][N],rev[N];
    void ini(){
        ll t = Pow(G,(P-1)/N);
        w[0][0] = w[1][0] = 1;
        rep(i,1,N) w[0][i] = t*w[0][i-1]%P;
        rep(i,1,N) w[1][i] = w[0][N-i];
        rep(i,0,N) for(int j=1;j<N;j*=B) (rev[i]<<=1)|=(i/j)%B;
    }
    void ntt(int *a,int n,int o){
        int tt = N/n;
        rep(i,0,n){
            int j = rev[i]/tt;
            if(i<j) swap(a[i],a[j]);
        }
        for(int i=1;i<n;i<<=1)
            for(int j=0,t=N/(i+i);j<n;j+=i+i)
                for(int k=j,l=0;k<j+i;++k,l+=t){
                    int b = (ll)a[k+i]*w[o][l]%P;
                    a[k+i] = a[k]-b; if(a[k+i]<0) a[k+i]+=P;
                    a[k] = a[k]+b; if(a[k]>=P) a[k]-=P;
                }
        if(o == 1){
            ll inv = Pow(n,P-2);
            rep(i,0,n) a[i] = a[i]*inv%P;
        }
    }
}
void pp(int &x,int d){
    x += d;if(x >= P) x -= P;
}

int T,K,n,m,a[10][N],fac[N]={1},sum[N],cnt0[N],prod[N],ifac[N],inv[P],num[10][N];
char s[N];
void solve(){
    scanf("%d%d%d",&K,&n,&m);
    rep(i,1,K) {
        scanf("%s",s);
        rep(j,0,n+1) a[i][j]=(num[i][j]=s[j]-'0')*ifac[j];
    }
    int len=1;
    while(len < (n * (K - 1) + 1)) len <<= 1;
    rep(i,1,K) rep(j,n+1,len) a[i][j]=0;
    rep(i,1,K) NTT::ntt(a[i],len,0);
    rep(i,0,len) sum[i]=cnt0[i]=0,prod[i]=1;
    rep(i,1,K) rep(j,0,len){
        if(a[i][j]==0) cnt0[j]++;
        else prod[j]=1ll*prod[j]*a[i][j]%P;
    }
    rep(i,0,len) if(!cnt0[i]) pp(sum[i],prod[i]);
    rep(times,0,m){
        int x,y;
        scanf("%d%d",&x,&y);
        int t=1ll*(num[x][y]?P-1:1)*ifac[y]%P,p=Pow(G,1ll*(P-1)/len*y);
        num[x][y]^=1;
        rep(j,0,len){
            if(a[x][j]) prod[j]=1ll*prod[j]*inv[a[x][j]]%P;
            else cnt0[j]--;
            pp(a[x][j],t);
            if(a[x][j]) prod[j]=1ll*prod[j]*a[x][j]%P;
            else cnt0[j]++;
            t=1ll*t*p%P;
        }
        rep(j,0,len) if(!cnt0[j]) pp(sum[j],prod[j]);
    }
    NTT::ntt(sum,len,1);
    int ans=0;
    rep(i,1,len) pp(ans,1ll*sum[i]*fac[i]%P);
    printf("%d\n",ans);
}

int main(){
    NTT::ini();
    rep(i,1,P) inv[i]=Pow(i,P-2);
    rep(i,1,N) fac[i]=1ll*fac[i-1]*i%P;
    ifac[N-1]=Pow(fac[N-1],P-2);
    per(i,0,N-1) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
    scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}

