#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
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
const int N = 110;
typedef int T;
int sgn(int x){return (x > 0) - (x < 0);}
struct P{
	T x , y;
	P(){} P(T x,T y):x(x),y(y){}
	void read(){ cin >> x >> y;}
	P operator - (const P&b) const {return P(x - b.x , y - b.y);}
	T operator / (const P&b) const {return x * b.y - y * b.x;}
	T operator * (const P&b) const {return x * b.x + y * b.y;}
}p[N];
struct L {
	P s,t;
	L(){} L(P s,P t):s(s),t(t){}
};
bool isSS(L a,L b){
	T c1 = (a.t-a.s)/(b.s-a.s) , c2 = (a.t-a.s)/(b.t-a.s);
	T c3 = (b.t-b.s)/(a.s-b.s) , c4 = (b.t-b.s)/(a.t-b.s);
	return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0 &&
		sgn(max(a.s.x,a.t.x) - min(b.s.x,b.t.x)) >= 0 && 
		sgn(max(b.s.x,b.t.x) - min(a.s.x,a.t.x)) >= 0 && 
		sgn(max(a.s.y,a.t.y) - min(b.s.y,b.t.y)) >= 0 && 
		sgn(max(b.s.y,b.t.y) - min(a.s.y,a.t.y)) >= 0;
}
int n;

typedef vector<P> polygon;
bool inPpolygon(P p,polygon A){
	int res=0;
	rep(i,0,sz(A)){
		P u = A[i] , v = A[(i+1)%sz(A)];
		int cross = sgn((v - u) / (p - u)) , d1 = sgn(u.y - p.y) , d2 = sgn(v.y - p.y);
		if(cross > 0 && d1 <= 0 && d2 > 0) ++res;
		if(cross < 0 && d2 <= 0 && d1 > 0) --res;
	}
	return res != 0;
}

bool checkin(int a,int b,int c,int d){
	polygon A;
	A.pb(p[b]);A.pb(p[c]);A.pb(p[d]);
	if(inPpolygon(p[a] , A)){
		string ans(n , 'A');
		ans[a] = 'B';
		cout << "YES" << endl;
		cout << ans << endl;
		return true;
	}
	return false;
}

bool ok(int a,int b,int c,int d){

	if(isSS(L(p[a] , p[b]) , L(p[c] , p[d]))){
		string ans(n , 'A');
		ans[c] = ans[d] = 'B';
		cout << "YES" << endl;
		cout << ans << endl;
		return true;
	}
	return false;
}

bool check(vi v){
	int a = v[0] , b = v[1] , c = v[2] , d = v[3];
	if(ok(a , b , c , d)) return true;
	if(ok(a , c , b , d)) return true;
	if(ok(a , d , b , c)) return true;
	if(checkin(a , b , c , d)) return true;
	if(checkin(b , a , c , d)) return true;
	if(checkin(c , a , b , d)) return true;
	if(checkin(d , a , b , c)) return true;
	return false;
}
bool check(int a,int b,int c){
	if((p[b] - p[a]) * (p[c] - p[a]) < 0){
		cout << "YES" << endl;
		string ans(n , 'A');
		ans[a] = 'B';
		cout << ans << endl;
		return true;
	}
	return false;
}


void solve(){
	cin >> n;
	rep(i,0,n) p[i].read();
	if(n <= 2){
		cout << "NO" << endl;
		return;
	}
	vi A , B;
	rep(i,2,n){
		if((p[i] - p[0]) / (p[1] - p[0]) == 0) A.pb(i);
		else B.pb(i);
	}
	if(sz(A)) {
		if(check(0 , 1 , A[0])) return;
		if(check(1 , A[0] , 0)) return;
		if(check(A[0] , 0 , 1)) return;
		return ;
	}
	int nn = min(10 , n);
	rep(i,0,nn) rep(j,i+1,nn) rep(k,j+1,nn) rep(t,k+1,nn) if(check({i,j,k,t})) return;
	cout << "NO" << endl;
}

int main() {
	int T;cin >> T;
	rep(i,0,T) solve();
	return 0;
}
