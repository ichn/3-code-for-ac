a,c,r = [1],1,[1]
while len(r) < 10000:
	d = c*10
	a = [i+d-c for i in a if bin(i+d-c).endswith(str(i+d-c))]+[i+d for i in a if bin(i+d).endswith(str(i+d))]
	r,c = r+a, d
open("binary.out","w").write(str(r[int(open("binary.in","r").read())-1]))
