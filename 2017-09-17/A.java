import java.io.PrintWriter;
import java.math.BigDecimal;
import java.util.Scanner;

public class Main {
    
    Scanner in = null;
    PrintWriter out = null;
    
    public class P {
        BigDecimal x, y;
        P() {
        }
        P(BigDecimal x, BigDecimal y) {
            this.x = x;
            this.y = y;
        }
        P subtract(P p) {
            return new P(this.x.subtract(p.x), this.y.subtract(p.y));
        }
        BigDecimal norm() {
            return x.multiply(x).add(y.multiply(y));
        }
    }
    
    BigDecimal cross(P a, P b) {
        return a.x.multiply(b.y).subtract(a.y.multiply(b.x));
    }
    
    P outC(P A, P B, P C) {
        P b = B.subtract(A), c = C.subtract(A);
        BigDecimal dB = b.norm(), dC = c.norm(), d = cross(b, c).multiply(BigDecimal.valueOf(2));
        P t = new P(b.y.multiply(dC).subtract(c.y.multiply(dB)), c.x.multiply(dB).subtract(b.x.multiply(dC)));
        t.x = t.x.divide(d, 50, BigDecimal.ROUND_HALF_DOWN);
        t.y = t.y.divide(d, 50, BigDecimal.ROUND_HALF_DOWN);
        return A.subtract(t);
    }
    
    Main() throws Exception {
        in = new Scanner(System.in);
        out = new PrintWriter(System.out);

        BigDecimal EPS = BigDecimal.valueOf(1);
        for (int i = 0; i < 30; ++i)
            EPS = EPS.divide(BigDecimal.valueOf(10), 50, BigDecimal.ROUND_HALF_DOWN);
        
        int T = in.nextInt();
        for (int cas = 0; cas < T; ++cas) {
            P[] A = new P[4];
            for (int i = 0; i < 4; ++i) {
                A[i] = new P();
                A[i].x = BigDecimal.valueOf(in.nextLong());
                A[i].y = BigDecimal.valueOf(in.nextLong());
            }
            P O = outC(A[0], A[1], A[2]);
            BigDecimal d0 = (A[0].subtract(O)).norm(); 
            BigDecimal d3 = (A[3].subtract(O)).norm();
            if (d3.subtract(d0).subtract(EPS).compareTo(BigDecimal.ZERO) > 0) {
                out.println("Accepted");
            } else {
                out.println("Rejected");                
            }
        }
        
        in.close();out.close();
    }
    
    public static void main(String[] args) throws Exception {
        new Main();
    }
    
}
