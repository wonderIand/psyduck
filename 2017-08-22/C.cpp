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

const int N = 1e4 + 10;
const db eps = 1e-13 , pi = acos(-1.);
int sgn(db x){return (x>eps)-(x<-eps);}
typedef db T;
struct P{
    T x,y;
    void read(){scanf("%lf%lf",&x,&y);}
    P(){} P(T x,T y):x(x),y(y){}
    T operator ^ (const P&b) const {return x*b.y-y*b.x;}
    P operator - (const P&b) {return P(x-b.x,y-b.y);}
    P operator + (const P&b) {return P(x+b.x,y+b.y);}
    P operator * (const T&k) {return P(x*k,y*k);}
    void show(){ printf("%f %f\n",x,y); }
    db arg() const {return atan2(y,x);}
};
T abs(P a) {return sqrt(a.x*a.x+a.y*a.y);}
bool order(const P&a,const P&b){
    return a.arg() < b.arg();
}
P dir;
struct L{
    P s,t;
    L(){} L(P s,P t):s(s),t(t){}
    void read(){s.read();t.read();}
};
P insLL(L a,L b){
    P s = a.s - b.s , v = a.t - a.s , w = b.t - b.s;
    db k1 = s ^ w , k2 = w ^ v;
    if(sgn(k2) == 0) return abs(b.s - a.s) < abs(b.t - a.s) ? b.s : b.t;
    return a.s + v * (k1 / k2);
}
bool operator < (const L&a,const L&b){
    L line(P(0,0),dir);
    return abs(insLL(line,a)) < abs(insLL(line,b));
}
struct Event{
    P p;db k;
    int type,id;
    Event(){}
    Event(P p,int type,int id):p(p),type(type),id(id){k=p.arg();}
    bool operator < (const Event&b) const{
        if(sgn(k-b.k) == 0) return type < b.type;
        return k < b.k;
    }
};
int n,m,Q;
P people[N],Ppeople[N];
L wall[N],Pwall[N];
Event event[N * 3];

set<L> walls;

int solve(int id){
    int tot=0;
    rep(i,0,n) event[tot++] = Event(people[i]=Ppeople[i]-Ppeople[id],1,i);
    walls.clear();
    rep(i,0,m){
        P &s=wall[i].s=Pwall[i].s-Ppeople[id],&t=wall[i].t=Pwall[i].t-Ppeople[id];
        if(order(t,s)) swap(s,t);
        if(sgn(t.arg() - s.arg() - pi) > 0) swap(s,t),walls.insert(L(s,t));
        event[tot++] = Event(s,0,i);
        event[tot++] = Event(t,2,i);
    }
    sort(event,event+tot);
    int ans=0;
    rep(i,0,tot){
        auto&e = event[i];
        dir=e.p;
        if(e.type == 0) walls.insert(wall[e.id]);
        else if(e.type == 2) walls.erase(wall[e.id]);
        else if(!sz(walls) || sgn(abs(insLL(*walls.begin(),L(P(0,0),dir))) - abs(people[e.id])) > 0)
            ++ans;
    }
    return ans;
}

int main(){
    while(~scanf("%d%d%d",&n,&m,&Q)){
        static int _ = 0;
        printf("Case #%d:\n",++_);
        rep(i,0,n) Ppeople[i].read();
        rep(i,0,m) Pwall[i].read();
        rep(i,0,Q) {
            Ppeople[n].read();
            printf("%d\n",solve(n));
        }
    }
    return 0;
}
