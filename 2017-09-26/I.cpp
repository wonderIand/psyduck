#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define de(x) cout << #x << " => " << x << endl
#define local 1
using namespace std;
const int N = 50 + 7;
int n, m;
int arr[1000][N][N];
//--------------------
int _ = 1;
int id[N][N];
int swap_rows(int _id, int _row1, int _row2) { return printf("swap_rows %d %d %d\n", _id, _row1, _row2), ++_; }
int swap_columns(int _id, int _col1, int _col2) { return printf("swap_columns %d %d %d\n", _id, _col1, _col2), ++_; }
int sum(int _id1, int _id2) { return printf("+ %d %d\n", _id1, _id2), ++_; }
void answer(int _id) { printf("answer %d", _id); };
//------
int main() {

    freopen("tables-puzzle.in", "r", stdin);
    freopen("tables-puzzle.out", "w", stdout);

    ///read
    scanf("%d%d", &n, &m);

    ///prework
    id[1][1] = 0;
    rep(row, 2, n + 1) id[row][1] = swap_rows(id[1][1], 1, row);
    rep(row, 1, n + 1) rep(col, 2, n + 1)
        id[row][col] = swap_columns(id[row][col - 1], col - 1, col + 1);

    ///work
    int pre_ans = 1;
    rep(row, 1, n + 1) {
        per(col, 1, row + 1) {
            int tmp1 = sum(id[row][col], pre_ans);
            int tmp2 = swap_columns(tmp1, col, col + 1);
            pre_ans = sum(pre_ans, tmp2);
        }
    }

    ///print
    answer(pre_ans);

    return 0;
}
