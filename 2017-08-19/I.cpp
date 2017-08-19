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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
int T,r1,r2,n;
const db pi = acos(-1.);

db solve(int n,db r1,db r2){
	db r = 2 * r1;
	db d1 = r * r / (2 * r1);
	db d2 = r * r / (2 * r2);
	db R = abs(d1 - d2) / 2;
	db d = (d1 + d2) / 2;
	db res=0.,up=r*r*R,down=d*d-R*R;
	db Rp = up/down;
	res+=Rp*Rp;
	for(int i=2;i<=n;i+=2){
		int j=i>>1;
		db Rp = up/(down+4.*j*j*R*R);
		if(Rp<=1e-8) break;
		if(i==n) res+=Rp*Rp;
		else res+=2*Rp*Rp;
	}
	return pi*res;
}

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&r1,&r2);
		if(r1>r2) swap(r1,r2);
		scanf("%d",&n);
		printf("%.5f\n",solve(n,r1,r2) + 1e-9);
	}
	return 0;
}
