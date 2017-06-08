#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <iostream>
#include <unordered_map>

template <typename T>
class union_find
{
private:
    std::unordered_map<T, T> parent_of_element_;
    std::unordered_map<T, int> rank_of_element_;

    bool has_key(const T element)
    {
        return (bool)rank_of_element_.count(element);
    }

public:
    union_find(){}
    ~union_find(){}

    void add_element(const T element)
    {
        if (has_key(element)) return;

        parent_of_element_[element] = element;
        rank_of_element_[element] = 0;
    }
    
    void unite(T x, T y)
    {
        x = find(x);
        y = find(y);

        if (x == y) return;

        if (rank_of_element_[x] < rank_of_element_[y]){
            parent_of_element_[x] = y;
        }
        else{
            parent_of_element_[y] = x;
            if (rank_of_element_[x] == rank_of_element_[y]){
                rank_of_element_[x] += 1;
            }
        }
    }
    
    const T find(const T element)
    {
        if (parent_of_element_[element] == element){
            return element;
        }
        else{
            return parent_of_element_[element] = find(parent_of_element_[element]);
        }
    }
    
    const bool find(const T x, const T y) const
    {
        return (find(x) == find(y));
    }


};

#endif // UNION_FIND_H