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
const int N = 12;
int a[N] , b[N] , n;
ll f[1<<N];

int main() {
	cin >> n;
	rep(i,0,n) cin >> a[i];
	rep(i,0,n) cin >> b[i];
	f[0] = 1;
	rep(i,0,n) per(j,0,1<<n) if(f[j]){
		rep(k,0,n) if(~j >> k & 1 && b[k] >= a[i])
			f[j | 1 << k] += f[j];
	}
	cout << f[(1<<n)-1] << endl;
	return 0;
}
