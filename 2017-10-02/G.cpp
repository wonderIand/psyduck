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
const int N = 1e5 + 10 , P = 777777777 , B = 26;
int weight[27] , pw[N] = {1};
struct ele{
	int hs , cnt;
	bool operator < (const ele&b) const {return hs < b.hs;}
}e[N];
struct Palindromic_Tree {
	static const int N = 1e5 + 10 , M = 26;
	int ne[N][M] , fail[N] , len[N] , S[N], last, n, p;
	int sz[N] , hs[N];
	int newnode(int l) {
		fill(ne[p], ne[p] + M, 0);
		len[p] = l;
		sz[p] = 0;
		return p++;
	}
	void ini() {
		p = 0; newnode(0);newnode(-1);
		S[n = last = 0] = -1;
		fail[0] = 1;
		hs[0] = hs[1] = 0;
	}
	int get_fail(int x) {
		while (S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c) {
		S[++n] = c;
		int cur = get_fail(last);
		if (!ne[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = ne[get_fail(fail[cur])][c];
			hs[now] = (hs[cur] + 1ll * weight[c] * pw[(len[now]-1)>>1] % P) % P;
			ne[cur][c] = now;
		}
		last = ne[cur][c];
//		cout << last << " " << len[last] << " " << hs[last] << endl;
		sz[last]++;
	}
	void solve(ll K){
		int _ = 0;
		for(int i=p-1;i>=2;--i) sz[fail[i]] += sz[i] , e[_++] = ele{hs[i] , sz[i]};
		sort(e , e + _);
		rep(i,0,_) {
			if(K <= e[i].cnt){
				printf("%d\n",e[i].hs);
				return;
			}
			K -= e[i].cnt;
		}
	}
}pa;

char s[N];
int T , len , m;

int main(){
	rep(i,1,N) pw[i] = 1ll * pw[i-1] * B % P;
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&len,&m);
		scanf("%s",s);
		rep(i,0,m){
			ll K;scanf("%lld",&K);
			rep(i,0,26) scanf("%d",weight + i);
			pa.ini();
			rep(i,0,len) pa.add(s[i] - 'a');
			pa.solve(K);
		}
		puts("");
	}
	return 0;
}


