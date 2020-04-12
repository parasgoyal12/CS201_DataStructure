#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;

long long * populate(long long k,long long n){
    long long *m=new long long[k];
    long long t=ceil(8*n*log(n));
    for(long long i=0;i<k;i++)m[i]=rand()%t+3;
    return m;
}
void initialize(long long *** p_powP,long long ***hashP,long long k,long long n){
	*p_powP=new long long*[k];
	*hashP=new long long*[k];
	for(long long i=0;i<k;i++){
        (*hashP)[i]=new long long[n+1];
        (*p_powP)[i]=new long long[n+1];
        (*hashP)[i][0]=0;
        (*p_powP)[i][0]=1;
    }
}
void populate_matrix(char*s,long long**p_pow,long long**h,long long *m,long long k, long long n,long long p){
    for(long long j=0;j<k;j++){
    for(long long i=1;i<=n;i++){
       p_pow[j][i]=(p_pow[j][i-1]*p)%m[j];
       h[j][i]=(h[j][i-1]+(s[i-1]-'0'+1)*p_pow[j][i-1])%m[j];
    }
    }
}
int main(){
    srand(time(0));
    long long n;
    cin>>n;
    long long k=ceil(-log(n)/(log(1-7.0/(8.0*log(n)))));
    long long *m=populate(k,n);
    long long p=2;
    long long **powersofbase;
    long long **h;
    initialize(&powersofbase,&h,k,n);
    /*long long ** powersofbase= new long long*[k];
    long long** h = new long long*[k];
    for(long long i=0;i<k;i++){
       h[i]=new long long[n+1];
        powersofbase[i]=new long long[n+1];
        h[i][0]=0;
        powersofbase[i][0]=1;
   }*/
    char * s=new char[n+1];
    cin>>s;
    populate_matrix(s,powersofbase,h,m,k,n,p);
    /*for(long long j=0;j<k;j++){
    for(long long i=1;i<=n;i++){
        powersofbase[j][i]=(powersofbase[j][i-1]*p)%m[j];
        h[j][i]=(h[j][i-1]+(s[i-1]-'0'+1)*powersofbase[j][i-1])%m[j];
    }
    }
    */
   

    long long t;
    cin>>t;
    while(t--){
        long long a,b,c,d;
        cin>>a>>b>>c>>d;
	    int flag=1;
	//cout<<"Hello Test"<<endl;
        for(long long i=0;i<k;i++){
        long long one=(h[i][b]-h[i][a-1]+m[i])%m[i];
        long long two=(h[i][d]-h[i][c-1]+m[i])%m[i];
        if(a<c)one=(one*powersofbase[i][c-a])%m[i];
        else two=(two*powersofbase[i][a-c])%m[i];
	if(!(one==two)){flag=0;break;}
        }
        cout<<flag<<endl;
    }

}
