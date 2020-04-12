#include<iostream>
#include "./bst.cpp"
using namespace std;

int* get_random(int n){
    srand(time(0));
    int* arr=new int [n];
    for(int i=0;i<n;i++){
        arr[i]=i;
    }
    for(int i=n;i>0;i--){
        int index=rand()%i;
        int temp=arr[index];
        arr[index]=arr[i-1];
        arr[i-1]=temp;
    }
    return arr;
}
int main(){
    int* arr;
    for(int i=0;i<100;i++){
        arr=
    }

}