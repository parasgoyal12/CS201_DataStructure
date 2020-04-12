#include <iostream>
#define MAX 99999
#define MIN -99999
using namespace std;

template <typename T>
class Node{
    private:
        T key;
        T key2;
        int reg;
        double x0;
        double v;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        int left_one;
        int right_one;


    public:

        Node(int reg_, double x, double t, double v_, int tree_type){
            reg = reg_;
            v = v_;
            x0 = x - (1.0*v*t);
            if(tree_type == 1){
                key = reg;
                key2 = -1;
            }
            else{
                key = x0;
                key2 = v;
            }
            height = 1;
            left = NULL;
            right = NULL;
            // aux = NULL;
        }

        T get_key(){ return key; }
        T get_key2(){ return key2; }
        Node<T> *get_left(){ return left; }
        Node<T> *get_right(){ return right; }
        Node<T> *get_parent(){ return parent; }
        int get_height(){ return height; }
        int get_reg(){ return reg; }
        double get_x0(){ return x0; }
        double get_v(){ return v; }
        int get_left_one(){ return left_one; }
        int get_right_one(){ return right_one; }
        // Tree<int> *get_aux(){ return aux; }

        void set_key(T key_){ key=key_; }
        void set_key2(T key_){ key2=key_; }
        void set_reg(int reg_){ reg=reg_; }
        void set_x0(double x0_){ x0=x0_; }
        void set_v(double v_){ v=v_; }
        void set_left_one(int left_one_){ left_one=left_one_; }
        void set_right_one(int right_one_){ right_one=right_one_; }
        void set_left(Node<T> *left_){ left=left_; }
        void set_right(Node<T> *right_){ right=right_; }
        void set_parent(Node<T> *parent_){ parent=parent_; }
        void set_height(int height_){ height=height_; }
        // void set_aux(Tree<int> *aux_){ aux=aux_; }


        void update_node_height(){
            int l, r, m;
            l = (left==NULL) ? 0 : left->get_height();
            r = (right==NULL) ? 0 : right->get_height();
            m = (l > r) ? l : r;
            height = m+1;
            return;
        }

        int get_balance_factor(){
            int l = (left==NULL) ? 0 : left->get_height();
            int r = (right==NULL) ? 0 : right->get_height();
            int balance_factor = l-r;
            return balance_factor;
        }


};

template <typename T>
class Tree{
    private:
        Node<T> *root;
        double *curr;

    public:
        Tree(){
            root = NULL;
        }

        Node<T> *get_root(){ return root; }
        void set_root(Node<T> *n){ root = n; }
        void set_curr(double *c){ curr = c; }

        void update_heights(Node<T> *p){
            while(p != root){
                p->update_node_height();
                p = p->get_parent();
            }
            p->update_node_height();
            return;
        }

        int compare(Node<T> *n, T val, T val2){
            // if(val2==-2)exit(0);
            // double t = *curr;
            // double t=5;
            if(val2==-1){

                if(n->get_key() < val) return -1;
                else if(n->get_key() > val) return 1;
                else return 0;
            }
            double pos1 = n->get_key() + (1.0 * n->get_key2() * (*curr));
            double vel1 = n->get_key2();
            double pos2 = val + (1.0 * val2 * (*curr));
            double vel2 = val2;
            if(pos1 < pos2) return -1;
            else if(pos1 > pos2) return 1;
            else{
                if(vel1 < vel2) return -1;
                else if(vel1 > vel2) return 1;
                else return 0;
            }
        }

        int compare(Node<T> *p, Node<T> *q){
            // double t = *curr;
            if(p->get_key2()==-1){
                if(p->get_key() < q->get_key()) return -1;
                else if(p->get_key() > q->get_key()) return 1;
                else return 0;
            }

            double pos1 = p->get_key() + (1.0 * p->get_key2() * (*curr));
            double vel1 = p->get_key2();
            double pos2 = q->get_key() + (1.0 * q->get_key2() * (*curr));
            double vel2 = q->get_key2();
            if(pos1 < pos2) return -1;
            else if(pos1 > pos2) return 1;
            else{
                if(vel1 < vel2) return -1;
                else if(vel1 > vel2) return 1;
                else return 0;
            }
        }

        int compare(double x1, double v1, double x2, double v2){
            double t = *curr;
            double pos1 = x1 + (1.0 * v1 * t);
            double pos2 = x2 + (1.0 * v2 * t);
            if(pos1 < pos2) return -1;
            else if(pos1 > pos2) return 1;
            else{
                if(v1 < v2) return -1;
                else if(v1 > v2) return 1;
                else return 0;
            }
        }

        void restructure(Node<T> *z){
            int l, r;
            Node<T> *y, *x, *a, *b, *c, *t1, *t2, *par;
            int pos = -1;
            par = z->get_parent();
            if(z != root){
                if(z->get_parent()->get_left() == z) pos = 0;
                else pos = 1;
            }
            l = (z->get_left()==NULL) ? 0 : z->get_left()->get_height();
            r = (z->get_right()==NULL) ? 0 : z->get_right()->get_height();
            y = (l > r) ? z->get_left() : z->get_right();
            l = (y->get_left()==NULL) ? 0 : y->get_left()->get_height();
            r = (y->get_right()==NULL) ? 0 : y->get_right()->get_height();
            x = (l > r) ? y->get_left() : y->get_right();

            if(compare(z, y)==-1 && compare(z, x)==-1){
                if(compare(y, x)==-1){
                    a = z;
                    b = y;
                    c = x;
                    t1 = b->get_left();
                    t2 = c->get_left();
                }
                else{
                    a = z;
                    b = x;
                    c = y;
                    t1 = b->get_left();
                    t2 = b->get_right();
                }
            }

            else if(compare(y, z)==-1 && compare(y, x)==-1){
                a = y;
                b = x;
                c = z;
                t1 = b->get_left();
                t2 = b->get_right();
            }

            else{
                a = x;
                b = y;
                c = z;
                t1 = a->get_right();
                t2 = b->get_right();
            }

            b->set_left(a);
            b->set_right(c);
            b->set_parent(par);
            a->set_right(t1);
            a->set_parent(b);
            if(t1 != NULL) t1->set_parent(a);
            c->set_left(t2);
            c->set_parent(b);
            if(t2 != NULL) t2->set_parent(c);

            a->update_node_height();
            c->update_node_height();
            b->update_node_height();

            if(pos == -1) root = b;
            else{
                if(pos==0) par->set_left(b);
                else par->set_right(b);
                par->update_node_height();
            }

            return;
        }

        Node<T> *restructure2(Node<T> *z){
            int l, r;
            Node<T> *y, *x, *a, *b, *c, *t1, *t2, *par;
            int pos = -1;
            par = z->get_parent();
            if(z != root){
                if(z->get_parent()->get_left() == z) pos = 0;
                else pos = 1;
            }
            l = (z->get_left()==NULL) ? 0 : z->get_left()->get_height();
            r = (z->get_right()==NULL) ? 0 : z->get_right()->get_height();
            y = (l > r) ? z->get_left() : z->get_right();
            l = (y->get_left()==NULL) ? 0 : y->get_left()->get_height();
            r = (y->get_right()==NULL) ? 0 : y->get_right()->get_height();
            if(l==r){
                if(z->get_left()==y) x = y->get_left();
                else x = y->get_right();
            }
            else{
                x = (l > r) ? y->get_left() : y->get_right();
            }

            if(compare(z, y)==-1 && compare(z, x)==-1){
                if(compare(y, x)==-1){
                    a = z;
                    b = y;
                    c = x;
                    t1 = b->get_left();
                    t2 = c->get_left();
                }
                else{
                    a = z;
                    b = x;
                    c = y;
                    t1 = b->get_left();
                    t2 = b->get_right();
                }
            }

            else if(compare(y, z)==-1 && compare(y, x)==-1){
                a = y;
                b = x;
                c = z;
                t1 = b->get_left();
                t2 = b->get_right();
            }

            else{
                a = x;
                b = y;
                c = z;
                t1 = a->get_right();
                t2 = b->get_right();
            }

            b->set_left(a);
            b->set_right(c);
            b->set_parent(par);
            a->set_right(t1);
            a->set_parent(b);
            if(t1 != NULL) t1->set_parent(a);
            c->set_left(t2);
            c->set_parent(b);
            if(t2 != NULL) t2->set_parent(c);

            a->update_node_height();
            c->update_node_height();
            b->update_node_height();

            if(pos == -1) root = b;
            else{
                if(pos==0) par->set_left(b);
                else par->set_right(b);
                par->update_node_height();
            }

            return b;

        }

        void copy_info(Node<T> *rem, Node<T> *p){

            rem->set_parent(p->get_parent());
            rem->set_left(p->get_left());
            rem->set_right(p->get_right());
            rem->set_height(p->get_height());
            if(p->get_parent()!=NULL){
                if(p->get_parent()->get_left() == p) p->get_parent()->set_left(rem);
                else p->get_parent()->set_right(rem);
            }
            if(p->get_left()!=NULL) p->get_left()->set_parent(rem);
            if(p->get_right()!=NULL) p->get_right()->set_parent(rem);
            if(p==root) root=rem;

            // key = rem->get_key();
            // key2 = rem->get_key2();
            // reg = rem->get_reg();
            // x0 = rem->get_x0();
            // v = rem->get_v();
            // left_one = rem->get_left_one();
            // right_one = rem->get_right_one();
            // return;
        }

        Node<T> *search(T val, T val2){
            if(root==NULL) return NULL;
            Node<T> *n = root;

            while(n!=NULL){
                if(compare(n, val, val2) == 1) n = n->get_left();
                else if(compare(n, val, val2) == -1) n = n->get_right();
                else return n;
            }
            return NULL;
        }

        int insert(Node<T> *n, T val, T val2){
            if(root==NULL){
                n->set_parent(NULL);
                root = n;
                return 1;
            }
            Node<T> *p = root;
            while(1){
                if(compare(p, val, val2) == 1){
                    if(p->get_left()==NULL){
                        n->set_parent(p);
                        p->set_left(n);
                        break;
                    }
                    else{
                        p = p->get_left();
                    }
                }
                else{
                    if(p->get_right()==NULL){
                        n->set_parent(p);
                        p->set_right(n);
                        break;
                    }
                    else{
                        p = p->get_right();
                    }
                }
            }

            update_heights(p);

            while(p != root){
                int balance_factor = p->get_balance_factor();
                if(balance_factor <= 1 && balance_factor >= -1){
                    p = p->get_parent();
                }
                else{
                    restructure(p);
                    return 1;
                }
            }
            int balance_factor = p->get_balance_factor();
            if(balance_factor < -1 || balance_factor > 1){
                restructure(p);
            }
            return 1;
        }

        int remove(Node<T> *p){
            Node<T> *s;
            if(p->get_right()==NULL){
                if(p == root){
                    root = p->get_left();
                    if(p->get_left()!=NULL) p->get_left()->set_parent(NULL);
                    s = p->get_parent();
                    // free(p);
                }
                else{
                    if(p->get_parent()->get_right() == p){
                        p->get_parent()->set_right(p->get_left());
                        if(p->get_left()!=NULL) p->get_left()->set_parent(p->get_parent());
                        s = p->get_parent();
                        // free(p);
                    }
                    else{
                        p->get_parent()->set_left(p->get_left());
                        if(p->get_left()!=NULL) p->get_left()->set_parent(p->get_parent());
                        s = p->get_parent();
                        // free(p);
                    }
                }
            }
            else{
                int flag = 0;
                Node<T> *rem = p->get_right();
                while(rem->get_left() != NULL) rem = rem->get_left();
                if(p==rem->get_parent()){
                    s = rem;
                    flag = 1;
                }
                // **p=**rem;
                if(rem->get_parent()->get_left() == rem){
                    rem->get_parent()->set_left(rem->get_right());
                    if(rem->get_right() != NULL) rem->get_right()->set_parent(rem->get_parent());
                    if(flag==0) s = rem->get_parent();
                    // free(rem);
                }
                else{
                    rem->get_parent()->set_right(rem->get_right());
                    if(rem->get_right() != NULL) rem->get_right()->set_parent(rem->get_parent());
                    if(flag==0) s = rem->get_parent();
                    // free(rem);
                }

                copy_info(rem, p);
                // if(p->get_key()==3) cout<<"HEEE "<<s->get_key()<<endl;
                // if(->get_reg()==rem->get_reg()) s=rem;


            }
            if(s==NULL) return 1;
            // if(p->get_key()==3){
            //     cout<<p->get_key()<<endl;
            //     return 1;

            // }
            update_heights(s);

            while(s != root){
                int balance_factor = s->get_balance_factor();
                if(balance_factor <= 1 && balance_factor >= -1){
                    s = s->get_parent();
                }
                else{
                    s = restructure2(s);
                    s = s->get_parent();
                }
            }

            int balance_factor = s->get_balance_factor();
            if(balance_factor < -1 || balance_factor > 1){
                restructure2(s);
            }

            // if(p->get_reg()==8){
            //         cout<<"DIE";
            //         exit(0);
            //     }
            // if(p->get_reg()==8)exit(0);
            return 1;
        }

        Node<T> *get_max_less_than_x(double x, double v, double t){
            Node<T> *c = root;
            Node<T> *m = NULL;
            while(c!=NULL){
                double curr_x = c->get_x0();
                double curr_v = c->get_v();
                if(compare(curr_x, curr_v, x, v)==-1){
                    m = c;
                    c = c->get_right();
                }
                else c = c->get_left();
            }
            return m;

        }

        Node<T> *get_min_greater_than_x(double x, double v, double t){
            Node<T> *c = root;
            Node<T> *m = NULL;
            while(c!=NULL){
                double curr_x = c->get_x0();
                double curr_v = c->get_v();
                if(compare(curr_x, curr_v, x, v) == 1){
                    m = c;
                    c = c->get_left();
                }
                else{
                    c = c->get_right();
                }
            }
            return m;
        }

        void _print_tree(Node<T>* head){
            if(head==NULL) return;
            cout<<head->get_reg()<<"|"<<head->get_x0()<<"|"<<head->get_v()<<"||"<<head->get_left_one()<<"|"<<head->get_right_one()<<"   ";
            //  cout<<head->get_reg()<<"|"<<head->get_x0()<<"|"<<head->get_v()<<"  ";
            _print_tree(head->get_left());
            _print_tree(head->get_right());
        }

        void print_tree(){
            _print_tree(root);
            cout << endl;
        }

};

class HeapNode{
    private:
        double val;
        Node<double> *left_node;
        Node<double> *right_node;

    public:

        HeapNode(double val_, Node<double> *left_node_, Node<double> *right_node_){
            val = val_;
            left_node = left_node_;
            right_node = right_node_;
        }

        double get_val(){ return val; }
        Node<double> *get_left_node(){ return left_node; }
        Node<double> *get_right_node(){ return right_node; }
        void set_val(double val_){ val = val_; }
        void set_left_node(Node<double> *left_node_){ left_node = left_node_; }
        void set_right_node(Node<double> *right_node_){ right_node = right_node_; }

};

class Heap{
    private:
        HeapNode* arr[1000];
        int size;

    public:
        Heap(){
            size = 0;
        }

        void swap_nodes(int i, int j){
            HeapNode *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            arr[i]->get_left_node()->set_left_one(i);
            arr[i]->get_right_node()->set_right_one(i);
            arr[j]->get_left_node()->set_left_one(j);
            arr[j]->get_right_node()->set_right_one(j);
            return;
        }

        void insert(Node<double> *n1, Node<double> *n2, double curr){
            double val;
            double x1 = n1->get_x0() + (1.0 * n1->get_v() * curr);
            double x2 = n2->get_x0() + (1.0 * n2->get_v() * curr);
            double v1 = n1->get_v();
            double v2 = n2->get_v();
            if(x1 == x2) val = MAX;
            else{
                if(v1 <= v2) val = MAX;
                else{
                    double num = x2 - x1;
                    double den = v1 - v2;
                    val = (1.0 * num)/den;
                    val += curr;
                }
            }
            HeapNode *hn = new HeapNode(val, n1, n2);
            arr[size] = hn;
            arr[size]->get_left_node()->set_left_one(size);
            arr[size]->get_right_node()->set_right_one(size);
            int i = size;
            size++;
            // print_heap();
            while(1){
                int par = (i-1)/2;
                if(i==0) break;
                if(arr[i]->get_val() < arr[par]->get_val()){
                    swap_nodes(i, par);
                    i = par;
                }
                else break;
            }

            return;
        }

        HeapNode *deleteMin(){

            HeapNode *hn = arr[0];
            size--;
            arr[0] = arr[size];
            arr[0]->get_left_node()->set_left_one(0);
            arr[0]->get_right_node()->set_right_one(0);

            int p = 0;
            while(1){
                int l = 2*p + 1;
                int r = 2*p + 2;
                if(l>=size) break;
                if(r>=size){
                    if(arr[l]->get_val() < arr[p]->get_val()) swap_nodes(l, p);
                    break;
                }
                if(arr[l]->get_val() < arr[p]->get_val() && arr[r]->get_val() < arr[p]->get_val()){
                    if(arr[l]->get_val() < arr[r]->get_val()){
                        swap_nodes(l, p);
                        p = l;
                    }
                    else{
                        swap_nodes(r, p);
                        p = r;
                    }
                }
                else if(arr[l]->get_val() < arr[p]->get_val() && arr[r]->get_val() >= arr[p]->get_val()){
                    swap_nodes(l, p);
                    p = l;
                }
                else if(arr[l]->get_val() >= arr[p]->get_val() && arr[r]->get_val() < arr[p]->get_val()){
                    swap_nodes(r, p);
                    p = r;
                }
                else break;
            }

            return hn;
        }

        void remove(int i){
            arr[i]->set_val(MIN);
            while(1){
                int par = (i-1)/2;
                if(i==0) break;
                if(arr[i]->get_val() < arr[par]->get_val()){
                    swap_nodes(i, par);
                    i = par;
                }
                else break;
            }
            HeapNode *hn = deleteMin();
            return;
        }

        double get_time_at_top(){
            if(size==0) return MAX;
            else return arr[0]->get_val();
        }

        HeapNode *get_top(){
            if(size==0) return NULL;
            else return arr[0];
        }

        void print_heap(){
            for(int i=0; i<size; i++){
                cout<<arr[i]->get_val()<<"|"<<arr[i]->get_left_node()->get_reg()<<"|"<<arr[i]->get_right_node()->get_reg()<<" ";
            }
            cout<<endl;
        }

        void check_for_time(Node<double>* pop[], double time_at_top, int &k, int curr){
            if(curr>=size) return;
            // time_at_top += 0.001;
            if(arr[curr]->get_val() > time_at_top){
                // cout<<arr[curr]->get_val()<<endl;
                return;

            }
            pop[k] = arr[curr]->get_left_node();
            pop[k+1] = arr[curr]->get_right_node();
            k = k+2;
            check_for_time(pop, time_at_top, k, curr*2 + 1);
            check_for_time(pop, time_at_top, k, curr*2 + 2);
        }

        void populate(Node<double>* pop[], double time_at_top, int &k){

            check_for_time(pop, time_at_top, k, 0);
            // if(time_at_top==3) cout<<k<<endl;
        }
};

class SortObject{
    private:
        double x;
        int reg;
        double v;

    public:
        SortObject(double pos, double r, double vel){
            x = pos;
            reg = r;
            v = vel;
        }

        double get_pos(){ return x; }
        int get_reg(){ return reg; }
        double get_vel(){ return v; }

        int comp(SortObject *o1, SortObject *o2){
            if(o1->get_pos() < o2->get_pos()) return -1;
            else if(o1->get_pos() > o2->get_pos()) return 1;
            else{
                if(o1->get_reg() < o2->get_reg()) return -1;
                else if(o1->get_reg() > o2->get_reg()) return 1;
                else return 0;
            }
        }

        void make_heap(SortObject* to_sort[], int k, int i){
            int max = i;
            int l = 2*i + 1;
            int r = 2*i + 2;
            if(l<k && comp(to_sort[l], to_sort[max])==1) max=l;
            if(r<k && comp(to_sort[r], to_sort[max])==1) max=r;
            if(max!=i){
                SortObject *temp;
                temp = to_sort[i];
                to_sort[i] = to_sort[max];
                to_sort[max] = temp;
                make_heap(to_sort, k, max);
            }
        }

        void sort_and_print(SortObject* to_sort[], int k){
            for(int i = (k/2)-1; i>=0; i--) make_heap(to_sort, k, i);
            for (int i =k-1; i>=0; i--){
                SortObject *temp;
                temp = to_sort[0];
                to_sort[0] = to_sort[i];
                to_sort[i] = temp;
                make_heap(to_sort, i, 0);
            }
            double curr_x = to_sort[0]->get_pos();
            cout<<curr_x<<" "<<to_sort[0]->get_reg()<<" ";
            for(int i=1; i<k; i++){
                if(to_sort[i]->get_pos() == curr_x) cout<<to_sort[i]->get_reg()<<" ";
                else{
                    cout<<endl;
                    curr_x = to_sort[i]->get_pos();
                    cout<<curr_x<<" "<<to_sort[i]->get_reg()<<" ";
                }
            }
            cout<<endl;
        }

};

class Highway{
    private:


    public:

        Tree<int> reg;
        Tree<double> pos_and_vel;
        Heap heap;
        double curr;

        Highway(){
            curr = 0;
            reg.set_curr(&curr);
            pos_and_vel.set_curr(&curr);
        }

        int insert(int r, double x, double v){
            Node<int> *n = reg.search(r, -1);
            if(n != NULL) return 0;
            Node<int> *t1 = new Node<int>(r, x, curr, v, 1);
            Node<double> *t2 = new Node<double>(r, x, curr, v, 2);
            double x0 = t2->get_x0();
            reg.insert(t1, r, -1);
            pos_and_vel.insert(t2, x0, v);
            Node<double> *imm_left = pos_and_vel.get_max_less_than_x(x0, v, curr);
            Node<double> *imm_right = pos_and_vel.get_min_greater_than_x(x0, v, curr);

            if(imm_left==NULL && imm_right==NULL) return 1;
            else if(imm_left==NULL || imm_right==NULL){

                if(imm_left==NULL){
                    heap.insert(t2, imm_right, curr);

                }
                if(imm_right==NULL){
                    heap.insert(imm_left, t2, curr);
                }


            }
            else{
                int pos = imm_left->get_left_one();
                heap.remove(pos);
                heap.insert(imm_left, t2, curr);
                heap.insert(t2, imm_right, curr);
            }
            return 1;
        }

        int remove(int r){
            Node<int> *n = reg.search(r, -1);
            if(n==NULL) return 0;

            double x = n->get_x0() + (1.0 * n->get_v() * curr);
            Node<double> *imm_left = pos_and_vel.get_max_less_than_x(n->get_x0(), n->get_v(), curr);
            Node<double> *imm_right = pos_and_vel.get_min_greater_than_x(n->get_x0(), n->get_v(), curr);
            Node<double> *m = pos_and_vel.search(n->get_x0(), n->get_v());

            if(imm_left==NULL && imm_right==NULL){

                reg.remove(n);
                pos_and_vel.remove(m);
                return 1;
            }
            else if(imm_left==NULL || imm_right==NULL){
                int index = (imm_left == NULL) ? m->get_left_one() : m->get_right_one();
                heap.remove(index);
                reg.remove(n);
                pos_and_vel.remove(m);
                return 1;
            }
            else{

                // heap.print_heap();
                int index1 = m->get_left_one();
                heap.remove(index1);
                // cout<<index1<<endl;

                int index2 = m->get_right_one();
                heap.remove(index2);
                heap.insert(imm_left, imm_right, curr);

                reg.remove(n);
                // cout<<m->get_reg();
                // if(r==8)exit(0);
                pos_and_vel.remove(m);
                // if(r==8) exit(0);
                return 1;
            }

        }

        int next_crossing(){
            double time_at_top = heap.get_time_at_top();
            if(time_at_top == MAX) return 0;
            double next_crossing = time_at_top;
            double new_curr = time_at_top;
            // cout<<curr<<endl;
            Tree<int> *collided = new Tree<int>();
            SortObject* to_sort[1000];
            SortObject *sentinel;
            int k2=0;
            int k = 0;
            Node<double>* pop[1000];
            // if(new_curr==3) heap.print_heap();
            heap.populate(pop, time_at_top, k2);
            // if(new_curr==3)cout<<k2<<endl;

            for(int i=0; i<k2; i+=2){
                int reg1 = pop[i]->get_reg();
                int reg2 = pop[i+1]->get_reg();
                double x0_1 = pop[i]->get_x0();
                double x0_2 = pop[i+1]->get_x0();
                double v1 = pop[i]->get_v();
                double v2 = pop[i+1]->get_v();
                double pos_of_collision = x0_1 + (1.0 * v1 * new_curr);
                double time_of_collision = new_curr;
                // if(i==4){
                //     cout<<reg1<<" "<<reg2<<endl;
                //     print_highway();
                //     // exit(0);
                // }
                // if(i==4)exit(0);
                remove(reg1);

                remove(reg2);

                Node<int> *car1 = collided->search(reg1, -1);
                if(car1==NULL){
                    Node<int> *c1 = new Node<int>(reg1, pos_of_collision, new_curr, v1, 1);
                    collided->insert(c1, reg1, -1);
                    SortObject *obj = new SortObject(pos_of_collision, reg1, v1);
                    to_sort[k] = obj;
                    k++;
                }
                // collided->print_tree();
                // return 1;
                Node<int> *car2 = collided->search(reg2, -1);

                if(car2==NULL){
                    Node<int> *c2 = new Node<int>(reg2, pos_of_collision, new_curr, v2, 1);
                    collided->insert(c2, reg2, -1);
                    SortObject *obj = new SortObject(pos_of_collision, reg2, v2);
                    to_sort[k] = obj;
                    k++;
                }


            }

            sentinel->sort_and_print(to_sort, k);
            curr = new_curr;

            for(int i=0; i<k; i++){
                int ri = to_sort[i]->get_reg();
                double xi = to_sort[i]->get_pos();
                double vi = to_sort[i]->get_vel();
                insert(ri, xi, vi);
            }
            return 1;
        }

        void print_highway(){
            cout<<"REG: ";
            reg.print_tree();
            cout<<"POS_AND_VEL: ";
            pos_and_vel.print_tree();
            cout<<"HEAP: ";
            heap.print_heap();
            return;
        }

};

int main(){
    Highway h;

    // h.remove(2);
    h.insert(13, -4, 4);
    h.insert(27,-2 , 2);
    h.insert(5,-1 ,1 );
    h.insert(16,1,1);
    h.insert(33,2,1);
    h.insert(8,3,3);
    h.insert(42,5,1);
    // h.print_highway();
    h.next_crossing();
    // h.insert(51, 4, 2);
    // h.print_highway();
    h.next_crossing();

    h.next_crossing();
    // h.print_highway();
    h.next_crossing();


}
