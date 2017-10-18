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
const int N = 1e5 + 10;
int p[N] , q[N] , vis[N] , in[N] , n , x[N];

int main() {
	scanf("%d",&n);
	int A = 0 , B = 0;
	rep(i,1,n+1) scanf("%d",p + i);
	rep(i,1,n+1) scanf("%d",q + i) , in[q[i]]++ , B += q[i] == 0;
	int need = 0;
	rep(i,1,n+1) if(!vis[i]){
		int _ = 0 , rm = 0;
		for(int c=i;c;c=p[c]) vis[c]=1,x[_++]=c;
		if(!in[i]) {
			for(int t=0,c=i;c&&t<_&&x[t]==c;++t,c=q[c])
				rm++;
			A += min(_ , 1 + (_ - rm));
			need += _ - rm;
		} else need += _ - 1 , A += _;
	}
	printf("%d\n",need + A - B);
	return 0;
}
