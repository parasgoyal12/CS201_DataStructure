/*
**********************************************************************
                    CS201 Programming Evaluation 5
                        Feasible Path Finding
**********************************************************************
The main idea is to find the minimum path from source to a vertex and
maintain an array for each vertex whose ith value represents the minimum
path length from source to that vertex using exactly i red edges. 
To do this, we run an algorithm similar to Dijkstra but do not ignore 
already visited vertices if the number of red edges in that path are 
different. 
***********************************************************************
                                                    Submitted by:
                                                    Ekansh Mahendru
                                                    2018csb1087
************************************************************************
PS: Increase heap size according to the computers working memory in case
    of a Heap Overflow error.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#define heap_size 275000    //Maximum number of edges in the heap at a time


//Class for the node to be inserted in the heap
class heapnode{
    public:
    int u, v, k;
    double priority;
    heapnode(){
        u=0;
        v=0;
        k=0;
        priority = 0;
    }
    heapnode(int s, int e, double pr, int j){
        u = s;
        v = e;
        priority = pr;
        k = j;
    }

    //Since the heap class was built for normal integer values, we overload the comparing operators
    bool operator > (heapnode x){
        return (priority > x.priority);
    }
};


template<typename T>
class heap{
    public:
    int i;  //Current heap size
    T hp[heap_size];    //The heap array
    
    heap<T>(){
        i=0;
    }
    
    void insert(T x){
        if(i>heap_size){
            //Heap cannot contain more edges
            cout<<"Heap Overflow\n";
            exit(0);
        }
        hp[i] = x;
        int j = i;
        i += 1;
        while(j!=0){
            if(hp[(j-1)/2]>hp[j]){
                T temp = hp[j];
                hp[j] = hp[(j-1)/2];
                hp[(j-1)/2] = temp;
                j = (j-1)/2;
            }else{
                break;
            }
        }
    }

    //Returns and deletes the minimum value in the heap
    T pop(){
        if(i==0){
            cout<<"Popping from an empty heap\n";
            exit(0);
        }
        T temp = hp[0];
        i--;
        hp[0] = hp[i];
        int j = 0;
        while(2*j+1<i){
            if(2*j+2<i && hp[j]>hp[2*j+1] && hp[j]>hp[2*j+2]){
                if(hp[2*j+2]>hp[2*j+1]){
                    T temp = hp[j];
                    hp[j] = hp[2*j+1];
                    hp[2*j+1] = temp;
                    j = 2*j+1;
                }else{
                    T temp = hp[j];
                    hp[j] = hp[2*j+2];
                    hp[2*j+2] = temp;
                    j=2*j+2;
                }
            }else if(hp[j]>hp[2*j+1]){
                T temp = hp[j];
                hp[j] = hp[2*j+1];
                hp[2*j+1] = temp;
                j=2*j+1;
            }else if(2*j+2<i && hp[j]>hp[2*j+2]){
                T temp = hp[j];
                hp[j] = hp[2*j+2];
                hp[2*j+2] = temp;
                j=2*j+2;
            }else{
                break;
            }
        }
        return temp;
    }

    int isEmpty(){
        if(i==0) return 1;
        return 0;
    }
};

//node class to represent each edge in the adjacency list of each vertex
class node{
    public:
    int v, c;   //Destination Vertex, Color of Edge
    double p;   //-log_10(1-p) for the edge
    node * next;    //Next node in the list
    node(int ver, double pr, int color){
        v = ver;
        p = pr;
        c = color;
        next = NULL;
    }
};

//Graph class to store the graph
class graph{
    private:
    node * adjlist[100000];
    int n,m = 0;    //Number of vertices, number of edges

    public:
    graph(int v){
        n = v;
        for(int i = 1; i <= n; i++)
            adjlist[i] = NULL;
    }

    void insert(int u, int v, double p, int c){
        m++;
        node * temp1 = new node(v,p,c);
        temp1->next = adjlist[u];
        adjlist[u] = temp1; //Insert v in the adjacency list of u
        node * temp2 = new node(u,p,c);
        temp2->next = adjlist[v];
        adjlist[v] = temp2; //Insert u in the adjacency list of v
    }

    void SpecialDijkstra(double g, int k, double * a){
        for(int i = 0; i < n*(k+1); i++)
            a[i] = -1;
        a[0] = 0;
        heap<heapnode> h;
        node * curr = adjlist[1];
        while(curr!=NULL){
            heapnode temp(1,curr->v,curr->p, curr->c);
            h.insert(temp);
            curr = curr->next;
        }
        while(!h.isEmpty()){
            heapnode temp = h.pop();
            if(a[(temp.v-1)*(k+1)+temp.k]!=-1){
                continue;
            }
            node * curr = adjlist[temp.v];
            a[(temp.v-1)*(k+1)+temp.k] = temp.priority;
            while(curr!=NULL){
                if(a[(curr->v-1)*(k+1)+temp.k+curr->c]!=-1 || temp.k+curr->c > k || temp.priority+curr->p > g){
                    curr = curr->next;
                    continue;
                }
                heapnode temp1(temp.v, curr->v, temp.priority+curr->p, temp.k+curr->c);
                h.insert(temp1);
                curr = curr->next;
            }
        }
    }
};

int main(void){
    double g;
    int k,n,m;
    cin>>g;
    cin>>k;
    cin>>n;
    cin>>m;

    graph gr(n);
    
    for(int i=0; i<m; i++){
        int u,v,c;
        double p;
        cin>>u>>v>>p>>c;
        gr.insert(u,v,-1*log10(1-p), c);
    }

    double a[n*(k+1)];
    gr.SpecialDijkstra(g, k, a);
    
    int f = 1;
    for(int i=(n-1)*(k+1); i<n*(k+1); i++){
        if(a[i]<=g && a[i]!=-1){
            cout<<"Yes\n";
            f = 0;
            break;
        }
    }
    if(f)
        cout<<"No\n";
}
