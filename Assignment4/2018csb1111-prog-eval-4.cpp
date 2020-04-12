#include<iostream>
using namespace std;
#define LEN 8

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
    int insert(string key,int start=0){
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
        if(level==key.length())return toor->count + toor->countEnd;
        int index = key[level]-'0';
        if(!toor->children[index]){return 0;}
        return search(toor->children[index],key,level+1);
    }
    
    int search2(TrieNode*toor,string key,int level=0){
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
class SuffixTree{
    private:
    Trie* Suffixes;
    Trie* Main;
    int maxlen;
    public:
    int length(string key){
        int len=0;
        while(key[len]!='\0')len++;
        return len;
    }
    SuffixTree(int n){
        Suffixes=new Trie();
        Main=new Trie();
        maxlen=n;
    }
    int insert(string key){
        if(Main->search(Main->root,key))return 0;
        Main->insert(key);
        for(int i=0;i<maxlen;i++)Suffixes->insert(key,i);
        return 1;
    }
    int remove(string key){
        if(!(Main->search(Main->root,key)))return 0;
	//cout<<"HEllo"<<endl;
        Main->remove(Main->root,key,0);
        for(int i=0;i<maxlen;i++)Suffixes->remove(Suffixes->root,key,i);
        return 1;
    }
    int search(string pattern){
        return Suffixes->search(Suffixes->root,pattern);
    }
    int search2(string pattern){
        return (Main->search2(Main->root,pattern));
    }
};
int main(){
    SuffixTree tree(LEN);
    int t;
    cin>>t;
    while(t--){
        int ch;
        cin>>ch;
        string pattern;
        switch(ch){
            case 1:                    
                    cin>>pattern;
                    
                    tree.insert(pattern);
                    break;
            case 2:
                    cin>>pattern;
                    tree.remove(pattern);
                    break;
            case 3:
                    cin>>pattern;
                    // cout<<"3 ";
                    cout<<tree.search(pattern)<<endl;
                    break;
            case 4:
                    cin>>pattern;
                    // cout<<"4 ";
                    cout<<tree.search2(pattern)<<endl;
                    break;

        }

    }

}
