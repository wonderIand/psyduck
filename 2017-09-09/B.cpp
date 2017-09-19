#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
///-----------

typedef ll T;
int sgn(T x){return (x > 0) - (x < 0);}
struct P{
	T x,y;
	P(){} P(T x,T y):x(x),y(y){}
	void read(){scanf("%lld%lld",&x,&y);}
	void out(){printf("(%lld,%lld)\n",x,y);}
	P operator - (const P&b) const {return P(x-b.x,y-b.y);}
	T operator / (const P&b) const {return x*b.y-y*b.x;}
	T operator * (const P&b) const {return x*b.x+y*b.y;}
};
struct L{
	P s,t;
	L(){} L(P s,P t):s(s),t(t){}
};
bool isSS(L a,L b){
	T c1=(a.t-a.s)/(b.s-a.s),c2=(a.t-a.s)/(b.t-a.s),
	  c3=(b.t-b.s)/(a.s-b.s),c4=(b.t-b.s)/(a.t-b.s);
	return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0 && 
		sgn(max(a.s.x,a.t.x) - min(b.s.x,b.t.x)) >= 0 &&
		sgn(max(b.s.x,b.t.x) - min(a.s.x,a.t.x)) >= 0 &&
		sgn(max(a.s.y,a.t.y) - min(b.s.y,b.t.y)) >= 0 &&
		sgn(max(b.s.y,b.t.y) - min(a.s.y,a.t.y)) >= 0;
}
P p[2][3] , v[2];

bool onPS(P p,P s,P t){
	return sgn((p-s)/(p-t)) == 0 && sgn((p-s)*(p-t))<=0;
}
typedef vector<P> polygon;
int inPpolygon(P p,polygon A){
	int res = 0;
	rep(i,0,sz(A)){
		P u=A[i],v=A[(i+1)%sz(A)];
		if(onPS(p,u,v)) return -1;
		T cross = sgn((v-u)/(p-u)) , d1 = sgn(u.y-p.y) , d2 = sgn(v.y-p.y);
		if(cross > 0 && d1 <= 0 && d2 > 0) ++res;
		if(cross < 0 && d2 <= 0 && d1 > 0) --res;
	}
	return res != 0;
}

bool collision(L l,P s,P v){
	if(v.x == 0 && v.y == 0) return false;
	ll lim = 1e9;
	ll ret = lim * 2;
	for (ll l = 1, r = lim * 2 + 1, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
		ll dx = s.x + 1ll * mid * v.x;
		ll dy = s.y + 1ll * mid * v.y;
		if (abs(dx) > lim || abs(dy) > lim) r = (ret = mid) - 1;
			else l = mid + 1;
	}
	v.x = v.x * ret + s.x;
	v.y = v.y * ret + s.y;

	return isSS(l , L(s , v));
}

bool solve(){
	rep(i,0,2){
		rep(j,0,3) p[i][j].read();
		v[i].read();
	}
	rep(i,0,2){
		vector<L> seg;
		polygon A;
		rep(j,0,3) seg.pb(L(p[i][j] , p[i][(j+1)%3])) , A.pb(p[i][j]);
		rep(j,0,3) if(inPpolygon(p[i^1][j] , A)) return true;
		for(auto e : seg) rep(j,0,3) if(isSS(e , L(p[i^1][j] , p[i^1][(j+1)%3]))) return true;
		P vs = v[i^1] - v[i];
		for(auto e : seg) rep(j,0,3) if(collision(e , p[i^1][j] , vs))
			return true;
	}
	return false;
}

void test(){
	polygon A;
	A.pb(P(0,0));
	A.pb(P(3,0));
	A.pb(P(0,3));
	cout << inPpolygon(P(0 , 0) , A) << endl;
	reverse(all(A));

	cout << inPpolygon(P(0 , 0) , A) << endl;
}

int main(){
	//test();
	int T;
	scanf("%d",&T);
	rep(i,1,T+1) printf("Case #%d: %s\n",i,solve() ? "YES" : "NO");
	return 0;
}

