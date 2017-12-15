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
//#define LOCAL 1
const int N = 1e4 + 10;
int _even[N] , _odd[N] , even[N] , odd[N] , n;
int _L , _R , L , R;

int ask(int a,int b){
	printf("? %d %d\n",a,b);
	fflush(stdout);
#ifdef LOCAL
	printf("%d %c %d\n",_even[a],_even[a]>_odd[b]?'>':'<',_odd[b]);
	return _even[a] > _odd[b];
#else
	static char op[10];
	scanf("%s",op);
	return op[0] == '>';
#endif
}

void answer(){
	printf("!");
	rep(i,1,L+1) printf(" %d",even[i]);
	rep(i,1,R+1) printf(" %d",odd[i]);
	puts("");
	fflush(stdout);
#ifdef LOCAL
	bool ok = true;
	rep(i,1,L+1) ok &= _even[i] == even[i];
	rep(i,1,R+1) ok &= _odd[i] == odd[i];
	if(!ok) puts("BooooooM");
	else printf("Ok!");
#endif
}

int lft[N] , pos[N] , vis[N];

int main(){
#ifdef LOCAL
	n = 111;
	_L = n >> 1 , _R = n - _L;
	rep(i,1,_L+1) _even[i] = i * 2;
	rep(i,1,_R+1) _odd[i] = i * 2 - 1;
	srand(time(NULL));
	random_shuffle(_even + 1 , _even + 1 + _L);
	random_shuffle(_odd + 1 , _odd + 1 + _R);
	printf("!");
	rep(i,1,_L+1) printf(" %d",_even[i]);
	rep(i,1,_R+1) printf(" %d",_odd[i]);
	puts("");
#else
	scanf("%d",&n);
#endif
	L = n >> 1 , R = n - L;
	vi v;
	rep(i,1,L+1) v.pb(i);
	srand(time(NULL));
	random_shuffle(all(v));
	rep(i,1,R+1){
		lft[i] = 1;
		pos[i] = i;
	}
	for(int x : v) {
		int l = 0 , r = R + 1;
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			if(ask(x , pos[mid])) l = mid;
			else r = mid;
		}
		int t = lft[l];
		l=lower_bound(lft+1,lft+1+R,t)-lft;
		r=upper_bound(lft+1,lft+1+R,t)-lft-1;
		//printf("range = %d %d\n",l,r);
		if(r!=R) r = upper_bound(lft+1,lft+1+R,lft[r+1])-lft-1;
		//printf("range = %d %d\n",l,r);
		vector<pii> A , B;
		map<int,vi> Mp;
		int&ans=even[x]=(l-1)*2;
		rep(i,l,r+1) {
			bool big = ask(x , pos[i]);
			ans += big * 2;
			(big ? A : B).pb(mp(pos[i],lft[i]));
		}
		for(auto e : A) Mp[e.se].pb(e.fi);
		for(auto e : B) Mp[max(ans+1,e.se)].pb(e.fi);
		int cur=l;
		for(auto e : Mp) for(auto f : e.se) {
			lft[cur]=e.fi;
			pos[cur++]=f;
		}
		//rep(i,1,R+1) printf("%d%c",pos[i]," \n"[i==R]);
		//rep(i,1,R+1) printf("%d%c",lft[i]," \n"[i==R]);
	}
	rep(i,1,R+1) odd[pos[i]] = i * 2 - 1;
	answer();
	return 0;
}

