#include "ds/avl-tree.h"
#include "ds/list.h"
#include "ds/vector.h"

#include <iostream>

constexpr std::uint32_t AVL_TREE_SIZE = 100;
constexpr std::uint32_t LIST_SIZE = 100;
constexpr std::uint32_t VECTOR_SIZE = 100;


int main() {
    auto tree = ds::avl_tree<std::int32_t, std::string>();
    for (std::int32_t i = 0; i < AVL_TREE_SIZE; ++i)
        tree.insert(i, std::to_string(i));

    std::cout << "avl-tree: ";
    for (std::int32_t i = 0; i < AVL_TREE_SIZE; ++i)
        std::cout << tree.search(i)->get_value() << " ";
    std::cout << std::endl;


    //---


    auto list = ds::list<std::int32_t>();
    for (std::int32_t i = 0; i < LIST_SIZE; ++i)
        list.push_back(i);


    //---


    auto vector = ds::vector<std::int32_t>();
    for (std::int32_t i = 0; i < VECTOR_SIZE; ++i) {
        vector.push_back(i);
    }

    std::cout << "vector: ";
    for (ds::vector<std::int32_t>::size_type i = vector.size(); i > 0; --i) {
        std::cout << vector[i - 1] << " ";
        vector.pop_back();
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
