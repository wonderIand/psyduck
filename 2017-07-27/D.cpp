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

///----------------------------------------------

int main() {

	int tcase=0; scanf("%d",&tcase);
	rep(icase,0,tcase) {
		///read
		int n,m,p; scanf("%d%d%d",&n,&m,&p);
		///work
		int niv=0;
		for (int num=n*m-1, siz=0; num>p; num-=siz) {
			siz = (num-1)/p+1;
			int tmp = siz*(siz-1)/2*(p-1);
			niv^=(tmp&1);
		}
		puts(niv ? "NO" : "YES");
	}

	return 0;

}
