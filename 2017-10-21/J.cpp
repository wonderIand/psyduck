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
const int N = 1e5 + 7;
char s[N];
bool solve() {
	int n = strlen(s);
	int cnt[2] = { 0, 0 };
	rep(i, 0, n)
		cnt[s[i] == 'W']++;
//	dd(cnt[0]), de(cnt[1]);
	return cnt[0] == cnt[1];
}
int main() {
	scanf(" %s", s);
	printf("%d", solve());
	return 0;
}
