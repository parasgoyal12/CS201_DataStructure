#include<iostream>
#include<climits>
using namespace std;
float curr;
class CarNode{
    public:
    int reg;
    float x;
    float v;
    CarNode(int r,float d,float s){
        reg=r;
        x=d;
        v=s;
    }
    bool operator <(CarNode t){
        float car_data=x+v*curr;
        float cart_data=t.x+(t.v)*curr;
        if(car_data<cart_data)
        return true;
        else if(car_data>cart_data)return false;
        else{
            if(v<(t.v))return true;
            else return false;
        }
    }
    bool operator >(CarNode t){
        float car_data=x+v*curr;
        float cart_data=t.x+(t.v)*curr;
        if(car_data>cart_data)
        return true;
        else if(car_data<cart_data)return false;
        else{
            if(v>(t.v))return true;
            else return false;
        }
    }
    bool operator ==(CarNode t){
        float car_data=x+v*curr;
        float cart_data=t.x+(t.v)*curr;
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
        Node<T,T1,T2>* succ;
        Node<T,T1,T2>* pred;
        T1 x;
        T2 v;
        Node(T k,T1 d,T2 s){
            key=k;
            x=d;
            v=s;
            left=NULL;
            right=NULL;
            succ=NULL;
            pred=NULL;
        }
        Node* get_left(){
            return left;
        }
        Node* get_right(){
            return right;
        }
        Node* set_right(Node* r){
            right=r;
        }
        Node* set_left(Node* l){
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
    float t;
    Node<CarNode,float,float>* left;
    Node<CarNode,float,float>* right;
    HeapNode(){
        t=INT_MIN;
        left=NULL;
        right=NULL;
    }
    HeapNode(Node<CarNode,float,float>*l,Node<CarNode,float,float>*r){
        left=l;
        right=r;
        float left_xcurr=l->x;
        float right_xcurr=r->x;
        if(l->v != r->v)
        t=(right_xcurr-left_xcurr)/((r->v)-(l->v));
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
                    toor->set_x(replacement->get_x());
                    toor->set_d(replacement->get_d());
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
        public:
        AVLTree(){
            root=NULL;
            status=0;
        }
         int insert(T k, T1 x, T2 v){
            root=insertNode(root,k,x,v);
            if(status == 1){
                status=0;
                
                return 1;
            }
            else return status;
        }
        //Helper functions used to find the Current State of the HIghway
        // void traversal(Node<T,T1,T2> *toor){
        //     if(toor==NULL)return;
        //     if(toor->succ!=NULL&&toor->pred!=NULL)
        //     cout<<toor->get_key()<<"  "<<toor->succ->get_key()<<"  "<<toor->pred->get_key()<<" "<<endl;
           
            

        //     traversal(toor->get_left());
        //     traversal(toor->get_right());
            
        //     return;
        // }
        // Node<T,T1,T2>* get(){
        //     return root;
        // }

};
int main(){
    AVLTree<int,float,float>* tree =new AVLTree<int,float,float>();
    tree->insert(0,1.0,1.0);
    tree->insert(1,1.0,2.0);
    tree->insert(2,1.0,1.0);
    tree->insert(5,2.0,5.0);
    tree->insert(4,5.0,8.0);
    tree->insert(89,5.0,2.0);
    tree->insert(34,5.0,5.0);
    tree->insert(11,3.0,5.0);
    tree->traversal(tree->get());

}