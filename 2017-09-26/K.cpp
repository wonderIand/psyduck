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
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
//-------
const int N = (1e5 + 10) * 2;
int n;
ll x[N] , S , cnt[61][2];
int pre[61][N] , type[61][N];

int main() {
	setIO("xor-cypher");
	cin >> n >> S;
	rep(i,0,n) cin >> x[i];
	rep(i,0,n) rep(j,0,60) cnt[j][x[i]>>j&1]++;
	memset(pre , -1 , sizeof(pre));
	per(i,0,2) if(pre[0][cnt[0][i]] == -1) pre[0][cnt[0][i]] = 0 , type[0][cnt[0][i]] = i ^ 1;
	rep(i,0,60) per(k,0,2) rep(j,0,N) if(pre[i][j] != -1 && (j & 1) == (S >> i & 1)){
		int nt = (j >> 1) + cnt[i+1][k];
		if(pre[i+1][nt] == -1)
			pre[i+1][nt] = j , type[i+1][nt] = k ^ 1;
	}
	if(pre[60][0] != -1) {
		ll ans = 0;int c = 0;
		per(i,0,61) {
			ans |= ll(type[i][c]) << i;
			c = pre[i][c];
		}
		cout << ans << endl;
	} else cout << -1 << endl;
	return 0;
}
