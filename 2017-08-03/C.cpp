#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
const int MOD = 998244353;
//-------
const int MAX_N = 1e6 + 7;
bool isP[MAX_N];
int P[MAX_N],pn;
void init() {
	///init
	memset(isP,true,sizeof(isP));
	pn=0;
	///work
	rep(i,2,MAX_N) {
		if (isP[i]) P[pn++] = i;
		for (int j=0; j<pn && P[j]*i<MAX_N; j++) {
			isP[P[j] * i] = false;
			if (i % P[j] == 0) break;
		}
	}
}
//-------
int ans[MAX_N];
ll val[MAX_N];
int main() {
	
	init();
	//rep(i,0,20) de(P[i]);

	int tcase=0; scanf("%d",&tcase);
	rep(icase,0,tcase) {
		///read
		ll l,r,k; cin>>l>>r>>k;
		///work
		rep(i,0,r-l+1) ans[i]=1;
		rep(i,0,r-l+1) val[i]=l+i; 
		rep(i,0,pn) {
			for (ll now = ((l-1)/P[i]+1)*P[i]; now <= r; now+=P[i]) {
				int can = 0; 
				for (; val[now-l]%P[i]==0; val[now-l]/=P[i]) can++;
				ans[now-l] = (ans[now-l] + 1ll * ans[now-l] * can % MOD  * k % MOD) % MOD;
			}
		}
		rep(i,0,r-l+1) if (val[i]>1) {
			ans[i] = 1ll * ans[i] * (k+1) % MOD;
		}
		///print
		int ret = 0;
		rep(i,0,r-l+1) ret=(ret+ans[i])%MOD;
		printf("%d\n",ret);
	}
		
		

	return 0;
}
