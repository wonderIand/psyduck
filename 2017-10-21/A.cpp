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
const int N = 307;
int n;
string s[N];
int a[N * N] , b[N * N] , need[N] , pl[N];
vi A , B;

void solve(vi id,int *f,int type){
	if(type == 1){
		for(int i : id){
			string&s=::s[i];
			reverse(all(s));
			rep(i,0,sz(s)) s[i] ^= '('^')';
		}
	}
	for(int i : id){
		int left = 0 , rm = 0;
		string&s = :: s[i];
		rep(i,0,sz(s)){
			if(s[i] == ')'){
				if(rm) --rm;
				else left++;
			} else rm++;
		}
		need[i] = left , pl[i] = rm - left;
	}
	sort(all(id) , [&](int a,int b){return need[a] < need[b];});
	int tot = N * N;
	rep(i,0,tot) f[i] = -1;
	f[0] = 0;
	for(int i : id){
		int tot = N * N;
		per(j,0,tot) if(j - need[i] >= 0 && f[j] != -1)
			f[j + pl[i]] = max(f[j + pl[i]] , f[j] + sz(s[i]));
	}
}
int main() {
	cin >> n;
	rep(i,0,n) {
		cin >> s[i];
		int cnt = 0;
		for(auto e : s[i])
			if(e == '(') cnt++;
			else cnt--;
		if(cnt >= 0) A.pb(i);
		else B.pb(i);
	}
	solve(A , a , 0);
	solve(B , b , 1);
	int ans = 0;
	rep(i,0,N*N) if(a[i] >= 0 && b[i] >= 0)
		ans = max(ans , a[i] + b[i]);
	cout << ans << endl;
	return 0;
}
