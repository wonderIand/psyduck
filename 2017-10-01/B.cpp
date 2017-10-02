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
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 10;
int T , n;
string s[N];

int main() {
	cin >> T;
	rep(i,0,T){
		cin >> n;
		rep(i,0,n) cin >> s[i];
		int id = 0;
		rep(i,0,n) if(sz(s[i]) > sz(s[id])) id = i;
		bool ok = true;
		rep(i,0,n) {
			rep(j,0,sz(s[i])) ok &= s[i][j] == s[id][j];
			if(!ok) break;
		}
		if(!ok) cout << "Impossible" << endl;
		else cout << sz(s[id]) << endl;
	}
	return 0;
}
