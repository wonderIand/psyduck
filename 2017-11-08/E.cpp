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
const int N = 55;
const ll linf = 1e15 + 10;
int H , W;
char s[N][N];
ll f[N][N] , g[N][N];
inline void Update(ll&x,ll d){
	x = max(x , d);
}

int main() {
	scanf("%d%d",&H,&W);
	rep(i,0,H) scanf("%s",s[i]);
	ll ans = 0;
	rep(i,0,H) rep(j,0,W) if(~(i + j) & 1){
		rep(x,0,H) rep(y,0,W) g[x][y] = 0;
		g[i][j] = s[i][j] - '0';
		rep(x,i,H) rep(y,j,W) if(~(x + y) & 1){
			if(g[x][y] != 0){
				Update(ans , min(linf , g[x][y] + f[i][j]));
				if(x + 1 != H) {
					if(s[x+1][y] == '*'){
						Update(g[x+2][y] , min(linf , g[x][y] * (s[x+2][y] - '0')));
						Update(g[x+1][y+1] , min(linf , g[x][y] * (s[x+1][y+1] - '0')));
					} else {
						Update(f[x+2][y] , min(linf , f[i][j] + g[x][y]));
						Update(f[x+1][y+1] , min(linf , f[i][j] + g[x][y]));
					}
				}
				if(y + 1 != W){
					if(s[x][y+1] == '*'){
						Update(g[x][y+2] , min(linf , g[x][y] * (s[x][y+2] - '0')));
						Update(g[x+1][y+1] , min(linf , g[x][y] * (s[x+1][y+1] - '0')));
					} else{
						Update(f[x][y+2] , min(linf , f[i][j] + g[x][y]));
						Update(f[x+1][y+1] , min(linf , f[i][j] + g[x][y]));
					}
				}
			}
		}
	}
	if(ans > 1e15) puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
