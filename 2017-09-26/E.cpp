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

const db eps = 1e-10 , inf = 1e50;
typedef double T;
int sgn(T x){return (x > eps) - (x < -eps);}
struct P{
    T x,y;
    P(){} P(T x,T y):x(x),y(y){}
    P operator - (const P&b) const {return P(x-b.x,y-b.y);}
    P operator + (const P&b) const {return P(x+b.x,y+b.y);}
    P operator * (const T&k) const {return P(x*k,y*k);}
    P operator / (const T&k) const {return P(x/k,y/k);}
    T operator * (const P&b) const {return x*b.x+y*b.y;}
    T operator / (const P&b) const {return x*b.y-y*b.x;}
    bool operator < (const P&b) const {return sgn(x-b.x)?x<b.x:y<b.y;}
    bool operator ==(const P&b) const {return sgn(x-b.x)==0&&sgn(y-b.y)==0;}
    P rot90() {return P(-y,x);}
    void out() {printf("%.16f %.16f\n",(double)x,(double)y);}
};
T norm(P a){return a*a;}
T abs(P a){return sqrt(norm(a));}
P normalize(P a){return a/abs(a);}
P proj(P p,P a,P b){return (b-a)*((p-a)*(b-a)/norm(b-a))+a;}
db disPL(P p,P a,P b){return fabs((b-a)/(p-a)) / abs(b-a);}
struct C{
    P o;T r;
    C(){} C(P o,T r):o(o),r(r){}
};

vector<P> tanCP(C c,P p){
    db x = norm(p - c.o) , d = x - c.r * c.r;
    vector<P> res;
    if(sgn(d) < 0) return res;
    d = max(d,0.);
    P mid = c.o + (p - c.o) * (c.r * c.r / x) ,
      del = ((p-c.o)*(c.r*sqrt(d)/x)).rot90();
    return {mid - del ,mid + del};
}
vector<pair<P,P> > intanCC(C c1,C c2){
    vector<pair<P,P> > res;
    P p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
    vector<P> ps = tanCP(c1 , p) , qs = tanCP(c2 , p);
    rep(i,0,min(sz(ps),sz(qs))) res.pb({ps[i],qs[i]});
    return res;
}
const int N = 55;
int n;
P p[N];
C c[N];

vector<P> check(db r){
    rep(i,0,n) c[i] = C(p[i] , r);
    rep(i,0,n) rep(j,i+1,n) {
        vector<pair<P,P> > lines = intanCC(c[i] , c[j]);
        P mid = (p[i]+p[j]) / 2 , dir = (p[i]-p[j]).rot90();
        lines.pb({mid + dir , mid - dir});
        for(auto e : lines) {
            P A = e.fi , B = e.se;
            if(A == B) continue;
            P left(inf,inf) , right(-inf,-inf);
            rep(k,0,n) if(sgn(disPL(p[k],A,B)-r)>0) {
                P c = proj(p[k],A,B);
                if(c < left) left = c;
                if(right < c) right = c;
            }
            if(left.x == inf || sgn(abs(left-right)-r*2)<=0) {
                P o = left.x == inf ? A : (left + right) / 2;
                P dir = normalize(B-A)*r;
                dir = dir + dir.rot90();
                vector<P> res;
                rep(i,0,4) res.pb(o+dir),dir=dir.rot90();
                return res;
            }
        }
    }
    return vector<P>();
}

int main(){
    cin >> n;
    rep(i,0,n) cin >> p[i].x >> p[i].y;
    int times = 100;
    db l = 0.5 , r = 1e5 + 10;
    rep(i,0,times){
        db mid = (l + r) / 2;
        if(sz(check(mid))) r = mid;
        else l = mid;
    }
    vector<P> ans = check(r);
    for(auto e : ans) e.out();
    return 0;
}
