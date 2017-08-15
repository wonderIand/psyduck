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


template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 10;
    int s , t , n , h[N] , cur[N] , level[N] , q[N] , e , ne[M] , to[M];
    T cap[M] , flow;
    void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
    void link(int u,int v,T w){ liu(u , v , w);liu(v , u , 0);}
    void ini(int _n = N) { fill(h , h + (n=_n) , -1);e = 0;}
    bool bfs(){
        int L = 0 , R = 0;
        fill(level , level + n , -1);
        level[q[R++] = s] = 0;
        while(L < R && level[t] == -1){
            int c = q[L++];
            for(int k=h[c];~k;k=ne[k])
                if(cap[k] > 0 && level[to[k]] == -1)
                    level[q[R++] = to[k]] = level[c] + 1;
        }
        return ~level[t];
    }
    T dfs(int c,T mx){
        if(c == t) return mx;
        T ret = 0;
        for(int &k = cur[c];~k;k = ne[k]){
            if(level[to[k]] == level[c] + 1 && cap[k] > 0){
                T flow = dfs(to[k] , min(mx , cap[k]));
                ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
                if(!mx) return ret;
            }
        }
        level[c] = -1;
        return ret;
    }
    T run(int _s,int _t){
        s = _s , t = _t;
        flow = 0;
        while(bfs()){
            copy(h , h + n , cur);
            flow += dfs(s,~0U>>1);
        }
        return flow;
    }
};
Dinic<ll> it;
const int N = 55 , inf = 1e9;
int T,n,m,K,a[N][N];

int main(){
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d%d",&n,&m,&K);
        rep(i,0,n) rep(j,0,m) scanf("%d",a[i]+j);
        int S=n*m,T=S+1;
        it.ini(T+1);
#define id(x,y) (x*m+y)
        int B=1000;
        rep(i,0,n) it.link(S,id(i,0),inf) , it.link(id(i,m-1),T,B-a[i][m-1]);
        rep(i,0,n) rep(j,0,m-1) it.link(id(i,j),id(i,j+1),B-a[i][j]);
        rep(i,0,K){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            --x;--y;
            rep(j,0,m) {
                int t=j-z;
                if(t>=0&&t<m)
                    it.link(id(x,j),id(y,t),inf);
                else if(t>=m)
                    it.link(id(x,j),T,inf);
            }
        }
        ll flow=it.run(S,T);
        if(flow>=inf) printf("%d\n",-1);
        else printf("%lld\n",B*n-flow);
    }
    return 0;
}
