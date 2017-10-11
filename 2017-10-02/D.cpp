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
typedef long double db;
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

const db inf = 1e20 , eps = 1e-8;
int sgn(db x){return (x>eps)-(x<-eps);}
int A,B,C,D,E;
vector<db> pts;

void add(int a,int b,int c,vector<db>&pts){
    if(a==0){
        if(b) pts.pb(1.*-c/b);
    } else {
        db delta=b*b-4*a*c;
        if(delta>=0) {
            pts.pb((-b+sqrtl(delta))/(2*a));
            pts.pb((-b-sqrtl(delta))/(2*a));
        }
    }
}
db F(db x){
    return A+(B*x+C)/(x*x+D*x+E);
}
db DOWN(db x){
    return x*x+D*x+E;
}
db UP(db x){
    return B*x+C;
}
struct Seg{
    db l,r;
    int lclose,rclose;
    Seg operator + (const Seg&b) const { // intersected
        Seg r=*this;
        if(sgn(b.l-r.l)<0||(sgn(b.l-r.l)==0&&(b.lclose>r.lclose)))
            r.l=b.l,r.lclose=b.lclose;
        if(sgn(b.r-r.r)>0||(sgn(b.r-r.r)==0&&(b.rclose>r.rclose)))
            r.r=b.r,r.rclose=b.rclose;
        return r;
    }
    bool operator < (const Seg&b) const {
        if(sgn(l-b.l)) return l<b.l;
        if(lclose!=b.lclose) return lclose;
        return false;
    }
    void out(){
        putchar(lclose?'[':'(');
        if(l==-inf) printf("-INF");
        else printf("%.4f",double(l));
        printf(", ");
        if(r==inf) printf("INF");
        else printf("%.4f",double(r));
        putchar(rclose?']':')');
    }
};

pair<db,int> getY(db x,db eps,db limit){
    if(x==limit) return mp(A,B==0&&C==0);
    else if(sgn(DOWN(x))==0){
        if(sgn(UP(x))==0) {
            if(B==0) return mp(A,1);
            else if(sgn(2*x+D)!=0) return mp(A+B/(2*x+D),0);
        }
        if(F(x+eps)>0) return mp(inf,0);
        return mp(-inf,0);
    } else return mp(F(x),1);
}
Seg getRange(db xl,db xr){
    pair<db,int> l=getY(xl,eps,-inf),r=getY(xr,-eps,inf);
    if(r<l) swap(l,r);
    return Seg{l.fi,r.fi,l.se,r.se};
}
int main(){
    int T;
    db x=9;
    scanf("%d",&T);
    rep(i,0,T){
        pts.clear();
        scanf("%d%d%d%d%d",&A,&B,&C,&D,&E);
        B-=A*D;
        C-=A*E;
        add(1,D,E,pts);
        add(-B,-2*C,B*E-C*D,pts);
        pts.pb(-inf);pts.pb(inf);
        sort(all(pts));
        pts.erase(unique(all(pts),[&](db a,db b){return fabs(a-b)<=eps;}),pts.end());
        //for(auto e : pts) printf("(%.12LF,%.12LF)\n",e,F(e));
        vector<Seg> vs;
        rep(i,0,sz(pts)-1) vs.pb(getRange(pts[i],pts[i+1]));
        sort(all(vs));
        vector<Seg> ans;
        for(int i=0,j=i;i<sz(vs);i=j){
            Seg s;
            for(j=i;j<sz(vs);++j){
                if(i==j) s = vs[i];
                else {
                    if(sgn(vs[j].l-s.r)>0) break;
                    if(sgn(vs[j].l-s.r)==0&&s.rclose==0&&vs[j].lclose==0) break;
                    s = s + vs[j];
                }
            }
            ans.pb(s);
        }
        rep(i,0,sz(ans)){
            if(i) printf(" U ");
            ans[i].out();
        }
        puts("");
    }
    return 0;
}
