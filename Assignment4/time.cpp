#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;
int length1(string key){
    int len=0;
    while(key[len]!='\0')len++;
    return len;
}
int main(){
    string length="105633215322155515454212321545212";
    auto start=high_resolution_clock::now();
    // int len=length1(length);
    int arr[1000];
    for(int i=0;i<1000;i++)arr[i]=length.length();
    auto stop=high_resolution_clock::now();
    cout<<(stop-start).count()<<endl;

}
// #include<iostream>
// using namespace std;
// #define N 8

// class TrieNode{
//     public:
//     TrieNode *children[2];
//     int count;
//     int countEnd;
//     TrieNode(){
//         countEnd=0;
//         count=0;
//         children[0]=NULL;
//         children[1]=NULL;
//     }
//     bool isEmpty(){
//         if(children[0]||children[1]||count||countEnd)
//             return false;
//         return true;
//     }
// };

// class Trie{
//     public:
//     TrieNode* root;
//     Trie(){
//         root=new TrieNode();
//     }
//     int insert(string key,int length,int start=0){
//         TrieNode* temp=root;
//         for(int i=start;i<length;i++){
//             int index=key[i]-'0';
//             temp->count+=1;
//             if(!temp->children[index])temp->children[index]=new TrieNode();
//             temp=temp->children[index];
//         }
//         temp->countEnd++;
//         return 1;
//         // temp->count+=1;
//     }
//     TrieNode* remove(TrieNode* toor, string key,int length,int level=0){
//         if(!toor)return NULL;
//         if(level==length){
//             toor->countEnd=toor->countEnd-1;
//             if(toor->isEmpty()){
//                 delete(toor);
//                 toor=NULL;
//             }
//             return toor;
//         }
//         int index=key[level]-'0';
//         toor->children[index]=remove(toor->children[index],key,length,level+1);
//         toor->count=toor->count-1;
//         if(toor->isEmpty()){
//             delete(toor);
//             toor=NULL;
//         }
//         return toor;
//     }
//     int search(TrieNode*toor,string key,int length, int level=0){
//         if(level==length)return toor->count + toor->countEnd;
//         int index = key[level]-'0';
//         if(!toor->children[index]){return 0;}
//         return search(toor->children[index],key,length,level+1);
//     }
    
//     int search2(TrieNode*toor,string key,int length,int level=0){
//         if(toor==NULL){
//            return 0;
//         }
//         if(level==length)
//         {   
//             int beta=level*(toor->count+toor->countEnd);
//             return beta;
//         }
//         if(key[level]=='?'){
//             int alpha=search2(toor->children[0],key,length,level+1)+ search2(toor->children[1],key,length,level+1);
//             return alpha ;
//             }
//         int index=key[level]-'0';

//         int test=search2(toor->children[index],key,length,level+1);
//         int final=(test)?(test):(level*(toor->count));
//         if(toor->children[!index]){
//             int gamma=level*(toor->children[!index]->count+toor->children[!index]->countEnd)+test;
//             return gamma;
//         }
//         return final;
//     }
// };
// class SuffixTree{
//     private:
//     Trie* Suffixes;
//     Trie* Main;
//     int maxlen;
//     public:
//     int length(string key){
//         int len=0;
//         while(key[len]!='\0')len++;
//         return len;
//     }
//     SuffixTree(int n){
//         Suffixes=new Trie();
//         Main=new Trie();
//         maxlen=n;
//     }
//     int insert(string key){
//         if(Main->search(Main->root,key,length(key)))return 0;
//         Main->insert(key,length(key));
//         for(int i=0;i<maxlen;i++)Suffixes->insert(key,length(key),i);
//         return 1;
//     }
//     int remove(string key){
//         if(!(Main->search(Main->root,key,length(key))))return 0;
//         Main->remove(Main->root,key,length(key),0);
//         for(int i=0;i<maxlen;i++)Suffixes->remove(Suffixes->root,key,length(key),i);
//         return 1;
//     }
//     int search(string pattern){
//         return Suffixes->search(Suffixes->root,pattern,length(pattern));
//     }
//     int search2(string pattern){
//         return (Main->search2(Main->root,pattern,length(pattern)));
//     }
// };
// int main(){
//     // Trie test;
//     // Trie st;
//     // string arr="10110101";
//     // string arr1="01010111";
//     // string arr2="10101111";
//     // string arr3="00001110";
//     // string arr4="00010001";
//     // string pattern="01100110";
//     // st.insert(arr,0);
//     // st.insert(arr1,0);
//     // st.insert(arr2,0);
//     // st.insert(arr3,0);
//     // st.insert(arr4,0);
//     // // cout<<pattern[1]<<endl;
//     // for(int i=0;i<8;i++)test.insert(arr,i);
//     // for(int i=0;i<8;i++)test.insert(arr1,i);
//     // for(int i=0;i<8;i++)test.insert(arr2,i);
//     // for(int i=0;i<8;i++)test.insert(arr3,i);
//     // for(int i=0;i<8;i++)test.insert(arr4,i);
//     // // for(int i=0;i<8;i++)test.remove(test.root,arr,i);

//     // cout<<st.search(st.root,pattern,0)<<endl;
//     // // TrieNode nn;
//     // // nn.children[1]=new TrieNode();
//     // // nn.count=100;
//     // // cout<<nn.isEmpty()<<endl;
//     // cout<<st.search2(st.root,pattern,0)<<endl;
//     // cout<<test.search(test.root,pattern)<<endl;
//     SuffixTree tree(32);
//     int t;
//     cin>>t;
//     while(t--){
//         int ch;
//         cin>>ch;
//         string pattern;
//         switch(ch){
//             case 1:                    
//                     cin>>pattern;
//                     tree.insert(pattern);
//                     break;
//             case 2:
//                     cin>>pattern;
//                     tree.remove(pattern);
//                     break;
//             case 3:
//                     cin>>pattern;
//                     cout<<tree.search(pattern)<<endl;
//                     break;
//             case 4:
//                     cin>>pattern;
//                     cout<<tree.search2(pattern)<<endl;
//                     break;

//         }

//     }

// }