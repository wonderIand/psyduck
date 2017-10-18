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
const int N = 180000;
int P[2] = {1000000007 , 258280327};
int B[2] = {19950311 , 2333333};
int pw[2][30];
int Q , n;
string s[N] , q[N];
int id[N] , dis[N] , pre[N] , hs[2][30];
map<pair<int,int>,int> v;
map<string,int> ID;

void gethash(int *hs,string&s,int B,int P){
	int t=0,n=sz(s);
	rep(i,0,n) {
		t=(1ll*t*B+s[i])%P;
		hs[i]=t;
	}
}
int get(int *hs,int *pw,int l,int r,int B,int P){
	if(l > r) return 0;
	return (hs[r] - 1ll * (l == 0 ? 0 : hs[l-1]) * pw[r-l+1] % P + P) % P;
}

int main() {
	rep(i,0,2) {
		pw[i][0] = 1;
		rep(j,1,30) pw[i][j] = 1ll * pw[i][j-1] * B[i] % P[i];
	}
	cin >> Q;
	rep(i,0,Q) cin >> q[i];
	cin >> n;
	s[n] = '.';dis[n] = 1;pre[n]=-1;
	rep(i,0,n) cin >> s[i] , pre[i] = -1 , dis[i] = 1 , id[i] = i;
	sort(id,id+n,[&](int a,int b){return sz(s[a]) < sz(s[b]);});
	rep(i,0,n) {
		int c = id[i] , n = sz(s[c]);
		ID[s[c]] = c;
		string order=s[c];
		sort(all(order));
		rep(j,0,2) gethash(hs[j] , order , B[j] , P[j]);
		pii pc(hs[0][n-1],hs[1][n-1]),p;
		if(n == 1){
			pre[c] = ::n;
			dis[c] = 2;
		}
		else{
			rep(skip,0,n){
				p.fi = (1ll * get(hs[0] , pw[0] , 0 , skip - 1 , B[0] , P[0]) * pw[0][n-1-skip] + get(hs[0] , pw[0] , skip + 1 , n - 1 , B[0] , P[0])) % P[0];
				p.se = (1ll * get(hs[1] , pw[1] , 0 , skip - 1 , B[1] , P[1]) * pw[1][n-1-skip] + get(hs[1] , pw[1] , skip + 1 , n - 1 , B[1] , P[1])) % P[1];
				//if(s[c] == "university") cout << order << endl;
				if(v.count(p)){
					int t = v[p];
					if(dis[t] + 1 > dis[c])
						dis[c] = dis[t] + 1 , pre[c] = t;
				}
			}
		}
		if(!v.count(pc) || dis[c] > dis[v[pc]]) v[pc] = c;
	}
	rep(i,0,Q){
		int c = ID[q[i]];
		cout << dis[c] << endl;
		vector<string> ans;
		for(;c!=-1;c=pre[c]) ans.pb(s[c]);
		rep(i,0,sz(ans)) {
			if(i) cout << " -> ";
			cout << ans[i];
		}
		cout << endl;
	}
	return 0;
}
