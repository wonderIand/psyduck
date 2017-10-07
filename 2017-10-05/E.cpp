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
const T eps = 1e-8 , pi = acos(-1.);
int sgn(T x){return (x > eps) - (x < -eps);}
struct P{
	T x,y;
	P(){} P(T x,T y):x(x),y(y){}
	T operator / (const P&b) const {return x * b.y - y * b.x;}
	T operator * (const P&b) const {return x * b.x + y * b.y;}
	P operator - (const P&b) const {return P(x-b.x,y-b.y);}
	P operator + (const P&b) const {return P(x+b.x,y+b.y);}
	P operator * (const T&k) const {return P(x*k,y*k);}
	P operator / (const T&k) const {return P(x/k,y/k);}

	bool operator < (const P&b) const {return sgn(x - b.x) ? x < b.x : y < b.y;}
	P rot(T a) {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	} // anti-clock
	T abs() {return sqrt(x * x + y * y);}
	void in(){double a,b;scanf("%lf%lf",&a,&b);x=a,y=b;}
	void out(){printf("(%f,%f)\n",(double)x,(double)y);}
};
struct V{
	P o,s,t;
	V(){} V(P o,P s,P t):o(o),s(s),t(t){}
};
const int N = 1010;
bool vis[N];
typedef vector<P> polygon;
vector<pair<int,pii> > action;
P p[N];
vector<polygon> A;
vector<V> B;

T dis(P a,P b){return sqrt((b - a) * (b - a));}
bool onS(P p,P a,P b){
	return sgn((p - a) / (b - a)) == 0 && sgn((p - a) * (p - b)) <= 0;
}
P ch[1010];
polygon convex(polygon p){
	sort(all(p));int m = 0 , n = sz(p);
	rep(i,0,n) {
		while(m > 1 && sgn((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	} int k = m;
	per(i,0,n-1) {
		while(m > k && sgn((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	} if(n > 1) --m;
	return polygon(ch , ch + m);
}
int Pinpoly(P o,polygon&p){
	int n = sz(p) , res = 0;
	rep(i,0,n) {
		P u = p[i] , v = p[(i+1)%n];
		if(onS(o , u , v)) return -1;
		int k = sgn((v - u) / (o - u)) , d1 = sgn(u.y - o.y) , d2 = sgn(v.y - o.y);
		if(k > 0 && d1 <= 0 && d2 > 0) ++res;
		if(k < 0 && d2 <= 0 && d1 > 0) --res;
	}
	return res != 0;
}
int n , m , th , R;
bool PinV(P p,V&v){
	p = p - v.o;
	if(sgn(p.abs() - R) > 0) return false;
	return sgn(v.s / p) >= 0 && sgn(p / v.t) >= 0;
}

polygon get(V v,P dir){
	polygon res;
	res.pb(v.o);
	res.pb(v.o + v.s);
	res.pb(v.o + v.t);
	dir = dir.rot(pi / 2); 
	if(PinV(v.o + dir * R, v)) res.pb(v.o + dir * R);
	dir = dir.rot(pi);
	if(PinV(v.o + dir * R, v)) res.pb(v.o + dir * R);
	return res;
}
polygon move(polygon A , P dir){
	polygon B = A;
	rep(i,0,sz(B)) B[i] = B[i] + dir;
	return B;
}

string solve(){
	scanf("%d%d%d%d",&n,&m,&th,&R);
	P s , v , dir;
	s.in();v.in();dir.in();
	dir = dir / dir.abs();
	v = v / v.abs() * R;
	action.clear();
	rep(i,0,n){
		p[i].in();
	}
	rep(i,0,m){
		int a , b , c;
		scanf("%d%d%d",&a,&b,&c);
		action.pb(mp(b , mp(a , c)));
	}
	rep(i,0,n) vis[i] = false;
	sort(all(action));
	A.clear();B.clear();
	int curtime = 0;
	V S(s , v.rot(-0.5 * th / 180 * pi) , v.rot(0.5 * th / 180 * pi));
	for(int i=0,j=0;i<sz(action);i=j){
		int newtime = action[i].fi;
		polygon PA = get(S , dir) , PB = move(PA , dir * (newtime - curtime));
		P d = dir * (newtime - curtime);
		V nS = V(S.o + d , S.s , S.t);
		for(auto e : PB) PA.pb(e);
		PA = convex(PA);
		A.pb(PA);
		B.pb(S);
		S = nS;
		for(j=i;j<sz(action) && action[j].fi == action[i].fi;++j){
			if(action[j].se.fi == 2) dir = dir.rot(-action[j].se.se / 180.0 * pi);
			else {
				T th = -action[j].se.se / 180.0 * pi;
				B.pb(V(S.o , S.s.rot(th) , S.s));
				B.pb(V(S.o , S.t.rot(th) , S.t));
				S = V(S.o , S.s.rot(th) , S.t.rot(th));
			}
		}
		curtime = newtime;
	}
	B.pb(S);
	/*
	for(auto e : B) {
		e.o.out();
		cout << "~~~" << endl;
	}
	*/
	rep(i,0,n) {
		for(auto e : A) if(Pinpoly(p[i] , e)){
			vis[i] = true;
			break;
		}
		if(!vis[i]){
			for(auto e : B) if(PinV(p[i] , e)){
				vis[i] = true;
				break;
			}
		}
	}
	string res(n , '1');
	rep(i,0,n) if(vis[i]) res[i] = '0';
	return res;
}

int main() {
	int T;cin >> T;
	rep(i,1,T+1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
