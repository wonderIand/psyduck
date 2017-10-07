#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
typedef long double T;
const T eps = 1e-8 , inf = 1e50;
int sgn(T x){return (x > eps) - (x < -eps);}
struct P{
    T x,y,z;
    P(){} P(T x,T y,T z):x(x),y(y),z(z){}
    P operator - (const P&b) const {return P(x-b.x,y-b.y,z-b.z);}
    P operator + (const P&b) const {return P(x+b.x,y+b.y,z+b.z);}
    P operator / (const P&b) const {return P(y*b.z-z*b.y , z*b.x-x*b.z , x*b.y-y*b.x);}
    P operator * (const T&k) const {return P(x*k,y*k,z*k);}
    T operator * (const P&b) const {return x*b.x+y*b.y+z*b.z;}
    bool operator < (const P&b) const {
        if(sgn(x - b.x)) return x < b.x;
        if(sgn(y - b.y)) return y < b.y;
        return z < b.z;
    }
    bool operator == (const P&b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
    }
    void read(){double a,b,c;scanf("%lf%lf%lf",&a,&b,&c);x=a,y=b,z=c;}
    void out(){printf("(%lf,%lf,%lf)\n",(double)x,(double)y,(double)z);}
}s,t,dir;
bool onS(P p,P a,P b){
    return sgn(((p - a) / (b - a)).z) == 0 && sgn((p - a) * (p - b)) <= 0;
}
T dis(P s,P t){
    return sqrt((t - s) * (t - s));
}
bool isSSr(P a1,P a2,P b1,P b2){
    T c1 = ((a2 - a1) / (b1 - a1)).z , c2 = ((a2 - a1) / (b2 - a1)).z;
    T c3 = ((b2 - b1) / (a1 - b1)).z , c4 = ((b2 - b1) / (a2 - b1)).z;
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
P insLL(P p,P v,P q,P w){
    P u = p - q;
    v = v - p;
    w = w - q;
    T t = (w / u).z / (v / w).z;
    return p + v * t;
}
int Pinploy(P o,vector<P>&p){
    int n = sz(p);
    int res=0;
    rep(i,0,n) {
        P u = p[i] , v = p[(i+1)%n];
        if(onS(o , u , v)) return -1;
        int k = sgn(((v - u) / (o - u)).z) , d1 = sgn(u.y - o.y) , d2 = sgn(v.y - o.y);
        if(k > 0 && d1 <= 0 && d2 > 0) ++res;
        if(k < 0 && d2 <= 0 && d1 > 0) --res;
    }
    return res != 0;
}

struct L{
    P a,b;
    L(){} L(P a,P b):a(a),b(b){}
};
struct PL{
    P a,b,c;
    PL(){} PL(P a,P b,P c):a(a),b(b),c(c){}
    void read() {a.read();b.read();c.read();}
};
P pvec(PL s){
    return (s.a - s.b) / (s.b - s.c);
}
int n;

P intersection(L l,PL s){
    P u = pvec(s);
    T t = (u * (s.a - l.a)) / (u * (l.b - l.a));
    return l.a + (l.b - l.a) * t;
}
P intersection(L u,L v){
    T t = 0;
    P a = (u.a - v.a) / (v.a - v.b);
    P b = (u.a - u.b) / (v.a - v.b);
    if(fabs(b.x) > fabs(b.y) && fabs(b.x) > fabs(b.z))
        t = a.x / b.x;
    else if(fabs(b.y) > fabs(b.z))
        t = a.y / b.y;
    else t = a.z / b.z;
    return u.a + (u.b - u.a) * t;
}

void Update(P&Max,P&Min,P u){
    if(Max < u) Max = u;
    if(u < Min) Min = u;
}
bool inter(P a,P b,P c,P d){
    P u = ((c - b) / (a - b)) , v = ((d - b) / (a - b));
    /*	u.x = sgn(u.x); u.y = sgn(u.y); u.z = sgn(u.z);
        v.x = sgn(v.x); v.y = sgn(v.y); v.z = sgn(v.z);
        */
    return sgn(u * v) <= 0;
}
bool dots_onplane(P a,PL pl){
    return sgn(pvec(pl) * (a - pl.a)) == 0;
}

T solve(PL pl,P s,P t,P dir){
    P u = pvec(pl);
    if(sgn(dir * u) == 0) {
        if(!dots_onplane(s , pl) || !dots_onplane(t , pl)) return 0.;
        if((t - s) / dir == P(0,0,0)){
            if(inter(s , s + dir , pl.a , pl.b)) return 1.;
            if(inter(s , s + dir , pl.b , pl.c)) return 1.;
            if(inter(s , s + dir , pl.c , pl.a)) return 1.;
            return 0.;
        } else {
            P Max = P(-inf,-inf,-inf);
            P Min = P(inf,inf,inf);
            if(t < s) swap(s , t);
            Update(Max , Min , intersection(L(pl.a , pl.a + dir) , L(s , t)));
            Update(Max , Min , intersection(L(pl.b , pl.b + dir) , L(s , t)));
            Update(Max , Min , intersection(L(pl.c , pl.c + dir) , L(s , t)));
            if(Min < s) Min = s;
            if(t < Max) Max = t;
            if(Min < Max) return dis(Min , Max) / dis(s , t);
            else return 0.;
        }
    }
    vector<P> q , tri;
    tri.pb(pl.a);tri.pb(pl.b);tri.pb(pl.c);
    P ps = intersection(L(s , s + dir) , pl);
    P pt = intersection(L(t , t + dir) , pl);
    q.pb(ps); q.pb(pt);
    T dx = fabs(u.x) , dy = fabs(u.y) , dz = fabs(u.z);
    //	T cof = sqrt(dx * dx + dy * dy + dz * dz);
    if(dx > dy && dx > dz) {
        rep(i,0,sz(q)) swap(q[i].x , q[i].z) , q[i].z = 0;
        rep(i,0,sz(tri)) swap(tri[i].x , tri[i].z) , tri[i].z = 0;
        //		cof /= dx;
    } else if(dy > dz) {
        rep(i,0,sz(q)) swap(q[i].y , q[i].z) , q[i].z = 0;
        rep(i,0,sz(tri)) swap(tri[i].y , tri[i].z) , tri[i].z = 0;
        //		cof /= dy;
    } else {
        rep(i,0,sz(q)) q[i].z = 0;
        rep(i,0,sz(tri)) tri[i].z = 0;
        //		cof /= dz;
    }
    if((t - s) / dir == P(0,0,0)){
        if(Pinploy(q[0] , tri)) return 1.;
        else return 0.;
    }
    vector<P> p;
    for(auto e : q) p.pb(e);
    for(auto e : tri) if(onS(e , q[0] , q[1])) p.pb(e);
    for(auto e : q) rep(j,0,3){
        if(isSSr(q[0] , q[1] , tri[j] , tri[(j+1)%3]))
            p.pb(insLL(q[0] , q[1] , tri[j] , tri[(j+1)%3]));
    }
    sort(all(p));
    p.erase(unique(all(p)) , p.end());
    T in = 0.;
    //for(auto e : p) e.out();
    rep(i,0,sz(p)-1){
        P mid = (p[i] + p[i+1]) * 0.5;
        if(Pinploy(mid , tri)) {
            in += dis(p[i] , p[i + 1]);
        }
    }
    return in / dis(q[0] , q[1]);
}


int main() {
    while(~scanf("%d",&n)){
        s.read();t.read();dir.read();
        T ans = 0.;
        rep(i,0,n){
            PL pl;
            pl.read();
            ans += solve(pl , s , t , dir);
        }
        printf("%.8f\n",(double)ans);
    }
    return 0;
}
