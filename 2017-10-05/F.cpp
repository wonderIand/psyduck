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
//-------
const int P = 1e9 + 7 , N = 1e6 + 10;
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=1ll*x*x%P)if(t&1)r=1ll*r*x%P;return r;}
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int n , m , K , inv[N] , pw[N] , vis[N] , pri[N] , _p;
int cofA[N] , cofB[N];

int solve(){
	scanf("%d%d%d",&n,&m,&K);
	int ans = 0;
	pw[0] = n == 1 ? 1 : 0;
	pw[1] = 1;
	_p = 0;
	rep(i,2,K+1){
		if(!vis[i]) pri[_p++] = i , pw[i] = Pow(i , n - 1);
		for(int j=0,o=0;j<_p&&(o=pri[j]*i)<=K;++j){
			vis[o] = true;
			pw[o] = (ll)pw[pri[j]] * pw[i] % P;
			if(i % pri[j] == 0) break;
		}
	}
	//rep(i,1,N) assert(pw[i] = Pow(i , n - 1));
	for(int i=1,B=1;i<=K;++i) B=cofB[i]=1ll*B*(m-i+1)%P*inv[i]%P;
	cofA[K]=1;for(int i=K-1,A=1;i>=1;--i) A=cofA[i]=1ll*A*(m-i)%P*inv[K-i]%P;
	for(int i=1;i<=K;++i){
		int add = 1ll * cofA[i] * cofB[i] % P * i % P * pw[i-1] % P;
		if((K - i) & 1) pp(ans , P - add);
		else pp(ans , add);
	}
	return ans;
}

int fast(int n,int m,int K){
	::n = n , ::m = m , ::K = K;
	int ans = 0;
	pw[0] = n == 1 ? 1 : 0;
	pw[1] = 1;
	_p = 0;
	rep(i,2,K+1){
		if(!vis[i]) pri[_p++] = i , pw[i] = Pow(i , n - 1);
		for(int j=0,o=0;j<_p&&(o=pri[j]*i)<=K;++j){
			vis[o] = true;
			pw[o] = (ll)pw[pri[j]] * pw[i] % P;
			if(i % pri[j] == 0) break;
		}
	}
	//rep(i,1,N) assert(pw[i] = Pow(i , n - 1));
	for(int i=1,B=1;i<=K;++i) B=cofB[i]=1ll*B*(m-i+1)%P*inv[i]%P;
	cofA[K]=1;for(int i=K-1,A=1;i>=1;--i) A=cofA[i]=1ll*A*(m-i)%P*inv[K-i]%P;
	for(int i=1;i<=K;++i){
		int add = 1ll * cofA[i] * cofB[i] % P * i % P * pw[i-1] % P;
		if((K - i) & 1) pp(ans , P - add);
		else pp(ans , add);
	}
	return ans;
}

int ans = 0;
void dfs(int c,int mask,int bf){
	if(c == n) ans += __builtin_popcount(mask) == K;
	else {
		rep(i,1,m+1) if(i != bf)
			dfs(c + 1 , mask | (1 << i) , i);
	}
}

int bf(int n,int m,int K){
	::n = n , ::m = m , ::K = K;
	ans = 0;
	dfs(0 , 0 , 0);
	return ans;
}

int main() {
	inv[1] = 1;rep(i,2,N) inv[i] = P-ll(P/i)*inv[P%i]%P;
	/*
	rep(n,1,8) rep(m,1,8) rep(K,1,min(n,m)+1) if(fast(n,m,K)!=bf(n,m,K)){
		cout << bf(n , m , K) << endl;
		cout << fast(n , m , K) << endl;
		cout << n << " " << m << " " << K << endl;
		return 0;
	}
	*/
	//rep(i,1,N) assert(1ll * i * inv[i] % P == 1);
	int T;scanf("%d",&T);
	rep(i,1,T+1) printf("Case #%d: %d\n",i , solve());
	return 0;
}
