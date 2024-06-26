#include<bits/stdc++.h>
using namespace std;
// #define l(i,st,n) for(int i=st;i<n;i++) 


class Entry{
    public:
    int key;
    int data;
    int hash;
    Entry(int key,int data,int hash=0){
        this->data=data;
        this->key=key;
        this->hash=hash;
    }
};
class Hashmap{
    
    int cap=1;
    int size=0;
    float load_factor=0;    
    public:
    hash<int> hash_fn;
    Hashmap(){
        
    }
    vector<vector<vector<int>>> v;

    hash<int> hash_int;

// if load factor goes up to threshold
    void resize(){

        vector<vector<vector<int>>> vnew;
        cap=cap+2;
        // pushing empty 2d matrix into vnew so that we can call it by index value
        for(int i=0;i<cap;i++){
            vector<vector<int>> vsample;
            vnew.push_back(vsample);
        }

        // copy all previous key data with newer hash value
        for(int i=0;i<v.size();i++){
            for(int j=0;j<v[i].size();j++){
                
                size_t hash1 = hash_int(v[i][j][0]);
                v[i][j][2]=hash1%cap;                      // changing the previous hash value with new
                vnew[v[i][j][2]].push_back(v[i][j]);      // pushing key,value,hash 's vector in the bucket at the index equal new hash
                
            }
        }
        v=vnew;
    }





    void insert(int key , int val){
        if(float(size)/cap>=0.6){
            this->resize();
        }

        Entry* e =new Entry(key , val);
        size_t hash1 = hash_fn(key);
        e->hash=hash1%cap;

        if(e->hash==cap-1){     // just pushing empty 2d vector so that can call it by index value
            vector<vector<int>> vsample;
            v.push_back(vsample);
            cap++;
        }

        bool check=false;      // to check if key already present
        for(int j=0;j<v[e->hash].size();j++){
            if(v[e->hash][j][0]==key){
                size--;
                v[e->hash][j][1]=e->data;          //if already present then change its value
                check=true;
                break;
            }
        }
        size++;
        if(check) return;
        
        vector<int> entry;
        entry={e->key,e->data,e->hash};
        v[e->hash].push_back(entry);
        load_factor=float(size)/cap;
    }


    void show_map(){
        cout<<"showing map:  ";
        for(int i=0;i<v.size();i++){
            for(int j=0;j<v[i].size();j++){
                for(int k=0;k<3;k++){
                    cout<<v[i][j][k]<<" ";
                }
                if(j<v[i].size()-1) cout<<", ";
            }
            if(v[i].size()) cout<<endl;
        }
    }


    void get(int key){
        size_t hash1 = hash_fn(key);
        int hashval=hash1%cap;
        for(int i=0;i<v[hashval].size();i++){
            if(v[hashval][i][0]==key){
                cout<<"value for this key is: "<<v[hashval][i][1]<<"\n";
                return;
            }
        }
        cout<<"KEY "<<key<<" NOT FOUND \n";

    }


    void deletekey(int key){
        size_t hash1 = hash_fn(key);
        int hashval=hash1%cap;
        int pos=-1;
        for(int i=0;i<v[hashval].size();i++){
            if(v[hashval][i][0]==key){
                pos=i;
                size--;
                load_factor=float(size)/cap;
                break;
            }
        }
        if(pos==-1){
            cout<<"KEY "<<key<<" NOT FOUND \n";
            return;
        }
        v[hashval].erase(v[hashval].begin()+pos);
    }  
};

int main(){

    Hashmap* a= new Hashmap();
    a->insert(1,10);
    a->show_map();
    a->insert(3,20);
    a->show_map();
    a->insert(3,19);
    a->show_map();
    a->insert(1,12);
    a->insert(5,13);
    a->show_map();
    cout<<"......................\n";
    a->insert(1,23);
    a->show_map();
    a->deletekey(1);
    a->show_map();
    a->insert(8,20);
    a->insert(23,25);
    a->insert(15,5);
    a->show_map();
    a->get(3);
    a->get(8);
    a->get(1);
    a->get(4);
    a->get(23);
}