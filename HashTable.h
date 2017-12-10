#ifndef HashTable_h
#define HashTable_h
#include <list>
#include "Queue.h"
using namespace std;

template <typename K, typename V, int CAP>
class HashTable
{
    struct Node
    {
        K key;
        V value;
    };
    list<Node> data[CAP];
    int (*hashCode)(const K& key);
    int siz;
    int nodeSize;
public:
    HashTable(int(*hashCode)(const K&) = 0);
    V operator[] (const K& key) const;
    V& operator[] (const K& key);
    bool containsKey(const K& key) const;
    void deleteKey(const K& key);
    Queue<K> keys() const;
    int size() const;
    void clear();
    double loadFactor() const;
    double nodeLoadFactor() const;
};
template <typename K, typename V, int CAP>
HashTable<K,V,CAP>::HashTable(int(*hashCode)(const K&))
{
    this->hashCode = hashCode;
    siz = 0;
}
template <typename K, typename V, int CAP>
V HashTable<K,V,CAP>::operator[](const K& key) const
{
    int index = hashCode(key) % CAP;
    if (index < 0)
    {
        index += CAP;
    }
    
    typename list<Node>::iterator it;
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (it->key == key)
        {
            return it->value;
        }
    }
    
    return V();
}
template <typename K, typename V, int CAP>
V& HashTable<K,V,CAP>::operator[](const K& key)
{
    int index = hashCode(key) % CAP;
    if (index < 0)
    {
        index += CAP;
    }
    typename list<Node>::iterator it;
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (it->key == key)
        {
            return it->value;
            
        }
    }
    if (it == data[index].end())
    {
        Node temp;
        temp.key = key;
        temp.value = V();
        data[index].push_back(temp);
    }
    siz++;
    return data[index].back().value;
}
template <typename K, typename V, int CAP>
bool HashTable<K,V,CAP>::containsKey(const K& key) const
{
    int index = hashCode(key) % CAP;
    if (index < 0)
    {
        index += CAP;
    }
    typename list<Node>::const_iterator it;
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (it->key == key)
        {
            return true;
        }
    }
    
    return false;
}
template <typename K, typename V, int CAP>
void HashTable<K,V,CAP>::deleteKey(const K& key)
{
    int index = hashCode(key) % CAP;
    if (index < 0)
    {
        index += CAP;
    }
    typename list<Node>::iterator it;
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (it->key == key)
        {
            data[index].erase(it);
        }
    }
    
}
template <typename K, typename V, int CAP>
int HashTable<K,V,CAP>::size() const
{
    return siz;
}
template <typename K, typename V, int CAP>
Queue<K> HashTable<K,V,CAP>::keys() const
{
    Queue<K> temp;
    for (int i = 0; i < CAP; i++)
    {
        typename list<Node>::const_iterator it;
        for (it = data[i].begin(); it != data[i].end(); it++)
        {
            temp.push(it->key);
        }
    }
    return temp;
}
template <typename K, typename V, int CAP>
void HashTable<K,V,CAP>::clear()
{
    for (int i = 0; i < CAP; i++)
    {
        data.clear();
    }
}
template <typename K, typename V, int CAP>
double HashTable<K,V,CAP>::loadFactor() const
{
    return 1.0 * siz/CAP;
}
template <typename K, typename V, int CAP>
double HashTable<K,V,CAP>::nodeLoadFactor() const
{
    return 1.0 * nodeSize/CAP;
}
#endif
