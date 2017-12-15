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
int l[3], a, b, c, w, h;
bool ok(int a, int b) {
	rep(i, 0, 2) {
		if (a <= w && b <= h) return true;
		swap(a, b);
	}
	return false;
}
bool gao() {
	int a = l[0], b = l[1], c = l[2];
	//rep(i, 0, 3) printf("%d%c", l[i], " \n"[i == 2]);
//	if (a == 3 && b == 2 && c == 1) {
	if (ok(a + 3 * b + c, a + c)) return true;
	if (ok(a + 2 * c    , 2 * b + 2 * c)) return true;
	if (ok(a + b + c    , 2 * b + 2 * c)) return true;
	if (ok(a + b + 2 * c, a + 2 * b)) return true;
	if (ok(a + b + 2 * c, a + b + c)) return true;
	return false;
}

void solve() {
	scanf("%d%d", &w, &h);
	l[0] = a; l[1] = b; l[2] = c;
	sort(l, l + 3);
	do {
		if (gao()) { puts("Yes"); return; }
	} while (next_permutation(l, l + 3));
	puts("No");
}
int main() {
	while (~scanf("%d%d%d", &a, &b, &c)) solve();
	return 0;
}
