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
const int N = 210 , B = 6;
#define order(x) sort(all(x));x.erase(unique(all(x)),x.end())
#define rk(x , a) lower_bound(all(x) , a) - x.begin()
int n , sx , sy , tx , ty;
vi X , Y;
void ins(vi&X,int x){
	X.pb(x - 1);
	X.pb(x + 1);
}

struct P {
	ll x,y;
	P(){} P(ll x,ll y):x(x),y(y){}
	ll operator / (const P&b) const {return x * b.y - y * b.x;}
	P operator - (const P&b) const {return P(x - b.x , y - b.y);}
	void out(){cout << x << "," << y << endl;}
};
struct Rec{
	int sx,sy,tx,ty;
	void read(){
		scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
		sx *= B , sy *= B , tx *= B ,  ty *= B;
		if(sx > tx) swap(sx , tx);
		if(sy > ty) swap(sy , ty);
		ins(X , sx);ins(X , tx);
		ins(Y , sy);ins(Y , ty);
	}
}rec[N];

const int inf = 1e8;
int dis[N][N][4] , finish[N][N];
priority_queue<pair<int,pii> > Q;
int sgn(ll x){
	return (x > 0) - (x < 0);
}

bool isSS(P a1,P a2,P b1,P b2){
	ll c1 = (a2 - a1) / (b1 - a1) , c2 = (a2 - a1) / (b2 - a1);
	ll c3 = (b2 - b1) / (a1 - b1) , c4 = (b2 - b1) / (a2 - b1);
	return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}

bool check(int x,int y){
	x = X[x] , y = Y[y];
	rep(i,0,n) if(rec[i].sx <= x && x <= rec[i].tx && rec[i].sy <= y && y <= rec[i].ty)
		return false;
	return true;
}
P p[4];
bool check(P s,P t){
	rep(i,0,n) {
		int sx = rec[i].sx , sy = rec[i].sy;
		int tx = rec[i].tx , ty = rec[i].ty;
		p[0] = P(sx , sy) , p[1] = P(tx , sy);
		p[2] = P(tx , ty) , p[3] = P(sx , ty);
		rep(j,0,4){
			if(isSS(s , t , p[j] , p[(j+1)&3])) return false;
		}
	}
	return true;
}

int ok[N][N][4] , dx[] = {1 , 0 , -1 , 0} , dy[] = {0 , 1 , 0 , -1};
void go(int x,int y,int dir,int pdir,int d){
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if(ok[x][y][dir] == -1){
		ok[x][y][dir] = 0 <= nx && nx < sz(X) && 0 <= ny && ny < sz(Y)
			&& check(P(X[x] , Y[y]) , P(X[nx] , Y[ny])); 
	}
	if(ok[x][y][dir]){
		int nd = d;
		if(abs(X[x] - X[nx]) <= 2 && abs(Y[y] - Y[ny]) <= 2) {
			dir = pdir;
		} else nd += dir != pdir;
		if(nd < dis[nx][ny][dir]){
			dis[nx][ny][dir] = nd;
		//	cout << x << " " << y << " " << nx << " " << ny << " " << nd << endl;
		//	cout << X[x] << " " << Y[y] << " " << X[nx] << " " << Y[ny] << " " << nd << endl;
			Q.push(mp(-nd , mp(nx * sz(Y) + ny , dir)));
		}
	}
}


void dij(){
	while(sz(Q)){
		int x = Q.top().se.fi / sz(Y), y = Q.top().se.fi % sz(Y), d = -Q.top().fi , pdir = Q.top().se.se;
		Q.pop();
		if(finish[x][y]){
			printf("%d\n",dis[x][y][pdir]);
			return;
		}
		if(d == dis[x][y][pdir]){
			rep(dir,0,4) go(x , y , dir , pdir , d);

		}
	}
	printf("-1\n");
}

int main() {
	while(~scanf("%d%d%d%d",&sx,&sy,&tx,&ty)){
		if(sx == 0 && sy == 0 && tx == 0 && ty == 0) break;
		X.clear();Y.clear();
		scanf("%d",&n);
		rep(i,0,n) rec[i].read();
		sx *= B , sy *= B , tx *= B,  ty *= B;
		ins(X , sx);ins(X , tx);
		ins(Y , sy);ins(Y , ty);
		order(X);order(Y);
		rep(i,0,sz(X)) rep(j,0,sz(Y)) {
			finish[i][j] = false;
			rep(k,0,4) dis[i][j][k] = inf , ok[i][j][k] = -1;
		}
		while(sz(Q)) Q.pop();
		for(int dx=-1;dx<=1;dx+=2) for(int dy=-1;dy<=1;dy+=2){
			int si = rk(X , dx + sx) , sj = rk(Y , dy + sy);
			int ti = rk(X , dx + tx) , tj = rk(Y , dy + ty);
			if(check(si , sj)) {
				rep(dir,0,4) dis[si][sj][dir] = 0 , Q.push(mp(0 , mp(si * sz(Y) + sj , dir)));
			}
			if(check(ti , tj)) finish[ti][tj] = true;
		}
		dij();
	}
	return 0;
}
