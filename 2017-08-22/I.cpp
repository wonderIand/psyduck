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
const int P = 1e9 + 7;
const int N = 5e5 + 10;
int T;
ll l,r,K;
map<pair<ll,int>,int> MpF,MpG;
int pri[N],_p,vis[N];

int G(ll,int);
int sum2(ll x){
	return __int128(x)*(x+1)/2%P;
}
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

int F(ll x,int y){
	if(y < 0) return 0;
	if(x <= 0) return 0;
	int K = pri[y];
	if(K>sqrt(x+0.5)) return K%P*(K<=x);
	if(MpF.count({x,y})) return MpF[{x,y}];
	int&ans=MpF[{x,y}] = 0;
	ans=sum2(x/K);
	pp(ans,P-G(x/K,y-1));
	ans = 1ll * ans * K % P;
	return ans;
}
int G(ll x,int y){
	if(y < 0) return 0;
	if(x <= 0) return 0;
	if(MpG.count({x,y})) return MpG[{x,y}];
	int&ans=MpG[{x,y}] = 0;
	rep(i,0,y+1) pp(ans,F(x,i));
	return ans;
}

bool isprime(ll x){
	for(ll i=2;i*i<=x;++i) if(x%i==0) return 0;
	return 1;
}

int solve(ll x,ll K){
	if(!isprime(K)) return 0;
	if(K>sqrt(x+0.5)) return K%P*(K<=x);
	int num = lower_bound(pri , pri + _p , K) - pri;
	return F(x , num);
}

int solve(){
	scanf("%lld%lld%lld",&l,&r,&K);
	int ans = (solve(r , K) - solve(l - 1 , K) + P) % P;
	return ans;
}

int main() {
	rep(i,2,N){
		if(!vis[i]) pri[_p++] = i;
		for(int j=0,o=0;j<_p&&(o=pri[j]*i)<N;++j){
			vis[o]=1;
			if(pri[j]%i==0) break;
		}
	}
	scanf("%d",&T);
	rep(i,0,T) printf("Case #%d: %d\n",i + 1,solve());
	return 0;
}
