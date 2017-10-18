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
int n;
db up[N] , down[N] , edgeup[N] , ed[N];
int du[N];
vi g[N];

void dfsup(int c,int fa){
    for(auto t : g[c]) if(t!=fa&&du[t]>=0){
        dfsup(t,c);
        int du=sz(g[t]);
        edgeup[t]=0;
        if(du>1) edgeup[t]+=up[t]/(du-1);
        edgeup[t]+=1./n/du;
        up[c]+=edgeup[t];
    }
}

void dfsdown(int c,int fa){
    for(auto t : g[c]) if(t!=fa&&du[t]>=0){
        if(du[c]==-1) down[t]+=ed[c]/(sz(g[c])-2);
        down[t]+=(down[c]+up[c]-edgeup[t])/(sz(g[c])-1);
        down[t]+=1./n/sz(g[c]);
        dfsdown(t,c);
    }
}

void bf(){
    int times=100000;
    int vis[100],cnt[100];
    rep(i,0,n) cnt[i]=0;
    rep(i,0,times){
        int s=rand()%n;
        rep(i,0,n) vis[i]=false;
        while(!vis[s]){
            vis[s]=1;
            vi go;
            for(auto e:g[s]) if(!vis[e]) go.pb(e);
            if(sz(go)==0) break;
            s=go[rand()%sz(go)];
        }
        cnt[s]++;
    }
    rep(i,0,n) printf("%f ",1.*cnt[i]/times);
    puts("");
}

int main(){
    while(~scanf("%d",&n)){
        if(n==0) break;
        rep(i,0,n) g[i].clear(),up[i]=down[i]=du[i]=edgeup[i]=ed[i]=0;
        rep(i,0,n){
            int u,v;
            scanf("%d%d",&u,&v);
            --u;--v;
            g[u].pb(v);
            g[v].pb(u);
            du[u]++;du[v]++;
        }
        //bf();
        vi tree , circle;
        rep(i,0,n) if(du[i]==1) tree.pb(i);
        rep(i,0,sz(tree)) for(auto e : g[tree[i]])
            if(--du[e]==1) tree.pb(e);
        int s=0;while(du[s]!=2) ++s;
        for(int c=s;;){
            circle.pb(c);du[c]=-1;
            int u=-1;for(auto t:g[c]) if(du[t]==2) {u=t;break;}
            if(u==-1) break;
            c=u;
        }
        for(auto e : circle) dfsup(e,-1);
        rep(i,0,sz(circle)){
            int s=circle[i];
            db pro=up[s]/(sz(g[s])-1)+1./n/(sz(g[s]));
            rep(j,1,sz(circle)){
                int c=circle[(i+j)%sz(circle)];
                if(j+1==sz(circle)) ed[c]+=pro;
                else down[c]+=pro;
                pro/=(sz(g[c]))-1;
            }
            pro=up[s]/(sz(g[s])-1)+1./n/(sz(g[s]));
            rep(j,1,sz(circle)){
                int c=circle[(i-j+sz(circle))%sz(circle)];
                if(j+1==sz(circle)) ed[c]+=pro;
                else down[c]+=pro;
                pro/=(sz(g[c]))-1;
            }
        }
        for(auto e : circle) dfsdown(e,-1);
        db all = 0;
        vector<db> f;
        rep(i,0,n) if(du[i]>=0&&sz(g[i])==1) f.pb(down[i]);
        rep(i,0,n) if(du[i]==-1&&sz(g[i])==2) f.pb(ed[i]);
        sort(all(f));reverse(all(f));
        db ans=0.;
        rep(i,0,min(sz(f),5)) ans+=f[i];
        printf("%.5f\n",ans+1e-8);
    }
    return 0;
}
