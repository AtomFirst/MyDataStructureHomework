#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<queue>

using namespace std;

template<typename T>
struct BiNode{
    T elem;
    BiNode *left,*right;

    BiNode():left(nullptr),right(nullptr){}

    BiNode(const T& elem):elem(elem),left(nullptr),right(nullptr){}

    ~BiNode(){
        delete left,right;
    }
};

map<char,string> HuffmanCoding(const map<char,int>& cnt){
    // build a Huffman tree
    priority_queue<pair<int,BiNode<char>*>>q;
    
    for(auto [ch,freq]:cnt)
        q.emplace(-freq,new BiNode<char>(ch));

    while(q.size()>1){
        auto [f1,ht1]=q.top(); q.pop();
        auto [f2,ht2]=q.top(); q.pop();
        auto ht=new BiNode<char>(char(-1));

        ht->left=ht1; ht->right=ht2;
        q.emplace(f1+f2,ht);
    }

    // get Huffman coding from tree
    auto root=q.top().second; q.pop();

    map<char,string>res;
    string path;

    auto dfs=[&](auto &&self,BiNode<char>* rt){
        if(rt->elem>=0){
            res[rt->elem]=path;
            return;
        }
        
        path+='0';
        self(self,rt->left);
        path.pop_back();

        path+='1';
        self(self,rt->right);
        path.pop_back();
    };

    dfs(dfs,root);
    delete root;

    return res;
}

bool encode(){
    ifstream fin("input/source.txt",ios::in);

    if(!fin.is_open()){
        cerr<<"Cannot open input/source.txt!\n";
        return false;
    }

    // calculate the frequency of each characters
    map<char,int>cnt{{'\0',1}};
    for(char ch;fin.get(ch);) 
        ++cnt[ch];
    
    // save the coding
    auto ch2code=HuffmanCoding(cnt);
    ofstream fout1("Huffman.txt",ios::out);

    for(auto [ch,freq]:cnt){
        string s{ch};
        if(ch=='\0') 
            s="EOF";
        else if(ch==' ') 
            s="space";
        else if(ch=='\n') 
            s="\\n";

        fout1<<s<<" "<<freq<<" "<<ch2code[ch]<<endl;
    }

    fout1.close();

    // calculate the size of code
    int len=ch2code['\0'].length();
    fin.clear(); fin.seekg(0);
    for(char ch;fin.get(ch);)
        len+=ch2code[ch].length();

    // encode
    int siz=(len+7)>>3;
    char* buffer=new char[siz]();
    fin.clear(); fin.seekg(0);
    int i=0;

    for(char ch;fin.get(ch);){
        for(auto bit:ch2code[ch]){
            if(bit=='1')
                buffer[i>>3]|=1<<(i&7);
            ++i;
        }
    }

    fin.close();

    // add EOF
    for(auto bit:ch2code['\0']){
        if(bit=='1')
            buffer[i>>3]|=1<<(i&7);
        ++i;
    }

    // write into "code.dat"
    ofstream fout2("code.dat",ios::out|ios::binary);
    fout2.write(buffer,(len+7)/8);
    fout2.close();

    delete [] buffer;

    return true;
}

bool decode(){
    // build tree from "Huffman.txt"
    ifstream fin1("Huffman.txt",ios::in);
    
    if(!fin1.is_open()){
        cerr<<"Cannot open Huffman.txt!\n";
        return false;
    }
    
    auto root=new BiNode<char>(-1);

    for(string s,code,freq;fin1>>s>>freq>>code;){
        char ch=s[0];
        if(s=="EOF") 
            ch='\0';
        else if(s=="\\n") 
            ch='\n';
        else if(s=="space") 
            ch=' ';

        auto cur=root;
        for(auto bit:code)
            if(bit=='0'){
                if(cur->left==nullptr)
                    cur->left=new BiNode<char>(-1);
                cur=cur->left;
            }else{
                if(cur->right==nullptr)
                    cur->right=new BiNode<char>(-1);
                cur=cur->right;
            }
        
        cur->elem=ch;
    }

    fin1.close();

    // decode
    ifstream fin2("code.dat",ios::in|ios::binary);

    if(!fin2.is_open()){
        cerr<<"Cannot open code.dat!\n";
        return false;
    }

    ofstream fout("recode.txt",ios::out);
    auto cur=root; bool end=0;

    for(char buffer;fin2.read(&buffer,1) && !end;){
        for(int i=0;i<8;i++){
            if(cur->elem>0){
                fout<<(cur->elem);
                cur=root;
            }else if(cur->elem=='\0'){
                end=1; break;
            }

            if((buffer>>i)&1)
                cur=cur->right;
            else
                cur=cur->left;
        }
    }

    fin2.close(); 
    fout.close();
    delete root;

    return true;
}

int main(){
    if(encode()) 
        cout<<"Encode succeed!\n";
    
    if(decode())
        cout<<"Decode succeed!\n";

    return 0;
}