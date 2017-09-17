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
struct Trie {
	static const int N = 101010, M = 26;
	int ne[N][M], fail[N], rt, L;
	int ed[N] , cnted;
	void ini() {
		fill_n(ne[fail[0] = N - 1], M, 0);
		L = 0; rt = newnode();
		cnted = 0;
	}
	int newnode() {
		ed[L] = 0;
		memset(ne[L] , 0 , sizeof(int) * M);
		return L++;
	}
	void add(char *s) {
		int p = rt;
		for (int i = 0; s[i]; ++i) {
			int c = s[i] - 'a';
			if (!ne[p][c]) ne[p][c] = newnode();
			p = ne[p][c];
		}
		if(!ed[p]) ed[p] = 1 , cnted++;
	}
	int q[N] , _;
	void Build() {
		_ = 0;
		q[_++] = rt;
		rep(i, 0, _) {
			int c = q[i];
			rep(i, 0, M) ne[c][i] ?
				q[_++] = ne[c][i] , fail[ne[c][i]] = ne[fail[c]][i] :
				ne[c][i] = ne[fail[c]][i];
		}
	}
	bool vis[N];
	bool check(char *s){
		int p = rt;
		rep(i,0,L) vis[i] = false;
		_ = 0;
		for(int i = 0; s[i];++i){
			int c = s[i] - 'a';
			p = ne[p][c];
			if(!vis[p]) vis[p] = 1 , q[_++] = p;
		}
		rep(i,0,_){
			int p = q[i];
			if(ed[p]) ed[p] = 0 , cnted--;
			if(p != N - 1) if(!vis[fail[p]]) vis[fail[p]] = 1 , q[_++] = fail[p];
		}
		return cnted == 0;
	}
}it;
const int N = 1e5 + 10;
char s[N] , t[N];

int main() {
	int T;
	scanf("%d",&T);
	rep(i,0,T){
		int n;
		scanf("%d",&n);
		int maxlen = -1;
		it.ini();
		rep(i,0,n) {
			scanf("%s",s);
			int lens = strlen(s);
			it.add(s);
			if(lens > maxlen) {
				maxlen = lens;
				rep(i,0,lens+1) t[i] = s[i];
			}
		}
		it.Build();
		puts(it.check(t) ? t : "No");
	}
	return 0;
}
