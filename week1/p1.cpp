#include "ADTList.cpp"
#include<string>
using namespace std;

template<typename T>
void test(string name){
    cout<<name<<":\n";
    T list; string s="hit";
    list.insertElem(0,"nuaa");
    list.insertElem(0,"seu");
    list.insertElem(1,"yau");
    list.insertElem(0,"njust");
    list.setElem(2,s);
    cout<<"Origin list: "; list.traverse();
    //for(auto x:list)
        //cout<<x<<",";
    //cout<<"\n";
    cout<<"Length of list is "<<list.length()<<".\n";
    list.getElem(1,s);
    cout<<"2nd element is "<<s<<".\n";
    
    list.priorElem("yau",s);
    cout<<"Precursor of hit is "<<s<<".\n";
    
    list.deleteElem(list.locateElem("seu"),s);
    cout<<"After delete seu: "; list.traverse();

    list.clear();
    cout<<"After clear list: "; list.traverse();
}

int main(){
    test<SquList<string>>("SquList");
    cout<<endl;
    test<LinkList<string>>("LinkList");
    
    return 0;
}