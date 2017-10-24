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

typedef double T;
const db pi = acos(-1.) , eps = 1e-6;
int sgn(T x){return (x>eps)-(x<-eps);}
struct P{
    T x,y,z;P(){} P(T x,T y,T z):x(x),y(y),z(z){}
    P operator - (const P&b) const {return P(x-b.x,y-b.y,z-b.z);}
    P operator + (const P&b) const {return P(x+b.x,y+b.y,z+b.z);}
    T operator * (const P&b) const {return x*b.x+y*b.y+z*b.z;}
    P operator / (const P&b) const {return P(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
    P operator * (const T&k) const {return P(x*k,y*k,z*k);}
    P operator / (const T&k) const {return P(x/k,y/k,z/k);}
    bool operator < (const P&b) const {return tie(x,y,z)<tie(b.x,b.y,b.z);}
    bool operator == (const P&b) const {return sgn(x-b.x)==0&&sgn(y-b.y)==0&&sgn(z-b.z)==0;}
    void in(){scanf("%lf%lf%lf",&x,&y,&z);}
    void out(){ cout << "(" << x << "," << y << "," << z << ")" << endl; }
    T len(){return sqrt(*this**this);}
};
T norm(P x){return x*x;}
T abs(P x){return sqrt(norm(x));}
P outC(P A,P B,P C){
    T d = 2 * norm((A-B)/(B-C));
    if(sgn(d) == 0) {
        if((B-A).len()<(C-A).len()) swap(B,C);
        if((B-A).len()<(C-B).len()) swap(A,C);
        return (A+B)/2;
    }
    T a = (A-B)*(A-C)*norm(B-C);
    T b = (B-C)*(B-A)*norm(C-A);
    T c = (C-A)*(C-B)*norm(A-B);
    return (A*a+B*b+C*c)/d;
}
T Mincir(vector<P>&p){
    random_shuffle(all(p));
    int n = sz(p);
    P o = p[0];T r = 0;
    rep(i,1,n) {
        if(sgn(abs(o-p[i])-r) <= 0) continue;
        o = p[i] , r = 0;
        rep(j,0,i) {
            if(sgn(abs(o-p[j])-r) <= 0) continue;
            o = (p[i] + p[j]) / 2 , r = abs(o-p[j]);
            rep(k,0,j) {
                if(sgn(abs(o-p[k])-r) <= 0) continue;
                o = outC(p[i],p[j],p[k]) , r = abs(o-p[k]);
            }
        }
    }
    return r;
}
struct PL{
    P a,b,c;
    PL(){} PL(P a,P b,P c):a(a),b(b),c(c){}
    P pvec() {return (b-a)/(c-a);}
    T area() {return pvec().len();}
};
T operator - (P a,PL s) {return fabs((a-s.a)*s.pvec()/s.pvec().len());}
P operator + (P a,PL s) {P d=s.pvec();return a+d*((s.a-a)*d/(d*d));}
T mix(P a,P b,P c){return a / b * c;}
T area(P a,P b,P c){return ((b - a) / (c - a)).len();}
namespace Convex{
    typedef tuple<int,int,int> F;
    const int N = 1010;
    int mark[N][N] , n , cnt;
    vector<F> face;// (p[a]-p[b])/(p[c]-p[b]) inward ?
    void build(vector<P> p){
        sort(all(p));p.erase(unique(all(p)),p.end());
        n = sz(p);
        random_shuffle(all(p));
        face.clear();
        auto volume = [&](int a,int b,int c,int d)
        {return mix(p[b]-p[a],p[c]-p[a],p[d]-p[a]);};
        auto insert = [&](int a,int b,int c)
        {face.pb(make_tuple(a,b,c));};
        auto find = [&](){
            rep(i,2,n){
                P dir = (p[0] - p[i]) / (p[1] - p[i]);
                if(dir == P(0 , 0 , 0)) continue;
                swap(p[i] , p[2]);
                rep(j,i+1,n) if(sgn(volume(0,1,2,j))) {
                    swap(p[j],p[3]);
                    insert(0,1,2);
                    insert(0,2,1);
                    return 1;
                }
            }
            return 0;
        };
        auto add = [&](int d){
            vector<F> tmp;
            int a, b, c;
            cnt++;
            for(auto f : face){
                tie(a , b , c) = f;
                if (sgn(volume(d, a, b, c)) < 0)
                    mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b]
                        = mark[c][a] = mark[a][c] = cnt;
                else tmp.pb(f);
            }
            face = tmp;
            for(auto f : tmp){
                tie(a , b , c) = f;
                if (mark[a][b] == cnt) insert(b,a,d);
                if (mark[b][c] == cnt) insert(c,b,d);
                if (mark[c][a] == cnt) insert(a,c,d);
            }
        };
        if(find()){
            rep(i,0,n) memset(mark[i],0,sizeof(int)*n);
            cnt = 0;
            rep(i,3,n) add(i);
        }
        vector<P> q(n);
        T ans = 1e50;
        for(auto f : face) {
            int a,b,c;
            tie(a,b,c) = f;
            PL pl(p[a],p[b],p[c]);
            T h = 0;
            rep(i,0,n) h = max(h,p[i]-pl);
            rep(i,0,n) q[i] = p[i] + pl;
            T r = Mincir(q);
            ans = min(ans , r * r * pi * h);
        }
        printf("%.12f\n",ans);
    }
}


int main(){
    int n;scanf("%d",&n);
    vector<P> p(n);
    rep(i,0,n) p[i].in();
    Convex::build(p);
    return 0;
}
