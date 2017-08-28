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

typedef unsigned int ui;
namespace NimProduct {
    const int N = 1 << (1 << 3) , M = 1 << 3;
    ui sg[N][N] , pw[5];
    inline ui Product(ui x,ui y){
        if(x < y) swap(x , y);
        if(x < N && ~sg[x][y]) return sg[x][y];
        int base = 4;
        while(base > 0 && x < pw[base]) --base;
        ui M = 1 << (1 << base);
        ui a = x >> (1 << base) , b = x & (M - 1);
        ui c = y >> (1 << base) , d = y & (M - 1);
        ui c1 = Product(a , c) ,
           c2 = Product(a^b , c^d) ,
           c3 = Product(b , d);
        ui res = ((c2^c3) << (1<<base)) | (Product(c1,M>>1)^c3);
        if(x < N) sg[x][y] = res;
        return res;
    }
    void Build(){
        rep(i,0,5) pw[i] = 1<<(1<<i);
        memset(sg , -1 , sizeof(sg));
        rep(i,0,N) sg[1][i]=sg[i][1]=i,sg[i][0]=sg[0][i]=0;
        rep(i,0,N) rep(j,0,N) Product(i,j);
    }
}
const int N = 2e6 + 10;
int SG(int x){return x ^ (x >> 1);}
#define order(x) sort(all(x));x.erase(unique(all(x)),x.end())
int xs[N],xt[N],y[N],id[N];
vi X;
int sg[N],add[N];
void modify(int c,int l,int r,int L,int R,int d){
    if(L <= l && r <= R){
        add[c] += d;
    } else {
        int m = (l + r) >> 1;
        if(L <= m) modify(c << 1 , l , m , L , R , d);
        if(R > m) modify(c << 1 | 1 , m + 1 , r , L , R , d);
    }
    if(add[c]) sg[c] = SG(X[r]) ^ SG(X[l - 1]);
    else sg[c] = l != r ? sg[c << 1] ^ sg[c << 1 | 1] : 0;
}

void solve(){
    int n,m;scanf("%d%d",&n,&m);
    X.clear();
    X.pb(0);
    rep(i,0,m<<1) id[i]=i;
    rep(i,0,m){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        --x1;++y2;
        xs[i<<1]=xs[i<<1|1]=x1;
        xt[i<<1]=xt[i<<1|1]=x2;
        y[i<<1] = y1;y[i<<1|1] = y2;
        X.pb(x1);X.pb(x2);
    }
    order(X);
    sort(id,id+(m<<1),[&](int a,int b){return y[a]<y[b];});
    int lasty = 1;
    ui ans = 0;
    rep(i,0,sz(X)<<2) sg[i]=add[i]=0;
#define rt 1,0,sz(X)-1
    for(int i=0,j=0,tot=m<<1;i<tot;i=j){
        ans ^= NimProduct::Product(sg[1],SG(y[id[i]]-1)^SG(lasty-1));
        lasty=y[id[i]];
        for(j=i;j<tot&&y[id[j]]==y[id[i]];++j){
#define rk(x) lower_bound(all(X),x)-X.begin()
            modify(rt,rk(xs[id[j]])+1,rk(xt[id[j]]),id[j]&1?-1:1);
        }
    }
    puts(ans ? "Yong Chol" : "Brother");
}

int main(){
    NimProduct::Build();
    int T;scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
