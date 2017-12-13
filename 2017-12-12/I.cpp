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

const int N = 2e5 + 10 , inf = 1e9 , C = 31 , NODE = N * C;
int n;
inline int col_id(char ch){
    return ch == 'r' ? 0 : (ch == 'a' ? 1 : 2);
}
struct Event{
    int y , l , r , op , id;
    bool operator < (const Event&b) const {
        return mp(y , op) < mp(b.y , b.op);
    }
};
vector<Event> events;
set<pair<pii,int> > segs;
vi g[N];
int par[N] , col[N] , light[N];
int cnt[NODE] , vis[NODE] , ne[NODE][3] , rt , _;

int main(){
    scanf("%d",&n);
    rep(i,1,n+1) {
        int x , y , r;
        char op[2];
        scanf("%d%d%d%s",&x,&y,&r,op);
        col[i] = col_id(op[0]);
        events.pb(Event{y - 2 * r , x - 2 * r , x + 2 * r , 1 , i});
        events.pb(Event{y + 2 * r , x - 2 * r , x + 2 * r ,-1 , i});
    }
    sort(all(events));
    segs.insert(mp(mp(-inf,inf),0));
    for(auto&e : events) {
        auto x = mp(mp(e.l,e.r),e.id);
        if(e.op == 1) {
            auto it = segs.upper_bound(mp(mp(e.l,inf),e.id));
            --it;
            g[it->se].pb(e.id);
            par[e.id] = it->se;
            int l = it->fi.fi , r = it->fi.se , id = it->se;
            segs.erase(it);
            segs.insert(x);
            if(l != e.l) segs.insert(mp(mp(l,e.l),id));
            if(r != e.r) segs.insert(mp(mp(e.r,r),id));
        } else {
            segs.erase(x);
            auto R = segs.upper_bound(x);
            int l = e.l , r = e.r , id = par[e.id];
            if(R->se == id) {
                r = R->fi.se;
                segs.erase(R);
            }
            auto L = segs.upper_bound(x);
            --L;
            if(L->se == id) {
                l = L->fi.fi;
                segs.erase(L);
            }
            segs.insert(mp(mp(l,r),id));
        }
    }
    rt = ++_;
    int m;scanf("%d",&m);
    rep(times,1,m+1) {
        static char s[N];
        static int num[N];
        scanf("%s",s);
        int n = strlen(s);
        rep(i,0,n) num[i] = col_id(s[i]);
        rep(i,0,n) {
            int c = rt;
            rep(j,0,C) {
                if(i + j >= n) break;
                int t = num[i + j];
                if(!ne[c][t]) ne[c][t] = ++_;
                c = ne[c][t];
                if(vis[c] != times)
                    vis[c] = times , cnt[c]++;
            }
        }
    }
    int Q;scanf("%d",&Q);
    rep(i,1,n+1) light[i] = true;
    rep(i,0,Q){
        char op[2];
        int x;
        scanf("%s%d",op,&x);
        if(op[0] == '+') light[x] = true;
        else if(op[0] == '-') light[x] = false;
        else {
            vi route;
            for(int c=x;c;c=par[c]) if(light[c])
                route.pb(col[c]);
            reverse(all(route));
            int c = rt;
            for(auto e : route) c = ne[c][e];
            printf("%d\n",cnt[c]);
        }
    }
    return 0;
}
