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
const int N = 1e3 + 7;
int n, a[N];
int main() {
	while (~scanf("%d", &n)) {
		if (n == 0) break;
		int sum = 0;
		rep(i, 0, n) {
			int x;
			scanf("%d", &x);
			sum += x * x;
		}
		printf("%d\n", sum);
	}

	return 0;
}
