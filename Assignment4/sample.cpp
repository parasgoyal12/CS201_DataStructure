int search2(TrieNode*toor,string key,int level=0){
        if(toor==NULL)return 0;
        if(level==key.length())return toor->count + toor->countEnd;
        // cout<<level<<endl;
        if(key[level]=='?'){
            // cout<<level<<endl;
            return search2(toor->children[0],key,level+1)+search2(toor->children[1],key,level+1);

        }
        int index = key[level]-'0';
        // cout<<index<<endl;
        
        return search2(toor->children[index],key,level+1);

    }
    int search2(TrieNode*toor,string key,int level){
        // if(toor==NULL)return 0;
        // if(level==key.length())return level*(toor->count+toor->countEnd);
        
        // int index=key[level]-'0';
        // cout<<toor->count<<" "<<toor->countEnd<<endl;
        // int test=search2(toor->children[index],key,level+1);
        // // if(test==0)return level*(toor->count);
        // return (test)?(test):(level*(toor->count));
        if(toor==NULL){
            // cout<<level<<" "<<0<<endl;
            return 0;
        }
        if(level==key.length())
        {   
            int beta=level*(toor->count+toor->countEnd);
            // cout<<level<<" "<<beta<<endl;
            return beta;
        }
        if(key[level]=='?'){
            int alpha=search2(toor->children[0],key,level+1)+ search2(toor->children[1],key,level+1);
            //cout<<level<<" "<<alpha<<endl;
            return alpha ;
            }
        int index=key[level]-'0';

        int test=search2(toor->children[index],key,level+1);
        int final=(test)?(test):(level*(toor->count));
        if(toor->children[!index]){
            int gamma=level*(toor->children[!index]->count+toor->children[!index]->countEnd)+test;
            // cout<<"Hello"<<endl;
            // cout<<level<<" "<<gamma<<endl;
            return gamma;
        }
        // cout<<level<<" "<<final<<endl;
        return final;

    }