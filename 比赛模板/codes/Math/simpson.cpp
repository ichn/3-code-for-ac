typedef double DB;
DB f(DB x) { // integral function
	return log(x*x+2.24234*x-M_PI);
}
DB simpson(DB a, DB b) {
	return (b-a)*(f(a)+4.0*f((a+b)/2.0)+f(b))/6.0;
}
DB asr(DB l, DB r, DB eps, DB res) {
	DB m = (l+r)/2.0;
	DB ls = simpson(l, m), rs = simpson(m, r);
	if (fabs(ls+rs-res) < eps*15) return ls+rs+(ls+rs-res)/15;
	return asr(l, m, eps/2.0, ls)+asr(m, r, eps/2.0, rs);
}
DB asr(DB l, DB r, DB eps) {
	return asr(l, r, eps, simpson(l, r));
}
int main() {
	printf("%.12lf\n", asr(1, 10, 1e-2));
	return 0;
}

