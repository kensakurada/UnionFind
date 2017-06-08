#include <iostream>
#include <vector>
#include <boost/functional/hash.hpp>
#include "union_find/union_find.h"

namespace std
{
    typedef struct element
    {
        std::string image;
        unsigned int index;

        // Need to overload operator ==
        inline bool operator==(const struct element& other) const
        {
            return (this->image == other.image) && (this->index == other.index);
        }
    } element;

    // Need to specialize std::hash<Type> because union_find class uses std::unordered_map
    template<>
    struct hash<element> {
        inline size_t operator()(const element& x) const {
            size_t seed = 0;
            // combine hash values
            boost::hash_combine(seed, x.image);
            boost::hash_combine(seed, x.index);
            return seed;
        }
    };

    // To print the struct members
    ostream& operator<<(std::ostream& os, const element& x)
    {
        return os << "(" <<  x.image << ", " << x.index << ")";
    }
}

int main()
{
    std::cout << std::endl;
    std::cout << "Example of std::string" << std::endl;
    std::cout << std::endl;

    union_find<std::string> uf;

    std::vector<std::string> inputs{"A", "B", "C", "D", "E", "F"};

    std::cout << "[Initialize]" << std::endl;
    for(auto input : inputs){
        uf.add_element(input);
    }
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite A & B, C & F]" << std::endl;
    uf.unite("A", "B");
    uf.unite("C", "F");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite E & F, B & C]" << std::endl;
    uf.unite("E", "F");
    uf.unite("B", "C");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite A & F, B & E]" << std::endl;
    uf.unite("A", "F");
    uf.unite("B", "E");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Add G, Unite B & G]" << std::endl;
    uf.add_element("G"); inputs.push_back("G");
    uf.unite("B", "G");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Add H, Unite D & H]" << std::endl;
    uf.add_element("H"); inputs.push_back("H");
    uf.unite("D", "H");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Add A & B]" << std::endl;
    uf.add_element("A");
    uf.add_element("B");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite D & G]" << std::endl;
    uf.unite("D", "G");
    for(auto input : inputs){
        std::cout << input << " :  parent = " << uf.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Example of user-defined struct" << std::endl;
    std::cout << std::endl;

    union_find<std::element> uf_element;

    std::vector<std::element> inputs_element{{"0.jpg", 24}, {"1.jpg", 53}, {"2.jpg", 86}, {"3.jpg", 14}};
    std::cout << "[Initialize]" << std::endl;
    for(auto input : inputs_element){
        uf_element.add_element(input);
    }
    for(auto input : inputs_element){
        std::cout << input << " :  parent = " << uf_element.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite {\"0.jpg\", 24} & {\"2.jpg\", 86}]" << std::endl;
    uf_element.unite({"0.jpg", 24}, {"2.jpg", 86});
    for(auto input : inputs_element){
        std::cout << input << " :  parent = " << uf_element.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Unite {\"3.jpg\", 14} & {\"0.jpg\", 24}]" << std::endl;
    uf_element.unite({"3.jpg", 14}, {"0.jpg", 24});
    for(auto input : inputs_element){
        std::cout << input << " :  parent = " << uf_element.find(input) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[Add {\"5.jpg\", 71}, Unite {\"5.jpg\", 71} & {\"1.jpg\", 53}]" << std::endl;
    uf_element.add_element({"5.jpg", 71}); inputs_element.push_back({"5.jpg", 71});
    uf_element.unite({"5.jpg", 71}, {"1.jpg", 53});
    for(auto input : inputs_element){
        std::cout << input << " :  parent = " << uf_element.find(input) << std::endl;
    }
    std::cout << std::endl;
}
