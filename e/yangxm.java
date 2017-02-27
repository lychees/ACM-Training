import java.math.*;
import java.util.*;

class Fraction implements Comparable<Fraction> {
    BigInteger p, q;
    
    public Fraction() {
        p = BigInteger.ZERO;
        q = BigInteger.ONE;
    }
    
    public Fraction(int _p, int _q) {
        p = BigInteger.valueOf(_p);
        q = BigInteger.valueOf(_q);
        BigInteger r = p.gcd(q);
        p = p.divide(r);
        q = q.divide(r);
    }
    
    public Fraction(BigInteger _p, BigInteger _q) {
        p = _p;
        q = _q;
        BigInteger r = p.gcd(q);
        p = p.divide(r);
        q = q.divide(r);
    }
    
    public Fraction add(Fraction o) {
        BigInteger pp = p.multiply(o.q).add(q.multiply(o.p));
        BigInteger qq = q.multiply(o.q);
        return new Fraction(pp, qq);
    }
    
    public int compareTo(Fraction o) {
        return p.multiply(o.q).compareTo(q.multiply(o.p));
    }
    
    public boolean LessOne() {
        return p.compareTo(q) < 0;
    }
}

public class Main {
    public static int parseInt(String str) {
        String[] xy = str.split("\\.");
        if (xy.length == 1) {
            return Integer.parseInt(xy[0]) * 1000;
        }
        int x = Integer.parseInt(xy[0]);
        int y = Integer.parseInt(xy[1]);
        if (xy[1].length() == 1) y *= 100;
        else if (xy[1].length() == 2) y *= 10;
        return x * 1000 + y;
    }
    
    public static Fraction parseLine(String line) {
        String[] ab = line.split(":");
        int a = parseInt(ab[0]);
        int b = parseInt(ab[1]);
        return new Fraction(a, a + b);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int ct = 1; ct <= t; ++ct) {
            int n = sc.nextInt();
            Fraction[] p = new Fraction[n];
            for (int i = 0; i < n; ++i) {
                String line = sc.next();
                p[i] = parseLine(line);
            }
            Arrays.sort(p);
            Fraction sum = new Fraction();
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                Fraction cur = sum.add(p[i]);
                if (cur.LessOne()) {
                    sum = cur; ++ans;
                } else {
                    break;
                }
            }
            System.out.printf("Case #%d: %d\n", ct, ans);
        }
    }
}