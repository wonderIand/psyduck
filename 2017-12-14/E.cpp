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
const int N = 1e3 + 10;
map<int,int> vis;
int a[N] , n , ans[N];

int main() {
	scanf("%d",&n);
	vi v;
	bool err = false;
	rep(i,1,n+1) {
		int a;scanf("%d",&a);
		::a[i] = a;
		if(err) continue;
		if(a > 0) vis[a]++;
		else if(a == 0) {
			v.pb(i);
		} else if(vis.count(-a)){
			if(--vis[-a]==0) vis.erase(-a);
		} else if(sz(v)){
			int t = v[sz(v)-1];
			v.pop_back();
			ans[t] = -a;
		} else err=true;
	}
	rep(i,0,sz(v)) ans[v[i]] = 1;
	if(err) puts("No");
	else {
		puts("Yes");
		vi v;
		rep(i,1,n+1) if(a[i]==0) v.pb(ans[i]);
		rep(i,0,sz(v)) printf("%d%c",v[i]," \n"[i+1==sz(v)]);
	}
	return 0;
}
