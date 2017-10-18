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
const int N = 100;
int n;
int a[3][N];

vector<pii> ans;
vi pos[3];

int main() {
	scanf("%d",&n);
	rep(i,0,3) rep(j,1,n+1) scanf("%d",a[i] + j);
	int mask = 0;
	rep(j,1,n+1){
		int cnt0 = 0;
		rep(i,0,3) cnt0 += a[i][j] == 0;
		if(cnt0 == 3) ans.pb(mp(j , -j));
		else if(cnt0 == 0) ans.pb(mp(-j , j));
		else {
			int uni = cnt0 == 1 ? 0 : 1;
			int s=0;
			rep(i,0,3) if(a[i][j] == uni) s=i;
			pos[s].pb(j);
			if(~mask >> s & 1){
				mask |= 1 << s;
				rep(k,1,n+1) ans.pb(mp(uni?j:-j,a[s][k]?k:-k));
			}
		}
	}
	if(mask == 7) puts("-1");
	else {
		rep(s,0,3) {
			vi&v=pos[s];
			int t=(s+1)%3;
			rep(i,0,sz(v)) ans.pb(mp(a[t][v[0]]?v[0]:-v[0],a[t][v[i]]?v[i]:-v[i]));
		}
		printf("%d\n",sz(ans));
		auto out = [&](int x){
			if(x > 0) printf("x%d",x);
			else printf("!x%d",-x);
		};
		rep(i,0,sz(ans)){
			int a = ans[i].fi , b = ans[i].se;
			out(a);
			printf(" -> ");
			out(b);
			puts("");
		}
	}
	return 0;
}
