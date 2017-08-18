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
Dinic<int> it;
const int inf = 1<<30;
const int N = 505;
int n,W,p,q;
int weight[N];

int main(){
    int T;scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d%d%d",&n,&W,&p,&q);
        rep(i,0,n) weight[i]=1;
        int S=n,T=S+1;
        it.ini(T+1);
        auto link = [&](int x,int y,int a,int b){
            it.link(x,y,2*a);
            it.link(y,x,2*a);
            weight[x]+=b;
            weight[y]-=b;
        };
        rep(i,0,p){
            int x,y,z,a,b,c,d,e,f;
            scanf("%d%d%d%d%d%d%d%d%d",&x,&y,&z,&a,&b,&c,&d,&e,&f);
            --x;--y;--z;
            link(x,y,a,d);
            link(y,z,b,e);
            link(z,x,c,f);
        }
        ll ans=0;
        rep(i,0,n){
            int nw=weight[i];
            int nd=abs(nw);
            ans-=nd;
            it.link(S,i,nw+nd);
            it.link(i,T,-nw+nd);
        }
        rep(i,0,q){
            int x,y,r;
            scanf("%d%d%d",&x,&y,&r);
            --x;--y;
            if(r==0) it.link(y,x,inf);
            if(r==1) it.link(x,y,inf),it.link(y,x,inf);
            if(r==2) it.link(S,x,inf),it.link(y,T,inf);
        }
        ans+=it.run(S,T);
        printf("%lld\n",1ll*W*ans);
    }
    return 0;
}
