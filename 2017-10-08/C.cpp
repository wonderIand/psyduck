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
const int N = 5050;
int v[N] , belong[N] ,  n , T , _;
int h[N] , to[N * 100] , ne[N * 100] , w[N * 100] , e;
void link(int u,int v,int w){
	to[e] = v;ne[e] = h[u];::w[e] = w;
	h[u] = e++;
}
int newid(int x){
	if(v[x] == -1) v[x] = _++;
	return v[x];
}
char s[N];
int citizen;

int pre[N] , recw[N] , q[N] , pp[N];
bool in[N];
void add(int c,int pre,int w){
	if(::pre[c] != -1) return;
	q[_++] = c;
	::pre[c] = pre;
	recw[c] = w;
	if(citizen >> belong[c] & 1)
		for(int k=h[c];~k;k=ne[k]){
			if(citizen >> belong[to[k]] & 1 && ::pre[to[k]] == -1)
				add(to[k] , pre , w);
		}
}
void bfs(int s,int t){
	int n = _;
	rep(i,0,n) pre[i] = -1 , in[i] = 0 , recw[i] = 1e8;
	_ = 0;add(s,-2,-1);
	for(int i=0,j=0;i<_;i=j){
		vi nid;
		for(j=i;j<_&&recw[j]==recw[i];++j){
			int c = q[j];
			for(int k=h[c];~k;k=ne[k]) {
				if(in[to[k]] == 0)
					in[to[k]] = 1 , nid.pb(to[k]);
				if(::pre[to[k]] == -1) {
					if(w[k] < recw[to[k]])
						recw[to[k]] = w[k] , pp[to[k]] = c;
				}
			}
		}
		sort(all(nid) , [&](int a,int b){return recw[a] < recw[b];});
		for(auto e : nid) add(e,pp[e],recw[e]);// , cout << e << " " << pp[e] << " " << recw[e] << endl;
	}
	vi ans;
	for(int i=t;i!=s&&i>=0;i=pre[i])
		if(recw[i]>=0)
			ans.pb(recw[i]);
	reverse(all(ans));
	rep(i,0,sz(ans)) printf("T%d%c",ans[i]," \n"[i+1==sz(ans)]);
	if(sz(ans) == 0) puts("");
}

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d",&n);
		_ = 0;e = 0;
		memset(v , -1 , sizeof(v));
		memset(h , -1 , sizeof(h));
		rep(i,0,n){
			int id;
			scanf("%d",&id);
			id = newid(id);
			scanf("%s",s);
			belong[id] = s[0] - 'A';
			int m , v;
			scanf("%d",&m);
			rep(i,0,m){
				scanf("%s%d",s,&v);
				v = newid(v);
				int w=0;
				for(int i=1;s[i];++i)
					w=w*10+s[i]-'0';
				link(id , v , w);
			}
		}
		int m;
		scanf("%d",&m);
		rep(i,0,m){
			int u,v;
			scanf("%d%d",&u,&v);
			u=newid(u);v=newid(v);
			citizen = 0;
			scanf("%s",s);
			for(int i=0;s[i];++i) citizen|=1<<(s[i]-'A');
			bfs(u , v);
		}
	}
	return 0;
}


