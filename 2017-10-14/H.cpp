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

typedef vi P;
typedef vector<P> B;
P inv(P p){
    P r=p;
    rep(i,0,sz(p)) r[p[i]]=i;
    return r;
}
P operator * (const P&a,const P&b){
    P r=a;
    rep(i,0,sz(a)) r[i]=b[a[i]];
    return r;
}
int n , m;
vector<B> buckets , bucketsInv;
vector<vi> lookupTable;
int fastFilter(const P&g,bool addToGroup = true){
    int n = sz(buckets);
    P p = g;
    rep(i,0,n) {
        int res=lookupTable[i][p[i]];
        if(res == -1){
            if(addToGroup) {
                buckets[i].push_back(p);bucketsInv[i].pb(inv(p));
                lookupTable[i][p[i]] = sz(buckets[i]) - 1;
            }
            return i;
        }
        p = p * bucketsInv[i][res];
    }
    return -1;
}
ll cal(){
    ll res=1;
    rep(i,0,n) res*=sz(buckets[i]);
    return res;
}
bool inGroup(const P&g) {return fastFilter(g , false) == -1;}
void solve(const B&gen,int _n) {
    n = _n , m = sz(gen);
    bucketsInv=buckets=vector<B>(n);
    lookupTable=vector<vi>(n);
    P id(n);
    rep(i,0,n){
        lookupTable[i].resize(n);
        fill(all(lookupTable[i]),-1);
    }
    rep(i,0,n) id[i]=i;
    rep(i,0,n){
        buckets[i].pb(id);bucketsInv[i].pb(id);
        lookupTable[i][i]=0;
    }
    rep(i,0,m) fastFilter(gen[i]);
    queue<pair<pii,pii> > toUpdate;
    rep(i,0,n) rep(j,i,n) rep(k,0,sz(buckets[i])) rep(l,0,sz(buckets[j]))
        toUpdate.push(mp(mp(i,k),mp(j,l)));
    while(sz(toUpdate)){
        pii a=toUpdate.front().fi , b=toUpdate.front().se;
        toUpdate.pop();
        int res=fastFilter(buckets[a.fi][a.se]*buckets[b.fi][b.se]);
        if(res==-1) continue;
        pii np(res,sz(buckets[res])-1);
        rep(i,0,n) rep(j,0,sz(buckets[i])){
            if(i<=res) toUpdate.push(mp(mp(i,j),np));
            if(res<=i) toUpdate.push(mp(np,mp(i,j)));
        }
    }
}

int a[100];
int main(){
    int n , R;
    scanf("%d%d",&n,&R);
    B buckets;
    rep(i,0,n){
        rep(j,0,R) scanf("%d",a + j) , a[j]--;
        buckets.pb(vi(a,a+R));
    }
    solve(buckets,R);
    printf("%lld\n",cal());
    return 0;
}

