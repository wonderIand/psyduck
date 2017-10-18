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
const int N = 1010;
int n , K , ans[N];

int main() {
	scanf("%d%d",&n,&K);
	rep(i,1,n+1) ans[i] = -1;
	rep(i,1,n+1) {
		vector<pii> v;
		rep(j,1,i) v.pb(mp(ans[j],-j));
		sort(all(v));
		int ok = (i + 1) / 2 - 1 , need = 0;
		rep(i,0,ok) need += v[i].fi + 1;
		if(K >= need){
			rep(i,0,ok) ans[-v[i].se] = v[i].fi + 1;
			rep(i,ok,sz(v)) ans[-v[i].se] = 0;
			ans[i] = K - need;
		} else ans[i] = -1;
	}
	per(i,1,n+1) printf("%d%c",ans[i]," \n"[i==1]);
	return 0;
}
