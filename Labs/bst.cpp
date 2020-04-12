#include<iostream>
using namespace std;
template<class T>
class Node{
    private:
         T x;
         Node<T> *left;
         Node<T> *right;
         Node<T> *parent;
         int nleft;
    public:
        Node(T v){
            x=v;
            left=NULL;
            right=NULL;
            parent=NULL;
            nleft=0;
        }
        Node<T>* get_right(){
            return right;
        }
        Node<T>* get_left(){
            return left;
        }
        Node<T>* get_parent(){
            return parent;
        }
        T get_x(){
            return x;
        }
        int get_nleft(){
            return nleft;
        }
        void set_right(Node<T>*r){
            right=r;
        }
        void set_left(Node<T>*l){
            left=l;
        }
        void set_parent(Node<T>*p){
            parent = p;
        }
        void set_x(T v){
            x=v;
        }
        void set_nleft(int x){
            nleft =x;
        }
};
template <class T>
class BST{
    private:
        Node<T>* root;
        int n;
        int h;
        int cal_height(Node<T>* r){
            if(r==NULL){
                return 0;
            }
            int hleft=cal_height(r->get_left())+1;
            int hright=cal_height(r->get_right())+1;
            return (hright>=hleft)?hright:hleft;
        }
    public:
        BST(){
            root=NULL;
            n=0;h=0;
        }
        Node<T>* search(T v){
            Node<T>*temp=root;
            while(temp!=NULL){
                if(temp->get_x()==v){
                    return temp;
                }
                else if(temp->get_x()>v){
                    temp=temp->get_left();
                }
                else if(temp->get_x()<v){
                    temp=temp->get_right();
                }
            }
            return temp;
        }
        int insert(T v){
            if(root==NULL){
                root=new Node<T>(v);
                return 1;
            }
            Node<T>*p=search(v);
            if(p!=NULL){
                return 0;//insert unsuccesful
            }
            Node<T>* alpha=new Node<T>(v);
            Node<T>*temp=root;
            while(1){
                if(temp->get_x()>v){
                    if(temp->get_left()==NULL){
                        temp->set_nleft(temp->get_nleft()+1);
                        temp->set_left(alpha);
                        alpha->set_parent(temp);
                        // cout<<"I am executed for "<<v<<endl;
                        return 1;
                    }
                    else {
                        temp->set_nleft(temp->get_nleft()+1);
                        temp=temp->get_left();
                        
                        // cout<<"I am executed for"<<v<<endl;
                    }
                }
                else {
                    if(temp->get_right()==NULL){
                        temp->set_right(alpha);
                        alpha->set_parent(temp);
                        return 1;
                    }
                    else temp=temp->get_right();
                }
            }
        }
        Node<T>* find_replacement(Node<T>* x){
            Node<T>* temp=x;
            temp=x->get_right();
            while(temp->get_left()!=NULL){

                temp=temp->get_left();
            }
            x->set_x(temp->get_x());
            return temp;
        }

        //Incomplete
        int delete_node(T v){
            Node<T>* temp=search(v);
            if(temp==NULL)return 0;
            
            if((temp->get_left()!=NULL)&&(temp->get_right()!=NULL)){
                temp=find_replacement(temp);
                // cout<<"Exe"<<endl;
            }
            if(temp==root){
                // cout<<"exe1"<<endl;
                if(root->get_left()!=NULL){
                    root=root->get_left();
                    
                }
                else{
                    root=root->get_right();
                }
                root->set_parent(NULL);
                delete temp;
                return 1;
            }
            Node<T>* p = temp->get_parent();
            if(temp->get_left()!=NULL){
                if(temp->get_parent()->get_left()==temp){
                    p->set_nleft(p->get_nleft()-1);
                    temp->get_parent()->set_left(temp->get_left());
                }
                else{

                    temp->get_parent()->set_right(temp->get_left());
                }
                temp->get_left()->set_parent(temp->get_parent());
                delete temp;
                
            }
            else if(temp->get_right()!=NULL){
                if(temp->get_parent()->get_left()==temp){
                    p->set_nleft(p->get_nleft()-1);
                    temp->get_parent()->set_left(temp->get_right());
                }
                else{
                    temp->get_parent()->set_right(temp->get_right());
                }
                temp->get_right()->set_parent(temp->get_parent());
                delete temp;
                
            }
            else {
                if(temp->get_parent()->get_left()==temp){
                    p->set_nleft(p->get_nleft()-1);
                    temp->get_parent()->set_left(NULL);
                }
                else temp->get_parent()->set_left(NULL);
                delete temp;
                
            }

            while(p->get_parent()!=NULL){
                 
               
                if(p->get_parent()->get_left()==p){
                   
                    p->get_parent()->set_nleft(p->get_nleft()-1);
                }
                p=p->get_parent();
            }
            
            return 1;
        }
        T order_statistics(int k){
            Node<T>* temp=root;
            while(1){
                if(k-1==temp->get_nleft()){
                    return temp->get_x();
                }
                else if(k-1<(temp->get_nleft())){
                    temp=temp->get_left();
                }
                else{
                    k=k-1-temp->get_nleft();
                    temp=temp->get_right();
                }
            }

        }
        int get_height(){
            return cal_height(root);
        }
        
};
// int main(){
//     BST<int>* tree=new BST<int>();
//     int arr[]={23,56,24,78,21,18,75,22};
//     cout<<tree->get_height()<<endl;

// }