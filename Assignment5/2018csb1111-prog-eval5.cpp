#include<iostream>
#include<cstdlib>
#define INT_MAX 2147483647
#include<math.h>
using namespace std;

class ListNode{
    public:
    int dest;
    double weight;
    bool isRed;
    ListNode* next;
    ListNode(int x,double p,bool red=false,ListNode* alpha=NULL){
        dest=x;
        weight=-log10(1-p);
        next=alpha;
        isRed=red;
    }
};
class List{
    public:
    ListNode* head;
    int visitcount;
    int minred;
    double prob;
    List(){
        head=NULL;
        visitcount=0;
        minred=INT_MAX;
        prob=-1;
    }
};

class Graph{
    public:
    int vertices;
    List* array;
    Graph(int v){
        vertices=v;
        array=new List[v+1];
        for(int i=0;i<=vertices;i++)array[i].head=NULL;
    }
    void addEdge(int src,int dest,double p,bool red){
        ListNode* temp=new ListNode(dest,p,red);
        temp->next=array[src].head;
        array[src].head=temp;

        temp=new ListNode(src,p,red);
        temp->next=array[dest].head;
        array[dest].head=temp;
    }
    // void test(){
    //     for(int i=1;i<=vertices;i++){
    //         cout<<i<<" "<<endl;
    //         ListNode*temp=array[i].head;
    //         while(temp!=NULL){
    //             cout<<temp->dest<<" "<<temp->weight<<" "<<temp->isRed<<endl;
    //             temp=temp->next;
    //         }
    //     }
    // }
};

class HeapNode{
    public:
    double distance;
    int redCount;
    int v;
    HeapNode(){distance=0.0;redCount=0;v=0;}
    HeapNode(int vertex,int count,double dist){
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
    int parent(int i){
        int j=(i-1)/2;
        return j;}
    int left(int i){
        int j=2*i+1;
        return j;}
    int right(int i){
        int j=2*i+2;
        return j;}
    void swap(HeapNode *a, HeapNode*b){
        HeapNode temp=*a;
        *a=*b;
        *b=temp;
    }
    int insert(int vertex,int count,double distance){
        if(heap_size==capacity){cout<<"Heap Overflow\n";exit(0);}
        heap_size++;
        int i=heap_size-1;
        arr[i]=HeapNode(vertex,count,distance);
        for(;i!=0 && arr[parent(i)]>arr[i];i=parent(i))
        
            swap(&(arr[i]),&(arr[parent(i)]));
            
        
    }
    void Heapify(int i){
        int smallL,smallY;
        int l=left(i);
        
         smallL=i;
         
        
        if(l<heap_size && arr[l]<arr[i] ){
        smallL=l;}
        int r=right(i);
        smallY=i;
        if((r<heap_size) && (arr[r]<arr[i])){
        smallY=r;}
        
        int smallest =(arr[smallL]<arr[smallY])?smallL:smallY;
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
    //     void test(){
    //     for(int i=0;i<heap_size;i++)cout<<arr[i].distance<<"\n";
    // }
};
int dijkastra(Graph* graph,int src,int k,double maxlen){
    int v=graph->vertices+1;
    
    Heap* h=new Heap(v*v*(k+1));
   
    graph->array[src].prob=0.0;
    ListNode *l=graph->array[src].head;
    graph->array[src].minred=0;
    graph->array[src].visitcount=1;
    while(l!=NULL){
        int var=(l->isRed)?1:0;
        if(var>k||(l->weight>maxlen)){l=l->next;continue;}
        h->insert(l->dest,var,l->weight);
        l=l->next;
    }
    while(h->heap_size!=0){
        HeapNode alpha=h->extractMin();
        int vertex=alpha.v;
        int curr_k=alpha.redCount;
        double curr_len=alpha.distance;
        if((graph->array[vertex].visitcount>k && k>0)||(k==0&& graph->array[vertex].visitcount>=1))continue;
        if(graph->array[vertex].visitcount>0 && graph->array[vertex].minred<curr_k)continue;
        if(graph->array[vertex].minred<=curr_k)continue;
        // cout<<vertex<<" "<<curr_len<<" "<<curr_k<<endl;
        graph->array[vertex].prob=curr_len;
        graph->array[vertex].visitcount++;
        graph->array[vertex].minred=curr_k;
        l=graph->array[vertex].head;
        while(l!=NULL){
            int next_k=curr_k + ((l->isRed)?1:0) ;
            double next_prob=curr_len + l->weight;
            
            if(next_k>=(graph->array[l->dest].minred)||next_k>k || next_prob>maxlen){ l=l->next;continue;}
            // cout<<vertex<<" "<<l->dest<<" "<<graph->array[l->dest].minred<<" "<<next_k<<endl;
            h->insert(l->dest,next_k,next_prob);
            l=l->next;
        }
    }
    // for(int i=1;i<v;i++){
    //     cout<<graph->array[i].visitcount<<" "<<graph->array[i].prob<<endl;
    // }

}
int main(){
    double p;
    cin>>p;
    int k;
    cin>>k;
    int m,n;
    cin>>n>>m;

    Graph g(n);
    while(m--){
        int n1,n2,r;
        double prob;
        cin>>n1>>n2>>prob>>r;
        if(r)g.addEdge(n1,n2,prob,true);
        else g.addEdge(n1,n2,prob,false);
    }
    
    dijkastra(&g,1,k,p);
    if(g.array[n].visitcount)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    // g.test();
}
