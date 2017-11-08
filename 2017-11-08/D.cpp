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
#define lb(x) ((x)&(-(x)))
const int N = 14;
int n , S;
db p[3][1 << N];
int a[1 << N];
db f[1 << N];

int main() {
	scanf("%d",&n);
	--n;
	scanf("%d",&S);
	rep(i,0,n){
		scanf("%d",a + (1 << i));
		rep(j,0,3) scanf("%lf",p[j] + (1 << i)) , p[j][1 << i] /= 100.;
	}
	rep(j,0,3) p[j][0] = 1.;
	rep(i,1,1<<n) {
		a[i] = max(a[i ^ lb(i)] , a[lb(i)]);
		rep(j,0,3) p[j][i] = p[j][i ^ lb(i)] * p[j][lb(i)];
	}
	f[0] = 1.;
	rep(i,1,1<<n) {
		db&best = f[i] = 0.;
		rep(j,0,3) {
			db tmp = 0. , tie = 1.;
			for(int k=i;k;k=(k-1)&i){
				db t = p[(j+2)%3][k] * p[j][k ^ i];
				tmp += t * f[k ^ i];
				tie -= t;
			}
			if(S > a[i]) {
				for(int k=i;k;k=(k-1)&i){
					db t = p[(j+1)%3][k] * p[j][k ^ i];
					tie -= t;
				}
				tmp += tie;
			}
			best = max(best , tmp);
		}
	}
	printf("%.16f\n",f[(1<<n)-1]);
	return 0;
}
