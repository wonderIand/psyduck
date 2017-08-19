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

const int N = 30003;
int n,P,phi[N];
int Pow(int x,ll t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

const db pi = acos(-1);
namespace FFT{
    const int N = 1<<16;
    struct vir {
        double r, i;
        vir() {r = i = 0;}
        vir(db r, db i) : r(r),i(i){}
        vir operator+(const vir &p) const {
            return vir(r + p.r, i + p.i);
        }
        vir operator-(const vir &p) const {
            return vir(r - p.r, i - p.i);
        }
        vir operator*(const vir &p) const {
            return vir(r * p.r - i * p.i, r * p.i + i * p.r);
        }
    };
    inline vir conj(const vir &p) {
        return vir(p.r, -p.i);
    }
    vir w[N], A[N], B[N], dfa[N], dfb[N], dfc[N], dfd[N];
    int L,n,bitrev[N];
    void init(int len) {
        L = 0;while(1<<L<=len) ++L;
        n=1<<L;
        rep(i,0,n) bitrev[i] = (bitrev[i>>1]>>1)|((i&1)<<(L-1));
        rep(i,0,n) w[i] = vir(cos(2*pi*i/n), sin(2*pi*i/n));
    }
    void fft(vir *a, const int &n) {
        rep(i,0,n) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
        for (int i=2,d=n>>1;i<=n;i<<=1,d>>=1)
            for (int j=0;j<n;j+=i) {
                vir *l=a+j,*r=a+j+(i>>1),*p=w;
                for (int k=0;k<(i>>1);++k) {
                    vir tmp=(*r)*(*p);
                    *r=*l-tmp,*l=*l+tmp;
                    ++l,++r,p+=d;
                }
            }
    }
    vi mul(const vi &a, const vi &b) {
        if((sz(a)<=100 && sz(b)<=100) || min(sz(a),sz(b))<=5){
            vi res(sz(a)+sz(b)-1,0);
            rep(i,0,sz(a)) rep(j,0,sz(b)) pp(res[i+j],1ll*a[i]*b[j]%P);
            return res;
        }
        init(sz(a)+sz(b));
        rep(i,0,n) A[i]=B[i]=vir(0,0);
        rep(i,0,sz(a)) A[i]=vir(a[i]&32767,a[i]>>15);
        rep(i,0,sz(b)) B[i]=vir(b[i]&32767,b[i]>>15);
        fft(A,n),fft(B,n);
        rep(i,0,n) {
            int j=(n-i)&(n-1);
            static vir da, db, dc, dd;
            da = (A[i] + conj(A[j])) * vir(0.5, 0);
            db = (A[i] - conj(A[j])) * vir(0, -0.5);
            dc = (B[i] + conj(B[j])) * vir(0.5, 0);
            dd = (B[i] - conj(B[j])) * vir(0, -0.5);
            dfa[j] = da * dc, dfb[j] = da * dd;
            dfc[j] = db * dc, dfd[j] = db * dd;
        }
        rep(i,0,n) {
            A[i]=dfa[i]+dfb[i]*vir(0, 1);
            B[i]=dfc[i]+dfd[i]*vir(0, 1);
        }
        fft(A,n),fft(B,n);
        vi ret(n,0);
        rep(i,0,n) {
            ll da = (ll) (A[i].r / n + 0.5) % P;
            ll db = (ll) (A[i].i / n + 0.5) % P;
            ll dc = (ll) (B[i].r / n + 0.5) % P;
            ll dd = (ll) (B[i].i / n + 0.5) % P;
            pp(ret[i], (da + ((db + dc) << 15) + (dd << 30)) % P);
        }
        return ret;
    }
}

int f[N],g[N],fac[N]={1},ifac[N];
vi A,B;
void divideF(int l,int r){
    if(l>=r) return;
    int mid=(l+r)>>1;
    divideF(l,mid);
    A.resize(mid-l+1);
    rep(i,l,mid+1) A[i-l]=1ll*f[i]*ifac[i-1]%P;
    B.resize(r-l+1);
    rep(i,0,sz(B)) B[i]=1ll*g[i]*ifac[i]%P;
    A=FFT::mul(A,B);
    rep(i,mid+1,r+1) pp(f[i] , P-1ll*A[i-l]*fac[i-1]%P);
    divideF(mid+1,r);
}

void divideG(int l,int r,int d){
    if(l>=r) return;
    int mid=(l+r)>>1;
    divideG(l,mid,d);
    A.resize(mid-l+1);
    rep(i,l,mid+1) A[i-l]=1ll*g[i*d]*ifac[i*d]%P;
    B.resize(r-l+1);
    rep(i,1,sz(B)) B[i]=1ll*f[i*d]*ifac[i*d-1]%P;
    A=FFT::mul(A,B);
    rep(i,mid+1,r+1) pp(g[i*d] , 1ll*A[i-l]*fac[i*d-1]%P);
    divideG(mid+1,r,d);
}

int solve(){
    scanf("%d%d",&n,&P);
    rep(i,1,n+1) fac[i]=1ll*fac[i-1]*i%P;
    ifac[n]=Pow(fac[n],P-2);
    per(i,0,n) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
    rep(i,1,n+1) f[i]=g[i]=Pow(2,1ll*i*(i-1)/2);
    divideF(1 , n);
    int ans=g[n];
    rep(i,2,n+1) if(n%i==0){
        for(int j=i;j<=n;j+=i) g[j]=f[j];
        divideG(1,n/i,i);
        pp(ans,1ll*phi[i]*g[n]%P);
    }
    return ans;
}

int main(){
    rep(i,1,N) phi[i]=i;
    rep(i,1,N) for(int j=i+i;j<N;j+=i) phi[j]-=phi[i];
    int T;scanf("%d",&T);
    rep(i,1,T+1) printf("Case #%d: %d\n",i,solve());
    return 0;
}
