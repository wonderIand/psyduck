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
const int N = 1010;
char s[N][N];
int dis[N * N] , q[N * N] , fa[N * N] ,  _ , n , m;
pair<pii,int> query[303030];
int ans[303030];
int to[N * N] , ne[N * N] , h[N] , e;
#define id(x,y) (x*(n)+y)

void link(int a,int b){
	ne[e] = h[a] , to[e] = b;
	h[a] = e++;
}
void ins(int x,int y,int d){
	int c = id(x , y);
	if(dis[c] > d) dis[c] = d , q[_++] = c , link(d , c);
}

inline int F(int x){return fa[x] == x ? x : fa[x] = F(fa[x]);}

int main() {
	///read
	scanf("%d", &n);
	rep(i, 1, n + 1) scanf("%s", s[i] + 1);
	n+=2;
	///prework
	memset(dis , 0x37 , sizeof(dis));
	rep(i,0,N) h[i] = -1;
	rep(i, 0, n) ins(0 , i , 0) , ins(n - 1, i , 0);
	rep(i, 0, n) ins(i , 0 , 0) , ins(i , n - 1, 0);
	rep(i, 1, n) rep(j, 1, n) if (s[i][j] == '#') ins(i , j , 0);
	rep(i,0,_){
		int c = q[i];
		int x = c / n , y = c % n;
		rep(dx,-1,2) rep(dy,-1,2){
			int nx=x+dx,ny=y+dy;
			if(0<=nx&&nx<n&&0<=ny&&ny<n)
				ins(nx , ny , dis[c] + 1);
		}
	}
	//rep(i,0,n) rep(j,0,n) printf("%d%c",dis[id(i,j)] , " \n"[j+1==n]);
	scanf("%d", &m);
	rep(i, 0, m) {
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		query[i] = mp(mp(id(a , b) , id(c , d)) , i);
	}
	int tot = n * n;
	rep(i,0,tot) fa[i] = i;
	int pm = m;
	per(r,1,N){
		for(int k=h[r];~k;k=ne[k]){
			int e=to[k];
			int x = e / n , y = e % n;
			rep(d,0,4){
				int nx = x + (d == 0) - (d == 2);
				int ny = y + (d == 1) - (d == 3);
				if(0 <= nx && nx < n && 0 <= ny && ny < n){
					int t = id(nx , ny);
					if(dis[t] >= r){
						int u = F(e) , v = F(t);
						if(u != v) fa[v] = u;
					}
				}
			}
		}
		rep(i,0,m) if(ans[query[i].se]==0){
			if(F(query[i].fi.fi) == F(query[i].fi.se)){
				ans[query[i].se] = r * 2 - 1;
				swap(query[i] , query[m-1]);
				--m;
				--i;
			}
		}
	}
	rep(i,0,pm) printf("%d\n",ans[i]);
	return 0;
}
