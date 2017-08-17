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
const int N = 1e5 + 7;
vi has[N];
struct Trie {
	static const int N = 101010, M = 26;
	int ne[N][M], fail[N], fa[N], rt, L , len[N];
	void ini() { fill_n(ne[fail[0] = N - 1], M, 0);L = 0;rt = newnode();}
	int newnode() { fill_n(ne[L], M, 0);return L++; };
	void add(char *s,int num) {
		int p = rt;
		for (int i = 0;s[i]; ++i) {
			int c = s[i] - 'a';
			if (!ne[p][c]) ne[p][c] = newnode(), fa[L - 1] = p;
			p = ne[p][c];
			len[p]=i+1;
			has[num].pb(p);
		}
	}
	void Build() {
		vi v;v.pb(rt);
		rep(i, 0, sz(v)) {
			int c = v[i];
			rep(i, 0, M) ne[c][i] ?
				v.pb(ne[c][i]), fail[ne[c][i]] = ne[fail[c]][i] :
				ne[c][i] = ne[fail[c]][i];
		}
	}
};
Trie tree;
int n;
char s[N];
int vis[N],times,q[N],_;

int main() {
	int T;scanf("%d",&T);
	rep(i,0,T){
		tree.ini();
		scanf("%d",&n);
		rep(i,0,n) {
			scanf("%s",s);
			has[i].clear();
			tree.add(s , i);
		}
		tree.Build();
		int m;scanf("%d",&m);
		rep(i,0,m){
			int u,v;scanf("%d%d",&u,&v);
			--u;--v;
			int ans=0;
			_=0;times++;
			for(auto e : has[u]) q[_++]=e,vis[e]=times;
			rep(i,0,_) {
				int c=q[i];
				if(c==0) continue;
				int e=tree.fail[c];
				if(vis[e]!=times) vis[e]=times,q[_++]=e;
			}
			_=0;
			times++;
			for(auto e : has[v]) {
				if(vis[e]==times-1) ans=max(ans,tree.len[e]);
				q[_++]=e,vis[e]=times;
			}
			rep(i,0,_) {
				int c=q[i];
				if(c==0) continue;
				int e=tree.fail[c];
				if(vis[e]==times) continue;
				if(vis[e]==times-1) ans=max(ans,tree.len[e]);
				vis[e]=times,q[_++]=e;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
