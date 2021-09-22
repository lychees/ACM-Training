import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {
    final static MathContext CONTEXT = new MathContext(50, RoundingMode.HALF_EVEN);

    class Point implements Comparable <Point> {
        BigDecimal x, y;

        Point(BigDecimal x, BigDecimal y) {
            this.x = x;
            this.y = y;
        }

        Point add(Point other) {
            return new Point(x.add(other.x), y.add(other.y));
        }

        Point subtract(Point other) {
            return new Point(x.subtract(other.x), y.subtract(other.y));
        }

        Point multiply(BigDecimal scale) {
            return new Point(x.multiply(scale), y.multiply(scale));
        }

        public int compareTo(Point other) {
            if (!x.equals(other.x)) {
                return x.compareTo(other.x);
            }
            return y.compareTo(other.y);
        }
    }

    BigDecimal det(Point a, Point b) {
        return a.x.multiply(b.y).subtract(a.y.multiply(b.x));
    }

    BigDecimal wrap(double value) {
        return new BigDecimal(value, CONTEXT);
    }

    Point nextPoint() throws IOException {
        int x = reader.nextInt();
        int y = reader.nextInt();
        return new Point(wrap(x), wrap(y));
    }

    BigDecimal[] getCoefficient(BigDecimal v1, BigDecimal p1, BigDecimal v2, BigDecimal p2) {
        return new BigDecimal[]{p1.multiply(p2),
            v1.multiply(p2).add(v2.multiply(p1)),
            v1.multiply(v2)};
    }

    BigDecimal sqrt(BigDecimal a) {
        if (a.equals(BigDecimal.ZERO)) {
            return BigDecimal.ZERO;
        }
        BigDecimal x = a;
        for (int _ = 0; _ < 60; ++ _) {
            x = x.add(a.divide(x, CONTEXT)).divide(wrap(2), CONTEXT);
        }
        return x;
    }

    class Pair implements Comparable <Pair> {
        int id;
        Point p;

        Pair(int id, Point p) {
            this.id = id;
            this.p = p;
        }
        
        public int compareTo(Pair other) {
            return p.compareTo(other.p);
        }
    }

    boolean check(Pair a, Pair b, Pair c) {
        return det(b.p.subtract(a.p), c.p.subtract(b.p)).signum() > 0;
    }

    public void run() {
        try {
            int n = reader.nextInt();
            BigDecimal t = wrap(reader.nextInt());
            Point[] p = new Point[n];
            Point[] v = new Point[n];
            for (int i = 0; i < n; ++ i) {
                p[i] = nextPoint();
                v[i] = nextPoint();
            }
            ArrayList <BigDecimal> events = new ArrayList <BigDecimal>();
            events.add(BigDecimal.ZERO);
            events.add(t);
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < i; ++ j) {
                    for (int k = 0; k < j; ++ k) {
                        Point va = v[i].subtract(v[j]);
                        Point vb = v[i].subtract(v[k]);
                        Point pa = p[i].subtract(p[j]);
                        Point pb = p[i].subtract(p[k]);
                        BigDecimal[] ret1 = getCoefficient(va.x, pa.x, vb.y, pb.y);
                        BigDecimal[] ret2 = getCoefficient(va.y, pa.y, vb.x, pb.x);
                        BigDecimal c = ret1[0].subtract(ret2[0]);
                        BigDecimal b = ret1[1].subtract(ret2[1]);
                        BigDecimal a = ret1[2].subtract(ret2[2]);
                        if (a.equals(BigDecimal.ZERO)) {
                            if (!b.equals(BigDecimal.ZERO)) {
                                events.add(c.divide(b, CONTEXT).negate());
                            }
                        } else {
                            BigDecimal d = b.multiply(b).subtract(wrap(4).multiply(a.multiply(c)));
                            if (d.signum() >= 0) {
                                events.add((b.negate().subtract(sqrt(d)).divide(a, CONTEXT).divide(wrap(2), CONTEXT)));
                                events.add((b.negate().add(sqrt(d)).divide(a, CONTEXT).divide(wrap(2), CONTEXT)));
                            }
                        }
                    }
                }
            }
            Collections.sort(events);
            BigDecimal answer = BigDecimal.ZERO;
            for (int k = 1; k < events.size(); ++ k) {
                BigDecimal t1 = events.get(k - 1);
                BigDecimal t2 = events.get(k);
                BigDecimal t0 = t1.add(t2).divide(wrap(2), CONTEXT);
                if (BigDecimal.ZERO.compareTo(t0) <= 0 && t0.compareTo(t) <= 0) {
                    Pair[] pairs = new Pair[n];
                    for (int i = 0; i < n; ++ i) {
                        pairs[i] = new Pair(i, p[i].add(v[i].multiply(t0)));
                    }
                    Arrays.sort(pairs);
                    Pair[] stack = new Pair[n + 1];
                    int top = 0;
                    for (int i = 0; i < n; ++ i) {
                        while (top >= 2 && !check(stack[top - 2], stack[top - 1], pairs[i])) {
                            top --;
                        }
                        stack[top ++] = pairs[i];
                    }
                    int end = top;
                    for (int i = n - 1; i >= 0; -- i) {
                        while (top > end && !check(stack[top - 2], stack[top - 1], pairs[i])) {
                            top --;
                        }
                        stack[top ++] = pairs[i];
                    }
                    for (int _ = 1; _ < top; ++ _) {
                        int i = stack[_ - 1].id;
                        int j = stack[_].id;
                        BigDecimal[] ret1 = getCoefficient(v[i].x, p[i].x, v[j].y, p[j].y);
                        BigDecimal[] ret2 = getCoefficient(v[j].x, p[j].x, v[i].y, p[i].y);
                        BigDecimal c = ret1[0].subtract(ret2[0]);
                        BigDecimal b = ret1[1].subtract(ret2[1]);
                        BigDecimal a = ret1[2].subtract(ret2[2]);
                        answer = answer.add(a.multiply(t2.multiply(t2).multiply(t2).subtract(t1.multiply(t1).multiply(t1)).divide(wrap(3), CONTEXT)))
                                       .add(b.multiply(t2.multiply(t2).subtract(t1.multiply(t1)).divide(wrap(2), CONTEXT)))
                                       .add(c.multiply(t2.subtract(t1)));
                    }
                }
            }
            writer.println(String.format("%.6f", answer.divide(t, CONTEXT).divide(wrap(2), CONTEXT).doubleValue()));
        } catch (IOException ex) {
        }
        writer.close();
    }

    InputReader reader;
    PrintWriter writer;

    Solution() {
        reader = new InputReader();
        writer = new PrintWriter(System.out);
    }

    public static void main(String[] args) {
        new Solution().run();
    }

    void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;

    InputReader() {
        reader = new BufferedReader(new InputStreamReader(System.in));
        tokenizer = new StringTokenizer("");
    }

    String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    Integer nextInt() throws IOException {
        return Integer.parseInt(next());
    }
}
