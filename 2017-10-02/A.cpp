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
const int N = 1e5 + 10;
int n;
__int128 l , r , a , b , p[N] , lft[N + N] , white[N + N] , _;

int main() {
	while(~scanf("%d",&n)){
		unsigned long long x , y;
		scanf("%llu%llu",&x,&y);
		l = x , r = y;
		scanf("%llu%llu",&x,&y);
		a = x , b = y;
		b = a - b;
		rep(i,0,n) {
			scanf("%llu",&x);
			p[i] = x;
		}
		if(b == 0) {
			printf("0\n");
			continue;
		}
		_ = 0;
		lft[_++] = l;
		lft[_++] = r - b + 1;
		rep(i,0,n) {
			if(p[i] <= r - b)
				lft[_++] = p[i] + 1;
			if(p[i] - b >= l - 1)
				lft[_++] = p[i] - b + 1;
		}
		sort(lft , lft + _);
		_ = unique(lft , lft + _) - lft;
		for(int i=0,l=0,r=0;i<_;++i){
			for(;r<n&&p[r]<=lft[i]+b-1;++r);
			for(;l<r&&p[l]<lft[i];++l);
			white[i] = r - l;
		}
		multiset<int> S;
		int Max = 0;
		for(int i=0,l=0,r=0;i<_;++i){
			if(lft[i] - 1 > ::r - a) break;
			for(;r<_&&lft[r]+b-1<=lft[i]+a-1;++r){
				S.insert(white[r]);
			}
			for(;l<r&&lft[l]<lft[i];++l){
				S.erase(S.lower_bound(white[l]));
			}
			Max = max(Max , *S.begin());
		}
		printf("%d\n",Max);
	}
	return 0;
}
