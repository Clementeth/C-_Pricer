#pragma once

#include <vector>
#include <iostream>


template <typename T>
class BinaryTree {
public:
    BinaryTree();
    void setDepth(int depth);
    void setNode(int level, int index, T value);  
    T getNode(int level, int index) const;
    void display() const;

private:
    int _depth;
    std::vector<std::vector<T> > _tree;
};


template <typename T>
BinaryTree<T>::BinaryTree() {
    _depth = 0;
}


template <typename T>
void BinaryTree<T>::setDepth(int depth) {

    _depth = depth;
    _tree.clear();
    _tree.resize(_depth + 1);

    for (int i = 0; i <= _depth; i++) {
        _tree[i].resize(i + 1);
    }

}


template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level < 0 || level >= int(_tree.size())) {
        return;
    }
    if (index < 0 || index >= int(_tree[level].size())) {
        return;
    }
    _tree[level][index] = value;
}


template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    return _tree[level][index];    
}


template <typename T>
void BinaryTree<T>::display() const {
    int total_levels = int(_tree.size());

    // Affichage à plat (lignes)
    for (int level = 0; level < total_levels; level++) {
        for (int j = 0; j < int(_tree[level].size()); j++) {
            std::cout << _tree[level][j];
            if (j < int(_tree[level].size()) - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Affichage en triangle
    for (int level = 0; level < total_levels; level++) {
        int indent = (total_levels - level - 1) * 3;
        for (int s = 0; s < indent; s++) {
            std::cout << " ";
        }

        for (int j = 0; j < int(_tree[level].size()); j++) {
            std::cout << _tree[level][j];
            if (j < int(_tree[level].size()) - 1) {
                std::cout << "     ";
            }
        }
        std::cout << std::endl;

        if (level < total_levels - 1) {
            int slash_indent = indent - 1;
            if (slash_indent < 0) {
                slash_indent = 0;
            }
            for (int s = 0; s < slash_indent; s++) {
                std::cout << " ";
            }
            for (int j = 0; j < int(_tree[level].size()); j++) {
                std::cout << "/ \\";
                if (j < int(_tree[level].size()) - 1) {
                    std::cout << "   ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
