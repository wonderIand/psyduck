#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
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
int l[] = {7 , 5 , 4 , 3 , 2 , 1 , 0 , 0 , 0 , 0};
int a;
vi v;


int main() {
	while(~scanf("%X",&a)) v.pb(a);
	for(int i=0,j=0,k=0;i<sz(v);){
		vector<int> num;
		for(j=i,k=j;j<sz(v);j=k+1){
			k = j;
			int times = 0 , a = v[k];
			bool err = false;
			if(a >> 7 & 1) {
				per(i,0,7) {
					if(a >> i & 1) times++;
					else break;
				}
				if(times > 5 || times == 0) err = true;
			}
			int mask = a & ((1 << l[times]) - 1);
			rep(i,0,times) {
				++k;
				if(k > sz(v)) err = true;
				else {
					if((v[k] >> 6) != 2) err = true;
					else mask = mask << 6 | (v[k] & ((1 << 6) - 1));
				}
			}
			if(!err) num.pb(mask);
			else {
				if(sz(num) >= 3){
					rep(t,0,sz(num)) printf("%X%c",num[t]," \n"[t + 1 == sz(num)]);
					num.clear();
					i = j;
				} else {
					++i;
				}
				break;
			}
		}
		if(sz(num)){
			if(sz(num) >= 3){
				rep(t,0,sz(num)) printf("%X%c",num[t]," \n"[t + 1 == sz(num)]);
				num.clear();
				i = j;
			} else ++i;
		}
	}
	return 0;
}
