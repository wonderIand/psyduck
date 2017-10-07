#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e4 + 10;
int x[N] , y[N] , _;
int dx[4] = {-1 , 0 , 1 , 1};
int dy[4] = {1 , 1 , 0 , -1};
int step[4] = {0 , 0 , 0 , 0};
int add(int a,int b){
	x[_] = a , y[_] = b;
	if(_ == 10000) return true;
	_++;
	return false;
}

void Prepare(){
	_ = 1;
	for(int sx=0,sy=0,sdx=-1,sdy=0,cnt=0;;sx+=sdx,sy+=sdy,swap(sdx,sdy),cnt++){
		int cx=sx,cy=sy;
		if(add(cx,cy)) return;
		rep(pas,0,4) rep(j,0,step[pas]) if(add(cx+=dx[pas],cy+=dy[pas])) return;
		step[1]++ , step[2]++;
		if(cnt % 2 == 1) step[0]++ , step[3]++;
	}
}

int main() {
	Prepare();
	//rep(i,1,40) cout << x[i] << " " << y[i] << endl;
	int a , b;
	while(~scanf("%d%d",&a,&b)){
		if(a == 0 && b == 0) break;
		int ax = x[a] , ay = y[a];
		int bx = x[b] , by = y[b];
		int ans = abs(ax - bx) + abs(ay - by);
		if((ax - bx) * (ay - by) < 0) ans -= min(abs(ax - bx) , abs(ay - by));
		printf("%d\n",ans);
	}
	return 0;
}
