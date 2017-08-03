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

// init!! , G is root , B is base , len = 2^x
namespace NTT {
    const int N = 1<<18 , P = ((5 * 47) << 22) + 1 , G = 3 , B = 2;
    int w[2][N],rev[N];
    ll Pow(ll x, ll t){ll r=1;for(;t;t>>=1,x=x*x%P)if(t&1)r=r*x%P;return r;}
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
    void mult(int *a,int *b,int len){
        ntt(a,len,0);ntt(b,len,0);
        rep(i,0,len) a[i] = (ll)a[i]*b[i]%P;
        ntt(a,len,1);
    }
}
const int N = 1<<18 , P = NTT::P;
int m,K,e[N],f[N]={1},rf[N];
int Pow(int x,int t){int r(1);for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
void pp(int &x,int d){x+=d;if(x>=P)x-=P;}
int A[N],B[N],pw[N][11];
int comb(int x,int y){
    if(x<y)return 0;
    return 1ll*f[x]*rf[y]%P*rf[x-y]%P;
}
int mul(int step){
    ll r=1;
    rep(i,0,m) r=r*comb(e[i]+step-1,e[i])%P;
    return r;
}

int main(){
    NTT::ini();
    rep(i,1,N) f[i]=1ll*f[i-1]*i%P;
    rf[N-1]=Pow(f[N-1],P-2);
    per(i,0,N-1) rf[i]=1ll*rf[i+1]*(i+1)%P;
    for(int _=1;~scanf("%d%d",&m,&K);++_){
        int sume=0,len=1;
        rep(i,0,m) scanf("%*d%d",e + i) , sume += e[i];
        while(len < 2 * (sume + 1)) len <<= 1;
        rep(i,0,len){
            A[i]=i<=sume?1ll*mul(i)*rf[i]%P:0;
            B[i]=i<=sume?1ll*(i&1?(P-1):1)*rf[i]%P:0;
        }
        NTT::mult(A,B,len);
        rep(i,0,sume+1) A[i]=1ll*A[i]*f[i]%P;
        A[sume+1]=0;
        //rep(i,0,sume+1) printf("%d%c",A[i]," \n"[i==sume]);
        printf("Case #%d:",_);
        rep(j,0,sume+2) rep(i,0,K+1) pw[j][i]=i?1ll*pw[j][i-1]*A[j]%P:1;
        rep(i,0,K){
            int x=0;
            rep(j,1,sume+1) pp(x,1ll*pw[j+1][i]*pw[j][K-i]%P);
            printf(" %d",x);
        }
        printf("\n");
    }
    return 0;
}
