import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
  static interface IStr {
    public BigInteger length();
    public char charAt(BigInteger n);
    public void substring(BigInteger s, BigInteger t, StringBuilder sb);
  }

  static class Chr implements IStr {
    char chr;

    public Chr(char chr) {
      this.chr = chr;
    }

    public BigInteger length() {
      return BigInteger.ONE;
    }

    public char charAt(BigInteger n) {
      if (n.equals(BigInteger.ZERO)) {
        return chr;
      } else {
        throw new IndexOutOfBoundsException();
      }
    }

    public void substring(BigInteger s, BigInteger t, StringBuilder sb) {
      if (s.signum() <= 0 && t.signum() > 0) {
        sb.append(chr);
      }
    }
  }

  static class Str implements IStr {
    BigInteger len = BigInteger.ZERO;
    ArrayList<IStr> str = new ArrayList<IStr>();

    public void add(IStr s) {
      len = len.add(s.length());
      str.add(s);
    }

    public BigInteger length() {
      return len;
    }

    public char charAt(BigInteger n) {
      for (IStr i: str) {
        if (n.compareTo(i.length()) < 0) {
          return i.charAt(n);
        } else {
          n = n.subtract(i.length());
        }
      }
      throw new IndexOutOfBoundsException();
    }

    public void substring(BigInteger s, BigInteger t, StringBuilder sb) {
      s = s.max(BigInteger.ZERO);
      t = t.min(len);
      for (IStr i: str) {
        if (t.signum() <= 0) {
          break;
        } else if (s.compareTo(i.length()) < 0) {
          i.substring(s, t, sb);
        }
        s = s.subtract(i.length());
        t = t.subtract(i.length());
      }
    }
  }

  static IStr[][] cache = new IStr[128][128];
  static String[] str = new String[] {
    "ACM-ICPC",
    "BIDU",
    "consonant:BCDFGHJKLMNPQRSTVXZWY",
    "D41D8CD98F00B204E9800998ECF8427E",
    "2.718281828459...",
    "0xFACEB00C",
    "1E100.net",
    "\\Huge{String}",
    "InternationalCollegiateProgrammingContest",
    "JinKeLa",
    "KeepItSimpleStupid",
    "1000mL",
    "Micro$oftCorp",
    "",
    "Oops",
    "pneumonoultramicroscopicsilicovolcanoconiosis",
    "A",
    "P",
    "M",
    "TheQuickBrownFoxJumpsOverTheLazyDog",
    "\\bigcup",
    "vowel:AEIOU",
    "WWW",
    "X-ray",
    "YOOOOOO!",
    "ZheJiangUniversity"
  };

  static IStr gao(char chr, int n) {
    if (cache[n][chr] == null) {
      if (n == 0) {
        cache[n][chr] = new Chr(chr);
      } else if (!Character.isUpperCase(chr)) {
        cache[n][chr] = gao(chr, 0);
      } else {
        cache[n][chr] = gao(str[chr - 'A'], n - 1);
      }
    }
    return cache[n][chr];
  }

  static IStr gao(String str, int n) {
    Str ret = new Str();
    for (char chr: str.toCharArray()) {
      ret.add(gao(chr, n));
    }
    return ret;
  }

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    if (args.length > 0 && args[0].equals("-length")) {
      String[] input = in.readLine().split(" ");
      System.out.println(gao(input[0], Integer.parseInt(input[1])).length());
      System.exit(0);
    }

    while (true) {
      String s = in.readLine();
      if (s == null) {
        break;
      }

      String t = in.readLine();
      String[] ts = t.split(" ");
      int n = Integer.parseInt(ts[0]);
      int m = Integer.parseInt(ts[1]);
      BigInteger k = new BigInteger(ts[2]);
      IStr str = gao(s, n);

      if (args.length > 0 && args[0].equals("-d")) {
        for (int i = 0; i < m; ++i) {
          try {
            System.out.print(str.charAt(k));
            k = k.add(BigInteger.ONE);
          } catch (IndexOutOfBoundsException ex) {
            break;
          }
        }
        System.out.println();
      } else {
        StringBuilder sb = new StringBuilder(m);
        str.substring(k, k.add(BigInteger.valueOf(m)), sb);
        System.out.println(sb.toString());
      }
    }
  }
}

