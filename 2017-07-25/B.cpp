#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1; i>=(l); --i)
#define debug(x) cout << #x << " = " << x << endl
typedef pair<int,int> pii;
const int MOD = 1000000000 + 7;
//-------
pair<vector<pii>,int> tab[26];

int tmp[26][200000];
int tmpn[26];
bool cmp(pair<vector<pii>,int> &a, pair<vector<pii>,int> &b) {
    int min_sz = min(sz(a.fi), sz(b.fi));
    rep(i,0,min_sz)
    if (a.fi[i].fi != b.fi[i].fi) {
        return a.fi[i].fi > b.fi[i].fi;
    }
    else if (a.fi[i].se != b.fi[i].se) {
        return a.fi[i].se > b.fi[i].se;
    }
    return sz(a.fi) > sz(b.fi);
}
bool can0[30];
char str[200000];
int main() {
    for(int n,icase=0; ~scanf("%d",&n); ) {
        ///init
        rep(i,0,26) can0[i]=true; int can0_sz=26;
        ///read
        rep(i,0,26) tmpn[i]=0;
        rep(i,0,n) {
            scanf(" %s",str); int len=strlen(str);
            reverse(str,str+len);
            if (len>1) {
                can0_sz-=can0[str[len-1]-'a'];
                can0[str[len-1]-'a']=false;
            }
            rep(j,0,len) {
                tmpn[str[j]-'a']=max(tmpn[str[j]-'a'],j+1);
                tmp[str[j]-'a'][j]++;
            }
        }
        ///prework
        rep(i,0,26) tab[i].fi.clear(),tab[i].se=i;
        rep(i,0,26) {
            rep(j,0,tmpn[i]) if (tmp[i][j]>=26) {
                tmp[i][j+1]+=tmp[i][j]/26;
                tmp[i][j]%=26;
                if (j+1>=tmpn[i]) tmpn[i]++;
            }
            per(j,0,tmpn[i]) if (tmp[i][j]>0) {
                tab[i].fi.pb(mp(j,tmp[i][j]));
                tmp[i][j]=0;
            }
        }
        sort(tab,tab+26,cmp);
        ///work
        int ans=0;
        int val=25;
        rep(i,0,26) if (sz(tab[i].fi)) {
            if (can0_sz==1 && can0[tab[i].se]) {
                can0_sz=0; continue;
            }
            if (can0[tab[i].se]) can0_sz--;
            int tmp=1, pre=0;
            per(j,0,sz(tab[i].fi)) {
                for (; pre<tab[i].fi[j].fi; pre++) tmp=1ll*tmp*26%MOD;
                ans=(ans+1ll*tab[i].fi[j].se*tmp%MOD*val%MOD)%MOD;
            }
            val--;
        }
        printf("Case #%d: %d\n",++icase, ans);


    }



    return 0;
}
