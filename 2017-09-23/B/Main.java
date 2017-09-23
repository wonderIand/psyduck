 import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	Scanner in = null;
	PrintWriter out = null;
	
	BigInteger C(int n, int m) {
		if (n < 0 || m < 0 || n < m) return BigInteger.ZERO;
		BigInteger ret = BigInteger.ONE;
		for (int i = 0; i < m; ++i)
			ret = ret.multiply(BigInteger.valueOf(n - i));
		for (int i = 0; i < m; ++i)
			ret = ret.divide(BigInteger.valueOf(i + 1));
		return ret;
	}
	
	Main() throws Exception {
		in = new Scanner(System.in);
		out = new PrintWriter(System.out);
		
		int T = in.nextInt();
		int[] a = new int[101010];
		int[] b = new int[101010];
		for (int cas = 0; cas < T; ++cas) {
			int n = in.nextInt();
			for (int i = 1; i <= n; ++i) {
				a[i] = 0;				
			}
			boolean same = false;
			for (int i = 1; i <= n; ++i) {
				b[i] = in.nextInt();
				if (a[b[i]] != 0)
					same = true;
				a[b[i]] = i;
			}
			a[n + 1] = 0;
			int cnt = 25;
			for (int i = 2; i <= n; ++i) {
				if (a[b[i] + 1] < a[b[i - 1] + 1]) {
					--cnt;
				}
			}
			if (same || cnt < 0) {
				out.println("0");
				continue;
			}
			BigInteger ans = BigInteger.ZERO;
			for (int i = 0; i <= cnt; ++i) {
				ans = ans.add(C(n - 1 - (25 - cnt), i).
						multiply(C(26, cnt - i)));
			}
			out.println(ans);
		}		
		in.close();out.close();
	}
	
	public static void main(String[] args) throws Exception {
		new Main();
	}
	
}

