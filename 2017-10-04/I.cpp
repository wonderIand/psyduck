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
const int N = 1e3 + 3 , P = 1e6 + 3;
int n , a[N] , cnt[31][2] , comb[N][N] = {{1}};
inline void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}

int main() {
	rep(i,1,N) rep(j,0,i+1) comb[i][j] = j ? (comb[i-1][j-1] + comb[i-1][j]) % P : 1;
	while(~scanf("%d",&n)){
		memset(cnt , 0 , sizeof(cnt));
		rep(i,0,n) scanf("%d",a + i);
		rep(i,0,n) rep(j,0,31) cnt[j][a[i] >> j & 1]++;
		rep(i,1,n+1) {
			int ans = 0;
			rep(j,0,31){
				ll b = (1 << j) % P;
				int tmp = 0;
				for(int k=1;k<=i&&k<=cnt[j][1];k+=2){
					if(i - k > cnt[j][0]) continue;
					pp(tmp , 1ll * comb[cnt[j][1]][k] * comb[cnt[j][0]][i-k] % P);
				}
				pp(ans , b * tmp % P);
			}
			printf("%d%c",ans," \n"[i==n]);
		}
	}
	return 0;
}
