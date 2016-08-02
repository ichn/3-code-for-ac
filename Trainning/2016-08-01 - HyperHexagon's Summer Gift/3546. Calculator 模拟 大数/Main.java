import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		BigInteger val[] = new BigInteger [20];
		for (int i = 0; i < 10; ++i)
			val[i] = BigInteger.valueOf(1);
		while (cin.hasNext()) {
			String s = cin.next();
			if (s.length() == 3) {
				val[s.charAt(0)-'A'] = val[s.charAt(2)-'A'];
			} else {
				if (s.charAt(1) == '*')
					val[s.charAt(0)-'A'] = val[s.charAt(0)-'A'].multiply(val[s.charAt(3)-'A']);
				else {
					val[s.charAt(0)-'A'] = val[s.charAt(0)-'A'].add(val[s.charAt(3)-'A']);
				}
			}
		}
		for (int i = 0; i < 10; ++i)
			System.out.println(val[i]);
	}
}
