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
typedef int T;
int sgn(int x){return (x>0)-(x<0);}
struct P {
	T x, y;
	P() {} P(T _x, T _y) {x = _x, y = _y;}
	P operator - (const P&b) const {return P(x-b.x,y-b.y);}
	T operator / (const P&b) const {return x*b.y-y*b.x;}
	P rot90() {return P(-y,x);}
	void in(){scanf("%d%d",&x,&y);x*=2,y*=2;}
};
const int N = 300;
P p[N];int type[N],n;
int solve(){
	scanf("%d",&n);
	rep(i,0,n) p[i].in() , scanf("%d",type+i);
	map<pii,int> Mp;
	rep(i,0,n) {
		pii t = mp(p[i].x,p[i].y);
		if(!Mp.count(t)) Mp[t] = type[i];
		else if(type[i] != Mp[t]) return 0;
	}
	int n = 0;
	for(auto e : Mp) p[n]=P(e.fi.fi,e.fi.se) , type[n++]=e.se;
	rep(i,0,n) rep(j,i+1,n) if(type[i]==type[j]){
		int sig = -2;
		bool err = false;
		rep(k,0,n) if(k!=i&&k!=j){
			if(err) break;
			int dir = sgn((p[k] - p[i]) / (p[j] - p[i]));
			if(type[k] == type[i]){
				if(dir) {
					if(sig == -2) sig = dir;
					else if(sig != dir) err = true;
				}
			} else {
				if(dir == 0) err = true;
				else {
					dir *= -1;
					if(sig == -2) sig = dir;
					else if(sig != dir) err = true;
				}
			}
		}
		if(!err) return 1;
	}
	rep(i,0,n) rep(j,i+1,n) if(type[i]!=type[j]){
		P mid=P((p[i].x+p[j].x)/2 , (p[i].y+p[j].y)/2);
		P v=(p[j]-p[i]).rot90();
		int sig = sgn((p[i] - mid) / v);
		bool err = false;
		rep(k,0,n) if(k!=i&&k!=j){
			if(err) break;
			int dir = sgn((p[k] - mid) / v);
			if(dir == 0) err = true;
			if(type[k] == type[i] && dir != sig) err = true;
			if(type[k] == type[j] && dir == sig) err = true;
		}
		if(!err) return 1;
	}
	return 0;
}

int main() {
	int T;scanf("%d",&T);
	rep(i,0,T) printf("%d\n",solve());
	return 0;
}
