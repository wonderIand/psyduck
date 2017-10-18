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
const int N = 1e6 + 10;
char s[N];
int num[N] , _;

int main() {
	scanf("%s",s);
	int len = strlen(s);
	per(i,0,len) if(s[i] == '1') num[len-1-i]++;
	_ = len;
	scanf("%s",s);
	len = strlen(s);
	per(i,0,len) if(s[i] == '1') num[len-1-i]++;
	_ = max(_ , len);
	rep(i,0,_){
		if(num[i] >= 2 && num[i+1] >= 2 && num[i+2] >= 1){
			int t = min(num[i] >> 1 , min(num[i+1] >> 1 , num[i+2]));
			num[i] -= t << 1;
			num[i+1] -= t << 1;
			num[i+2] -= t;
		}
		if(num[i] >= 2){
			int t = num[i] >> 1;
			num[i] &= 1;
			num[i + 2] += t;
			num[i + 3] += t;
			if(i + 4 >= _) _ = i + 4;
		}
	}
	while(_ > 1 && num[_-1] == 0) --_;
	per(i,0,_) putchar(num[i] + '0');
	puts("");
	return 0;
}
