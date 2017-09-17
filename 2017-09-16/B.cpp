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
const int P = 1e9 + 7;
void pp(int &x,int d){if((x+=d)>=P)x-=P;}
typedef vector<vi> MM;
MM operator * (const MM a,const MM b){
	int L = sz(a);MM r(L , vi(L , 0));
	rep(i,0,L) rep(j,0,L) rep(k,0,L) pp(r[i][j] , 1ll * a[i][k] * b[k][j] % P);
	return r;
}

MM operator ^ (MM a,ll t){
	int L = sz(a);MM r(L,vi(L,0));
	rep(i,0,L) r[i][i] = 1;
	for(;t;t>>=1,a=a*a) if(t&1) r=r*a;
	return r;
}
int inverse(int a){return a == 1 ? 1 : P - ll(P/a)*inverse(P%a)%P;}

int main() {
	int T;
	cin >> T;
	rep(i,0,T){
		int p , q , K;
		cin >> q >> p >> K;
		MM A(2 , vi(2 , 0));
		p = 1ll * p * inverse(q) % P;
		A[0][1] = A[1][0] = p;
		p = (1 - p + P) % P;
		A[0][0] = A[1][1] = p;
		A = A ^ K;
		cout << A[0][0] << endl;
	}
	return 0;
}
