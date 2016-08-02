def main():
	fin = open("binary.in", "r")
	fout = open("binary.out", "w")
	a, b, c, r = [], [0, 1], 1, []
	while len(b) < 10000:
		c = c * 10
		for i in b:
			a.append(i)
		for i in b:
			i += c
			if bin(i).endswith(str(i)):
				a.append(i)
		b = a
		a = []
	print len(b)
	print >> fout, b[map(int, fin.readline().split())[0]]

if __name__ == "__main__":
	import profile
	profile.run("main()")


