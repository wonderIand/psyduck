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
const int N = 1e5 + 10 , inf = 1e8;
int n , a[N];
int Min[N << 2] , Add[N << 2] , id[N << 2];
void Update(int c){
	if(Min[c << 1] <= Min[c << 1 | 1])
		Min[c] = Min[c << 1] , id[c] = id[c << 1];
	else 
		Min[c] = Min[c << 1 | 1] , id[c] = id[c << 1 | 1];
	Min[c] += Add[c];
}
void build(int c,int l,int r){
	Add[c] = 0;
	if(l == r) {
		Min[c] = a[l];
		id[c] = l;
	} else {
		int m = (l + r) >> 1;
		build(c << 1 , l , m);
		build(c << 1 | 1 , m + 1 , r);
		Update(c);
	}
}
void add(int c,int l,int r,int L,int R,int d){
	if(L > R) return ;
	if(L <= l && r <= R){
		Min[c] += d;
		Add[c] += d;
	} else {
		int m = (l + r) >> 1;
		if(L <= m) add(c << 1 , l , m , L , R , d);
		if(R > m) add(c << 1 | 1 , m + 1 , r , L , R , d);
		Update(c);
	}
}

int main() {
	while(~scanf("%d",&n)){
		if(n == 0) break;
		rep(i,1,n+1) scanf("%d",a + i);
		build(1 , 1 , n);
		vi neg , ans;
		bool err = 0;
		int j = 0;
		rep(i,0,n){
			int Min = ::Min[1] , id = ::id[1];
			if(Min < 0) {
				err = 1;
				break;
			}
			while(Min > 0 && j < sz(neg)){
				add(1 , 1 , n , neg[j] + 1 , n , -1);
				Min = ::Min[1] , id = ::id[1];
				ans.pb(-neg[j]);
				++j;
			}
			if(Min > 0){
				err = 1;
				break;
			} else {
				add(1 , 1 , n , 1 , id - 1 , -1);
				add(1 , 1 , n , id , id , inf);
				ans.pb(id);
				neg.pb(id);
			}
		}
		for(;j<sz(neg);++j) ans.pb(-neg[j]);
		if(err) puts("Impossible");
		else {
			reverse(all(ans));
			rep(i,0,sz(ans)) printf("%d ",ans[i]);
			puts("");
		}
	}
	return 0;
}
