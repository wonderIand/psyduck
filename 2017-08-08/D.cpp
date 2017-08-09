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

const int N = 1e5 + 10;
int T,n,m,a[N],P;
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*x*r%P;return r;}
void pp(int &x,int d){
    if((x+=d)>=P) x-=P;
}

const db pi = acos(-1);
namespace FFT{
    const int N = 1<<18;
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

int pri[N],_p,vis[N],phi[N],fac[N]={1},ifac[N];
int C(int a,int b){
    return 1ll*fac[a]*ifac[b]%P*ifac[a-b]%P;
}
void solve(){
    scanf("%d%d",&n,&P);
    rep(i,1,n+1) fac[i]=1ll*fac[i-1]*i%P;
    ifac[n]=Pow(fac[n],P-2);
    per(i,0,n) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
    vi a;
    int ans=0;
    rep(d,1,n+1) {
        int sz=n/d+1;
        a.resize(sz);
        rep(i,0,sz) a[i]=i?ifac[i*d]:0;
        vi r=FFT::mul(a,a);
        int tmp=0;
        rep(i,0,sz) pp(tmp,1ll*ifac[n-i*d]*r[i]%P);
        pp(ans,1ll*phi[d]*tmp%P);
    }
    ans=1ll*ans*fac[n]%P;
    rep(i,1,n+1) pp(ans,2ll*C(n,i)*i%P);
    ans=1ll*ans*Pow(3,n)%P;
    printf("%d\n",ans);
}



int main(){
    phi[1]=1;
    rep(i,2,N){
        if(!vis[i]) pri[_p++] = i , phi[i] = i-1;
        for(int j=0,o;j<_p&&(o=pri[j]*i)<N;++j){
            vis[o] = true;
            if(i%pri[j]) phi[o] = (pri[j] - 1) * phi[i];
            else{
                phi[o] = pri[j] * phi[i];
                break;
            }
        }
    }
    scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
