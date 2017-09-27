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
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
//-------
int n;
vector<pii> v , cur;

int main() {
	setIO("brick-count");
	scanf("%d",&n);
	rep(i,0,n){
		int x , y;
		scanf("%d%d",&x,&y);
		v.pb(mp(x,y));
	}
	sort(all(v));
	ll ans = 0;
	int y = 0;
	for(int i=0;i<n||sz(cur);){
		if(!sz(cur)) y = v[i].fi;
		int j = i;
		for(;j<n&&v[j].fi == y;++j);
		vector<pii> range;
		int left = -1 , right = -1 , has = 0;
		auto add = [&](pii a){
			if(has && a.fi - 2 <= right) right = max(a.se , right);
			else {
				if(has) range.pb(mp(left,right));
				has = true , left = a.fi , right = a.se;
			}
		};
		for(int a=0,b=i;a<sz(cur)||b<j;){
			if(b==j||(a<sz(cur)&&cur[a].fi<v[b].se)) add(cur[a++]);
			else add(mp(v[b].se , v[b].se)) , ++b;
		}
		if(has) range.pb(mp(left , right));
		for(auto e : range) ans += (e.se - e.fi) / 2 + 1;
		y++;
		cur.clear();
		for(auto e : range) if(e.fi != e.se) cur.pb(mp(e.fi + 1 , e.se - 1));
		i = j;
	}
	printf("%lld\n",ans);
	return 0;
}
