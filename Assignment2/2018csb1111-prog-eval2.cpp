#include<iostream>
#define INT_MIN -9999999.0
#define INT_MAX 99999999.0
using namespace std;
double curr;
class CarNode{
    public:
    int reg;
    double x;
    double v;
    CarNode(){
        reg=-9999;
        x=-898665966;
        v=-895656512;
    }
    CarNode(int r,double d,double s){
        reg=r;
        x=d;
        v=s;
    }
    bool operator <(CarNode t){
        double car_data=x+v*curr;
        double cart_data=t.x+(t.v)*curr;
        if(car_data<cart_data)
        return true;
        else if(car_data>cart_data)return false;
        else{
            if(v<(t.v))return true;
            else return false;
        }
    }
    bool operator >(CarNode t){
        double car_data=x+v*curr;
        double cart_data=t.x+(t.v)*curr;
        if(car_data>cart_data)
        return true;
        else if(car_data<cart_data)return false;
        else{
            if(v>(t.v))return true;
            else return false;
        }
    }
    bool operator ==(CarNode t){
        double car_data=x+v*curr;
        double cart_data=t.x+(t.v)*curr;
        if(car_data==cart_data && v==t.v)return true;
        else return false;
        
    }
};
template <typename T,typename T1,typename T2>
class Node{
    private:
    T key;
    Node<T,T1,T2>* left;
    Node<T,T1,T2>* right;
    int height;
    public:
        int hi1;//denotes predcessor connection
        int hi2;//denotes succesor connnection
        T1 x;
        T2 v;
        Node(T k,T1 d,T2 s){
            key=k;
            x=d;
            v=s;
            left=NULL;
            right=NULL;
            hi1=-1;
            hi2=-1;
        }
        void set_key(T k){
            key=k;
        }
        Node<T,T1,T2>* get_left(){
            return left;
        }
        Node<T,T1,T2>* get_right(){
            return right;
        }
        Node<T,T1,T2>* set_right(Node* r){
            right=r;
        }
        Node<T,T1,T2>* set_left(Node* l){
            left=l;
        }
        void set_height(int h){
            height=h;
        }
        int get_height(){
            return height;
        }
        T get_key(){
            return key;
        }
};
class HeapNode{
    public:
    double t;
    Node<CarNode,double,double>* left;
    Node<CarNode,double,double>* right;
    HeapNode(){
        t=INT_MIN;
        left=NULL;
        right=NULL;
    }
    HeapNode(Node<CarNode,double,double>*l,Node<CarNode,double,double>*r){
        if(l!=NULL and r!=NULL){left=l;
        right=r;
        double left_xcurr=l->x;
        double right_xcurr=r->x;
        if(l->v != r->v)
        t=(right_xcurr-left_xcurr)/((r->v)-(l->v));}
        else{
            t=INT_MIN;
            left=NULL;
            right=NULL;
        }
    }
};
class MaxHeap{
    public:
    HeapNode* arr;
    int size;
    int capacity;
    MaxHeap(int cap){
        size=0;
        capacity=cap;
        arr=new HeapNode[cap];
    }
    int parent(int i){return (i-1)/2;}
    int left(int i){return 2*i+1;}
    int right(int i){return 2*(i+1);}
    void swap(HeapNode*a,HeapNode*b){
        HeapNode temp=*a;
        *a=*b;
        *b=temp;
    }
    HeapNode getMax(){return arr[0];}
    int insertKey(HeapNode k){
        if(size==(capacity))return -1;
        arr[size]=k;
        int i=size;
        if(arr[i].left!=NULL && arr[i].right!=NULL){
        arr[size].left->hi2=i;
        arr[size].right->hi1=i;}

        size=size+1;
        while(i!=0 && arr[parent(i)].t<arr[i].t){
            if(arr[i].left!=NULL && arr[i].right!=NULL && arr[parent(i)].left!=NULL && arr[parent(i)].right!=NULL){
            arr[i].left->hi2=parent(i);
            arr[i].right->hi1=parent(i);
            arr[parent(i)].left->hi2=i;
            arr[parent(i)].right->hi1=i; }          
            swap(&arr[parent(i)],&arr[i]);
            i=parent(i);
        }
    }
    void increaseKey(int i){
        arr[i].t=INT_MAX;
        while(i!=0 && arr[parent(i)].t<arr[i].t){
            if(arr[i].left!=NULL && arr[i].right!=NULL && arr[parent(i)].left!=NULL && arr[parent(i)].right!=NULL){
            arr[i].left->hi2=parent(i);
            arr[i].right->hi1=parent(i);
            arr[parent(i)].left->hi2=i;
            arr[parent(i)].right->hi1=i; }   
            swap(&arr[parent(i)],&arr[i]);
            i=parent(i);
        }
    }
    void Heapify(int i){
        int l=left(i);
        int r=right(i);
        int largest=i;
        if(l<size && arr[l].t>arr[largest].t)largest=l;
        if(r<size && arr[r].t>arr[largest].t)largest=r;
        if(largest!=i){
            if(arr[i].left!=NULL && arr[i].right!=NULL && arr[largest].left!=NULL && arr[largest].right!=NULL){
            arr[i].left->hi2=largest;
            arr[i].right->hi1=largest;
            arr[largest].left->hi2=i;
            arr[largest].right->hi1=i; }   
            swap(&arr[largest],&arr[i]);
            Heapify(i);
        }
    }
    HeapNode extractMax(){
        // if(size<=0)return HeapNode(INT_MAX,NULL,NULL);
        if(size<=0)return HeapNode(NULL,NULL);
         if(size==1){
            size--;
            arr[size].left->hi2=-1;
            arr[size].right->hi1=-1;
            return arr[size];
        }
        HeapNode root= arr[0];
        root.left->hi2=-1;
        root.right->hi1=-1;
        arr[0]=arr[--size];
        arr[0].left->hi2=0;
        arr[0].right->hi1=0;
        Heapify(0);
        return root;
    }
    void deleteKey(int i){
        // HeapNode t(INT_MAX,NULL,NULL);
        increaseKey(i);
        extractMax();
    }
    void updateLeft(int i,Node<CarNode,double,double>*l){
        arr[i].left=l;
    }
    void updateRight(int i,Node<CarNode,double,double>*r){
        arr[i].right=r;
    }
   void test(){
         for(int i=0;i<size;i++)cout<<"##"<<arr[i].t<<" "<<arr[i].left->get_key().reg<<"  "<<arr[i].right->get_key().reg<<endl;
     }
};
class PrintNode{
    public:
    double x;
    int r;
    double v;
    PrintNode(){
        r=-1;
        x=-999999.0;
    }
    PrintNode(int reg,double pos,double s){
        r=reg;
        x=pos;
        v=s;
    }
    bool operator <(PrintNode b){
        if(x<b.x)return true;
        else if(x>b.x)return false;
        if(r<b.r)return true;
        else return false;
    }
    bool operator >(PrintNode b){
        if(x>b.x)return true;
        else if(x<b.x)return false;
        if(r>b.r)return true;
        else return false;
    }
    bool operator ==(PrintNode b){
        if(x==b.x && r==b.r)return true;
        else return false;
    }
};
template<typename T,typename T1,typename T2>
class AVLTree{
    private:
        Node<T,T1,T2>* root;
        int status;
     
        int height(Node<T,T1,T2> *N)  
        {  
            if (N == NULL)  
            return 0;  
            return N->get_height();  
        }
        Node<T,T1,T2> *rightRotate(Node<T,T1,T2> *y)  
        {  
            Node<T,T1,T2> *x = y->get_left();  
            Node<T,T1,T2> *t2 = x->get_right(); 
            x->set_right(y);  
            y->set_left(t2);
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            return x;  
        }
        Node<T,T1,T2> *leftRotate(Node<T,T1,T2> *x)  
        {  
            Node<T,T1,T2> *y = x->get_right();  
            Node<T,T1,T2> *t2 = y->get_left();  
   
            y->set_left(x);  
            x->set_right(t2);
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
   
            return y;  
        }
        void supec(Node<T,T1,T2>* toor,Node<T,T1,T2>** succesor,Node<T,T1,T2>** pred,T k){
            if(toor==NULL)return;
            T info=toor->get_key();

            if(info==k){
                if (toor->get_left() != NULL) 
                { 
                    Node<T,T1,T2>* temp = toor->get_left(); 
                    while (temp->get_right()) 
                        temp = temp->get_right(); 
                    *pred = temp ; 
                } 
                if (toor->get_right() != NULL) 
                { 
                    Node<T,T1,T2>* temp = toor->get_right() ; 
                    while (temp->get_left()) 
                        temp = temp->get_left() ; 
                    *succesor = temp ; 
                } 
                return ; 
            }

            if(info>k){
                *succesor=toor;
                supec(toor->get_left(),succesor,pred,k);
            }
            else{
                *pred=toor;
                supec(toor->get_right(),succesor,pred,k);
            }
            return;
        }
        Node<T,T1,T2>* insertNode(Node<T,T1,T2>*toor,T k,T1 x,T2 v){
            if(toor==NULL){
                status=1;
                Node<T,T1,T2>* temp= new Node<T,T1,T2>(k,x,v);
                // supec(root,&(temp->succ),&(temp->pred),k);
                // if(temp->succ!=NULL)temp->succ->pred=temp;
                // if(temp->pred!=NULL)temp->pred->succ=temp;
                return temp;
            }
            if(toor->get_key()>k)toor->set_left(insertNode(toor->get_left(),k,x,v));
            else if(toor->get_key()<k)toor->set_right(insertNode(toor->get_right(),k,x,v));
            else{
                status=0; 
                // cout<<"Fail"<<endl;
                return toor;
            }

            

            // cout<<"\n"<<toor->get_key()<< "  "<<toor->n_left<<"  "<<toor->n_right<<endl; 
            //Update the height of the nodes
            toor->set_height((height(toor->get_left())>height(toor->get_right()))?(height(toor->get_left())+1):(height(toor->get_right())+1));
            int diff= height(toor->get_left())-height(toor->get_right());
            //Balancing Here
            if(diff>1 && k<toor->get_left()->get_key())return rightRotate(toor);
            if(diff<-1 && k>toor->get_right()->get_key())return leftRotate(toor);
            if(diff>1 && k>toor->get_left()->get_key()){
                toor->set_left(leftRotate(toor->get_left()));
                return rightRotate(toor);
            }
            if(diff<-1 && k<toor->get_right()->get_key()){
                toor->set_right(rightRotate(toor->get_right()));
                return leftRotate(toor);
            }
            return toor;
        } 
        Node<T,T1,T2>* insertNode2(Node<T,T1,T2>*toor,T k,T1 x,T2 v,Node<T,T1,T2>*succ,Node<T,T1,T2>*pred,MaxHeap* h){
            if(toor==NULL){
                status=1;
                Node<T,T1,T2>* temp= new Node<T,T1,T2>(k,x,v);
                
                if(pred!=NULL){
                    if(succ!=NULL){
                        if(pred->hi2!=-1 && succ->hi1!=-1){
                            int heapindex=pred->hi2;
                            h->deleteKey(heapindex);
                        }
                            double pred_v=pred->v;
                            double pred_x=pred->x+pred_v*curr;
                            double succ_v=succ->v;
                            double succ_x=succ->x+succ_v*curr;
                            if(v!=pred_v){
                            bool coll_1=((x+v*curr-pred_x)/(v-pred_v))<0;
                            if(coll_1)h->insertKey(HeapNode(pred,temp));
                            }
				if(v!=succ_v){
				bool coll_2=((x+v*curr-succ_x)/(v-succ_v))<0;
                            
                            if(coll_2)h->insertKey(HeapNode(temp,succ));
			}
                    }
                    else{
                        double pred_v=pred->v;
                        double pred_x=pred->x+pred_v*curr;
                        bool coll_1=((x+v*curr-pred_x)/(v-pred_v))<0;
                        if(coll_1)h->insertKey(HeapNode(pred,temp));
                    }
                }
                else{
                    if(succ!=NULL){
                        double succ_v=succ->v;
                        double succ_x=succ->x+succ_v*curr;
                        bool coll_2=((x+v*curr-succ_x)/(v-succ_v))<0;
                        if(coll_2)h->insertKey(HeapNode(temp,succ));
                    }
                }

                return temp;
            }
            if(toor->get_key()>k)toor->set_left(insertNode2(toor->get_left(),k,x,v,succ,pred,h));
            else if(toor->get_key()<k)toor->set_right(insertNode2(toor->get_right(),k,x,v,succ,pred,h));
            else{
                status=0; 
                return toor;
            }
            toor->set_height((height(toor->get_left())>height(toor->get_right()))?(height(toor->get_left())+1):(height(toor->get_right())+1));
            int diff= height(toor->get_left())-height(toor->get_right());
            //Balancing Here
            if(diff>1 && k<toor->get_left()->get_key())return rightRotate(toor);
            if(diff<-1 && k>toor->get_right()->get_key())return leftRotate(toor);
            if(diff>1 && k>toor->get_left()->get_key()){
                toor->set_left(leftRotate(toor->get_left()));
                return rightRotate(toor);
            }
            if(diff<-1 && k<toor->get_right()->get_key()){
                toor->set_right(rightRotate(toor->get_right()));
                return leftRotate(toor);
            }
            return toor;
        } 
        Node<T,T1,T2>* findReplacement(Node<T,T1,T2>* temp){
            temp=temp->get_right();     
            while (temp->get_left() != NULL)  
                temp = temp->get_left();  
            return temp;  
        }
        int balance(Node<T,T1,T2>* temp){
            if(temp==NULL)return 0;
            return height(temp->get_left())-height(temp->get_right());
        }
        Node<T,T1,T2>* deleteNode(Node<T,T1,T2>* toor,T k){
            if(toor==NULL){
                status=0;
                return NULL;
            }
            if(k>toor->get_key()){
                toor->set_right(deleteNode(toor->get_right(),k));
            }
            else if(k<toor->get_key()){
                toor->set_left(deleteNode(toor->get_left(),k));
            }
            else{
                if(toor->get_right()==NULL || toor->get_left()==NULL){
                    Node<T,T1,T2>*temp;
                    if(toor->get_left()==NULL)temp=toor->get_right();
                    else temp=toor->get_left();
                    if(temp==NULL){
                        temp=toor;
                        toor=NULL;
                    }
                    else *toor=*temp;
                    delete temp;
                    status=1;
                }
                //both childs are non-NULL and have something then we find the succesor(when keys are arranged in ascending order)
                else
                {
                    Node<T,T1,T2>*replacement=findReplacement(toor);
                    toor->set_key(replacement->get_key());
                    toor->x=replacement->x;
                    toor->v=(replacement->v);
                    // toor->right=deleteNode(replacement,replacement->key); Erroneous because it can cause imbalance
                    toor->set_right(deleteNode(toor->get_right(),replacement->get_key()));
                }
            }
            if(toor==NULL)return NULL; //this statment is for the case of both NULL childs of the Node to be deleted(in short, for leaf node:-])

            toor->set_height((height(toor->get_left())>height(toor->get_right()))?(height(toor->get_left())+1):(height(toor->get_right())+1));
            int bal=height(toor->get_left())-height(toor->get_right());
            int balleft=balance(toor->get_left());
            int balright=balance(toor->get_right());
            // cout<<"FRIEND "<<bal <<" "<<balleft<<" "<<balright<<endl;
            if(bal>1 && balleft>=0){return rightRotate(toor);}
            if(bal<-1 && balright<=0)return leftRotate(toor);
            if(bal>1 && balleft<0){
                toor->set_left(leftRotate(toor->get_left()));
                return rightRotate(toor);
            }
            if(bal<-1 && balright>0){
                toor->set_right(rightRotate(toor->get_right()));
                return leftRotate(toor);
            }
            return toor;
        }
        Node<T,T1,T2>* deleteNode2(Node<T,T1,T2>* toor,T k,Node<T,T1,T2>*succ,Node<T,T1,T2>*pred,MaxHeap*h){
            if(toor==NULL){
                status=0;
                return NULL;
            }
            if(k>toor->get_key()){
                toor->set_right(deleteNode2(toor->get_right(),k,succ,pred,h));
            }
            else if(k<toor->get_key()){
                toor->set_left(deleteNode2(toor->get_left(),k,succ,pred,h));
            }
            else{
                
                if(toor->get_right()==NULL || toor->get_left()==NULL){
                    if(toor->hi1!=-1)h->deleteKey(toor->hi1);
                    if(toor->hi2!=-1)h->deleteKey(toor->hi2);
                    if(pred!=NULL){
                      if(succ!=NULL){
                          if(succ->v!=pred->v){
                          bool colli=((succ->x-pred->x)/(succ->v-pred->v)+curr)<0;
                          if(colli)h->insertKey(HeapNode(pred,succ));}
                      }  
                    }
                    Node<T,T1,T2>*temp;
                    if(toor->get_left()==NULL)temp=toor->get_right();
                    else temp=toor->get_left();
                    
                    

                    if(temp==NULL){
                        temp=toor;
                        toor=NULL;
                    }
                    else{ 
                        *toor=*temp;
                        if(toor->hi2!=-1)h->updateLeft(toor->hi2,toor);
                        if(toor->hi1!=-1)h->updateRight(toor->hi1,toor);
                    }

                    delete temp;
                    status=1;
                }
                //both childs are non-NULL and have something then we find the succesor(when keys are arranged in ascending order)
                else
                {
                    Node<T,T1,T2>*replacement=findReplacement(toor);
                    toor->set_key(replacement->get_key());
                    toor->x=replacement->x;
                    toor->v=(replacement->v);
                    int temp1,temp2;
                    temp1=toor->hi1;
                    temp2=toor->hi2;
                    toor->hi1=replacement->hi1;
                    toor->hi2=replacement->hi2;
                    if(toor->hi2!=-1)h->updateLeft(toor->hi2,toor);
                    if(toor->hi1!=-1)h->updateRight(toor->hi1,toor);
                    replacement->hi1=temp1;
                    replacement->hi2=temp2;
                    // toor->right=deleteNode(replacement,replacement->key); Erroneous because it can cause imbalance
                    toor->set_right(deleteNode2(toor->get_right(),replacement->get_key(),succ,pred,h));
                }
            }
            if(toor==NULL)return NULL; //this statment is for the case of both NULL childs of the Node to be deleted(in short, for leaf node:-])

            toor->set_height((height(toor->get_left())>height(toor->get_right()))?(height(toor->get_left())+1):(height(toor->get_right())+1));
            int bal=height(toor->get_left())-height(toor->get_right());
            int balleft=balance(toor->get_left());
            int balright=balance(toor->get_right());
            // cout<<"FRIEND "<<bal <<" "<<balleft<<" "<<balright<<endl;
            if(bal>1 && balleft>=0){return rightRotate(toor);}
            if(bal<-1 && balright<=0)return leftRotate(toor);
            if(bal>1 && balleft<0){
                toor->set_left(leftRotate(toor->get_left()));
                return rightRotate(toor);
            }
            if(bal<-1 && balright>0){
                toor->set_right(rightRotate(toor->get_right()));
                return leftRotate(toor);
            }
            return toor;
        }
        Node<T,T1,T2>* search(Node<T,T1,T2>* toor,T k){
            if(toor==NULL) return NULL;
            if(toor->get_key()==k) return toor;
            else if(toor->get_key()<k)return search(toor->get_right(),k);
            else return search(toor->get_left(),k);
        }
        public:
        int index;
        AVLTree(){
            root=NULL;
            status=0;
            index=0;
        }
        int insert(T k, T1 x, T2 v){
            root=insertNode(root,k,x,v);
            if(status == 1){
                status=0;
                
                return 1;
            }
            else return status;
        }
        int insert2(T k, T1 x,T2 v,MaxHeap*h){
            Node<T,T1,T2>*succ=NULL;
            Node<T,T1,T2>*pred=NULL;
            supec(root,&succ,&pred,k);
            
            root=insertNode2(root,k,x,v,succ,pred,h);
            if(status==1){
                status=0;return 1;
            }
            else return 0;
        }
        Node<T,T1,T2>* Nodesearch(T k){
            Node<T,T1,T2>* result= search(root,k);
            return result;
        }
        int remove(T k){
            root=deleteNode(root,k);
            if(status==1){
                status=0;
                return 1;
            }
            else return status;
        }
        int remove2(T k,MaxHeap*h){
            Node<T,T1,T2>*succ=NULL;
            Node<T,T1,T2>*pred=NULL;
            supec(root,&succ,&pred,k);
            root=deleteNode2(root,k,succ,pred,h);
            if(status==1){
                status=0;
                return 1;
            }
            else return status;
        }
        
    
        // Helper functions used to find the Current State of the HIghway
        void traversal(Node<T,T1,T2> *toor,PrintNode *arr){
            if(toor==NULL)return;
            // double xcurr=toor->get_key().x;
            // if(x!=xcurr)cout<<"\n"<<xcurr<<" ";
            traversal(toor->get_left(),arr);
            // cout<<toor->get_key().r<<" ";
            arr[index++]=toor->get_key();
            traversal(toor->get_right(),arr);
            
        }
        Node<T,T1,T2>* get(){
            return root;
        }

};

class Highway{
    public:
    AVLTree<int,double,double>* master=new AVLTree<int,double,double>();
    AVLTree<CarNode,double,double>* xtree=new AVLTree<CarNode,double,double>();
    MaxHeap *h=new MaxHeap(10000);
    int insert(int r,double x,double v){
        if(master->insert(r,x-v*curr,v)==1){
           
            double x0=x-v*curr;
            CarNode a=CarNode(r,x0,v);
            if(xtree->insert2(a,x0,v,h)==1)
            return 1;
            else return 0;
        }
        else return 0;
    }
    
    int remove(int r){
        Node<int,double,double>* temp=master->Nodesearch(r);
        if(temp==NULL){
            return 0;
        }

        double x=temp->x;
        double v=temp->v;
        CarNode a(r,x,v);
        master->remove(r);
        xtree->remove2(a,h);
        return 1;
    }
    void next_crossings(){
        double t_of_cos=-(h->getMax().t);
        AVLTree<PrintNode,int,int>* cross=new AVLTree<PrintNode,int,int>();
        int count=0;
        if(h->size==0)return;
        while((-(h->getMax().t))==t_of_cos){
            count++;
            HeapNode a=h->extractMax();
            if(a.left==NULL || a.right==NULL)break;
            int car1_reg=a.left->get_key().reg;
            double car1_x=a.left->get_key().x+(a.left->get_key().v)*t_of_cos;
            int car2_reg=a.right->get_key().reg;
            double car2_x=a.right->get_key().x+(a.right->get_key().v)*t_of_cos;
            PrintNode one(car1_reg,car1_x,a.left->get_key().v);
            PrintNode two(car2_reg,car2_x,a.right->get_key().v);
            cross->insert(one,0,0);
            cross->insert(two,0,0);
        }
        PrintNode arr[2*(count+1)];

        cross->traversal(cross->get(),arr);
        double xn=arr[0].x;
        
        for(int i=0;i<cross->index;i++){
            PrintNode next_car=arr[i];
            if(xn!=next_car.x||i==0){
                xn=next_car.x;
                if(i==0)cout<<xn<<" ";
                else cout<<"\n"<<xn<<" ";
            }
            cout<<next_car.r<<" ";
        }
        cout<<endl;
        for(int i=0;i<cross->index;i++){
            PrintNode next_car=arr[i];
            Highway::remove(next_car.r);
        }
        // cout<<"Success"<<endl;
        curr=t_of_cos;
        for(int i=0;i<cross->index;i++){
            PrintNode next_car=arr[i];
		//cout<<next_car.r<<endl;
            Highway::insert(next_car.r,next_car.x,next_car.v);
        }
        
    }
   void test(){
         h->test();
     }

};
int main(){
    curr=0;
     Highway* a=new Highway();
    //  cout<<a->insert(13,-4,4)<<endl;
    //  cout<<a->insert(27,-2,2)<<endl;
    //  cout<<a->insert(5,-1,1)<<endl;
    //  cout<<a->insert(16,1,1)<<endl;
    //  cout<<a->insert(33,2,1)<<endl;
    //  cout<<a->insert(8,3,3)<<endl;
    //  cout<<a->insert(42,5,1)<<endl;
    //  a->test();
    //  a->next_crossings();
    //  a->insert(51,4,2);
    // cout<<curr<<endl;
      //a->test();
    int test,r;
    double x,v;
    cin>>test;
    while (test--)
    {
        int fid;
        cin>>fid;
        switch(fid){
            case 1:cin>>r>>x>>v;
                    a->insert(r,x,v);
			//cout<<test<<endl;
			//a->test();
                    break;
            case 2:cin>>r;
                    a->remove(r);
			//cout<<test<<endl;
			//a->test();
                    break;
            case 3:
                    a->next_crossings();
			//a->test();
                    break;
        }
    }
}
