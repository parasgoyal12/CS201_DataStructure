/**CS201 Lab Evaluation 1
 * Name-Paras Goyal
 * Roll No.-2018CSB1111
 * Help taken from GeeksForGeeks ,StackOverflow and NPTEL for coding the AVL Tree.
 */
#include<iostream>
using namespace std;
template <typename T,typename T1, typename T2>
class Node{
    private:
        T key;
        T1 d;
        T2 x;
        Node<T,T1,T2> *left;
        Node<T,T1,T2> *right;
        // Node<T,T1,T2> *parent;
        int height;
        int n_left;
        int n_right;
    public:

        Node(T v,T1 dir,T2 xco){
            key=v;
            d=dir;
            x=xco;
            left=NULL;
            right=NULL;
            n_left=0;
            n_right=0;
            // parent=NULL;
            height=1;
        }
        int get_n_left(){
            return n_left;
        }
        int get_n_right(){
            return n_right;
        }
        int set_n_left(int x){
            n_left=x;
        }
        int set_n_right(int x){
            n_right=x;
        }
        Node<T,T1,T2>* get_left(){
            return left;
        }
        Node<T,T1,T2>* get_right(){
            return right;
        }
        T get_key(){
            return key;
        }
        T2 get_x(){
            return x;
        }
        T1 get_d(){
            return d;
        }
        int get_height(){
            return height;
        }
        void set_left(Node<T,T1,T2>* l){
            left=l;
        }
        void set_right(Node<T,T1,T2>* r){
            right=r;
        }
        void set_d(T1 D){
            d=D;
        }
        void set_x(T2 X){
            x=X;
        }
        void set_key(T k){
            key=k;
        }
        void set_height(int h){
            height=h;
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
        //utility function to get the number of nodes in a subtree.
        int calc_nodes(Node<T,T1,T2>* N){
            if(N==NULL)return 0;
            else return (N->get_n_left() + N->get_n_right() + 1);
        }  
        Node<T,T1,T2> *rightRotate(Node<T,T1,T2> *y)  
        {  
            Node<T,T1,T2> *x = y->get_left();  
            Node<T,T1,T2> *t2 = x->get_right();  
            // cout<<"I was Here "<< y->key<<endl;
            x->set_right(y);  
            y->set_left(t2);  
            //Order of updating Y and X for n_left and n_right is important.....!!Warning
            y->set_n_left(calc_nodes(y->get_left()));
            y->set_n_right(calc_nodes(y->get_right()));
            x->set_n_left(calc_nodes(x->get_left()));
            x->set_n_right(calc_nodes(x->get_right()));
            //  cout<<"\n"<<x->get_key()<< "  "<<x->n_left<<"  "<<x->n_right<<endl;
            //   cout<<"\n"<<y->get_key()<< "  "<<y->n_left<<"  "<<y->n_right<<endl;
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            // cout<<x->key<<"  Blabla"<<endl<<endl;
            return x;  
        }
        Node<T,T1,T2> *leftRotate(Node<T,T1,T2> *x)  
        {  
            Node<T,T1,T2> *y = x->get_right();  
            Node<T,T1,T2> *t2 = y->get_left();  
   
            y->set_left(x);  
            x->set_right(t2);  
            //Order of updating Y and X nodes for n_left and n_right is important.....!!Warning
            x->set_n_left(calc_nodes(x->get_left()));
            x->set_n_right(calc_nodes(x->get_right()));
            y->set_n_left(calc_nodes(y->get_left()));
            y->set_n_right(calc_nodes(y->get_right()));
            //  cout<<"\n"<<x->get_key()<< "  "<<x->n_left<<"  "<<x->n_right<<endl;
            //   cout<<"\n"<<y->get_key()<< "  "<<y->n_left<<"  "<<y->n_right<<endl;
            x->set_height((height(x->get_left())>height(x->get_right()))?(height(x->get_left())+1):(height(x->get_right())+1));  
            y->set_height((height(y->get_left())>height(y->get_right()))?(height(y->get_left())+1):(height(y->get_right())+1));  
   
            return y;  
        }  
        Node<T,T1,T2>* insertNode(Node<T,T1,T2>*toor,T k,T1 d,T2 x){
            if(toor==NULL){
                status=1;
                // cout<<"Success"<<endl;
                return new Node<T,T1,T2>(k,d,x);
            }
            if(toor->get_key()>k)toor->set_left(insertNode(toor->get_left(),k,d,x));
            else if(toor->get_key()<k)toor->set_right(insertNode(toor->get_right(),k,d,x));
            else{
                status=0; 
                // cout<<"Fail"<<endl;
                return toor;
            }

            toor->set_n_left(calc_nodes(toor->get_left()));
            toor->set_n_right(calc_nodes(toor->get_right()));

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
        Node<T,T1,T2>* search(Node<T,T1,T2>* toor,T k){
            if(toor==NULL) return NULL;
            if(toor->get_key()==k) return toor;
            else if(toor->get_key()<k)return search(toor->get_right(),k);
            else return search(toor->get_left(),k);
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
                    toor->set_x(replacement->get_x());
                    toor->set_d(replacement->get_d());
                    // toor->right=deleteNode(replacement,replacement->key); Erroneous because it can cause imbalance
                    toor->set_right(deleteNode(toor->get_right(),replacement->get_key()));
                }
            }
            if(toor==NULL)return NULL; //this statment is for the case of both NULL childs of the Node to be deleted(in short, for leaf node:-])

            toor->set_n_left(calc_nodes(toor->get_left()));
            toor->set_n_right(calc_nodes(toor->get_right()));

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
        void supec(Node<T,T1,T2>* toor,Node<T,T1,T2>** succesor,Node<T,T1,T2>** pred,T k,double shift){
            if(toor==NULL)return;
            //shift=0 for same dir else shift=-t for dir=1 and shift=t for dir=0
            T info=toor->get_key()-2*shift;

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
                supec(toor->get_left(),succesor,pred,k,shift);
            }
            else{
                *pred=toor;
                supec(toor->get_right(),succesor,pred,k,shift);
            }
            return;
        }
        //for car in same same dir shift=0, else if dir=1 shift is -ve dir = 0 shift is +ve
        int sumup(Node<T,T1,T2>* toor,T d,double shift){
            if(toor==NULL)return 0;
            if((toor->get_key()-2*shift)<d) return sumup(toor->get_right(),d,shift);
            else if((toor->get_key()-2*shift)==d) return  toor->get_n_right();
            else return sumup(toor->get_left(),d,shift)+toor->get_n_right()+1;
        }
        int sumdown(Node<T,T1,T2>* toor,T d,double shift){
            if(toor==NULL)return 0;
            if((toor->get_key()-2*shift)>d) return sumdown(toor->get_left(),d,shift);
            else if((toor->get_key()-2*shift)==d) return  toor->get_n_left();
            else return sumdown(toor->get_right(),d,shift)+toor->get_n_left()+1;
        }
        
    public:
        AVLTree(){
            root=NULL;
            status=0;
        }
        int insert(T k, T1 d, T2 x){
            root=insertNode(root,k,d,x);
            if(status == 1){
                status=0;
                
                return 1;
            }
            else return status;
        }
        Node<T,T1,T2>* Nodesearch(T k){
            Node<T,T1,T2>* result= search(root,k);
            return result;
        }
        //Helper function for performing a delete operation on an AVL TREE. Actual task performed 
        int remove(T k){
            root=deleteNode(root,k);
            if(status==1){
                status=0;
                return 1;
            }
            else return status;
        }
        //function for finding the succesor of a node. Makes a private function call after detting appropriate values
        Node<T,T1,T2>* succesor(T cor,T1 d,double time){
            Node<T,T1,T2>* succesor,*pred;
            succesor=pred=NULL;
            if(d==0){
                supec(root,&succesor,&pred,cor,time);
            }
            else{
                time=-1*time;
                supec(root,&succesor,&pred,cor,time);
            }
            return succesor;
        }
        //function for finding the predessor of a node. This makes a call to the private function which performes the main task
        Node<T,T1,T2>* pred(T cor,T1 d,double time){
            Node<T,T1,T2>* succesor,*pred;
            succesor=pred=NULL;
            if(d==0){
                supec(root,&succesor,&pred,cor,time);
            }
            else{
                time=-1*time;
                supec(root,&succesor,&pred,cor,time);
            }
            // cout<<pred<<endl;
            return pred;
        }
        //helper function for finding number of nodes greater than a key. This makes a call to the private function which performes the main task
        int greater(T cor, T1 dir,double time){
            int sum;
            time=(dir==0)?time:(-1*time);
            sum=sumup(root,cor,time);
            return sum;
        }
        // helper function for finding number of nodes less than a key this makes a call to the private function which executes the main task
        int smaller(T cor,T1 dir,double time){
            int sum;
            time=(dir==0)?time:(-1*time);
            sum=sumdown(root,cor,time);
            return sum;
        }
        //Helper functions used to find the Current State of the HIghway
        // void traversal(Node<T,T1,T2> *toor,double t){
        //     if(toor==NULL)return;
        //     if(toor->get_d()==1)
        //     cout<<toor->get_key()<<"  "<<toor->get_d()<<"  "<<toor->get_x()+t<<" "<<endl;
        //     else
        //     cout<<toor->get_key()<<"  "<<toor->get_d()<<"  "<<toor->get_x()-t<<" "<<endl;

        //     traversal(toor->get_left(),t);
        //     traversal(toor->get_right(),t);
            
        //     return;
        // }
        // Node<T,T1,T2>* get(){
        //     return root;
        // }
};

class Highway{
    private:
    double curr;
    AVLTree<int,int,double>* master ;
    //1 means >--------->>------>>-------
    AVLTree<double,int,int>* dir1;
    //0 means <---------<<-------<<-------
    AVLTree<double,int,int>* dir0;
    public:
    Highway(){
        curr=0;
        //registration number direction position as at t=0
        master = new AVLTree<int,int,double>();
        //position as t=0 direction registration number
        dir1 = new AVLTree<double,int,int>();
        dir0=new AVLTree<double,int,int>();
    }
    int insert(int reg,double x,double t,int d){
        if(master->Nodesearch(reg)!=NULL)return 0;
        curr=t;
        //shifting the car back in time i.e. assuming the car entered on highway on past time at t=0 
        
        if(d==0){
            master->insert(reg,d,x+t);
            dir0->insert(x+t,d,reg);
        }
        else{
            master->insert(reg,d,x-t);
            dir1->insert(x-t,d,reg);
            
        }
        
        return 1;
    }
    //helper function to check the state of the highways
    // void printstate(){
    //     // master->traversal(master->get(),curr);
    //     master->traversal(master->get(),curr);
    //     cout<<endl;
    //     // dir0->traversal(dir0->get(),curr);

    // }
    int remove(int r,double t){
        Node<int,int,double>* temp=master->Nodesearch(r);
        if(temp==NULL){
            return 0;
        }

        double x=temp->get_x();
        int d=temp->get_d();
        curr=t;
        master->remove(r);
        if(d==0){
            dir0->remove(x);
            return 1;
        }
        else {
            dir1->remove(x);
            return 1;
        }
    }
    int find_immediate_left(int r,double t){
        Node<int,int,double>* car=master->Nodesearch(r);
        if(car==NULL)return -1;
       
        int direction=car->get_d();
        Node<double,int,int>* pred1;
        Node<double,int,int>* pred0;
        if(direction==1){
            pred1=dir1->pred(car->get_x(),1,0);
            pred0=dir0->pred(car->get_x(),0,t);
            if(pred1==NULL&&pred0==NULL)return -1;
            if(pred1==NULL)return pred0->get_x();
            if(pred0==NULL)return pred1->get_x();
            // cout<<pred1->get_x()<<"  "<<pred0->get_x()<<endl;
            if(pred1->get_key()>(pred0->get_key()-2*t))return pred1->get_x();
            else if(pred1->get_key()==(pred0->get_key()-2*t)){
                if(pred1->get_x()>pred0->get_x()){
                    cout<<pred0->get_x()<<" ";
                    return pred1->get_x();
                }
                else{
                    cout<<pred1->get_x()<<" ";
                    return pred0->get_x();
                }
            }
            else return pred0->get_x();
        }
        else{
            pred1=dir1->pred(car->get_x(),1,t);
            pred0=dir0->pred(car->get_x(),0,0);
            if(pred1==NULL&&pred0==NULL)return -1;
            if(pred1==NULL)return pred0->get_x();
            if(pred0==NULL)return pred1->get_x();
            // cout<<pred1->get_x()<<"  "<<pred0->get_x()<<endl;
            if((pred1->get_key()+2*t)>pred0->get_key())return pred1->get_x();
            else if(pred1->get_key()==(pred0->get_key()+2*t)){
                if(pred1->get_x()>pred0->get_x()){
                    cout<<pred0->get_x()<<" ";
                    return pred1->get_x();
                }
                else{
                    cout<<pred1->get_x()<<" ";
                    return pred0->get_x();
                }
            }
            else return pred0->get_x();            
        }

    }
    int find_immediate_right(int r,double t){
        Node<int,int,double>* car=master->Nodesearch(r);
        if(car==NULL)return -1;
       
        int direction=car->get_d();
        Node<double,int,int>* suc1;
        Node<double,int,int>* suc0;
        if(direction==1){
            suc1=dir1->succesor(car->get_x(),1,0);
            suc0=dir0->succesor(car->get_x(),0,t);
            if(suc1==NULL&&suc0==NULL)return -1;
            if(suc1==NULL)return suc0->get_x();
            if(suc0==NULL)return suc1->get_x();
            // cout<<suc1->get_x()<<"  "<<suc0->get_x()<<endl;
            if(suc1->get_key()<(suc0->get_key()-2*t))return suc1->get_x();
            else if(suc1->get_key()==(suc0->get_key()-2*t)){
                if(suc1->get_x()>suc0->get_x()){
                    cout<<suc0->get_x()<<" ";
                    return suc1->get_x();
                }
                else{
                    cout<<suc1->get_x()<<" ";
                    return suc0->get_x();
                }
            }
            else return suc0->get_x();
        }
        else{
            suc1=dir1->succesor(car->get_x(),1,t);
            suc0=dir0->succesor(car->get_x(),0,0);
            if(suc1==NULL&&suc0==NULL)return -1;
            if(suc1==NULL)return suc0->get_x();
            if(suc0==NULL)return suc1->get_x();
            // cout<<pred1->get_x()<<"  "<<pred0->get_x()<<endl;
            if((suc1->get_key()+2*t)<suc0->get_key())return suc1->get_x();
            else if(suc1->get_key()==(suc0->get_key()+2*t)){
                if(suc1->get_x()>suc0->get_x()){
                    cout<<suc0->get_x()<<" ";
                    return suc1->get_x();
                }
                else{
                    cout<<suc1->get_x()<<" ";
                    return suc0->get_x();
                }
            }
            else return suc0->get_x();            
        }
    }
    int count_right(int r,double t){
        Node<int,int,double>* car=master->Nodesearch(r);
        if(car==NULL)return -1;
        int direction=car->get_d();
        if(direction==1){
            int a=dir1->greater(car->get_x(),1,0);
            int b=dir0->greater(car->get_x(),0,t);
            return a+b;
        }
        else{
            int a=dir1->greater(car->get_x(),1,t);
            int b=dir0->greater(car->get_x(),0,0);
            return a+b;
        }
    }
    int count_left(int r,double t){
        Node<int,int,double>* car=master->Nodesearch(r);
        if(car==NULL)return -1;
        int direction=car->get_d();
        if(direction==1){
            int a=dir1->smaller(car->get_x(),1,0);
            int b=dir0->smaller(car->get_x(),0,t);
            return a+b;
        }
        else{
            int a=dir1->smaller(car->get_x(),1,t);
            int b=dir0->smaller(car->get_x(),0,0);
            return a+b;
        }
    }
    int number_of_crossings(int r,double t){
        Node<int,int,double>* car=master->Nodesearch(r);
        if(car==NULL)return -1;
        int direction=car->get_d();
        double x=car->get_x();
        if(direction==0){
            Node<double,int,int>* car2=dir1->Nodesearch(x-2*curr);
            //to solve the case when there is a car in oppsite direction at same x cordinate at t=curr;
            if(car2==NULL)
            return count_right(r,t)-count_right(r,curr);
            else 
            return count_right(r,t)-count_right(r,curr)-1;
        }
        else{
            Node<double,int,int>* car2=dir0->Nodesearch(x+2*curr);
            if(car2==NULL)return count_left(r,t)-count_left(r,curr);
            else return count_left(r,t)-count_left(r,curr)-1;
        }
    }
    
};
int main(){

    Highway* GTRoad = new Highway();

    int test,r,d;
    double x,t;
    cin>>test;
    while (test--)
    {
        int fid;
        cin>>fid;
        switch(fid){
            case 1:cin>>r>>x>>t>>d;
                    GTRoad->insert(r,x,t,d);
                    break;
            case 2:cin>>r>>t;
                    GTRoad->remove(r,t);
                    break;
            case 3:cin>>r>>t;
                    
                    cout<<GTRoad->find_immediate_left(r,t)<<endl;
                    break;
            case 4:cin>>r>>t;
            
                    cout<<GTRoad->find_immediate_right(r,t)<<endl;
                    break;
            case 5:cin>>r>>t;
            
                    cout<<GTRoad->count_left(r,t)<<endl;
                    break;
            case 6:cin>>r>>t;
            
                    cout<<GTRoad->count_right(r,t)<<endl;
                    break;
            case 7:cin>>r>>t;
                    
                    cout<<GTRoad->number_of_crossings(r,t)<<endl;
                    break;
            
            
        }
    }
        // GTRoad->printstate();
    
}