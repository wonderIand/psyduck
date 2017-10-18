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
typedef __int128 T;
const int B = 1e9;
int n;
char str[100];
pair<T, T> read() {
	scanf(" 0.%s", str);
	T x = 0, y = 1;
	for (int i = 0; str[i]; ++i) {
		x = x * 10 + str[i] - '0';
		y *= 10;
	}
	return mp(x, y);
}
int cmp(const pair<T, T> &a, const pair<T, T> &b) {
	T x = a.fi * b.se - a.se * b.fi;
	return (x > 0) - (x < 0);
}
void solve(pair<T, T> x) {
	pair<T, T> L = mp(x.fi * 10 - 5, x.se * 10);
	pair<T, T> R = mp(x.fi * 10 + 5, x.se * 10);	
	int l1 = 0, r1 = 1;
	int l2 = 1, r2 = 1;	
	if (x.fi == 0) {
		cout << 0 << " " << 1 << endl;	
		return ;
	}
	while (true) {
		pair<T, T> m = mp(l1 + l2, r1 + r2);
		int c1 = cmp(m, L), c2 = cmp(m, R);
		if (0 <= c1 && c2 < 0) {
			cout << l1 + l2 << " " << r1 + r2 << endl;	

			return ;
		}
		if (c1 < 0) {
			// l1 = l1 + l2;
			// r1 = r1 + r2;
			int l = 1, r = (B - r1) / r2;
			while (l + 1 < r) {
				// System.out.println(l + " > " + r);
				int k = (l + r) >> 1;
				pair<T, T> v = mp(l1 + k * l2, r1 + k * r2);	
				if (cmp(v, x) <= 0) {
					l = k;
				} else {
					r = k;
				}
			}
			pair<T, T> v = mp(l1 + r * l2, r1 + r * r2);
			if (cmp(v, x) <= 0) {
				l1 = l1 + r * l2;
				r1 = r1 + r * r2;
			} else {
				l1 = l1 + l * l2;
				r1 = r1 + l * r2;
			}
			v = mp(l1, r1);
			if (0 <= cmp(v, L) && cmp(v, R) < 0) {
				cout << l1 << " " << r1 << endl;
				return ;
			}
		} else {
			// l2 = l1 + l2;
			// r2 = r1 + r2;
			int l = 1, r = (B - r2) / r1;
			while (l + 1 < r) {
				// System.out.println(l + " < " + r);
				int k = (l + r) >> 1;
				pair<T, T> v = mp(k * l1 + l2, k * r1 + r2);
				if (cmp(v, x) >= 0) {
					l = k;
				} else {
					r = k;
				}
			}
			pair<T, T> v = mp(r * l1 + l2, r * r1 + r2);
			if (cmp(v, x) >= 0) {
				l2 = l1 * r + l2;
				r2 = r1 * r + r2;
			} else {
				l2 = l1 * l + l2;
				r2 = r1 * l + r2;
			}
			v = mp(l2, r2);
			if (0 <= cmp(v, L) && cmp(v, R) < 0) {
				cout << l2 << " " << r2 << endl;
				return ;
			}
		}
	}	
}
int main() {
	scanf("%d", &n);
	rep(i, 0, n) {
		pair<T, T> x = read();
//		dd((ll)x.fi), de((ll)x.se);
		solve(x);
	}
	return 0;
}
