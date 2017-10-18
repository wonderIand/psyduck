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

typedef __int128 T;
const int N = 1e4 + 10 , NODE = N * 20;
const T eps = 0 , inf = 1e8;
int sgn(T x){return (x>eps)-(x<-eps);}
struct P{
    T x,y;int id;P(){} P(T x,T y,int id=0):x(x),y(y),id(id){}
    P operator - (const P&b) const {return P(x-b.x,y-b.y);}
    T operator * (const P&b) const {return x*b.x+y*b.y;}
    T operator / (const P&b) const {return x*b.y-y*b.x;}
    void out() {cout << "(" << (int)x <<"," << (int)y << ")" << endl;}
};
T norm(P a){return a*a;}
T cross(P a,P b,P p){return (b-a)/(p-a);}
bool inCir(P a,P b,P c,P p){
    T A = (b - p) / (c - p) * (norm(a) - norm(p));
    T B = (c - p) / (a - p) * (norm(b) - norm(p));
    T C = (a - p) / (b - p) * (norm(c) - norm(p));
    return sgn(A + B + C) > 0;
}

struct Tri;
struct Edge{
    Tri* tri;int side;
    Edge(Tri* tri=NULL,int side=0):tri(tri),side(side){}
};
struct Tri{
    P p[3];Edge edge[3];Tri*son[3];Tri(){}
    Tri(P p0,P p1,P p2){p[0]=p0,p[1]=p1,p[2]=p2;rep(i,0,3) son[i]=NULL;}
    bool has_son() const {return son[0];}
    bool contains(P q) const {
        rep(i,0,3) if(sgn(cross(p[i],p[(i+1)%3],q))<0) return false;
        return true;
    }
}tri_pool[NODE],*pt;
void set_edge(Edge a,Edge b){
    if(a.tri) a.tri->edge[a.side]=b;
    if(b.tri) b.tri->edge[b.side]=a;
}
Tri* root;
//Tri* find(P p){
    //Tri*c=root;
    //while(c->has_son()) rep(i,0,3)
        //if(c->son[i]->contains(p))
        //{c=c->son[i];break;}
    //return c;
//}
bool out(T x){return x==inf||x==-inf;}
bool out(Tri*c){
    rep(i,0,3) if(out(c->p[i].x) || out(c->p[i].y))
        return true;
    return false;
}
Tri* find(P p,bool force=true){
    queue<Tri*> Q;Q.push(root);
    while(sz(Q)){
        Tri*c=Q.front();Q.pop();
        if(!c->has_son()){
            if(force) return c;
            if(out(c)) continue;
            return c;
        }
        for(int i=0;i<3&&c->son[i];++i)
            if(c->son[i]->contains(p))
                Q.push(c->son[i]);
    }
    return NULL;
}
void flip(Tri*x,int px){
    Tri* y=x->edge[px].tri;int py=x->edge[px].side;
    if(!y||!inCir(x->p[0],x->p[1],x->p[2],y->p[py])) return;
    Tri*s[2];
    s[0]=new(pt++) Tri(x->p[(px+1)%3],y->p[py],x->p[px]);
    s[1]=new(pt++) Tri(y->p[(py+1)%3],x->p[px],y->p[py]);
    set_edge(Edge(s[0],0),Edge(s[1],0));
    set_edge(Edge(s[0],1),x->edge[(px+2)%3]),set_edge(Edge(s[0],2),y->edge[(py+1)%3]);
    set_edge(Edge(s[1],1),y->edge[(py+2)%3]),set_edge(Edge(s[1],2),x->edge[(px+1)%3]);
    rep(i,0,2) x->son[i]=y->son[i]=s[i];
    x->son[2]=y->son[2]=0;
    rep(i,0,2) flip(s[i],1),flip(s[i],2);
}
void add(P p){
    Tri*c=find(p),*s[3];
    rep(i,0,3) c->son[i]=s[i]=new(pt++) Tri(c->p[i],c->p[(i+1)%3],p);
    rep(i,0,3) set_edge(Edge(s[i],0),Edge(s[(i+1)%3],1));
    rep(i,0,3) set_edge(Edge(s[i],2),c->edge[(i+2)%3]);
    rep(i,0,3) flip(s[i],2);
}
P p[N];
int lx,ly,rx,ry,ox,oy,w,h,n;
void print(Tri*c){
    printf("3");
    per(i,0,3) printf(" %d",c->p[i].id);
    ox=oy=0;
    rep(i,0,3) ox+=c->p[i].x,oy+=c->p[i].y;
    ox/=3,oy/=3;
    puts("");
}
int main(){
    scanf("%d",&n);
    lx=ly=inf,rx=ry=-inf;
    rep(i,1,n+1) {
        int x,y;scanf("%d%d",&x,&y);
        p[i]=P(x,y,i);
    }
    lx=p[4].x,ly=p[4].y;
    rx=p[2].x,ry=p[1].y;
    w=rx-lx,h=ry-ly;
    pt=tri_pool;
    root = new(pt++) Tri(P(-inf,-inf),P(inf,-inf),P(0,inf));
    random_shuffle(p+1,p+n+1);
    rep(i,1,n+1) add(p[i]);
    int Q,x,y;scanf("%d%d%d",&Q,&x,&y);
    Tri*res=find(P(x,y),false);
    print(res);
    rep(i,1,Q){
        scanf("%d%d",&x,&y);
        x=((x+ox)%w+w)%w+lx;
        y=((y+oy)%h+h)%h+ly;
        Tri*res=find(P(x,y),false);
        print(res);
    }
    return 0;
}
