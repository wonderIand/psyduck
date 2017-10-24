/*
 *   Generate all strings for a given n that use the first n letters of
 *   the alphabet with a used once, b used twice, etc., and that don't
 *   have consecutive identical letters.
 */
#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;
const int MAXN = 30 ;
const int MAXSUM = MAXN * (MAXN + 1) / 2 ;
int n ;
int sum ;
long long ii ;
char str[MAXSUM+1] ;
int used[MAXN] ;
long long cnt ;
unsigned long long mpow[MAXN] ;

typedef pair<int, unsigned long long> keytype ;
map<keytype, unsigned long long> increment ;
long long target ;
char seen = 0 ;

///0, 27, 0, 0, 0
void recur(int at, int prev, int powsum, int distinct, unsigned long long cnts) {
   if (cnt > target)
      return ;
   if (at == sum) {
      if (powsum + n + 2 == (2 << n) && distinct == n) {
         cnt++ ;
         if (cnt == target) {
            cout << str << endl ;
            seen = 1 ;
         }
      }
      return ;
   }
   keytype key = make_pair(at * 100 + used[prev], cnts) ;
   if (increment.find(key) != increment.end()) {
      unsigned long long inc = increment[key] ;
      if (inc + cnt < target) {
         cnt += increment[key] ;
         return ;
      }
   }

   unsigned long long ocnt = cnt ;
   for (int i=0; i<26; i++)
      if (i != prev) {
         int u = used[i] ;
         if (powsum + (1 << u) + n + 2 <= (2 << n) && (u || distinct < n)) {
            str[at] = 'a' + i ;
            used[i]++ ;
            recur(at+1, i, powsum + (1 << u), distinct + (u == 0),
                  cnts + mpow[u]) ;
            used[i]-- ;
         }
      }
   increment[key] = cnt - ocnt ;


}
int main(int argc, char *argv[]) {
freopen("xx.in", "r", stdin);
   cin >> n >> target ;
   sum = n * (n + 1) / 2 ;
   mpow[0] = 1 ;
   for (int i=0; i<n; i++)
      mpow[i+1] = ((unsigned long long)(n+1)) * mpow[i] ;
   recur(0, 27, 0, 0, 0) ;
   if (!seen)
      cout << -1 << endl ;
}
