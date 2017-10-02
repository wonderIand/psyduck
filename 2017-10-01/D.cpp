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
const int N = 1e4 + 10;
int n , m , K , T , cap[N];
vector<pii> v[N];
db p[51][N] , sum[51][N] , ans[N];

int main() {
	cin >> n >> m >> K >> T;
	rep(i,1,n+1) cin >> cap[i];
	rep(i,0,K) {
		int a , b , c;
		cin >> a >> b >> c;
		v[a].pb(mp(c , b));
	}
	rep(j,1,T+1) rep(i,1,m) cin >> p[i][j];
	rep(i,1,m) rep(j,1,T+1) sum[i][j] = p[i][j] + sum[i][j-1];
	rep(i,1,n+1) {
		int start = -1;
		vector<pii> s;
		for(auto e : v[i]) 
			if(e.se == m) start = e.fi;
			else s.pb(e);
		if(start == -1) continue;
		sort(all(s));
		rep(j,start,T+1) {
			db g = 1.;
			for(int i=0;i<sz(s)&&s[i].fi<j;++i){
				int a = s[i].fi , b = s[i].se;
				g *= 1 - (sum[b][j-1] - sum[b][a-1]);
			}
			ans[j] += g * cap[i];
		}
	}
	int id = 1;db p = 0;
	rep(i,1,T+1) if(ans[i] > p) p = ans[i] , id = i;
	printf("%.16f %d\n",p,id);
	return 0;
}

