#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
int main() {
	
	int tcase=0; scanf("%d",&tcase);
	rep(icase,0,tcase) {
		///read
		int n; cin>>n;
		int num1=0;
		rep(i,0,n) {
			int dig; scanf("%d",&dig),num1+=(dig&1);
		}
		///
		printf("%d %d\n",2, num1*2>=n ? 1 : 0);
	}
	return 0;
}
