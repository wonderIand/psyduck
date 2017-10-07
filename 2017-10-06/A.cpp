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
int T,n;
char s[12345];

int main() {
	while(1);
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d",&n);
		scanf("%s",s);
		int sum = 0 , cnt = 0;
		rep(i,0,n){
			if(sum == 0 && s[i] == ')')
				++cnt , s[i] = '(';
			sum += s[i] == '(' ? 1 : -1;
		}
		cnt += sum / 2;
		printf("%d\n",cnt);
	}
	return 0;
}
