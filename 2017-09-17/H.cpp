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
string str[] = {
	"rat", "ox", "tiger", "rabbit", "dragon", "snake", "horse", "sheep", "monkey", "rooster", "dog", "pig"
};
string s1, s2;
int get(const string &s) {
	rep(i, 0, 12) if (s == str[i]) return i;
	return -1;
}
int solve() {
	int x = get(s1), y = get(s2);
	int d = y - x;
	if (d <= 0) d += 12;
	return d;
}
int main() {
	int T;
	cin >> T;
	rep(cas, 0, T) {
		cin >> s1 >> s2;
		cout << solve() << endl;
	}
	return 0;
}
