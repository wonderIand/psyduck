#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;
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
const db EPS = 1e-8;
struct P {
	db x, y, z;
	P() {}
	P(db _x, db _y, db _z) {
		x = _x, y = _y, z = _z;
	}
	P operator - (const P&b) const {return P(x - b.x , y - b.y , z - b.z);}
	void read() {
		double a , b , c;
		cin >> a >> b >> c;
		x = a , y = b , z = c;
	}
};
struct line3 {
	P a, b;
	line3() {}
	line3(P _a, P _b) {
		a = _a, b = _b;
	}
};
struct plane3 {
	P a, b, c;
	plane3() {}
	plane3(P _a, P _b, P _c) {
		a = _a, b = _b, c = _c;
	}
};
int sign(db x) {
	if (fabs(x) < EPS) return 0;
	return x > 0 ? 1 : -1;
}
P xmult(P u, P v) {
	P ret;
	ret.x = u.y * v.z - v.y * u.z;
	ret.y = u.z * v.x - u.x * v.z;
	ret.z = u.x * v.y - u.y * v.x;
	return ret;
}
db dmult(P u, P v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}
P subt(P u, P v) {
	P ret;
	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return ret;
}
P pvec(plane3 s) {
	return xmult(subt(s.a, s.b), subt(s.b, s.c));
}
int same_side(P p1, P p2, plane3 s) {
	return dmult(pvec(s), subt(p1, s.a))
		* dmult(pvec(s), subt(p2, s.a)) > -EPS;
}
P intersection(line3 l, plane3 s) {
	P ret = pvec(s);
	db t = (ret.x * (s.a.x - l.a.x) + ret.y * (s.a.y - l.a.y)
		+ ret.z * (s.a.z - l.a.z)) /
			(ret.x * (l.b.x - l.a.x) + ret.y * (l.b.y - l.a.y)
		+ ret.z * (l.b.z - l.a.z));
	ret.x = l.a.x + (l.b.x - l.a.x) * t;
	ret.y = l.a.y + (l.b.y - l.a.y) * t;
	ret.z = l.a.z + (l.b.z - l.a.z) * t;
	return ret;
}
const int N = 110;
int n;
P p[N];
pair<db,db> ans;

struct P2{
	db x,y;
	P2(){} P2(db x,db y):x(x),y(y){}
	db operator / (const P2&b) const {return x * b.y - y * b.x;}
	P2 operator - (const P2&b) const {return P2(x - b.x , y - b.y);}
	bool operator < (const P2&b) const {
		return sign(x - b.x) ? x < b.x : y < b.y;
	}
};
P2 p2[N],tmp[N];
db convexhull(P2 *p,int n,P2 *ch){
	sort(p , p + n);int m = 0;
	rep(i,0,n) {
		while(m > 1 && sign((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	} int k = m;
	per(i,0,n-1) {
		while(m > k && sign((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	}
	db res = 0.;
	rep(i,0,m-1) res += ch[i] / ch[i + 1];
	return fabs(res) / 2;
}

void check(int i,int j,int k){
	plane3 s(p[i] , p[j] , p[k]);
	P dir = pvec(s);
	vector<P> inter;
	db dis = 0.;
	rep(t,0,n) if(t != i && t != j && t != k){
		P u = intersection(line3(p[t] , p[t] - dir) , s);
		dis = max(dis , sqrt(dmult(p[t] - u , p[t] - u)));
		inter.pb(u);
	}
	inter.pb(p[i]);inter.pb(p[j]);inter.pb(p[k]);
	db area = 0. , x = fabs(dir.x) , y = fabs(dir.y) , z = fabs(dir.z);
	if(x > y && x > z) {
		rep(i,0,sz(inter)) p2[i] = P2(inter[i].y , inter[i].z);
		area = convexhull(p2 , sz(inter) , tmp) * sqrt(x * x + y * y + z * z) / fabs(x);
	} else if(y > z) {
		rep(i,0,sz(inter)) p2[i] = P2(inter[i].x , inter[i].z);
		area = convexhull(p2 , sz(inter) , tmp) * sqrt(x * x + y * y + z * z) / fabs(y);
	} else if(1) {
		rep(i,0,sz(inter)) p2[i] = P2(inter[i].x , inter[i].y);
		area = convexhull(p2 , sz(inter) , tmp) * sqrt(x * x + y * y + z * z) / fabs(z);
	}
	ans = max(ans , mp(dis , -area));
}

int main() {
	while(cin >> n){
		if(n == 0) break;
		rep(i,0,n) p[i].read();
		ans = mp(0 , 0);
		rep(i,0,n) rep(j,i+1,n) rep(k,j+1,n) {
			plane3 s(p[i] , p[j] , p[k]);
			int dir = -2 , ok = 1;
			rep(t,0,n) if(t != i && t != j && t != k){
				int sig = sign(dmult(pvec(s) , subt(p[t] , s.a)));
				//cout << i << " " << j << " " << k << " " << t << " " << sig << endl;
				if(sig != 0){
					if(dir == -2) dir = sig;
					else if(sig != dir){
						ok = false;
						break;
					}
				}
			}
			if(ok) check(i , j , k);
		}
		printf("%.3f %.3f\n",(double)(ans.fi + EPS) , double(-ans.se + EPS));
	}
	return 0;
}
