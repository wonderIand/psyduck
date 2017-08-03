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
#define de(x) cout << #x << " = " << x << endl;
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
//-------
const int N = 404 , P = 998244353 , M = 201010;
int n , m , g[N][N] , f[M] = {1} , du[N] , rf[M];
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}

int a[N][N];
int tG(){
    n=m;
    rep(i,0,n) rep(j,0,n){
        if(i == j) a[i][j] = du[i] - g[i][i];
        else a[i][j] = (P - g[i][j]) % P;
    }
    //rep(i,0,n) rep(j,0,n){
    //    printf("%d%c",a[i][j]," \n"[j+1==n]);
    //}
    int x=1;
    --n;
    rep(i,0,n){
        if(!a[i][i]){
            int j;
            for(j=i+1;j<n;++j)
                if(a[j][i]) break;
            if(j==n) return 0;
            for(int k=i;k<n;++k)
                swap(a[i][k],a[j][k]);
            x=1ll*x*(P-1)%P;
        }
        x=1ll*x*a[i][i]%P;
        int s=Pow(a[i][i],P-2);
        for(int k=i+1;k<n;++k)
            a[i][k]=1ll*a[i][k]*s%P;
        for(int j=i+1;j<n;j++)
            for(int k=i+1;k<n;++k)
                a[j][k]=(a[j][k]-1ll*a[j][i]*a[i][k]%P+P)%P;
    }
    return x;
}
int out[N];
int solve(){
    rep(i,0,m) du[i]=out[i]=0;
    rep(i,0,m) rep(j,0,m) scanf("%d",g[i] + j) , du[j] += g[i][j] , out[i] += g[i][j];
    rep(i,0,m) if(out[i] != du[i]) return 0;
    ll ans=1;
    rep(i,0,m) if(du[i]) ans=ans*f[du[i]-1]%P;
    ans=ans*tG()%P*du[0]%P;
    rep(i,0,m) rep(j,0,m) if(g[i][j]) ans=ans*rf[g[i][j]]%P;
    return ans;
}

int main() {
    rep(i,1,M) f[i] = 1ll * f[i-1] * i % P;
    rep(i,0,M) rf[i] = Pow(f[i] , P - 2);
    int t=0;
    while(~scanf("%d",&m)){
        printf("Case #%d: %d\n",++t,solve());
    }
    return 0;
}
