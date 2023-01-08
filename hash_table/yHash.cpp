/*
unordered_map and unordered_set
TODO:
    Universal Hashing (with Chaining)
    Perfect Hashing
    Consistent Hashing
    Linear Probling
    Double Hashing
    Cuckoo Hashing
https://stackoverflow.com/questions/10416404/finding-items-in-an-universal-hash-table
https://github.com/efficient/libcuckoo
https://github.com/sparsehash/sparsehash
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename KeyType, typename ValType>
class yHash{
private:
    // only conside integer key here
    using pkv = pair<KeyType, ValType>;
    const int mod = 65537;
    vector<vector<pkv>> slots;
    int find(int key){
        int key_mod = key % mod;
        for(int i = 0; i < slots[key_mod].size(); i++){
            if(slots[key_mod][i].first == key){
                return i;
            }
        }
        return -1;
    }

public:
    yHash() {
        slots.resize(mod);
    }
    
    void put(int key, int value) {
        int key_mod = key % mod;
        int id = find(key);
        if(id == -1){
            slots[key_mod].push_back({key,value});
        }
        else{
            slots[key_mod][id].second = value;
        }
    }
    
    int get(int key) {
        int key_mod = key % mod;
        int id = find(key);
        return id == -1 ? -1 : slots[key_mod][id].second;
    }
    
    void remove(int key) {
        int key_mod = key % mod;
        int id = find(key);
        if(id > -1){
            swap(slots[key_mod][id], slots[key_mod].back());
            slots[key_mod].pop_back();
        }
    }
};

int main(){
    yHash<int, int> hash_map;
    int const n = 1000000;
    for(int i = 0; i < n; i++){
        hash_map.put(i, rand());
    }
    cout << hash_map.get(100) <<endl;
    hash_map.put(100, 10);
    cout << hash_map.get(100) <<endl;
    hash_map.remove(100);
    cout << hash_map.get(100) <<endl;
}