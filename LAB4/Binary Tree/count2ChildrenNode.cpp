int countTwoChildrenNode() {
    return countTwoChildrenNodeHelper(this->root);
}

int countTwoChildrenNodeHelper(Node* node) {
    if (!node) return 0;

    int count = 0;
    if (node->pLeft && node->pRight) {
        count = 1;
    }

    return count + countTwoChildrenNodeHelper(node->pLeft) + countTwoChildrenNodeHelper(node->pRight);
}
