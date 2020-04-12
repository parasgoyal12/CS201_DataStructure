#include<iostream>
using namespace std;
template <typename T>
class Node{
    private:
        T key;
        Node<T> *left;
        Node<T> *right;
        // Node<T> *parent;
        int height;
    public:
        Node(T v){
            key=v;
            left=NULL;
            right=NULL;
            // parent=NULL;
            height=1;
        }
        Node<T>* get_left(){
            return left;
        }
        Node<T>* get_right(){
            return right;
        }
        T get_key(){
            return key;
        }
        int get_height(){
            return height;
        }
        void set_left(Node<T>* l){
            left=l;
        }
        void set_right(Node<T>* r){
            right=r;
        }
        void set_key(T k){
            key=k;
        }
        void set_height(int h){
            height=h;
        }
};
template<typename T>
class AVLTree{
    private:
        Node<T>* root;
        int status;
        int height(Node<T> *N)  
        {  
            if (N == NULL)  
            return 0;  
            return N->get_height();  
        }  
        Node<T> *rightRotate(Node<T> *y)  
        {  
            Node<T> *x = y->get_left();  
            Node<T> *T2 = x->get_right();  
            // cout<<"I was Here "<< y->key<<endl;
            x->set_right(y);  
            y->set_left(T2);  
    
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            // cout<<x->key<<"  Blabla"<<endl<<endl;
        return x;  
        }
        Node<T> *leftRotate(Node<T> *x)  
        {  
            Node<T> *y = x->get_right();  
            Node<T> *T2 = y->get_left();  
   
            y->set_left(x);  
            x->set_right(T2);  
    
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
   
            return y;  
        }  
        Node<T>* insertNode(Node<T>*toor,T k){
            if(toor==NULL){
                status=1;
                // cout<<"Success"<<endl;
                return new Node<T>(k);
            }
            if(toor->get_key()>k)toor->set_left(insertNode(toor->get_left(),k));
            else if(toor->get_key()<k)toor->set_right(insertNode(toor->get_right(),k));
            else{
                status=0; 
                // cout<<"Fail"<<endl;
                return toor;
            }

            toor->set_height((height(toor->get_left())>height(toor->get_right()))?(height(toor->get_left())+1):(height(toor->get_right())+1));
            int diff= height(toor->get_left())-height(toor->get_right());

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
        Node<T>* search(Node<T>* toor,T k){
            if(toor==NULL) return NULL;
            if(toor->get_key()==k) return toor;
            else if(toor->get_key()<k)return search(toor->right,k);
            else return search(toor->left,k);
        }
        Node<T>* findReplacement(Node<T>* temp){
            temp=temp->get_right();     
            while (temp->get_left() != NULL)  
                temp = temp->get_left();  
            return temp;  
        }
        int balance(Node<T>* temp){
            if(temp==NULL)return 0;
            return height(temp->get_left())-height(temp->get_right());
        }
        Node<T>* deleteNode(Node<T>* toor,T k){
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
                    Node<T>*temp;
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
                    Node<T>*replacement=findReplacement(toor);
                    toor->set_key(replacement->get_key());
                    // toor->right=deleteNode(replacement,replacement->key); Erroneous because it can cause imbalance
                    toor->set_right(deleteNode(toor->get_right(),replacement->get_key()));
                }
            }
            //Could be writeen above only
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
        int insert(T k){
            root=insertNode(root,k);
            if(status == 1){
                status=0;
                
                return 1;
            }
            else return status;
        }
        Node<T>* Nodesearch(T k){
            Node<T>* result= search(root,k);
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
        // void preorder(Node<T> *toor){
        //     if(toor==NULL)return;
        //     cout<<toor->get_key()<<"  "<<toor->get_height()<<endl;
        //     preorder(toor->get_left());
        //     preorder(toor->get_right());
            
        //     return;
        // }
        // Node<T>* get(){
        //     return root;
        // }
};

int main(){
    AVLTree<int>* tree =new AVLTree<int>();
    tree->insert(9);
    tree->insert(5);
    tree->insert(10);
    tree->insert(0);
    tree->insert(6);
    tree->insert(11);
    tree->insert(-1);
    tree->insert(1);
    tree->insert(2);
    // tree->preorder(tree->get());
    // cout<<tree->Nodesearch(7)<<endl;
    cout<<endl<<endl;
    tree->remove(10);
    // tree->preorder(tree->get());
}