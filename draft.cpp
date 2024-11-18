#include <iostream>

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    // Recursive helper function for searching
    TreeNode* searchRecursive(TreeNode* node, int target) {
        if (!node) return nullptr;  // Target not found
        if (node->val == target) return node;  // Target found
        if (target < node->val) return searchRecursive(node->left, target);  // Search in the left subtree
        return searchRecursive(node->right, target);  // Search in the right subtree
    }

    // Recursive helper function for insertion
    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);  // Insert new node
        if (value < node->val)
            node->left = insertRecursive(node->left, value);  // Insert in left subtree
        else
            node->right = insertRecursive(node->right, value);  // Insert in right subtree
        return node;  // Return the (potentially modified) root
    }

    // Recursive helper function for deletion
    TreeNode* deleteRecursive(TreeNode* node, int value) {
        if (!node) return nullptr;

        // Node to be deleted is found
        if (value < node->val)
            node->left = deleteRecursive(node->left, value);
        else if (value > node->val)
            node->right = deleteRecursive(node->right, value);
        else {
            // Case 1: Node has no children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }

            // Case 2: Node has one child
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            TreeNode* successor = findMin(node->right);
            node->val = successor->val;  // Copy the value of the successor
            node->right = deleteRecursive(node->right, successor->val);  // Delete the successor
        }
        return node;
    }

    // Find the node with the minimum value (used for deletion)
    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

public:
    TreeNode* root;

    BST() : root(nullptr) {}

    // Bootstrap function for searching a value
    TreeNode* search(int value) {
        return searchRecursive(root, value);
    }

    // Bootstrap function for inserting a value
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Bootstrap function for deleting a value
    void remove(int value) {
        root = deleteRecursive(root, value);
    }

    // Inorder traversal to display the tree
    void inorderTraversal(TreeNode* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->val << " ";
            inorderTraversal(node->right);
        }
    }

    // Bootstrap function for traversal
    void display() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    BST tree;
    
    // Inserting elements
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::cout << "Inorder Traversal after insertion: ";
    tree.display();

    // Searching elements
    int target = 40;
    if (tree.search(target))
        std::cout << "Element " << target << " found in the tree." << std::endl;
    else
        std::cout << "Element " << target << " not found in the tree." << std::endl;

    // Deleting elements
    tree.remove(20);
    std::cout << "Inorder Traversal after deleting 20: ";
    tree.display();

    tree.remove(30);
    std::cout << "Inorder Traversal after deleting 30: ";
    tree.display();

    tree.remove(50);
    std::cout << "Inorder Traversal after deleting 50: ";
    tree.display();

    return 0;
}