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

const db pi=acos(-1.);
db a1,b1,c1,a2,b2,c2;

db cal(db a,db b,db c,db A,db B,db C){
    db K=A*a+B*b,x=acos(c);
    return 2*(K*(sin(x)/4-sin(3*x)/12)+C*(x/2-sin(2*x)/4));
}

db G(db a,db b,db A,db B,db C){
    db l=-1,r=1,need=pi*C/2;
    rep(i,0,50){
        db mid=(l+r)/2;
        if(cal(a,b,mid,A,B,C)<=need) r=mid;
        else l=mid;
    }
    return (l+r)/2;
}

db F(db th){
    db a=cos(th),b=sin(th);
    return G(a,b,a1,b1,c1)-G(a,b,a2,b2,c2);
}

int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a1,&b1,&c1,&a2,&b2,&c2);
    db l=0,r=pi;
    rep(i,0,50){
        db mid=(l+r)/2,fmid=F(mid);
        if((fmid>=0)==(F(l)>=0)) l=mid;
        else r=mid;
    }
    l=(l+r)/2;
    db c=G(cos(l),sin(l),a1,b1,c1);
    printf("%.12f %.12f %.12f\n",cos(l),sin(l),c);
    return 0;
}
