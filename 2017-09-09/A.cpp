#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
///-----------
int n, m;
bitset<52> pre[52], has[52];
int main()
{
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///init
		rep(i, 1, 51) pre[i].reset();
		rep(i, 1, 51) has[i].reset();
		///read
		cin >> n >> m;
		rep(i, 0, n) {
			int a, b; scanf("%d%d", &a, &b);
			pre[a][b] = 1;
		}
		rep(i, 0, m) {
			int a, b; scanf("%d%d", &a, &b);
			has[b][a] = 1;
		}
		///work
		rep(i, 1, 51) rep(j, 1, 51) {
			if ((pre[i] & has[j]).count() > 0)
			{
				printf("%d %d\n", i, j);
			}
		}
		printf("\n");
	}
			

	return 0;
}

