#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
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

const int MAX_N = 1e7 + 7;
unsigned tab[MAX_N];
///----------------------------------------------
unsigned x, y, z;
unsigned rng61() {
	static unsigned t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;
	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;
	return z;
}
///-----
map<int,unsigned> ans;
void work(int l,int r,vector<int> &hv) {
	///prework
	int piv = l + rand()%(r-l+1);
	swap(tab[l], tab[piv]);
	int mid = l;
	rep(i,l+1,r+1) if (tab[i] <= tab[l]) {
		swap(tab[++mid],tab[i]);
	}
	swap(tab[l], tab[mid]);
	///work
	for (; !hv.empty(); ) {
		if (hv.back()<l) return;
		if (hv.back()<mid) work(l,mid-1,hv); else 
		if (hv.back()>mid) work(mid+1,r,hv); else {
			ans[hv.back()] = tab[mid];
			hv.pop_back();
		}
	}
}	
///-----
int qry[200];
int main() {	
	
	for (int n,m; ~scanf("%d%d",&n,&m); ) {
			
		///read
		cin>>x>>y>>z;
		rep(i,0,n) tab[i]=rng61();
		
		///prework
		rep(_m,0,m) scanf("%d",&qry[_m]);
		vector<int> v;
		rep(_m,0,m) v.pb(qry[_m]);
		sort(all(v));
		v.erase(unique(all(v)),v.end());
		
		///work
		ans.clear();
		work(0,n-1,v);
		static int icase=0;
		printf("Case #%d:", ++icase);
		rep(_m,0,m) cout << " " << ans[qry[_m]];
		cout << endl;
	
	}


}
