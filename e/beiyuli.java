import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;

public class Main
{
    public static void main(String args[])
    {
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        
        int T = cin.nextInt();
        int cas = 0;
        
        while (T --> 0) {
            int n = cin.nextInt();
            long a[] = new long[n];
            long b[] = new long[n];
            for (int i = 0; i < n; ++i) {
                String[] s = cin.next().split(":");
                a[i] = (long)(Double.parseDouble(s[0]) * 1000 + 1e-10);
                b[i] = (long)(Double.parseDouble(s[1]) * 1000 + 1e-10);
            }
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (a[j] * b[i] < a[i] * b[j]) {
                        a[j] ^= (a[i] ^= a[j]); a[i] ^= a[j];
                        b[j] ^= (b[i] ^= b[j]); b[i] ^= b[j];
                    }
            int ret = n;
            BigInteger x = BigInteger.ZERO;
            BigInteger y = BigInteger.ONE;
            for (int i = 0; i < n; ++i) {
                x = x.multiply(BigInteger.valueOf(a[i] + b[i]))
                .add(y.multiply(BigInteger.valueOf(a[i])));
                y = y.multiply(BigInteger.valueOf(a[i] + b[i]));
                if (x.compareTo(y) >= 0) {
                    ret = i;
                    break;
                }
            }
            System.out.printf("Case #%d: ", ++cas);
            System.out.println(ret);
        }
    }
}