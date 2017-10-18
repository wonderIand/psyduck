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
const int N = 15;
static ll inf = 1ll<<50;
template<class T>
struct KM {
	static const int N = 20;
	int n, m, left[N], pre[N], used[N];
	T g[N][N], Lx[N], Ly[N], slack[N];
	void ini(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 0, n) rep(j, 0, m) g[i][j] = -inf;
	}
	void go(int now) {
		rep(i, 0, m + 1) used[i] = 0, slack[i] = inf;
		left[m] = now; int u, v;
		for (u = m; ~left[u]; u = v) {
			used[u] = 1;
			T d = inf;
			rep(i, 0, m) if (!used[i]) {
				T tmp = Lx[left[u]] + Ly[i] - g[left[u]][i];
				if (tmp < slack[i]) slack[i] = tmp, pre[i] = u;
				if (slack[i] < d) d = slack[v = i];
			}
			rep(i,0,m + 1) if (used[i]) Lx[left[i]] -= d, Ly[i] += d;
			else slack[i] -= d;
		}
		for (; u != m; left[u] = left[pre[u]], u = pre[u]);
	}
	T run() {
		fill_n(Lx, n, 0); fill_n(Ly, m, 0);
		fill_n(left, m , -1);
		rep(i, 0, n) go(i);
		T ans = 0;
		rep(i, 0, n) ans += Lx[i];
		rep(i, 0, m) ans += Ly[i];
		return -ans;
	}
};
KM<ll> km;
int n,K,c,m;
int a[110][20] , sum[110][20];
ll cost[20][20];
ll f[110];
int main() {
	cin >> n >> K >> c >> m;
	rep(i,0,K) rep(j,0,n) cost[i][j]=inf;
	rep(i,0,m){
		int s , t , w;
		cin >> s >> t >> w;
		--s;--t;
		cost[t][s] = w;
	}
	int Q;scanf("%d",&Q);
	rep(i,1,Q+1) rep(j,0,K) scanf("%d",a[i] + j);
	rep(i,1,Q+1) rep(j,0,K) sum[i][j] = sum[i-1][j] + a[i][j];
	f[0] = 0;
	rep(t,1,Q+1) {
		f[t] = inf;
		rep(s,0,t){
			km.ini(K , n);
			rep(i,0,K) {
				ll need = sum[t][i] - sum[s][i];
				if(need == 0) rep(j,0,n) km.g[i][j] = 0;
				else rep(j,0,n) if(cost[i][j]!=inf)
					//de(-cost[i][j] * (sum[t][i] - sum[s][i])) , 
					km.g[i][j] = -cost[i][j] * (sum[t][i] - sum[s][i]);
			}
			ll co = km.run();
			//cout << s << " " << t << " " << co << endl;
			f[t] = min(f[t] , f[s] + co + c);
		}
	}
	printf("%lld\n",f[Q]);
	return 0;
}
