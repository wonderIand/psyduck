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
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
int n;
vector<pii> ans , p;

int ask(int x,int y){
	cout << "? " << x << " " << y << endl;
	fflush(stdout);
	int r;
	cin >> r;
	return r;
}

pii search(){
	int l = -1e6 - 1 , r = 1e6;
	while(l + 1 < r) {
		int m = (l + r) / 2;
		int x = m , y = 1e6;
		int gt = ask(x , y);
		rep(i,0,sz(ans)) gt -= ans[i].fi <= x && ans[i].se <= y;
		if(gt > 0) r = m;
		else l = m;
	}
	int x = r;
	l = -1e6 - 1 , r = 1e6;
	while(l + 1 < r) {
		int m = (l + r) / 2;
		int y = m;
		int gt = ask(x , y);
		rep(i,0,sz(ans)) gt -= ans[i].fi <= x && ans[i].se <= y;
		if(gt > 0) r = m;
		else l = m;
	}
	int y = r;
	return mp(x , y);
}

int main() {
	cin >> n;
	rep(i,0,n) ans.pb(search());
	cout << "!";
	rep(i,0,n) cout << " " << ans[i].fi << " " << ans[i].se;
	cout << endl;
	fflush(stdout);
	return 0;
}
