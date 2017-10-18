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
#define de(x) cout << #x << " = " << x << ebdl
//-------
int main() {
	string str;
	getline(cin, str);
	int cnt = 0;
	rep(i, 0, sz(str)) cnt += str[i] == '!';
	if (!cnt) {
		cout << "Pfff";
	} else {
		cout << "W";
		rep(i, 0, cnt) cout << "o";
		cout << "w";
	}


	return 0;
}
