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
int main() {

	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		int x; scanf("%d", &x);
		int len = 0; for (; x; x /= 10) len++;
		rep(i, 0, 233) {
			printf("1");
			rep(j, 1, len) printf("0");
		}
		printf("\n");
	}

	return 0;
}
