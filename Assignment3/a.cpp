#include<cstring>
#include<math.h>
#include<iostream>
using namespace std;
long long int hashs(char *s){
    long long int val=0;
    int len = strlen(s);
    // cout<<len<<"HELLO"<<endl;
    // while(len--){
    //     val+=s[]
    // }
    for(int i=0;i<len;i++){
        val=val+(s[i]-'a')*(int)pow(26,i);
       
    }
    
    return val;
}
class Node{
    public:
         long long int hval;
        bool exist;
        int one;
        int zero;
        Node(){
            one=0;
            zero=0;
        }
        bool operator==(Node b){
            if(hval==b.hval)return true;
            else return false;
        }
};

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        Node arr[n];
        int counter=0;
        while(n--){
            char str[6];
            int val;
            cin>>str>>val;
            Node temp;
            int flag=0;
            temp.hval=hashs(str);
            for(int i=0;i<counter;i++){
                if(arr[i]==temp){
                    if(val)arr[i].one+=1;
                    else arr[i].zero+=1;
                    flag=1;
                    break;
                }
            }
            if(flag){
                flag=0;
                continue;
            }
            else{
                arr[counter]=temp;
                if(val)arr[counter].one+=1;
                else arr[counter].zero+=1;
                counter++;
            }
        }
        int output=0;
        for(int i=0;i<counter;i++){
            int test =(arr[i].one>arr[i].zero)?arr[i].one:arr[i].zero;
            output=output+test;
            
        }
        cout<<output<<endl;
    }
}