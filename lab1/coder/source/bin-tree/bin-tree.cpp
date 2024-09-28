#include "bin-tree.h"


BinaryTree::BinaryTree(std::string const &code) noexcept {
    currentCode = code;
}

BinaryTree::BinaryTree() noexcept {
}

BinaryTree *BinaryTree::Left() const noexcept {
    return left;
}

BinaryTree *BinaryTree::Right() const noexcept {
    return right;
}

void BinaryTree::setLeft(BinaryTree* node) noexcept {
    left = node;
}

void BinaryTree::setRight(BinaryTree* node) noexcept {
    right = node;
}

std::string BinaryTree::Code() const noexcept {
    return currentCode;
}
