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

const int N = 3030 , M = 201;
struct P{
    int x,y;
    P(){} P(int x,int y):x(x),y(y){}
    int operator ^ (const P&b) const {return x*b.y-y*b.x;}
    void read() {scanf("%d%d",&x,&y);}
    void show() {cout<<"(" << x << "," << y << ")";}
    bool operator < (const P&b) const{
        return mp(x,y) < mp(b.x,b.y);
    }
}p[N];
int Gcd[M][M] , rk[M+M][M+M];
vector<P> dir;
vector<vector<pii> > seg;
int pos[N] , id[N] , center[N * N] , rcenter[N * N];

int main(){
    dir.pb(P(0,1));
    dir.pb(P(-1,0));
    rep(i,1,M){
        Gcd[i][0] = Gcd[0][i] = i;
        rep(j,1,M) {
            int d = Gcd[i][j] = __gcd(i , j);
            if(d == 1){
                dir.pb(P(-i , j));
                dir.pb(P(-i , -j));
            }
        }
    }
    sort(all(dir),[&](P a,P b){return (a^b)>0;});
    rep(i,0,sz(dir)) rk[dir[i].x + M][dir[i].y + M] = i;
    int Tcnt = 0;scanf("%d",&Tcnt);
    rep(i,0,Tcnt){
        int n;scanf("%d",&n);
        rep(i,0,n) p[i].read();
        sort(p,p+n);
        seg = vector<vector<pii> >(sz(dir),vector<pii>(0,mp(0,0)));
        rep(i,0,n) rep(j,i+1,n) if(p[i].x != p[j].x){
            int dx = p[i].x - p[j].x , dy = p[i].y - p[j].y;
            int d = Gcd[-dx][abs(dy)];
            dx /= d , dy /= d;
            seg[rk[dx + M][dy + M]].pb(mp(i , j));
        }
        int leftcnt = 0;
        rep(i,0,n) pos[i] = i , id[i] = i , leftcnt += p[i] < P(0,0);
        int tota = 0 , totb = 0;
        center[tota++] = id[leftcnt];
        rcenter[totb++] = id[n - 1 - leftcnt];
        rep(i,1,sz(dir)){
            for(auto e : seg[i]){
                int a = e.fi , b = e.se;
                id[pos[a]] = b , id[pos[b]] = a , swap(pos[a] , pos[b]);
            }
            if(id[leftcnt] != center[tota-1])
                center[tota++] = id[leftcnt];
            if(id[n - 1 - leftcnt] != rcenter[totb - 1])
                rcenter[totb++] = id[n - 1 - leftcnt];
        }
        rep(i,0,totb) if(rcenter[i] != center[tota-1]) center[tota++] = rcenter[i];
        while(tota > 1 && center[tota-1] == center[0]) --tota;
        int Q;scanf("%d",&Q);
        rep(i,0,Q){
            int x;scanf("%d",&x);
            x = center[x % tota];
            printf("%d %d\n",p[x].x , p[x].y);
        }
    }
    return 0;
}
