#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define debug(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

const int MAX_N = 1e5 + 7;
const int MOD = 1e9 + 7;
///----------------------------------------------
inline void inc(int &x, int y) { if ((x += y) >= MOD) x-=MOD; }
inline void dec(int &x, int y) { if ((x -=y ) <   0 ) x+=MOD; }
//-----
int f[MAX_N];
int main() {
	
	for (int n,m; ~scanf("%d%d", &n, &m); ) {
		
		///init
		f[0]=1; memset(f+1, 0, (n<<1)*sizeof(int));
		rep(i,1,n<<1|1) {
			for (int j=1,w=1; w<=i; w+=3*j+1, j++) 
				if (j&1) inc(f[i], f[i-w]);
					else dec(f[i], f[i-w]);
			for (int j=1,w=2; w<=i; w+=3*j+2, j++)
				if (j&1) inc(f[i], f[i-w]);
					else dec(f[i], f[i-w]);
		}

		///read
		rep(i,1,n+1) {
			int a; scanf("%d",&a);
			ll w = 1ll * i * (a+1);
			per(j,w,n<<1|1) dec(f[j], f[j-w]);

		}
		for (int i=1,s=f[0]; i<=n; inc(s,f[i++])) 
			dec(f[n+i],s);
		int ans=0;
		for (int b; m--; ) {
			scanf("%d",&b);
			inc(ans,f[(n<<1)-b]);
		}
		static int icase=0;
		printf("Case #%d: %d\n", ++icase, ans);
		
	}
	

}
