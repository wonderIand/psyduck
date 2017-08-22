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
map<int,ll> Max;
map<int,ll> last;
char s[100];
int n,m;

inline ll _Max(int x){
	if(!Max.count(x)){
		if(x > n){
			Max[x] = 0;
		} else {
			ll ans = 0 , cur = x , r = x;
			while(cur * 2 <= n){
				cur *= 2 , r = r * 2 + 1;
			}
			r = min(r , (ll)n);
			for(;r>=x;r>>=1) ans+=r;
			Max[x] = ans;
		}
	}
	return Max[x];
}
inline ll Last(int x){
	if(!last.count(x)) last[x] = x;
	return last[x];
}

void change(int x,ll y){
	ll d = y - Last(x);last[x] = y;
	_Max(x); Max[x] += d;
	ll Mx = Max[x];
	for(int i=x;i>1;i>>=1){
		int j = i>>1;
		int dir = i & 1;
		Mx = Max[j] = max(Mx, _Max(j<<1|(dir^1))) + Last(j);
	}
}

ll query(int x){
	ll ans = -1;
	ans = max(ans , _Max(x << 1) + _Max(x << 1 | 1) + Last(x));
	ll Mx = _Max(x);
	for(int i=x;i>1;i>>=1){
		int j = i>>1;
		int dir = i & 1;
		ll tmp = Mx + _Max(j<<1|(dir^1)) + Last(j);
		Mx += Last(j);
		ans = max(ans , tmp);
	}
	return ans;
}

int main() {
	while(~scanf("%d%d",&n,&m)){
		Max.clear();
		last.clear();
		int x;ll y;
		rep(i,0,m){
			scanf("%s%d",s,&x);
			if(s[0] == 'q') printf("%lld\n",query(x));
			else {
				scanf("%lld",&y);
				change(x , y);
			}
		}
	}
	return 0;
}
