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

const int N = 202;
const ll linf = 1ll << 62;
int n , m;
int x[N] , y[N];
map<ll,ll> gap;

bool cell_in(int X,int Y){
    int cnt = 0;
    rep(i,0,m)
        cnt += x[i] == x[i+1] && x[i] <= X &&
            min(y[i],y[i+1]) <= Y && Y < max(y[i],y[i+1]);
    return cnt & 1;
}

struct Rec{
    int lx,rx,ly,ry;
    Rec up(){return Rec{lx,rx,(ly>>1)+(ry>>1),ry};}
    Rec down(){return Rec{lx,rx,ly,(ly>>1)+(ry>>1)};}
    Rec left(){return Rec{lx,(lx>>1)+(rx>>1),ly,ry};}
    Rec right(){return Rec{(lx>>1)+(rx>>1),rx,ly,ry};}
    bool contain(int x,int y){return lx<x&&x<rx&&ly<y&&y<ry;}
    bool interX(int x,int yl,int yr){
        if(x<=lx||x>=rx) return false;
        if(yl>yr) swap(yl,yr);
        return max(ly,yl) < min(ry,yr);
    }
    bool interY(int y,int xl,int xr){
        if(y<=ly||y>=ry) return false;
        if(xl>xr) swap(xl,xr);
        return max(lx,xl) < min(rx,xr);
    }
    void out(){cout << "(" << lx << " " << ly << ") -> (" << rx << " " << ry <<  ")" << endl;}
};
int check(Rec rec){
    rep(i,0,m) if(rec.contain(x[i],y[i])) return 0;
    rep(i,0,m){
        if(x[i] == x[i+1] && rec.interX(x[i],y[i],y[i+1])) return 1;
        if(y[i] == y[i+1] && rec.interY(y[i],x[i],x[i+1])) return 2;
    }
    if(cell_in(rec.lx,rec.ly)) return 3;
    return 4;
}

void solve(int dep,Rec rec,ll mul,ll&left,ll&right){
    left = linf , right = -1;
    if(dep == 0){
        if(cell_in(rec.lx,rec.ly)) left = right = 0;
        return ;
    }
    int type = check(rec);
    if(type == 3) left = 0 , right = (1ll << dep) - 1;
    if(type >= 3) return;
    ll l[2] , r[2];
    if(dep & 1) {
        if(type == 1) {
            solve(dep - 1 , rec.down() , mul*2 , l[0] , r[0]);
            l[1] = l[0] , r[1] = r[0];
        } else {
            solve(dep - 1 , rec.down() , mul , l[0] , r[0]);
            solve(dep - 1 , rec.up() , mul , l[1] , r[1]);
        }
    } else {
        if(type == 2) {
            solve(dep - 1 , rec.left() , mul*2 , l[0] , r[0]);
            l[1] = l[0] , r[1] = r[0];
        } else {
            solve(dep - 1 , rec.left() , mul , l[0] , r[0]);
            solve(dep - 1 , rec.right() , mul , l[1] , r[1]);
        }
    }
    if(l[1] != linf) l[1] += (1ll<<(dep-1)) , r[1] += (1ll<<(dep-1));
    if(l[0] != linf && l[1] != linf && l[1] - r[0] > 1)
        gap[l[1] - r[0] - 1] += mul;
    left = min(l[0] , l[1]);
    right = max(r[0] , r[1]);
    //rec.out();
    //cout << left << " " << right << " " << type << " " << dep << endl;
}

int main(){
    cin >> n >> m;
    rep(i,0,m) cin >> x[i] >> y[i];
    x[m] = x[0] , y[m] = y[0];
    ll left = 0 , right = 0;
    solve(2 * n , Rec{0,1<<n,0,1<<n} , 1 , left , right);
    ll tot = right - left + 1;
    vector<ll> size , cnt;
    for(auto e : gap) size.pb(e.fi) , cnt.pb(e.se);
    reverse(all(size));reverse(all(cnt));
    size.insert(size.begin() , 0);
    cnt.insert(cnt.begin() , 0);
    vector<ll> sumcnt = cnt , sum = cnt;
    rep(i,1,sz(sumcnt)) sumcnt[i] += sumcnt[i - 1];
    rep(i,1,sz(sum)) sum[i] = sum[i-1] + size[i] * cnt[i];
    int Q;cin >> Q;
    rep(i,0,Q) {
        int k;
        cin >> k;
        --k;
        ll ans = tot;
        if(k >= sumcnt.back()) ans -= sum.back();
        else {
            auto j = upper_bound(all(sumcnt) , k) - sumcnt.begin();
            ans -= sum[j - 1];
            ans -= (k - sumcnt[j - 1]) * size[j];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
