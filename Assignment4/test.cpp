#include<iostream>
using namespace std;
#define N 8

class TrieNode{
    public:
    TrieNode *children[2];
    int count;
    int countEnd;
    TrieNode(){
        countEnd=0;
        count=0;
        children[0]=NULL;
        children[1]=NULL;
    }
    bool isEmpty(){
        if(children[0]||children[1]||count||countEnd)
            return false;
        return true;
    }
};

class Trie{
    public:
    TrieNode* root;
    Trie(){
        root=new TrieNode();
    }
    int insert(string key,int start){
        TrieNode* temp=root;
        for(int i=start;i<key.length();i++){
            int index=key[i]-'0';
            temp->count+=1;
            if(!temp->children[index])temp->children[index]=new TrieNode();
            temp=temp->children[index];
        }
        temp->countEnd++;
        return 1;
        // temp->count+=1;
    }
    TrieNode* remove(TrieNode* toor, string key,int level=0){
        if(!toor)return NULL;
        if(level==key.length()){
            toor->countEnd=toor->countEnd-1;
            if(toor->isEmpty()){
                delete(toor);
                toor=NULL;
            }
            return toor;
        }
        int index=key[level]-'0';
        toor->children[index]=remove(toor->children[index],key,level+1);
        toor->count=toor->count-1;
        if(toor->isEmpty()){
            delete(toor);
            toor=NULL;
        }
        return toor;
    }
    int search(TrieNode*toor,string key, int level=0){
        if(level== key.length())return toor->count + toor->countEnd;
        int index = key[level]-'0';
        if(!toor->children[index]){return 0;}
        return search(toor->children[index],key,level+1);
    }
    
    int search2(TrieNode*toor,string key,int level){
        if(toor==NULL){
           return 0;
        }
        if(level==key.length())
        {   
            int beta=level*(toor->count+toor->countEnd);
            return beta;
        }
        if(key[level]=='?'){
            int alpha=search2(toor->children[0],key,level+1)+ search2(toor->children[1],key,level+1);
            return alpha ;
            }
        int index=key[level]-'0';

        int test=search2(toor->children[index],key,level+1);
        int final=(test)?(test):(level*(toor->count));
        if(toor->children[!index]){
            int gamma=level*(toor->children[!index]->count+toor->children[!index]->countEnd)+test;
            return gamma;
        }
        return final;
    }
};
int main(){
    Trie test;
    Trie st;
    string arr="10110101";
    string arr1="01010111";
    string arr2="10101111";
    string arr3="00001110";
    string arr4="00010001";
    string pattern="000";
    st.insert(arr,0);
    st.insert(arr1,0);
    st.insert(arr2,0);
    st.insert(arr3,0);
    st.insert(arr4,0);
    // cout<<pattern[1]<<endl;
    for(int i=0;i<8;i++)test.insert(arr,i);
    for(int i=0;i<8;i++)test.insert(arr1,i);
    for(int i=0;i<8;i++)test.insert(arr2,i);
    for(int i=0;i<8;i++)test.insert(arr3,i);
    for(int i=0;i<8;i++)test.insert(arr4,i);
    for(int i=0;i<8;i++)test.remove(test.root,arr,i);

    st.remove(st.root,arr,0);
    // TrieNode nn;
    // nn.children[1]=new TrieNode();
    // nn.count=100;
    // cout<<nn.isEmpty()<<endl;
    cout<<st.search2(st.root,pattern,0)<<endl;
    cout<<test.search(test.root,pattern)<<endl;

}