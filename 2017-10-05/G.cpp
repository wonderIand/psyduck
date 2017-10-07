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
struct PalindromicTree{
	static const int N = 2e5 + 10 , M = 26;
	int ne[N][M] , fail[N] , len[N] , S[N] , last , n , p;
	int sz[N];
	int newnode(int l){
		fill(ne[p] , ne[p] + M , 0);
		len[p] = l;
		sz[p] = 0;
		return p++;
	}
	void ini(){
		p = 0;newnode(0);newnode(-1);
		S[n = last = 0] = -1;
		fail[0] = 1;
	}
	int get_fail(int x){
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c){
		S[++n] = c;
		int cur = get_fail(last);
		if(!ne[cur][c]){
			int now = newnode(len[cur] + 2);
			fail[now] = ne[get_fail(fail[cur])][c];
			ne[cur][c] = now;
		}
		last = ne[cur][c];
		sz[last]++;
	}
	void dp(){
		per(i,2,p) sz[fail[i]]+=sz[i];
	}
}A , B;

const int N = 2e5 + 10;
char s[N];
void input(PalindromicTree&pa){
	pa.ini();
	scanf("%s",s);
	int len = strlen(s);
	rep(i,0,len) pa.add(s[i] - 'a');
	pa.dp();
}
ll ans;

void dfs(int l,int r){
	if(l > 1 && r > 1){
		ans += 1ll * A.sz[l] * B.sz[r];
	}
	rep(i,0,26) if(A.ne[l][i] && B.ne[r][i])
		dfs(A.ne[l][i] , B.ne[r][i]);
}

ll solve(){
	input(A);
	input(B);
	ans = 0;
	dfs(0 , 0);
	dfs(1 , 1);
	return ans;
}

int main() {
	int T;scanf("%d",&T);
	rep(i,1,T+1) printf("Case #%d: %lld\n",i , solve());
	return 0;
}
