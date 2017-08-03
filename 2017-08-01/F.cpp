#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define de(x) cout << #x << " = " << x << endl
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
//-------

const int N = 1<<19 , P = 998244353 , G = 3 , B = 2;
ll Pow(ll x,ll t){ll r=1;for(;t;t>>=1,x=x*x%P)if(t&1)r=r*x%P;return r;}
namespace NTT{
    int w[2][N] , rev[N];
    void ini(){
        ll t=Pow(G,(P-1)/N);
        w[0][0]=w[1][0]=1;
        rep(i,1,N) w[0][i]=t*w[0][i-1]%P;
        rep(i,1,N) w[1][i]=w[0][N-i];
        rep(i,0,N) for(int j=1;j<N;j*=B) (rev[i]<<=1)|=(i/j)%B;
    }
    void ntt(int *a,int n,int o){
        int tt=N/n;
        rep(i,0,n){
            int j=rev[i]/tt;
            if(i<j) swap(a[i],a[j]);
        }
        for(int i=1;i<n;i<<=1)
            for(int j=0,t=N/(i+i);j<n;j+=i+i)
                for(int k=j,l=0;k<j+i;++k,l+=t){
                    int b=(ll)a[k+i]*w[o][l]%P;
                    a[k+i] = a[k]-b; if(a[k+i]<0) a[k+i]+=P;
                    a[k]= a[k]+b; if(a[k]>=P) a[k]-=P;
                }
        if(o==1){
            ll inv = Pow(n,P-2);
            rep(i,0,n) a[i]=a[i]*inv%P;
        }
    }
    void mul(int *a,int*b,int len){
        ntt(a,len,0);ntt(b,len,0);
        rep(i,0,len) a[i]=(ll)a[i]*b[i]%P;
        ntt(a,len,1);
    }
}

void pp(int &x,int d){x += d;if(x >= P) x-=P;}
int n , a[N] , b[N] , m , f[N] = {1}, rf[N] , x , pw[N];

int main() {
    rep(i,1,N) f[i] = 1ll * f[i-1] * i % P;
    rf[N-1] = Pow(f[N-1] , P-2);
    per(i,0,N-1) rf[i] = 1ll * rf[i + 1] * (i + 1) % P;
    NTT::ini();
    while(~scanf("%d",&n)){
        rep(i,0,n+1) scanf("%d",a + i);
        scanf("%d",&m);
        x = 0;
        int tmp;
        rep(i,0,m){
            scanf("%d",&tmp);
            pp(x , tmp);
        }
        int len = 1;
        while(len < (n + 1) * 2) len <<= 1;
        rep(i,0,n+1) a[i] = 1ll * a[i] * f[i] % P;
        tmp=1;
        rep(i,0,n+1) b[n-i] = 1ll * (i & 1 ? P - 1 : 1) * rf[i] % P * tmp % P , tmp = 1ll*tmp*x%P;
        //rep(i,0,n+1) printf("%d%c",a[i]," \n"[i==n]);
        //rep(i,0,n+1) printf("%d%c",b[i]," \n"[i==n]);
        rep(i,n+1,len) a[i]=b[i]=0;
        NTT::mul(a,b,len);
        rep(i,0,n+1) a[n+i] = 1ll * a[n+i] * rf[i] % P;
        rep(i,0,n+1) printf("%d ",a[n+i]);
        puts("");
    }
    return 0;
}
