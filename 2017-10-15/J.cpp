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
const int N = 2e5 + 10;
int a[N] , b[N] , link[N] , to[N] , n;

int main() {
	scanf("%d",&n);
	rep(i,0,n) scanf("%d",a + i);
	rep(i,0,n) scanf("%d",b + i);
	sort(a , a + n);
	sort(b , b + n);
	a[n] = -1;
	per(i,0,n)
		if(a[i] == a[i+1]) to[i] = to[i+1];
		else to[i] = i;
	int l = -1 , r = 2e9;
	ll S = 1ll * n * (n - 1) / 2 + 1 , T = 1ll * n * (n + 1) / 2;
	while(l + 1 < r){
		int mid = (0ll + l + r) / 2;
		ll sum = 0;
		rep(i,0,n) {
			int t = upper_bound(a , a + n , mid - b[i]) - a - 1;
			sum += t + 1;
		}
		if(sum >= S) r = mid;
		else l = mid;
	}
	ll skip = S - 1;
	rep(i,0,n){
		int t = lower_bound(a , a + n , r - b[i]) - a;
		skip -= t;
		link[i] = t;
	}
	rep(i,0,n) if(skip && link[i] != n && b[i] + a[link[i]] == r){
		ll t = min(skip , to[link[i]] - link[i] + 1ll);
		skip -= t;
		link[i] += t;
	}
	priority_queue<pii> Q;
	rep(i,0,n) if(link[i] != n) Q.push(mp(-(b[i] + a[link[i]]) , i));
	for(ll i=S;i<=T;++i){
		auto e = Q.top();Q.pop();
		printf("%d%c",-e.fi," \n"[i==T]);
		int c = e.se;
		link[c]++;
		if(link[c] != n){
			Q.push(mp(-(b[c] + a[link[c]]) , c));
		}
	}
	return 0;
}
