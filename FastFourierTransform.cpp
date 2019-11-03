const double pi=3.141592653589793238462643383;
struct comp{
	double re,im;
	comp(double x=0.,double y=0.){
		re=x,im=y;
	}
};
int rev[1<<20];
comp operator +(const comp &a,const comp &b){
	return comp(a.re+b.re,a.im+b.im);
}
comp operator -(const comp &a,const comp &b){
	return comp(a.re-b.re,a.im-b.im);
}
comp operator *(const comp &a,const comp &b){
	return comp(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re);
}
void FFT(int n,comp *a,int f){
	comp x,y;
	for(int i=0;i<n;++i)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1){
        comp wn(comp(cos(pi/i),f*sin(pi/i)));
		for(int j=0;j<n;j+=i<<1){
            comp w(comp(1,0));
			for(int k=0;k<i;k++,w=w*wn){
				x=w*a[j+k+i],y=a[j+k],a[j+k]=y+x,a[j+k+i]=y-x;
			}
        }
    }
	if(f==-1){
		for(int i=0;i<n;++i)
			a[i].re/=n;
	}
}
int work(int n){
	int nm=1,L=0;
	for(;nm<n;nm<<=1,++L);
	for(int i=0;i<nm;++i){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	}
	return nm;
}