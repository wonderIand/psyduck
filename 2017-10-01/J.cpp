#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 10;
int T,n;
db L;
pair<db,db> ele[N];

int main() {
	cin >> T;
	rep(i,0,T){
		cin >> n >> L;
		L *= 1000;
		rep(i,0,n) cin >> ele[i].fi >> ele[i].se , ele[i].se /= 1000000;
		sort(ele , ele + n);
		reverse(ele , ele + n);
		db dis = 0 , tm = 0 , v = 0;
		rep(i,0,n) {
			if(dis >= L) break;
			db a = ele[i].fi , t = ele[i].se;
			db nv = v + a * t;
			db del = (nv * nv - v * v) / (2 * a);
			if(dis + del > L) {
				nv = sqrtl(2 * a * (L - dis) + v * v);
				tm += (nv - v) / a;
				dis = L;
			} else {
				dis += del;
				tm += t;
				v = nv;
			}
		}
		if(dis < L) tm += (L - dis) / v;
		printf("%.16f\n",(double)tm);
	}
	return 0;
}
