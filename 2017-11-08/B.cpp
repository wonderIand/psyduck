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
const int N = 1e5 + 10;
int S , T , D , w[N];
ll sum[N];

int main() {
	scanf("%d%d%d",&S,&T,&D);
	rep(i,0,D) scanf("%d",w + i);
	rep(i,0,D) sum[i] = (i ? sum[i-1] : 0) + w[i];
	ll ans = 1ll<<60;
	rep(i,0,D) {
		ll need = S - T;
		if(-sum[i] >= need) ans = min(ans , i + 1ll);
		else if(sum[D-1] < 0){
			// x * sum[D - 1] + sum[i] <= -need
			// x >= (-sum[i] - need) / sum[D - 1]
			ll up = sum[i] + need;
			ll down = - sum[D - 1];
			ans = min(ans , 1ll * D * ((up + down - 1) / down) + i + 1);
		}
	}
	if(ans == 1ll<<60) puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
