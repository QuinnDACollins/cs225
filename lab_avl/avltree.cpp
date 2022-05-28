/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

bool debug_flag = false;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(debug_flag)
    {
        std::cout<<"left node_val: "<<t->value<<std::endl;
    }
    Node *temp = t->right;
    t->right = t->right->left;
    temp->left = t;
    //swap(t->right, t->right->left);
    if(t == root)
    {
        root = temp;
        return;
    }
    Node *parent = findParent(root, t);
    if(parent == NULL)
    {
        return;
    }
    if(parent->left == t)
    {
        parent->left = temp;
    }
    else
    {
        parent->right = temp;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    if(debug_flag)
    {
        std::cout<<"leftRight node_val: "<<t->value<<std::endl;
    }
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if(debug_flag)
    {
        std::cout<<"right node_val: "<<t->value<<std::endl;
    }
    Node *temp = t->left;
    t->left = t->left->right;
    temp->right = t;

    if(t == root)
    {
        root = temp;
        return;
    }
    Node *parent = findParent(root, t);
    if(parent == NULL)
    {
        return;
    }
    if(parent->left == t)
    {
        parent->left = temp;
    }
    else
    {
        parent->right = temp;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(debug_flag)
    {
        std::cout<<"rightLeft node_val: "<<t->value<<std::endl;
    }
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL)
    {
        return;
    }
    rebalance(subtree->right);
    rebalance(subtree->left);

    int rightH = height(subtree->right);
    int leftH = height(subtree->left);

    if(rightH == leftH)
    {
        subtree->height = height(subtree);
        return;
    }
    if(rightH - leftH > 1)
    {
        int rightrightH = height(subtree->right->right);
        int rightleftH = height(subtree->right->left);

        if(rightrightH > rightleftH)
        {
            rotateLeft(subtree);
        }
        else
        {
            rotateRightLeft(subtree);
        }
    }
    else if(leftH - rightH > 1)
    {
        int leftrightH = height(subtree->left->right);
        int leftleftH = height(subtree->left->left);

        if(leftleftH > leftrightH)
        {
            rotateRight(subtree);
        }
        else
        {
            rotateLeftRight(subtree);
        }
    }
    subtree->height = height(subtree);

    /*
    if((rightH == 0 && leftH == -1) || (rightH == -1 && leftH == 0) || (rightH == -1 && leftH == -1))
    {
        subtree->height = height(subtree);
        return;
    }
    else if(leftH-rightH > 1)
    {
        if(subtree->left->right != NULL && subtree->left->right->left == NULL && (height(subtree->left->right) > height(subtree->left->left)))
        {
            rotateLeftRight(subtree);
        }
        rotateRight(subtree);
    }
    else if(rightH-leftH > 1)
    {
        if(subtree->right->left != NULL && subtree->right->left->right == NULL && (height(subtree->right->left) > height(subtree->right->right)))
        {
            rotateRightLeft(subtree);
        }
        rotateLeft(subtree);
    }
     */
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findParent(Node*& subtree, Node*& node)
{
    if (subtree == NULL)
        return (Node*)NULL;
    else if (node == subtree->right || node ==subtree->left)
        return subtree;
    else {
        if (node->key < subtree->key)
            return findParent(subtree->left, node);
        else
            return findParent(subtree->right, node);
    }
}

template <class K, class V>
int AVLTree<K, V>::height()
{
    return height(root);
}

template <class K, class V>
int AVLTree<K, V>::height(Node*& subtree)
{
    // your code here
    if(subtree == NULL)
    {
        return -1;
    }
    if(subtree->right == NULL && subtree->left==NULL)
    {
        return 0;
    }
    return 1 + std::max(height(subtree->right), height(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
    {
        subtree = new Node(key, value);
        rebalance(root);
        return;
    }
    else if(key < subtree->key)
    {
        insert(subtree->left, key, value);
    }
    else
    {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
return;
    }

