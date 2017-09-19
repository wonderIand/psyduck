#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define de(x) cout << #x << " => " << x << endl
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
const int N = 1e5 + 7;
///-----------
struct Tree {
	static const int N = ::N;
	int sum[N], n;
	int lowbit(int d) { return d & -d; }
	void init(int _n) { n = _n; rep(i, 0, n + 1) sum[i] = 0; }
	void add(int pos, int val) { pos++; for (; pos <= n; pos += lowbit(pos)) sum[pos] += val; }
	int query(int pos) { int ret = 0; for (; pos > 0; pos -= lowbit(pos)) ret += sum[pos]; return ret; }
	int query(int l, int r) {
		if (l > r) return 0;
		int ret = query(r);
		if (l - 1 > 0) ret -= query(l - 1);
		return ret;
	}
}	tree;
//-----
char str1[N]; int n1;
char str2[N]; int n2;
bool check(int pos) {
	if (pos < 0) return false;
	if (pos + n2 - 1 >= n1) return false;
	rep(i, 0, n2) if (str2[i] != str1[pos + i]) return false;
	return true;
}
int main()
{
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		int m; scanf("%d", &m);
		scanf(" %s", str1); n1 = strlen(str1);
		scanf(" %s", str2); n2 = strlen(str2);
		///prework
		tree.init(n1);
		rep(i, 0, n1 - n2 + 1)
			if (check(i)) tree.add(i, 1);
		///work
		rep(_m, 0, m) {
			char op; scanf(" %c", &op);
			if (op == 'Q') {
				int l, r; scanf("%d%d", &l, &r);
				if (l > r) swap(l, r);
				r = r - n2 + 1;
				printf("%d\n", tree.query(l, r));
			}
			else if (op == 'C') {
				int pos; char ch; scanf("%d %c", &pos, &ch); pos--;
				rep(i, pos - n2 + 1, pos + 1)
					if (check(i)) tree.add(i, -1);
				str1[pos] = ch;
				rep(i, pos - n2 + 1, pos + 1) 
					if (check(i)) {
					//	de(i);
						tree.add(i, 1);
					}
						
			}
		}
		printf("\n");
	}
		

	return 0;
}

