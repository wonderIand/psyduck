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
const int N = 100;
const db pi = acos(-1.);
char s[N];
int n;

db cal(char ch,int num){
	if(num == 0){
		if(ch == 'S') return 2;
		else return pi / 2;
	} else {
		if(ch == 'S'){
			db res = num + 2;
			db x = num - 0.5;
			db y = 1 - sqrt(3.) / 2;
			res += sqrt(x * x + y * y);
			return res;
		} else {
			db res = num + 1.5;
			db x = num;
			db y = sqrt(3.) / 2 - 0.5;
			db d = sqrt(x * x + y * y);
			db p = sqrt(x * x + y * y - 0.5 * 0.5);
			res += p;
			db th = acos(0.5 / d);
			db th2 = atan(x / y);
			th2 = pi - th2;
			th = th2 - th;
			th = pi / 2 - asin(y / d) - acos((0.5 * 0.5 + d * d - p * p) / d);
			res += th * 0.5;
			return res;
		}
	}
}

int main() {
	scanf("%d%s",&n,s+1);
	int left = n + 1 , right = 0;
	rep(i,1,n+1) if(s[i] != 'T')
		left = min(left , i) , right = max(right , i);
	db ans;
	if(left == n + 1){
		ans = n + n + 1;
	} else {
		ans = (right - left) * 2;
		ans += cal(s[left] , left - 1);
		ans += cal(s[right] , n - right);
	}
	printf("%.16f\n",ans);
	return 0;
}
