#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
using namespace std;
typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;

///---------------------------------------------------------------------------------
int n;
char str[100];
bool isdig(char ch) { return ch >= '1' && ch <= '9'; }
bool ok(char str[]) {
	rep(i, 0, 8) if (i != 4 && isdig(str[i]) == false) return false;
	if (str[4] < 'A' || str[4] > 'Z') return false;
	if (str[0] != str[1]) return false;
	return true;
}
int main() {

	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0 , tcase) {
		///read
		scanf(" %s", str); n = strlen(str);
		///work
		if (ok(str)) puts(str);
	}



	return 0;

}
