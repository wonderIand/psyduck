#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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
typedef double db;
const int N = 110;
int n , V , x[N],y[N],dx[N],dy[N],v[N];

const db pi = acos(-1.) , eps = 1e-8;

int sign(db x) {return (x > eps) - (x < -eps);}
struct P {
	db x,y;
	P(){}
	P (db x,db y) {this->x = x;this->y = y;}
	P operator - (const P&c) const {return P(x-c.x,y-c.y);}
	P operator + (const P&c) const {return P(x+c.x,y+c.y);}
	P operator * (const db& c) const {return P(x * c , y * c);}
};
db norm(P a){return a.x*a.x+a.y*a.y;}
db abs(P a){return sqrt(norm(a));}
db ang(P a,P b){return atan2(b.y-a.y,b.x-a.x);}
P rot(P a,db rad){return P(a.x * cos(rad) - a.y * sin(rad) , a.x * sin(rad) + a.y * cos(rad));}
db cross(P a,P b){return a.x * b.y - a.y * b.x;}

struct C {P o;db r;C(){}C(P o,db r) : o(o),r(r){}};

struct Event{
	P p;
	db ang;
	int delta;
	Event() {}
	Event(P p=P(0,0) , db ang=0 , int delta=0) : p(p) , ang(ang) ,delta(delta) {}
	bool operator < (const Event& c) const{
		return ang < c.ang;
	}
};
db sqr(db x) {return x * x;}

void addEvent(C a,C b,vector<Event>&evt,int &cnt) {
	db d2 = norm(a.o-b.o) , 
		dRatio = ((a.r - b.r) * (a.r + b.r) / d2 + 1) / 2 ,
		pRatio = sqrt(-(d2-sqr(a.r-b.r))*(d2-sqr(a.r+b.r))/(d2*d2*4));
	P d = b.o - a.o , p = rot(d , pi / 2) , 
		q0 = a.o + d * dRatio + p * pRatio,
		q1 = a.o + d * dRatio - p * pRatio;
	db ang0 = ang(a.o , q0) , ang1 = ang(a.o , q1);
	evt.pb(Event(q1,ang1,1));evt.pb(Event(q0,ang0,-1));
	cnt+=ang1>ang0;
}
bool issame(C a,C b) {return !sign(abs(a.o-b.o)) && !sign(a.r - b.r);}
bool overlap(C a,C b) {return sign(a.r - b.r - abs(a.o - b.o)) >= 0;}
bool intersect(C a,C b) {return sign(abs(a.o - b.o) - a.r - b.r )< 0;}

void solve(C *c,int n,db *ans){
	memset(ans , 0 , sizeof(db) * (n + 2));
	for(int i=0;i<n;++i){
		int cnt=1;
		vector<Event> evt;
		for(int j=0;j<i;++j) if(issame(c[i],c[j])) ++cnt;
		for(int j=0;j<n;++j)
			if(j!=i && !issame(c[i],c[j]) && overlap(c[j],c[i]))
				cnt++;
		for(int j=0;j<n;++j)
			if(j!=i && !overlap(c[j],c[i]) && !overlap(c[i],c[j]) && intersect(c[i],c[j]))
				addEvent(c[i],c[j],evt,cnt);
		if(!sz(evt)) ans[cnt] += pi * c[i].r * c[i].r;
		else{
			sort(all(evt));
			evt.pb(evt.front());
			for(int j=0;j+1<sz(evt);++j) {
				cnt += evt[j].delta;
				ans[cnt] += cross(evt[j].p , evt[j + 1].p) / 2;
				db ang = evt[j + 1].ang - evt[j].ang;
				if(ang < 0) ang += pi * 2;
				ans[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
			}
		}
	}
}

C c[N];
db ans[N];

bool check(db t){
	db r = t * V;
	rep(i,0,n){
		db vq = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);
		c[i] = C(P(t * v[i] * dx[i] / vq + x[i] , t * v[i] * dy[i] / vq + y[i]) , r);
	}
	solve(c , n , ans);
	return sign(ans[n]) == 1;
}

int main() {
	while(~scanf("%d%d",&n,&V)){
		rep(i,0,n){
			scanf("%d%d%d%d%d",x+i,y+i,dx+i,dy+i,v+i);
		}
		int times = 50;
		db l = 0 , r = 1000;
		rep(i,0,times){
			db mid = (l + r) / 2;
			if(check(mid)) r = mid;
			else l = mid;
		}
		printf("%.4f\n",(l + r) / 2 + eps);
	}
	return 0;
}
