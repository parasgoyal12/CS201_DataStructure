#include<iostream>
using namespace std;

class HeapNode{
    public:
    float distance;
    int redCount;
    int v;
    HeapNode(){distance=0.0;redCount=0;v=0;}
    HeapNode(int vertex,int count,float dist){
        v=vertex;
        redCount=count;
        distance=dist;
    }
    bool operator >(HeapNode b){return distance > (b.distance);}
    bool operator <(HeapNode b){return distance < (b.distance);}
};
class Heap{
    public:
    int capacity;//total created capacity
    HeapNode * arr;
    int heap_size;//current no. in heap
    Heap(int cap){
        capacity=cap;
        heap_size=0;
        arr=new HeapNode[capacity+1];
    }
    int parent(int i){return (i-1)/2;}
    int left(int i){return (2*i+1);}
    int right(int i){return (2*i+2);}
    void swap(HeapNode *a, HeapNode*b){
        HeapNode temp=*a;
        *a=*b;
        *b=temp;
    }
    int insert(int vertex,int count,float distance){
        if(heap_size==capacity){cout<<"Heap Overflow\n";return 0;}
        heap_size++;
        int i=heap_size-1;
        // cout<<i<<endl;
        arr[i]=HeapNode(vertex,count,distance);
        while(i!=0 && arr[parent(i)]>arr[i]){
            // cout<<arr[i].distance<<" "<<arr[parent(i)].distance<<endl;

            swap(&(arr[i]),&(arr[parent(i)]));
            i=parent(i);
        }
    }
    void Heapify(int i){
        int l=left(i);
        int r=right(i);
        int smallest=i;
        if(l<heap_size && arr[l]<arr[i] )smallest=l;
        if(r<heap_size && arr[r]<arr[smallest])smallest=r;
        if(smallest!=i){
            swap(&arr[i],&arr[smallest]);
            Heapify(smallest);
        }
    }
    HeapNode extractMin(){
        if(heap_size<=0)return HeapNode();
        if(heap_size==1){
            heap_size--;
            return arr[0];
        }
        HeapNode root=arr[0];
        arr[0]=arr[heap_size-1];
        heap_size--;
        Heapify(0);
        return root;
    }
    void test(){
        for(int i=0;i<heap_size;i++)cout<<arr[i].distance<<"\n";
    }
};
void swap(HeapNode *a,HeapNode *b){
    HeapNode temp=*a;

}
int main(){
    // HeapNode a(1,2,1.20);
    // HeapNode b(2,3,0.26);
    // cout<< (a<b)<<endl;
    Heap a(7);
    a.insert(1,0,1.20);
    // a.test();
    // cout<<endl;
    a.insert(2,1,0.26);
    // // a.test();
    a.insert(3,1,0.569);
    a.insert(7,5,0.35);
    a.insert(8,2,500);
    a.insert(4,1,0.89);
    a.insert(5,0,0.23);
    for(int i=0;i<=;i++){HeapNode b=a.extractMin();
    cout<<b.v<<" "<<b.redCount<<" "<<b.distance<<endl;
    }
}