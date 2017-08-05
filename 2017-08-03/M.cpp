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

const int N = 1e5 + 10 , K = 9 , SZ = 1<<K , B = 200;
int T,n,m,a[N],L;
int ne[N];
vi line[N];

struct Chain{
    int start,end,sz,col;
    void ini(int pos,int _col){
        start=end=pos;
        sz=1;
        col=_col;
        ne[pos]=~pos;
    }
    Chain operator += (const Chain& b){
        ne[end]=b.start;ne[b.end]=~start;
        end=b.end;sz+=b.sz;
        return *this;
    }
}chain[N];

int first[N];
struct Block{
    int cntA[B] , cntB[N] , from , to;
    void ini(int i){
        fill_n(cntA,L,0);fill_n(cntB,n,0);
        from=i<<K;to=min(n,(i+1)<<K);
    }
    void add(int i,int x){
        cntA[x>>K]++,cntB[x]++;
        chain[i].ini(i , x);
        if(cntB[x]>1) chain[first[x]]+=chain[i];
        else line[x].pb(i) , first[x]=i;
    }
    void rebuild(){
        rep(i,from,to) if(ne[i]<0){
            int col=chain[~ne[i]].col;
            for(int k=~ne[i];k>=0;k=ne[k])
                a[k]=col;
        }
    }
}block[B];

int difx[B],dify[B],X[N],Y[N];
int f[B],times,vis[B];
void inline modify(int b,int sz){
    difx[b]-=sz;dify[b]+=sz;
}
void change(int l,int r,int x,int y){
    if(x == y) return;
    rep(i,0,::L) difx[i]=dify[i]=0;
    ++times;
    static int A[::B],B[::B];
    int lenA=0,lenB=0;
    for(auto e : line[y]) vis[e>>K]=times,f[e>>K]=e;
    int L=l>>K,R=r>>K;

    auto load = [&](int *x,int len,int col){
        if(len){
            rep(i,0,len) chain[x[i]].ini(x[i],col);
            rep(i,1,len) chain[x[0]]+=chain[x[i]];
        }
    };

    auto split = [&](int e,int from,int to){
        int lenX=0,lenY=0;
        for(int i=e;i>=0;i=ne[i]) {
            if(from <= i && i < to) modify(e>>K , 1) , Y[lenY++]=i;
            else X[lenX++]=i;
        }
        load(X,lenX,x);
        if(lenX) A[lenA++]=X[0];
        load(Y,lenY,y);
        if(lenY) {
            int b=e>>K;
            if(vis[b] == times) chain[f[b]]+=chain[Y[0]];
            else B[lenB++]=Y[0];
        }
    };

    for(auto e : line[x]){
        int b = e>>K;
        if(b == L){
            int from = l , to = min(r + 1 , block[L].to);
            split(e , from , to);
        } else if(b == R){
            int from = block[R].from , to = r + 1;
            split(e , from , to);
        } else if(L < b && b < R){
            if(vis[b] == times) modify(b , chain[e].sz) , chain[f[b]]+=chain[e];
            else modify(b , chain[e].sz) , B[lenB++]=e , chain[e].col = y;
        } else A[lenA++]=e;
    }
    line[x]=vi(A,A+lenA);
    line[y].insert(line[y].end(),B,B+lenB);
    rep(i,1,::L) difx[i]+=difx[i-1],dify[i]+=dify[i-1];
    rep(i,0,::L) {
        block[i].cntA[x>>K]+=difx[i];
        block[i].cntA[y>>K]+=dify[i];
        block[i].cntB[x]+=difx[i];
        block[i].cntB[y]+=dify[i];
    }
}

int cntA[B],cntB[N],q[N];
inline void add(int x,int d){cntA[x>>K]+=d,cntB[x]+=d;}
int query(int l,int r,int kth){
    int L=l>>K,R=r>>K;
    block[L].rebuild();
    if(L!=R) block[R].rebuild();
    if(L+1>=R) {
        int _=0;
        rep(i,l,r+1) q[_++]=a[i];
        nth_element(q,q+kth-1,q+_);
        return q[kth-1];
    }
    rep(i,l,(L+1)<<K) add(a[i],1);
    rep(i,R<<K,r+1) add(a[i],1);
    int i=0,sum=0;
    for(;;i++) {
        sum=block[R-1].cntA[i]-block[L].cntA[i]+cntA[i];
        if(sum<kth) kth-=sum;
        else break;
    }
    for(i<<=K;;++i){
        sum=block[R-1].cntB[i]-block[L].cntB[i]+cntB[i];
        if(sum<kth) kth-=sum;
        else break;
    }
    rep(i,l,(L+1)<<K) add(a[i],-1);
    rep(i,R<<K,r+1) add(a[i],-1);
    return i;
}

void solve(){
    scanf("%d%d",&n,&m);
    L=(n>>K)+1;
    rep(i,0,L) block[i].ini(i);
    rep(i,0,n) line[i].clear();
    rep(i,0,n){
        scanf("%d",a + i);--a[i];
        block[i>>K].add(i , a[i]);
    }
    rep(i,1,L) rep(j,0,L) block[i].cntA[j]+=block[i-1].cntA[j];
    rep(i,1,L) rep(j,0,n) block[i].cntB[j]+=block[i-1].cntB[j];
    int op,l,r,x,y;
    rep(i,0,m){
        scanf("%d%d%d%d",&op,&l,&r,&x);--l,--r;
        if(op==1) scanf("%d",&y) , change(l,r,x-1,y-1);
        else printf("%d\n",query(l,r,x) + 1);
    }
}

int main(){
    scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
