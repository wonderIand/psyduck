#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------

const int N = 110 , inf = 1e9;
int n , m , d[N] , f[N][N][N] , s[N];
inline void update(int &x,int d){
	x=max(x,d);
}

int main() {
	while(~scanf("%d%d",&n,&m)){
		rep(i,0,n) scanf("%d",d + i);
		s[1] = 0;
		rep(i,2,n+1) s[i]=s[i-1]+d[i-1];
		rep(i,0,n+1) rep(j,0,m+1) rep(k,0,m+1) f[i][j][k]=-inf;
		f[0][0][0] = 0;
		rep(i,0,n) rep(j,0,m+1) rep(k,0,m+1) if(f[i][j][k]!=-inf){
			// ->-> <-<-
			//cout<<i<<" "<<j<<" "<<k<<" "<<f[i][j][k]<<endl;
			update(f[i+1][j][k],f[i][j][k]);
			if(j)
				update(f[i+1][j+1][k] , f[i][j][k]);
			// -><-
			if(k>=1&&j+1<=m)
				update(f[i+1][j+1][k-1] , f[i][j][k] + d[0] + 2*s[i+1]);
			// <->-
			if(j+1<=m)
				update(f[i+1][j+1][k+1] , f[i][j][k] + d[0] - 2*s[i+1]);
		}
		printf("%d\n",f[n][m][0]);
	}
	return 0;
}
