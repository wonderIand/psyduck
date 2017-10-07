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
set<string> S;
string F(string str) {
	rep(i, 0, sz(str)) if (str[i] == '1') {
		str = str.substr(i, sz(str) - i) + str.substr(0, i);
		break;
	}
	return str;
}
string rev(string str, int x) {	
	stringstream ss;
	ss << str[x + 3] << str[x + 2] << str[x + 1] << str[x];
	return str.substr(0, x) + ss.str() + str.substr(x + 4);

	int n = sz(str);
	str = str + str;
	str = str.substr(0, x) + ss.str() + str.substr(x + 4);
	return str.substr(x, n);
}
void gao(string STR) {	
	queue<string> que;
	S.insert(STR), que.push(STR);
	vector<string> ret;
	while (!que.empty()) {
		string str = que.front();	
		if (str[0] == '1' && str[1] == '2')
			de(str);
		que.pop();
		rep(i, 0, sz(str) - 3) {
			string nstr = rev(str, i);
//			dd(i), dd(str), de(nstr);
			if (!S.count(nstr)) {
				S.insert(nstr), que.push(nstr);
			}
		}
	}
	sort(all(ret));
	ret.erase(unique(all(ret)), ret.end());
	de(sz(ret));
}
int main() {
	gao("123456");

	return 0;
}
