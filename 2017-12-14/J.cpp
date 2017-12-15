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

const int N = 3030;
const ll inf = 1e18;
int n , m , K;
vi val;
vector<pii> g[N];

ll dis[N];
ll dijkstra(int del) {
    rep(i,0,n) dis[i]=inf;
    dis[0]=0;
    priority_queue<pair<ll,int> > Q;
    Q.push(mp(0,0));
    int c,t;ll d,nd;
    while(sz(Q)) {
        d=-Q.top().fi;c=Q.top().se;Q.pop();
        if(d==dis[c]) {
            for(auto e : g[c]) {
                t=e.fi;
                nd=d+max(0,e.se-del);
                if(nd<dis[t])
                    dis[t]=nd,Q.push(mp(-dis[t],t));
            }
        }
    }
    return dis[n-1]+ll(K)*del;
}

int main(){
    scanf("%d%d%d",&n,&m,&K);
    rep(i,0,m){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        --u;--v;
        g[u].pb(mp(v , c));
        g[v].pb(mp(u , c));
        val.pb(c);
    }
    val.pb(0);
    ll ans = inf;
    for(auto e : val)
        ans = min(ans , dijkstra(e));
    printf("%lld\n",ans);
    return 0;
}
