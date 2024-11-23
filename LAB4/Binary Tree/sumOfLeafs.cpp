int sumOfLeafs() {
    return sumOfLeafsHelper(this->root);
}

int sumOfLeafsHelper(Node* node) {
    if (!node) return 0;
    if (!node->pLeft && !node->pRight) {
        return node->value;
    }
    return sumOfLeafsHelper(node->pLeft) + sumOfLeafsHelper(node->pRight);
}
