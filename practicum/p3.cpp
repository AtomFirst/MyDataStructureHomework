#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stdlib.h>
using namespace std;

struct Date{
    int year,month,day;
    auto operator<=>(const Date&) const=default;
};

struct People{
    string name,address;
    Date date_of_birth,date_of_death;
    bool married,alive;

    friend istream& operator>>(istream& in,People &p){

        return in;
    }

    friend ostream& operator<<(ostream& out,const People &p){

        return out;
    }
};

template<typename T>
struct Node{
    Node():parent(nullptr) {}
    Node(const T& elem):parent(nullptr),elem(elem) {}

    Node* parent;
    vector<Node*> children;
    T elem;
};

class Printer{
public:
    Printer():unicode_table{{"lr","─"},{"ud","│"},{"udr","├"},{"ur","└"}}{
#if defined(_WIN32)
        system("chcp 65001");
#endif
    }

    void operator()(ostream &out,Node<string>* root){
        buffer.clear();
        auto [r,c]=draw(root,0,0);

        for(int i=0;i<r;i++,out<<endl)
            for(int j=0;j<c;j++)
                out<<(buffer.count({i,j})?buffer[{i,j}]:" ");
    }

private:
    static vector<string> norm(const string &s){
        vector<string>res;

        for(int i=0,len;i<s.length();res.emplace_back(s.substr(i,len)),i+=len){
            if(s[i]&0x80){
                len=2;
                while((s[i]>>(7-len))&1) ++len;
            }else
                len=1;
        }

        return res;
    }

    pair<int,int> draw(Node<string>* root,int sx,int sy){
        if(root==nullptr) return {0,0};

        auto text=norm(root->elem);
        int len=0,n=root->children.size();
        for(auto &x:text)
            len+=min(2,(int)x.size());

        for(int i=0;i<text.size();i++)
            buffer[{sx,sy+i}]=text[i];
        
        if(!n) return {1,len};

        int dx=1,dy=0,mxdy=len;
        for(int i=0;i<n;i++){
            buffer[{sx+dx,sy+dy}]=unicode_table[i!=n-1?"udr":"ur"];
            for(int j=1;j<=2;j++)
                buffer[{sx+dx,sy+dy+j}]=unicode_table["lr"];

            auto [tx,ty]=draw(root->children[i],sx+dx,sy+dy+4);

            if(i<n-1)
                for(int j=1;j<=tx;j++)
                    buffer[{sx+dx+j,sy+dy}]=unicode_table["ud"];
            
            dx+=tx; mxdy=max(mxdy,dy+4+ty);
        }

        return {dx,mxdy};
    }

    map<string,string>unicode_table;
    map<pair<int,int>,string>buffer;
};

int main(){
/*
    // Printer Test
    Printer p;
    Node<string> arr[]{string("李海龙"),string("Gilles . Wood"),string("二孩"),string("孙"),string("孙二")};

    arr[0].children.emplace_back(arr+1);
    arr[0].children.emplace_back(arr+2);
    arr[1].children.emplace_back(arr+3);
    arr[1].children.emplace_back(arr+4);
    p(cout,arr);
*/

    return 0;
}