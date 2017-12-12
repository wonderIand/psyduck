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
const int N = 1e5 + 7;
const ll inf = 1e18;
int n , a[N] , rk[N]; 
vi v;
set<int> s[N];
priority_queue<pair<ll,int> > q[N];
ll f[N];
inline ll cost(int x,int y){
	return f[x] - ll(y - x) * (y - x - 1) / 2 + a[y];
}
inline ll ceil(ll a,ll b){
	return (a + b - 1) / b;
}
inline ll cal(int j,int i){
	return ceil(2 * (f[j] - f[i]) + ll(i) * i + i - ll(j) * j - j ,
			2 * (i - j));
}

int main() {
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",a + i) , v.pb(a[i]);
	sort(all(v));
	v.erase(unique(all(v)),v.end());
	rep(i,1,n+1) rk[i] = upper_bound(all(v) , a[i]) - v.begin();
	ll ans = - ll(n) * (n + 1) / 2;
	rep(i,1,n+1) {
		f[i] = cost(0 , i);
		int x=rk[i];
		for(int t=x;t>=1;t&=t-1){
			set<int>&s=::s[t];
			priority_queue<pair<ll,int> >&q=::q[t];
			while(sz(q) && -q.top().fi <= i) {
				int x = q.top().se;q.pop();
				if(!s.count(x)) continue;
				auto it = s.lower_bound(x);
				if(it != s.begin()) {
					int t = *prev(it);
					if(cost(x , i) >= cost(t , i))
						s.erase(prev(it));
				}
				it = s.lower_bound(x);
				if(it != s.begin()) {
					int t = *prev(it);
					if(cost(x , i) >= cost(t , i))
						q.push(mp(-i , x));
					else
						q.push(mp(-cal(t , x) , x));
				}
			}
			if(sz(s)){
			//	cout << i << " " << *s.begin() << " " << cost(*s.begin() , i) << endl;
				f[i] = max(f[i] , cost(*s.begin() , i));
			}
		}
		for(int t=x;t<=sz(v);t+=t&-t){
			set<int>&s=::s[t];
			priority_queue<pair<ll,int> >&q=::q[t];
			while(sz(s)){
				auto it = s.end();
				--it;
				if(cost(i , i + 1) >= cost(*it , i + 1))
					s.erase(it);
				else break;
			}
			if(sz(s)) {
				auto it = s.end();
				--it;
				/*
				if(i == 4) {
					cout << t << endl;
					cout << *it << " " << i << " " << cal(*it , i) << endl;
				}
				*/
				q.push(mp(-cal(*it , i) , i));
			}
			s.insert(i);
		}
		ans = max(ans , f[i] - ll(n - i + 1) * (n - i) / 2);
	}
	printf("%lld\n",ans);
	return 0;
}
