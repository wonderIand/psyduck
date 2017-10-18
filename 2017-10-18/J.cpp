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
const int N = 3e5 + 10 , inf = 1e9 + 7;
int a[N] , n , d , m;
map<pii,int> R[2] , O[2];
map<pii,pii> cnt;
map<pii,string> V;

void Update(map<pii,int>&Mp,pii x,int d){
	if(!Mp.count(x)) Mp[x] = d;
	else if(d < Mp[x]) Mp[x] = d;
}

int main() {
	scanf("%d%d",&n,&d);
	rep(i,1,d+1) scanf("%d",a + i);
	rep(i,1,d) {
		int x = a[i] , y = a[i+1];
		if(x > y) swap(x,y) , cnt[mp(x,y)].se++ , V[mp(x,y)]+=')';
		else cnt[mp(x,y)].fi++,V[mp(x,y)]+='(';
	}
	scanf("%d",&m);
	char op[10];
	rep(i,0,m){
		int s,t,cost;
		scanf("%d%d%s%d",&s,&t,op,&cost);
		int dir=0;
		if(s > t) swap(s,t),dir^=1;
		if(op[0] == 'R'){
			Update(R[dir] , mp(s , t) , cost);
		}
		Update(O[dir] , mp(s , t) , cost);
	}
	ll ans = 0;
	for(auto e : cnt){
		pii path = e.fi;
		int left = e.se.fi , right = e.se.se;
		int two = min(left , right);
		if(left > right) ans += 1ll * (left - right) * O[0][path];
		else ans += 1ll * (right - left) * O[1][path];
		string&s=V[path];
		int cost[2] = {inf,inf};
		rep(i,0,2) if(R[i].count(path)) cost[i]=R[i][path];
		//cout << path.fi << " " << path.se << " " << left << " " << right << " " << two << endl;
		if(cost[0]==inf&&cost[1]==inf){
			ans += 1ll * two * (O[0][path] + O[1][path]);
		} else{
			if(O[0].count(path) && O[1].count(path)){
				rep(i,0,2) cost[i] = min(cost[i] , O[0][path] + O[1][path]);
			}
			if(cost[1] < cost[0]){
				swap(cost[0] , cost[1]);
				rep(i,0,sz(s)) s[i]^='('^')';
			}
			//cout << s << endl;
			int match = 0 , rm = 0;
			rep(i,0,sz(s)){
				if(s[i] == '(') rm++;
				else if(rm) --rm , match++;
			}
			ans += 1ll * match * cost[0];
			if(cost[1] != inf) ans += 1ll * (two - match) * cost[1];
			else ans += 1ll * (two - match) * (O[0][path] + O[1][path]);
		}
		//de(ans);
	}
	printf("%lld\n",ans);
	return 0;
}
