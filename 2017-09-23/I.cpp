#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define fi frist
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
const int N = (1 << 17) + 10 , inf = 1 << 30;
int T , n , a[N];
int Max[N << 2] , Min[N << 2] , ABSMin[N << 2];

void ins(int c,int l,int r,int pos,int x){
	if(l == r){
		Max[c] = Min[c] = x;
		ABSMin[c] = abs(x);
	} else {
		int m = (l + r) >> 1;
		if(pos <= m) ins(c << 1 , l , m , pos , x);
		else ins(c << 1 | 1 , m + 1 , r , pos , x);
		Max[c] = max(Max[c << 1] , Max[c << 1 | 1]);
		Min[c] = min(Min[c << 1] , Min[c << 1 | 1]);
		ABSMin[c] = min(ABSMin[c << 1] , ABSMin[c << 1 | 1]);
	}
}

int A , B , C;
void query(int c,int l,int r,int L,int R){
	if(L <= l && r <= R){
		A = max(A , Max[c]);
		B = min(B , Min[c]);
		C = min(C , ABSMin[c]);
	} else {
		int m = (l + r) >> 1;
		if(L <= m) query(c << 1 , l , m , L , R);
		if(R > m) query(c << 1 | 1 , m + 1 , r , L , R);
	}
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) {
		scanf("%d",&n);
		n = 1 << n;
		rep(i,1,n+1) scanf("%d",a + i);
		rep(i,1,n+1) ins(1 , 1 , n , i , a[i]);
		int m;
		scanf("%d",&m);
		int op , l , r;
		rep(i,0,m){
			scanf("%d%d%d",&op,&l,&r);
			if(op == 1){
				++l,++r;
				A = -inf , B = C = inf;
				query(1 , 1 , n , l , r);
				ll ans = min(1ll * C * C , 1ll * A * B);
				printf("%lld\n",ans);
			} else {
				++l;
				ins(1 , 1 , n , l , r);
			}
		}
	}
	return 0;
}
