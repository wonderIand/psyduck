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
const int N = 130;
typedef bool BB[N];
struct Maxclique {
	const BB *e; int pk, level; const db Tlimit;
	struct Vertex {int i, d; Vertex(int i): i(i),d(0) {}};
	typedef vector<Vertex> Vertices; typedef vector<int> ColorClass;
	Vertices V; vector<ColorClass> C; ColorClass QMAX, Q;
	static bool desc_degree(const Vertex &vi, const Vertex &vj) {
		return vi.d > vj.d;
	}
	void init_colors(Vertices &v) {
		const int max_degree = v[0].d;
		for (int i = 0; i < sz(v); ++i) v[i].d = min(i, max_degree) + 1;
	}
	void set_degrees(Vertices &v) {
		for (int i = 0, j; i < sz(v); ++i)
			for (v[i].d = j = 0; j < sz(v); ++j)
				v[i].d += e[v[i].i][v[j].i];
	}
	struct StepCount {int i1, i2; StepCount():i1(0),i2(0){}};
	vector<StepCount> S;
	bool cut1(const int pi, const ColorClass &A) {
		for (int i = 0; i < sz(A); ++i) if (e[pi][A[i]]) return true;
		return false;
	}
	void cut2(const Vertices &A, Vertices &B) {
		for (int i = 0; i < sz(A) - 1; ++i)
			if (e[A.back().i][A[i].i])
				B.pb(A[i].i);
	}
	void color_sort(Vertices &R) {
		int j = 0, maxno = 1, min_k = max(sz(QMAX) - sz(Q) + 1, 1);
		C[1].clear(), C[2].clear();
		rep(i, 0, sz(R)) {
			int pi = R[i].i, k = 1;
			while (cut1(pi, C[k])) ++k;
			if (k > maxno) maxno = k, C[maxno + 1].clear();
			C[k].pb(pi);
			if (k < min_k) R[j++].i = pi;
		}
		if (j > 0) R[j - 1].d = 0;
		for (int k = min_k; k <= maxno; ++k)
			rep(i, 0, sz(C[k]))
				R[j].i = C[k][i], R[j++].d = k;

	}
	void expand_dyn(Vertices &R) {
		S[level].i1 = S[level].i1 + S[level - 1].i1 - S[level].i2;
		S[level].i2 = S[level - 1].i1;
		while (sz(R)) {
			if (sz(Q) + R.back().d > sz(QMAX)) {
				Q.pb(R.back().i);
				Vertices Rp; cut2(R, Rp);
				if (sz(Rp)) {
					if ((db) S[level].i1 / ++pk < Tlimit) degree_sort(Rp);
					color_sort(Rp);
					S[level].i1++, level++;
					expand_dyn(Rp);
					--level;
				}
				else if (sz(Q) > sz(QMAX)) QMAX = Q;
				Q.pop_back();

			}
			else return ;
			R.pop_back();
		}
	}
	void mcqdyn(int *maxclique, int &siz) {
		set_degrees(V); sort(all(V), desc_degree); init_colors(V);
		rep(i, 0, sz(V) + 1) S[i].i1 = S[i].i2 = 0;
		expand_dyn(V); siz = sz(QMAX);
		rep(i, 0, sz(QMAX)) maxclique[i] = QMAX[i];
	}
	void degree_sort(Vertices &R) {
		set_degrees(R); sort(all(R), desc_degree);
	}
	Maxclique(const BB *conn, const int sz, const db tt = 0.025): pk(0), level(1), Tlimit(tt) {
		rep(i, 0, sz) V.pb(Vertex(i));
		e = conn, C.resize(sz + 1), S.resize(sz + 1);
	}
};
BB can[N];
int pos[N][N];
int ans[N] , siz;

int main() {
	int n , m;
	while(~scanf("%d%d",&n,&m)){
		if(n == 0 && m == 0) break;
		rep(i,0,n) rep(j,0,n) pos[i][j] = 0;
		rep(i,0,m){
			int u,v;
			scanf("%d%d",&u,&v);
			pos[u][v] = pos[v][u] = 1;
		}
		int sz = n - 1;
		rep(i,0,sz) rep(j,0,sz) can[i][j] = i==j;
		rep(i,1,n) rep(j,i+1,n) {
			if((pos[0][i] == pos[0][j]) == pos[i][j]) can[i-1][j-1] = can[j-1][i-1] = 1;
		}
		//rep(i,0,sz) rep(j,0,sz) printf("%d%c",can[i][j]," \n"[j+1==sz]);
		Maxclique it(can , sz);
		it.mcqdyn(ans , siz);
		printf("%d\n",siz + 1);
	}
	return 0;
}
