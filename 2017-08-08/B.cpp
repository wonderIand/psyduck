#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
struct Trie {
	static const int N = 1010, M = 2;
	int ne[N][M], fail[N], fa[N], rt, L;
	int ed[N];
	string str[N];
	void ini() {
		fill_n(ne[fail[0] = N - 1], M, 0);
		L = 0, rt = newnode();
	}
	int newnode() {
		fill_n(ne[L], M, 0);ed[L] = 0;str[L]="";return L++;
	}
	void add(char *s,int id) {
		int p = rt;
		for (int i = 0; s[i]; ++i) {
			int c = s[i] - '0';
			if (!ne[p][c]) ne[p][c] = newnode(), fa[L - 1] = p , str[L - 1] = str[p] + s[i];
			p = ne[p][c];
		}
		ed[p] |= 1 << id;
	}
	void Build() {
		vi v;v.pb(rt);
		rep(i, 0, sz(v)) {
			int c = v[i];
			ed[c] |= ed[fail[c]];
			rep(i, 0,M) ne[c][i] ?
				v.pb(ne[c][i]), fail[ne[c][i]] = ne[fail[c]][i]:
				ne[c][i] = ne[fail[c]][i];
		}
	}
};
Trie pre , suf;
int T;

const int N = 6 * 20 + 10 , P = 998244353;
int dp[N][N][1<<6] , pd[N][N][1<<6] , n , L;
char s[10][N];
inline void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}

char ss[N] , len[10];
void solve(){
	scanf("%d%d",&n,&L);
	rep(i,0,n) scanf("%s",s[i]);
	pre.ini();
	suf.ini();
	rep(i,0,n){
		pre.add(s[i] , i);
		int len=strlen(s[i]);
		::len[i] = len;
		reverse(s[i],s[i]+len);
		rep(j,0,len) s[i][j]^='0'^'1';
		suf.add(s[i] , i);
		reverse(s[i],s[i]+len);
		rep(j,0,len) s[i][j]^='0'^'1';
	}
	pre.Build();
	suf.Build();
	int A = pre.L , B = suf.L;
	rep(i,0,A) rep(j,0,B) rep(k,0,1<<n) dp[i][j][k] = 0;
	dp[0][0][0] = 1;
	rep(t,0,L){
		rep(i,0,A) rep(j,0,B) rep(k,0,1<<n) pd[i][j][k] = 0;
		rep(i,0,A) rep(j,0,B) rep(k,0,1<<n) if(dp[i][j][k]){
			//cout << t << " " << pre.str[i] << " " << suf.str[j] << " " << dp[i][j][k] << endl;
			rep(ch,0,2){
				int x=pre.ne[i][ch],y=suf.ne[j][ch];
				int nk = k | pre.ed[x] | suf.ed[y];
				pp(pd[x][y][nk],dp[i][j][k]);
			}
		}
		rep(i,0,A) rep(j,0,B) rep(k,0,1<<n) dp[i][j][k] = pd[i][j][k];
	}
	int ans=0;
	rep(i,0,A) rep(j,0,B) rep(k,0,1<<n) if(dp[i][j][k]){
		int mask = k;
		string s=pre.str[i];
		string t=suf.str[j];
		reverse(all(t));
		rep(i,0,sz(t)) t[i]^='0'^'1';
		s+=t;
		rep(i,0,sz(s)) ss[i] = s[i];
		ss[sz(s)] = 0;
		rep(i,0,n) if(strstr(ss,::s[i])){
			mask |= 1 << i;
		}
		//cout << ss << " " << dp[i][j][k] << " " << mask<< " " << k << endl;
		if(mask == (1<<n)-1) pp(ans,dp[i][j][k]);
	}
	printf("%d\n",ans);
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
