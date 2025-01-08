#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

struct Date{    
    Date():
        year(9999),month(9999),day(9999) {}

    auto operator<=>(const Date&) const=default;

    string get_string() const{
        if(*this==Date()) 
            return "-";

        return 
            to_string(year)
            + "-" + to_string(month)
            + "-" + to_string(day);
    }

    int year,month,day;
};

istream& operator>>(istream& in,Date& d){
    string tmp; in>>tmp;

    if(tmp=="-") d=Date();
    else{
        d.year=d.month=d.day=0;
        int i=0,n=tmp.length();

        for(;i<n && isdigit(tmp[i]);++i)
            d.year=d.year*10+(tmp[i]-'0');
        
        for(++i;i<n && isdigit(tmp[i]);++i)
            d.month=d.month*10+(tmp[i]-'0');
        
        for(++i;i<n && isdigit(tmp[i]);++i)
            d.day=d.day*10+(tmp[i]-'0');
    }

    return in;
}

ostream& operator<<(ostream& out,const Date& d){
    if(d==Date()) 
        return out<<"-";

    return 
        out<<d.year
        <<"-"<<d.month
        <<"-"<<d.day;
}


struct People{
    People():
        name("-"),address("-"),
        married(false),alive(true) {}

    string rows_format() const{
        return name + " " +
            date_of_birth.get_string() + " " +
            (married?"true":"false") + " " +
            address + " " +
            (alive?"true":"false") + " " +
            date_of_death.get_string();
    }

    string name,address;
    Date date_of_birth,date_of_death;
    bool married,alive;
};

istream& operator>>(istream& in,People &p){
    return in>>p.name
        >>p.date_of_birth
        >>boolalpha>>p.married
        >>p.address
        >>p.alive
        >>p.date_of_death;
}

ostream& operator<<(ostream& out,const People &p){
    return out<<p.name
        <<" => date of birth: "<<p.date_of_birth
        <<", married: "<<boolalpha<<p.married
        <<", address: "<<p.address
        <<", alive: "<<p.alive
        <<", date of death: "<<p.date_of_death;
}

template<typename T>
struct Node{
    Node():
        parent(nullptr) {}
    
    Node(const T& elem):
        parent(nullptr),elem(elem) {}
    
    ~Node(){
        for(auto child:children)
            delete child;
    }

    Node* parent;
    vector<Node*> children;
    T elem;
};

// print family tree
class Printer{
public:
    Printer():
        unicode_table{{"lr","─"},{"ud","│"},{"udr","├"},{"ur","└"}}{
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
    // partition each characters
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

    // draw the tree in buffer
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

class Genealogy{
public:
    Genealogy(): root(nullptr) {}

    bool load_data(const char filename[]){
        ifstream fin(filename,ios::in);

        if(!fin.is_open()){
            cerr<<"error: cannot open "<<filename<<endl;

            return false;
        }

        // name to people
        map<string,Node<People>*>n2p;
        // parent
        map<string,string>n2f;

        People p; string f;

        while(fin>>p>>f){
            if(n2p.count(p.name)){
                cerr<<"error: multiple rows of "<<p.name<<endl;
                fin.close();
                return false;
            }

            n2p[p.name]=new Node<People>(p);
            n2f[p.name]=f;
        }

        fin.close();

        // add edges
        bool first=true;

        for(auto [n,f]:n2f){
            if(n2p.count(f)){
                auto par=n2p[f];
                auto child=n2p[n];
                par->children.emplace_back(child);
                child->parent=par;
            }
            else if(f=="-"){
                if(!first){
                    cerr<<"error: multiple people has no parents' data"<<endl;
                    return false;
                }

                root=n2p[n];
                first=false;
            }
            else{
                cerr<<"error: cannot find parent of "<<n<<endl;
                return false;
            }
        }

        if(first){
            cerr<<"error: loop in family tree"<<endl;
            return false;
        }

        _sort_children(root,true);        

        return true;
    }

    bool save_data(const char filename[]){
        ofstream fout(filename,ios::out);

        if(!fout.is_open()){
            cerr<<"error: cannot open "<<filename<<endl;

            return false;
        }

        queue<Node<People>*>q;
        q.emplace(root);

        while(q.size()){
            auto cur=q.front(); q.pop();
  
            fout<<cur->elem.rows_format()<<" "<<(cur->parent?cur->parent->elem.name:"-")<<endl;

            for(auto child:cur->children)
                q.emplace(child);
        }

        fout.close();

        return true;
    }

    void show_family_tree(){        
        auto build=[](auto &&self,Node<People>* b)->Node<string>*{
            auto item=b->elem.name + 
                " (" + b->elem.date_of_birth.get_string() +
                ", " + b->elem.date_of_death.get_string() +
                ")";
            
            auto rt=new Node<string>(item);

            for(auto child:b->children)
                rt->children.push_back(self(self,child));

            return rt;
        };

        Node<string>* name_tree=build(build,root);

        cout<<"family tree:"<<endl;

        Printer printer;
        printer(cout,name_tree);

        cout<<endl;
    }

    void show_n_generation(int n){
        if(n<1){
            cerr<<"error: input should greater than zero"<<endl;
            return;
        }

        cout<<n<<" generation:"<<endl;
        _show_n_generation(root,n);
        cout<<endl;
    }

    Node<People>* select_name(const string& name){
        return _select_name(root,name);
    }

    void show_selete_date_of_birth(Date& d){
        vector<Node<People>*>list;
        _select_date_of_birth(root,d,list);

        if(list.empty()){
            cout<<"cannot found people who birth in"<<d<<endl;
            return;
        }

        for(auto p:list)
            cout<<p->elem.name<<" ";

        cout<<endl<<endl;
    }

    void show_relationship(Node<People>* a,Node<People>* b){ 
        auto get_ancestors=[&](Node<People>* cur){
            vector<Node<People>*>res;
            
            for(;cur;cur=cur->parent)
                res.emplace_back(cur);
            
            return res;
        };

        auto aca=get_ancestors(a),
            acb=get_ancestors(b);
        
        auto lca=a;
        for(;!aca.empty() && !acb.empty() && aca.back()==acb.back();
            aca.pop_back(),acb.pop_back())
            lca=aca.back();
        
        int d=aca.size()-acb.size();

        auto na=a->elem.name,
            nb=b->elem.name;

        cout<<na<<" and "<<nb<<" 's lowest common ancestor is "<<(lca->elem.name)<<",\nwho is "<<na<<" 's father^"<<aca.size()<<" and "<<nb<<" 's father^"<<acb.size()<<".\n";

        if(lca==a){
            cout<<"Also known as "<<na<<" is "<<nb<<" 's ";
            for(int i=1;i<(-d);i++)
                cout<<"grand";
            cout<<"father."<<endl;
        }
        else if(lca==b){
            cout<<"Also known as "<<na<<" is "<<nb<<" 's ";
            for(int i=1;i<d;i++)
                cout<<"grand";
            cout<<"son."<<endl;
        }
        else if(d==0){
            cout<<"Also known as "<<na<<" is "<<nb<<" 's "
                <<(aca.size()==1?"brother":"cousin")
                <<".\n";
        }
        else if(d==1){
            cout<<"Also known as "<<na<<" is "<<nb<<" 's "
                <<"nephew."
                <<endl;
        }
        else if(d==-1){
            cout<<"Also known as "<<na<<" is "<<nb<<" 's "
                <<"uncle."
                <<endl;
        }

        cout<<endl;
    }

    void _sort_children(Node<People>* rt,bool r=false){
        if(rt==nullptr)
            return;

        sort(rt->children.begin(),rt->children.end(),[](Node<People>* pa,Node<People>* pb){
            return pa->elem.date_of_birth < pb->elem.date_of_birth;
        });

        if(r)
            for(auto child:rt->children)
                _sort_children(child,r);
    }

private:
    void _show_n_generation(Node<People>* rt,int n){
        if(n==1){
            cout<<(rt->elem)<<endl;
            return;
        }

        for(auto child:rt->children)
            _show_n_generation(child,n-1);
    }

    Node<People>* _select_name(Node<People>* rt,const string& name){
        if(rt==nullptr || rt->elem.name==name)
            return rt;
        
        for(auto child:rt->children){
            auto t=_select_name(child,name);

            if(t!=nullptr)
                return t;
        }

        return nullptr;
    }

    void _select_date_of_birth(Node<People>* rt,const Date& d,vector<Node<People>*>& res){
        if(rt==nullptr)
            return;

        if(rt->elem.date_of_birth==d)
            res.emplace_back(rt);
        
        for(auto child:rt->children)
            _select_date_of_birth(child,d,res);
    }

    Node<People>* root;
};

const char name[]="\
Genealogy Management System\n\n",
    hint[]="\
command lists:\n\
help  =>  show hint\n\
tree  =>  output the family tree\n\
generation NUM  =>  output all people which in NUM generation\n\
show_data NAME  =>  find people whose name is NAME\n\
select_by_date_of_birth YYYY-MM-DD  =>  find people who birth in YYYY-MM-DD\n\
relationship A B  =>  find relationship between A and B\n\
add_child PARENT CHILD  =>  say no more...\n\
delete NAME  =>  delete that one also his descendant\n\
change NAME DATE_OF_BIRTH MARRIED ADDRESS ALIVE DATE_OF_DEATH  =>  change ones' data\n\
save FILENAME  =>  save data into file\n\
exit  =>  exit this program\n\n\
";

Genealogy genealogy;

void react(){
    for(string cmd;cout<<"> ",cin>>cmd;){
        if(cmd=="exit") 
            break;
        
        if(cmd=="help"){
            cout<<hint;
        }
        else if(cmd=="tree"){
            genealogy.show_family_tree();
        }
        else if(cmd=="generation"){
            int n; cin>>n;
            genealogy.show_n_generation(n);

        }
        else if(cmd=="show_data"){
            string name; cin>>name;
            auto p=genealogy.select_name(name);
            
            if(p==nullptr)
                cout<<"cannot found "<<name<<endl;
            else{
                cout<<(p->elem)<<endl;
                
                if(p->parent)
                    cout<<".parent:"<<endl<<(p->parent->elem)<<endl;

                cout<<".children:"<<endl;
            
                for(auto child:p->children)
                    cout<<(child->elem)<<endl;
            }

            cout<<endl;
        }
        else if(cmd=="select_by_date_of_birth"){
            Date d; cin>>d;

            genealogy.show_selete_date_of_birth(d);
        }
        else if(cmd=="relationship"){
            string na,nb; cin>>na>>nb;

            if(na==nb){
                cerr<<"you should input two different people"<<endl;
                continue;
            }

            auto a=genealogy.select_name(na),
                b=genealogy.select_name(nb);

            if(a==nullptr){
                cerr<<"cannot found "<<na<<endl;
                continue;
            }

            if(b==nullptr){
                cerr<<"cannot found "<<nb<<endl;
                continue;
            }

            genealogy.show_relationship(a,b);
        }
        else if(cmd=="add_child"){
            string parent_name,child_name;
            cin>>parent_name>>child_name;

            auto parent=genealogy.select_name(parent_name),
                child=genealogy.select_name(child_name);
            
            if(parent==nullptr){
                cerr<<"cannot found "<<parent_name<<endl;
                continue;
            }

            if(child!=nullptr){
                cerr<<child_name<<" already existed"<<endl;
                continue;
            }

            child=new Node<People>;
            child->elem.name=child_name;
            parent->children.emplace_back(child);
        }
        else if(cmd=="delete"){
            string name; cin>>name;
            
            auto people=genealogy.select_name(name);

            if(people==nullptr){
                cerr<<"cannot found "<<people<<endl;
                continue;
            }

            auto parent=people->parent;

            if(parent)
                for(auto it=parent->children.begin();it!=parent->children.end();++it)
                    if(*it==people){
                        parent->children.erase(it);
                        break;
                    }
            
            delete people;
        }
        else if(cmd=="change"){
            People people; cin>>people;

            auto ptr=genealogy.select_name(people.name);

            if(ptr==nullptr){
                cerr<<"cannot found "<<people<<endl;
                continue;
            }

            ptr->elem=people;

            if(ptr->parent)
                genealogy._sort_children(ptr->parent);
        }
        else if(cmd=="save"){
            string filename; 
            cin>>filename;

            genealogy.save_data(filename.c_str());
        }
        else
            cout<<"invaild input"<<endl;
    }
}

/*
test input:

tree
generation 3
show_data 王文远
select_by_date_of_birth 1950-07-04
relationship 王景飞 王子晨
add_child 王源 王芙蓉
delete 王浩
change 王芙蓉 1946-4-2 true 重庆 true -
tree
save 家谱（新）.txt
exit
*/

int main(){
    cout<<"Loading data... ";

    if(!genealogy.load_data("input/家谱.txt"))
        return 0;
    
    cout<<"done.\n\n"<<name<<hint;

    react();

    return 0;
}