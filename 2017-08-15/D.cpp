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

const int N = 2e5 + 10;
int n,m,x[N],y[N],c[N],w[N],du[N];
vi v[N];

int main(){
    int T;scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d",&n,&m);
        rep(i,1,n+1) c[i]=0,w[i]=2-(i*2==n+1),du[i]=0,v[i].clear();
        auto link = [&](int a,int b){
            du[a]++;
            c[a]+=w[b];
        };
        rep(i,0,m) {
            scanf("%d%d",x+i,y+i);
            link(x[i],y[i]);
            if(x[i]!=y[i]) link(y[i],x[i]);
        }
        ll ans=1ll*n*n*n;
        rep(i,1,n) if(c[i]) ans+=-3ll*n*w[i]*c[i]+3ll*w[i]*c[i]*c[i];
        rep(i,0,m) {
            int&a=x[i],&b=y[i];
            if(du[a]>du[b]) swap(a,b);
            v[a].pb(b);
        }
        rep(i,1,n+1) sort(all(v[i]));
        rep(i,0,m){
            int way[]={0,1,3,6};
            int a=x[i],b=y[i],cof=3-(a==b);
            vi&A=v[a],&B=v[b];
            for(int i=0,j=0;i<sz(A)&&j<sz(B);){
                if(A[i]<B[j]) ++i;
                else if(A[i]>B[j]) ++j;
                else ans-=w[a]*w[b]*w[A[i]]*way[cof-(a==A[i]||b==A[i])],++i,++j;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
