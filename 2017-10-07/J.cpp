#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 10;
int sgn(ll x){return (x>0)-(x<0);}
struct P{
	ll x,y;
	P(){} P(ll x,ll y):x(x),y(y){}
	P operator - (const P&b) const {return P(x-b.x,y-b.y);}
	ll operator / (const P&b) const {return x*b.y-y*b.x;}
	bool operator < (const P&b) const {return x!=b.x?x<b.x:y<b.y;}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
}p[N] , ch[N];
int n;
int convex(P *p,int n,P *ch){
	sort(p , p + n); int m = 0;
	rep(i,0,n){
		while(m > 1 && sgn((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	} int k=m;
	per(i,0,n-1){
		while(m > k && sgn((ch[m - 1] - ch[m - 2]) / (p[i] - ch[m - 2])) <= 0) --m;
		ch[m++] = p[i];
	} if(n > 1) --m;
	return m;
}

int main() {
	while(~scanf("%d",&n)){
		if(n == 0) break;
		rep(i,0,n) p[i].read();
		int m = convex(p , n , ch);
		int a = 0 , b = 0;
		rep(i,0,m){
			int dx = abs(ch[i].x - ch[(i+1)%m].x);
			int dy = abs(ch[i].y - ch[(i+1)%m].y);
			a += abs(dx - dy);
			b += min(dx , dy);
		}
		printf("%d %d\n",a,b);
	}
	return 0;
}
