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
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		int n; cin >> n;
		///work
		int base = 3;
		int len1 = 1;
		int len2 = 1;
		int ans = 4;
		for (int can = 2; can < n; base++, ans += 2) {
			if (len1 - 1 + can >= n) {
				ans++;
				break;
			}
			can += base - (base & 1);
			if (base & 1) len1++;
				else len2++;
		}
		///print
		printf("%d\n", ans);
	}


	return 0;
}
