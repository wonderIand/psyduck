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

void dfs(int &x,int &y,int &K,int n,int opt){
	if(n == 0){
		if(opt == 1) x = 0 , y = 0;
		else K = 0;
	} else {
		int nx , ny , nK;
		int b = (1 << (n + n)) >> 2;
		int d = ((1 << n) >> 1);
		if(opt == 1){
			if(K < b) {
				nK = K;
				dfs(nx , ny , nK , n - 1 , opt);
				x = ny , y = nx;
			} else if(K < b + b){
				nK = K - b;
				dfs(nx , ny , nK , n - 1 , opt);
				x = nx , y = ny + d;
			} else if(K < b + b + b){
				nK = K - b - b;
				dfs(nx , ny , nK , n - 1 , opt);
				x = nx + d , y = ny + d;
			} else {
				nK = K - b - b - b;
				dfs(nx , ny , nK , n - 1 , opt);
				x = (1 << n) - 1 - ny , y = d - 1 - nx;
			}
		} else if(opt == 2){
			if(x < d && y < d){
				nx = y , ny = x;
				dfs(nx , ny , nK , n - 1 , opt);
				K = nK;
			} else if(x < d && y >= d){
				nx = x , ny = y - d;
				dfs(nx , ny , nK , n - 1 , opt);
				K = nK + b;
			} else if(x >= d && y < d){
				nx = d - 1 - y , ny = (1 << n) - 1 - x;
				dfs(nx , ny , nK , n - 1 , opt);
				K = nK + b + b + b;
			} else {
				nx = x - d , ny = y - d;
				dfs(nx , ny , nK , n - 1 , opt);
				K = nK + b + b;
			}
		}
	}
}

int main() {
	int n , K;
	while(~scanf("%d",&n)){
		if(n == 0) break;
		scanf("%d",&K);
		int x , y;
		--K;
		dfs(x , y , K , n , 1);
		vector<pii> ans;
		ll Max = 0;
		rep(d,0,4){
			int nx = x + (d == 2) - (d == 0);
			int ny = y + (d == 3) - (d == 1);
			if(nx < 0 || nx >= (1 << n) || ny < 0 || ny >= (1 << n)) continue;
			int nK;
			dfs(nx , ny , nK , n , 2);
			if(abs(nK - K) > Max)
				ans.clear() , Max = abs(nK - K) , ans.pb(mp(nx,ny));
			else if(abs(nK - K) == Max)
				ans.pb(mp(nx,ny));
		}
		sort(all(ans));
		printf("%d %d",x , y);
		rep(i,0,sz(ans)) printf(" %d %d",ans[i].fi , ans[i].se);
		puts("");
	}
	return 0;
}
