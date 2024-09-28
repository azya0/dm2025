#pragma once

#include <string>

class BinaryTree {
private:
    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;

    std::string currentCode = "";
public:
    BinaryTree() noexcept;
    BinaryTree(std::string const & code) noexcept;

    BinaryTree* Left() const noexcept;
    BinaryTree* Right() const noexcept;

    void setLeft(BinaryTree*) noexcept;
    void setRight(BinaryTree*) noexcept;

    std::string Code() const noexcept;
};
