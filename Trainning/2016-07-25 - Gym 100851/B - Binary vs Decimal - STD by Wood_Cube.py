def main():
	fin = open('binary.in', 'r')
	fout = open('binary.out', 'w')
	
	i = 1
	s = [1]
	a = [1]
	b = []
	
	def check(x):
		return bin(x).endswith(str(x))
	
	while len(s) <= 10000:
		for x in a:
			if check(x + 10 ** i - 10 ** (i - 1)):
				b.append(x + 10 ** i - 10 ** (i - 1))
		for x in a:
			if check(x + 10 ** i):
				b.append(x + 10 ** i)
	
		for x in b:
			s.append(x)
	
		a = b
		b = []
		i += 1
	
	[n] = map(int, fin.readline().split())
	fout.write(str(s[n-1]) + '\n')

if __name__ == "__main__":
	import profile
	profile.run("main()")
