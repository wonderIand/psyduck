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
const int N = 2e5 + 10;
int n , K , Q , a[N] , cnt[N] , sum , del , on[N];
map<int,int> c[N];
vector<pii> out[N];
int in[N];

int main() {
	scanf("%d%d%d",&n,&K,&Q);
	rep(i,0,n) scanf("%d",a + i);
	for(int i=0,j=0;i<n;i=j){
		for(j=i;j<n&&a[i]==a[j];++j);
		cnt[a[i]]++;
	}
	rep(i,1,n) {
		int x = a[i-1] , y = a[i];
		if(x == y) continue;
		c[x][y]++;
		c[y][x]++;
	}
	rep(i,1,K+1) {
		pii x = mp(sz(c[i]) , i);
		for(auto e : c[i]) {
			if(x < mp(sz(c[e.fi]) , e.fi))
				out[i].pb({e.fi , e.se});
		}
	}
	rep(i,0,Q){
		int x;
		scanf("%d",&x);
		if(on[x]) {
			sum -= cnt[x];
			for(auto e : out[x]){
				if(on[e.fi]) del -= e.se;
				in[e.fi] -= e.se;
			}
			del -= in[x];
		} else {
			sum += cnt[x];
			for(auto e : out[x]){
				if(on[e.fi]) del += e.se;
				in[e.fi] += e.se;
			}
			del += in[x];
		}
		on[x] ^= 1;
		printf("%d\n",sum - del);
	}
	return 0;
}
