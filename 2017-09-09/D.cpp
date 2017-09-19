#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
///-----------

const int N = 1010 , inf = 1<<30;
int T,n,L,K,dp[N][N][2];
pii p[N];
inline void Update(int &x,int d){x = min(x , d);}

int solve(){
	scanf("%d%d%d",&n,&L,&K);
	rep(i,0,n) {
		scanf("%d%d",&p[i].fi , &p[i].se);
	}
	sort(p , p + n);
	rep(i,0,n) rep(j,i,n) rep(k,0,2) dp[i][j][k] = inf;
	dp[0][n-1][0] = max(p[0].fi , p[0].se);
	dp[0][n-1][1] = max(p[n-1].fi , p[n-1].se);
	for(int d=n-2;d>=0;--d)
		for(int i=0;i+d<n;++i){
			int j = i + d;
			rep(k,0,2){
				int c = k ? j : i;
				if(i != 0) Update(dp[i][j][k] , max(p[c].se , dp[i-1][j][0] + (p[c].fi - p[i-1].fi)));
				if(j + 1 != n) Update(dp[i][j][k] , max(p[c].se , dp[i][j+1][1] + (p[j+1].fi - p[c].fi)));
			}
		}
	int ans = inf;
	rep(i,0,n) rep(k,0,2) Update(ans , dp[i][i][k] + abs(p[i].fi - K));
	return ans;
}

int main(){
	scanf("%d",&T);
	rep(i,0,T) printf("Case #%d: %d\n",i+1,solve());
	return 0;
}

