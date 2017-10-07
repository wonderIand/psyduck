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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
int n;
db v(string s){
	if(s == "A") return 4.;
	if(s == "A-") return 3.7;
	if(s == "B+") return 3.3;
	if(s == "B") return 3;
	if(s == "B-") return 2.7;
	if(s == "C+") return 2.3;
	if(s == "C") return 2;
	if(s == "C-") return 1.7;
	if(s == "D") return 1.3;
	if(s == "D-") return 1.0;
	return 0;
}

int main() {
	while(cin >> n){
		int a , sum = 0;
		db up = 0;
		string s;
		rep(i,0,n){
			cin >> a >> s;
			if(s != "P" && s !=	"N"){
				sum += a;
				up += v(s) * a;
			}
		}
		if(sum == 0) printf("0.00\n");
		else printf("%.2f\n",1. * up / sum + 1e-8);
	}
	return 0;
}
