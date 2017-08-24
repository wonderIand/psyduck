#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi frist
#define se second
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 7;
int n, m;
struct edge {
	int v1, v2, v;
} e[N << 1];
struct node {
	int v;
	ll len;
};
queue<node> Q;
int F[N];
vector<ll> heap[N];
bool cmp(const edge &a, const edge &b) {
	return a.v1 < b.v1;
}
void insert(int num, ll x) {
	heap[num].push_back(x);
	push_heap(all(heap[num]));
}
ll findmin(int s, int t, int k, int n, int m) {
	int i;
	node x, tmp;
	sort(e, e + m, cmp);
//	rep(i, 0, m) printf("u = %d, v = %d, w = %d\n", e[i].v1, e[i].v2, e[i].v);
//	memset(F, -1, sizeof(F[0]) * (n + 1));
	memset(F, -1, sizeof(F));
	rep(i, 0, n + 1) F[i] = -1, heap[i].clear();
	F[e[0].v1] = 0;
	for (i = 1; i < m; ++i) if (e[i].v1 != e[i - 1].v1)
		F[e[i].v1] = i;
	tmp.v = s, tmp.len = 0;	
	Q.push(tmp);
	while (!Q.empty()) {
		x = Q.front();
		Q.pop();
		for (int i = F[x.v]; i != -1 && i < m && e[i].v1 == x.v; ++i) {
			tmp.v = e[i].v2;
			tmp.len = x.len + e[i].v;
			if (heap[tmp.v].size() < k) {
				insert(tmp.v, tmp.len);
				Q.push(tmp);
			} else if (tmp.len < heap[tmp.v][0]) {
				pop_heap(all(heap[tmp.v]));
				*(heap[tmp.v].rbegin()) = tmp.len;
				push_heap(all(heap[tmp.v]));
				Q.push(tmp);
			}
		}
	}
	sort_heap(all(heap[t]));
	if (heap[t].size() < k)	return -1;
	return heap[t][k - 1];
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &m);
		int t = 0;	
		rep(i, 0, m) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[t].v1 = u, e[t].v2 = v, e[t].v = w, ++t;
			e[t].v1 = v, e[t].v2 = u, e[t].v = w, ++t;
		}
		ll ans = findmin(1, n, 2, n, t);	
		printf("%lld\n", ans);
	}
	return 0;
}

