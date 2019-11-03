/*
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
if n < 18,446,744,073,709,551,616 = 264, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
if n < 318,665,857,834,031,151,167,461, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
if n < 3,317,044,064,679,887,385,961,981, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41.
*/
namespace MillerRabin {
	long long Mul(long long a,long long b,long long mo){
		long long tmp=a*b-(long long)((long double)a/mo*b+1e-8)*mo;
		return (tmp%mo+mo)%mo;
	}

	long long Pow(long long a,long long b,long long mo){
		long long res=1;
		for(;b;b>>=1,a=Mul(a,a,mo))if(b&1)res=Mul(res,a,mo);
		return res;
	}

	bool IsPrime(long long n){
		if(n==2)return 1;
		if(n<2||!(n&1))return 0;
		static const int P=9,num[P]={2,3,5,7,11,13,17,19,23};
		long long x=n-1;int t=0;
		for(;!(x&1);x>>=1)++t;
		for(int i=1;i<P;++i){
			long long a=num[i]%(n-1)+1,res=Pow(a%n,x,n),last=res;
			for(int j=1;j<=t;++j){
				res=Mul(res,res,n);
				if(res==1&&last!=1&&last!=n-1)return 0;
				last=res;
			}
			if(res!=1)return 0;
		}
		return 1;
	}
}

namespace PollardRho {
	using namespace MillerRabin;
	unsigned long long seed;
	
	long long Rand(long long mo){
		return (seed+=4179340454199820289ll)%mo;
	}
	
	long long F(long long x,long long c,long long mo){
		return (Mul(x,x,mo)+c)%mo;
	}
	
	long long gcd(long long a,long long b){
		return b?gcd(b,a%b):a;
	}

	long long Get(long long c,long long n){
		long long x=Rand(n),y=F(x,c,n),p=n;
		for(;x!=y&&(p==n||p==1);x=F(x,c,n),y=F(F(y,c,n),c,n))
			p=x>y?gcd(n,x-y):gcd(n,y-x);
		return p;
	}

	void Divide(long long n,long long p[]){
		if(n<2)return;
		if(IsPrime(n)){p[++*p]=n;return;}
		for(;;){
			long long tmp=Get(Rand(n-1)+1,n);
			if(tmp!=1&&tmp!=n){
				Divide(tmp,p);
				Divide(n/tmp,p);
				return;
			}
		}
	}
}