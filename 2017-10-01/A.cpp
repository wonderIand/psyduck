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
int n;
string s;

int main() {
	cin >> n;
	rep(i,0,n){
		cin >> s;
		string ans = "";
		for(int i=sz(s)-1;i>=0;i-=4){
			int t = 0;
			for(int j=i-3;j<=i;++j){
				t = t << 1 | (j >= 0 && s[j] == '1');
			}
			if(t <= 9) ans += char(t + '0');
			else ans += char('A' + t - 10);
		}
		reverse(all(ans));
		cout << ans << endl;
	}
	return 0;
}
