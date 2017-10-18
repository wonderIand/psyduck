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
bool ask(int id1, int id2) {
	printf("? %d %d\n", id1, id2);
	fflush(stdout);
	int ret; scanf("%d", &ret);
	return ret;
}
const int N = 5e2 + 7;
int dig[N], tmp[N], n;
void gao(int l, int r) {
	if (l >= r) return;
	int mid = l + (rand() % (r - l + 1));
	int ll = l, rr = r;
	rep(i, l, r + 1) if (i != mid)
		if (ask(dig[mid], dig[i])) tmp[rr--] = dig[i];
			else tmp[ll++] = dig[i];
	assert(ll == rr);
	tmp[ll] = dig[mid];
	rep(i, l, r + 1) dig[i] = tmp[i];
	gao(l, ll - 1);
	gao(ll + 1, r);
}
int main() {
	
	srand((unsigned)time(0));
	scanf("%d", &n);
	rep(i, 1, n + 1) dig[i] = i;
	gao(1, n);
	bool yes = !ask(dig[n], dig[1]);
	printf("! "); puts(yes ? "YES" : "NO");
	if (!yes) printf("%d ", n);
	rep(i, 1, n + 1) printf("%d%c", dig[i], " \n"[i == n]); 
	fflush(stdout);
	return 0;
}
