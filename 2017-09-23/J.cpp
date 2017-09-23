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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
string a , b;
int K;
queue<pair<string,int> > Q;

int TS, ts[1 << 21][8];
bool inq[1 << 21][8];
int dis[1 << 21][8];

int encode(string &s) {
	int ret = 0;
	rep(i, 0, 7) {
		if (i >= sz(s)) {
			ret = ret << 3;
		} else {
			ret = (ret << 3) | (s[i] - 'a' + 1);
		}
	}
	return ret;
}

string decode(int val) {
}

void ins(string &s,int K,int d){
	int c = encode(s);
	if (ts[c][K] != TS)
		ts[c][K] = TS, dis[c][K] = INT_MAX, inq[c][K] = false;
	if (dis[c][K] > d) {
		dis[c][K] = d;
		if (!inq[c][K])
			inq[c][K] = true, Q.push(mp(s, K));
	}
}

int main() {
	while(cin >> a >> K >> b){	
		++TS;
		while(sz(Q)) Q.pop();
		ins(a , K , 0);
		int ans = -1;
		while(sz(Q)) {
			string s = Q.front().fi;int K = Q.front().se;
			int c = encode(s);
			int d = dis[c][K];Q.pop();
			inq[c][K] = false;
			if (~ans && d >= ans) continue;
			if(s == b) {
				if (ans == -1 || ans > d)
					ans = d;
			}
			if(K != 0) ins(s , K - 1 , d + 1);
			if(K != sz(s)) ins(s , K + 1 , d + 1);
			if(K != 0) {
				string ns = "";
				rep(i,0,sz(s)) if(i != K - 1) ns += s[i];
				ins(ns , K - 1, d + 2);
			}
			if(K != sz(s)){
				string ns = "";
				rep(i,0,sz(s)) if(i != K) ns += s[i];
				ins(ns , K , d + 2);
			}
			int mask = 0;
			rep(i,0,sz(s)) mask |= 1 << (s[i] - 'a');
			rep(i,0,7) if(~mask >> i & 1) {
				string ns = "";
				rep(j,0,K) ns += s[j];
				ns += string(1 , 'a' + i);
				rep(j,K,sz(s)) ns += s[j];
				ins(ns , K + 1 , d + 2);
			}
		}
		if (~ans) {
			printf("%d.%d\n",ans >> 1 , (ans & 1) * 5);
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}

