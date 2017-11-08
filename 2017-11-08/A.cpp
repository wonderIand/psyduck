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
string s;

int main() {
	cin >> s;
	int pos = s.find('*');
	int ans = 0;
	rep(i,0,pos) rep(j,pos+1,sz(s)){
		int left = 0;
		bool err = false;
		if(j - i + 1 < 3) continue;
		rep(k,i,j+1) {
			if(s[k] == '*') continue;
			if(s[k] == '(') left++;
			if(s[k] == ')'){
				if(left) left--;
				else {
					err = true;
					break;
				}
			}
			if(left == 0 && k != j) {
				err = true;
				break;
			}
		}
		if(!err && left == 0) ans ++;
	}
	cout << ans << endl;
	return 0;
}
