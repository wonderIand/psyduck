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
const int N = 210 , inf = 1<<20;
int T;
char s[N];
vector<pii> ele;
int n , dp[N][N];
void inline Update(int &x,int d){
	if(x > d) x = d;
}
bool ok[10][10][10];

int main() {
	ok[1][1][1]=ok[1][1][2]=ok[2][1][1]=1;
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%s",s);
		int len = strlen(s);
		ele.clear();
		for(int i=0,j=0;i<len;i=j){
			for(j=i;j<len&&s[j]==s[i];++j);
			ele.pb({s[i] - '0' , j - i});
		}
		n = sz(ele);
		rep(i,0,n) rep(j,i,n) dp[i][j] = inf;
		rep(i,0,n) dp[i][i] = 3 - ele[i].se;
		rep(d,1,n) for(int l=0;l+d<n;++l){
			int r = l + d;
			for(int k=l;k<=r-1;++k) Update(dp[l][r] , dp[l][k] + dp[k+1][r]);
			if(ele[l].fi == ele[r].fi){
				Update(dp[l][r] , dp[l+1][r-1] + (ele[l].se + ele[r].se == 2));
				for(int k=l+2;k<r;k+=2) {
					if(ok[ele[l].se][ele[k].se][ele[r].se])
						Update(dp[l][r] , dp[l+1][k-1]+dp[k+1][r-1]);
				}
			}
		}
		printf("Case #%d: %d\n",i + 1,dp[0][n-1]);
	}
	return 0;
}
