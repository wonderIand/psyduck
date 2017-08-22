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
const int N = 2525;
int T;
char s[N] , t[N];
int pre[N];
bool ok[N][N];
int sum[N][N];

inline int Sum(int l,int r,int x){
	if(l == 0) return sum[r][x];
	return sum[r][x] - sum[l-1][x];
}

bool solve(){
	scanf("%s%s",s + 1 , t + 1);
	int n = strlen(s + 1);
	int m = strlen(t + 1);
	pre[1] = 1;
	rep(i,2,n+1) pre[i] = s[i] == s[i-1] ? pre[i-1] : i;
	rep(i,0,n+1) rep(j,0,m+1) ok[i][j] = 0;
	ok[0][0] = 1;
	rep(i,0,n+1) sum[i][0] = (i?sum[i-1][0]:0)+ok[i][0];
	rep(j,1,m+1) {
		if(j < m && t[j + 1] == '*'){
			rep(i,0,n+1) ok[i][j] = ok[i][j-1];
			if(t[j] == '.'){
				rep(i,1,n+1) ok[i][j] |= Sum(pre[i]-1,i,j-1);
			} else {
				rep(i,1,n+1) ok[i][j] |= Sum(pre[i]-1,i,j-1) && (s[i] == t[j]);
			}
		} else if(t[j] == '*'){
			rep(i,0,n+1) ok[i][j] = ok[i][j-1];
		} else if(t[j] == '.'){
			rep(i,1,n+1) ok[i][j] = ok[i-1][j-1];
		} else {
			rep(i,1,n+1) ok[i][j] = ok[i-1][j-1] & (s[i] == t[j]);
		}
		rep(i,0,n+1) sum[i][j] = (i?sum[i-1][j]:0)+ok[i][j];
		//rep(i,0,n+1) printf("%d%c",(int)ok[i][j]," \n"[i==n]);
	}
	return ok[n][m];
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) puts(solve() ? "yes" : "no");
	return 0;
}
