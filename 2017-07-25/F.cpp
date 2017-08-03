#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
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
bool visa[MAX_N];
bool visb[MAX_N];
int a[MAX_N];
int b[MAX_N];
int main() {

	for (int n,m; ~scanf("%d%d",&n,&m); ) {
		
		///read
		rep(i,0,n) scanf("%d",&a[i]);
		rep(i,0,m) scanf("%d",&b[i]);
		
		///
		map<int,int> M;
		rep(i,0,n) visa[i]=false;
		rep(i,0,m) visb[i]=false;
		rep(i,0,m) if (!visb[i]) {
			int siz=0;
			for (int u=i; !visb[u]; u=b[u]) siz++,visb[u]=true;
			M[siz]+=siz;
		}
		int ans=1;
		rep(i,0,n) if (!visa[i]) {
			int siz=0; for (int u=i; !visa[u]; u=a[u]) siz++,visa[u]=true;
			int tmp=0;
			for (int j=1; j*j<=siz; j++) if (siz%j==0) {
				tmp=(tmp+M[j])%MOD;
				if (j*j<siz)
					tmp=(tmp+M[siz/j])%MOD;
			}
			ans=1ll*ans*tmp%MOD;
		}

		///
		static int icase=0;
		printf("Case #%d: %d\n",++icase,ans); 

	}

}
