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

const int N = 55 , P = 998244353 , M = 2500;
int m,b,c,comb[N][N]={{1}};
char s[M];
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
void pp(int &x,int d){if((x+=d)>=P)x-=P;}

struct Poly{
    int cof[N];
    Poly(){rep(i,0,m+1) cof[i]=0;}
    Poly(vi v){rep(i,0,m+1) cof[i]=i<sz(v)?v[i]:0;}
    Poly(int p){cof[0]=1;rep(i,1,m+1)cof[i]=1ll*cof[i-1]*p%P;}
    void output(){
        rep(i,0,m+1) printf("%d%c",cof[i]," \n"[i==m]);
    }
    Poly operator + (const Poly&b){
        Poly r;
        rep(i,0,m+1) r.cof[i]=(cof[i]+b.cof[i])%P;
        return r;
    }
    Poly operator * (const Poly&b){
        Poly r;
        rep(i,0,m+1) rep(j,0,i+1) pp(r.cof[i],1ll*cof[j]*b.cof[i-j]%P);
        return r;
    }
    Poly binomial (const Poly&b){
        Poly r;
        rep(i,0,m+1) rep(j,0,i+1) pp(r.cof[i],1ll*cof[j]*b.cof[i-j]%P*comb[i][j]%P);
        return r;
    }
}f[N][N];

struct Big{
    ll a[M],len,base;
    int sig;
    Big(){}
    Big(char *s){
        len=strlen(s);
        base=10;sig=1;
        rep(i,0,len) a[i]=s[len-1-i]-'0';
    }
    void output(){
        rep(i,0,len) printf("%lld%c",a[i]," \n"[i+1==len]);
    }
    void convert(int nbase){
        Big r;r.len=0,r.base=nbase;
        while(len>0){
            ll x=0;
            per(i,0,len){
                x=x*base+a[i];
                a[i]=x/nbase;
                x%=nbase;
            }
            while(len>0&&!a[len-1]) --len;
            r.a[r.len++]=x;
        }
        *this = r;
    }
    Big operator + (ll x){
        for(ll i=0,r=0;i<len;++i){
            r+=x%base;
            x/=base;
            r+=a[i];
            a[i]=r%base;
            r/=base;
            if(r&&i+1==len) ++len;
        }
        return *this;
    }
    Big operator - (ll x){
        for(ll i=0,r=0;i<len;++i){
            r-=x%base;
            x/=base;
            r+=a[i];
            a[i]=r%base;
            r/=base;
            if(a[i]<0) a[i]+=base,--r;
            if(i+1==len&&r) {
                sig=-1;
                return *this;
            }
        }
        while(len>0&&!a[len-1]) --len;
        return *this;
    }
}n;

int main(){
    rep(i,1,N) rep(j,0,i+1) comb[i][j]=j?(comb[i-1][j-1]+comb[i-1][j])%P:1;
    while(~scanf("%d%d%d",&m,&b,&c)){
        scanf("%s",s);
        n=Big(s);
        n.convert(b);
        f[0][0] = Poly(0);
        rep(i,1,m+1) {
            f[i][0] = Poly(0);
            rep(j,1,m+1) f[i][j]=f[i-1][j]+f[i-1][j-1].binomial(Poly(Pow(b,i)));
        }
        int ans(0);
        rep(szS,0,m+1){
            ll lim=ll(szS)*(c-1);
            Big a=n;
            if(lim>0) a=a+lim;
            else if(lim<0) a=a-(-lim);
            if(a.sig==-1) continue;
            Big a0=a;a0.convert(P);
            int remain=a0.a[0];
            Poly p(0);
            rep(i,0,m) p=p*Poly({(int)(remain-1+m-i+P)%P,P-1});
            Poly prefix(0),sum;int cnt1=0;
            if(a.len>m+1) sum=f[m][szS];
            else{
                per(i,0,a.len){
                    if(cnt1>szS) break;
                    if(a.a[i]>=1){
                        sum=sum+prefix.binomial(f[max(0,i-1)][szS-cnt1]);
                    }
                    if(a.a[i]>=2 && i){
                        prefix = prefix.binomial(Poly(Pow(b,i)));
                        cnt1++;
                        if(szS-cnt1>=0)
                            sum=sum+prefix.binomial(f[max(0,i-1)][szS-cnt1]);
                        break;
                    }
                    if(a.a[i]==1){
                        cnt1++;
                        prefix = prefix.binomial(Poly(Pow(b,i)));
                    }
                }
            }
            int tmp=0;
            rep(i,0,m+1) pp(tmp,1ll*sum.cof[i]*p.cof[i]%P);
            if(szS & 1) pp(ans,P - tmp);
            else pp(ans , tmp);
        }
        rep(i,1,m+1) ans=1ll*ans*Pow(i,P-2)%P;
        static int cs = 0;
        printf("Case #%d: %d\n",++cs,ans);
    }
    return 0;
}

