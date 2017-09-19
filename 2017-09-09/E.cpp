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

ll ans[] = {1ll,8ll,49ll,288ll,1681ll,9800ll,57121ll,332928ll,1940449ll,11309768ll,65918161ll,384199200ll,2239277041ll,13051463048ll,76069501249ll,443365544448ll,2584123765441ll,15061377048200ll,87784138523761ll,511643454094368ll,2982076586042449ll,17380816062160328ll,101302819786919521ll,590436102659356800ll};

bool isQ(ll x){
	ll q = sqrt(x + 0.5);
	return q * q == x;
}

int main2(){
	const int UP = 1e9 + 10;
	vector<ll> ans;
	rep(i,1,UP + 1)	{
		if(i & 1){
			ll t = 1ll * i * i + 1;
			if(isQ(t / 2))
				ans.pb(1ll * i * i);
		} else {
			ll t = 1ll * i * i * 2 + 1;
			if(isQ(t))
				ans.pb(2ll * i * i);
		}
	}
	sort(all(ans));
	rep(i,0,sz(ans)) printf("%lldll,",ans[i]);
	return 0;
}

int main(){
	//main2();
	int T;
	scanf("%d",&T);
	rep(cs,0,T){
		ll n;
		scanf("%lld",&n);
		for(int i=0;;++i) if(ans[i] >= n){
			printf("Case #%d: %lld\n",cs+1,ans[i]);
			break;
		}
	}
}
