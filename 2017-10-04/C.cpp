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
const int P = 1e9 + 7;
int n , m , C , D;
char s[110][20];
int f[1 << 10][21] , g[1 << 10][21];
inline void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}

int main() {
	while(~scanf("%d%d%d%d",&n,&m,&C,&D)){
		rep(i,0,n) scanf("%s",s[i]);
		rep(i,0,1<<m) rep(j,0,D+1) f[i][j] = 0;
		f[0][0] = 1;
		rep(x,0,n) rep(y,0,m){
			int can = s[x][y] - '0';
			rep(i,0,1<<m) rep(j,0,D+1) g[i][j] = 0;
			rep(i,0,1<<m) rep(j,0,D+1) if(f[i][j]){
				//cout << x << " " << y << " " << i << " " << j << " " << f[i][j] << endl;
				if(can){
					if(i >> y & 1) pp(g[i^(1<<y)][j] , f[i][j]);
					if(y > 0 && (i >> (y - 1) & 1)) {
						int has = i >> y & 1;
						if(has + j <= D) pp(g[i^(1<<(y-1))^(has<<y)][has+j] , f[i][j]);
					}
				}
				int has = i >> y & 1;
				if(has + j <= D) pp(g[i^(can<<y)^(has<<y)][has+j] , f[i][j]);
			}
			rep(i,0,1<<m) rep(j,0,D+1) f[i][j] = g[i][j];
		}
		int ans = 0;
		rep(i,0,1<<m) rep(j,0,D+1){
			int c = j + __builtin_popcount(i);
			if(C <= c && c <= D) pp(ans , f[i][j]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
