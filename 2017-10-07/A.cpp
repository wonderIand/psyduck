#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
using namespace std;
typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;

///---------------------------------------------------------------------------------
int n, m, k;
int main() {

	for (; ~scanf("%d%d%d", &n, &m, &k) && n; ) {
		int ned = n / 2 + 1;
		int mid = n - m - k;
		if (m >= ned) { puts("0"); continue; }
		if (m + mid < ned) puts("-1");
			else printf("%d\n", ned - m);
	}


	return 0;

}
