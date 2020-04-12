#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int m=198511;
    int p=2;
    int* p_pow= new int[n+1];
    int* h = new int[n+1];
    char * s=new char[n+1];
     h[0]=0;
    cin>>s;
     p_pow[0]=1;
    for(int i=1;i<=n;i++){
        p_pow[i]=(p_pow[i-1]*p)%m;
        h[i]=(h[i-1]+((s[i-1]-'0'+1)*(p_pow[i-1])))%m;
    }
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
	int flag=1;
        int one=(h[b]-h[a-1]+m)%m;
        int two=(h[d]-h[c-1]+m)%m;
        if(a<c)one=(one*p_pow[c-a])%m;
        else two=(two*p_pow[a-c])%m;
        cout <<(one==two)<<" "<<m<<endl;
    }
	for(int i=0;i<=n;i++)cout<<h[i]<<" ";
}
