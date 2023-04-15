#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
};


void rotate_right(TreeNode *&root) {
    TreeNode *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root = new_root;
}

void rotate_left(TreeNode *&root) {
    TreeNode *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root = new_root;
}




int getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return max(left_height, right_height) + 1;
}

bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

void balance(TreeNode *&root) {
    if (!root) {
        return;
    }
    int balance_factor = getHeight(root->left) - getHeight(root->right);
    if (balance_factor > 1) {
        if (getHeight(root->left->left) >= getHeight(root->left->right)) {
            rotate_right(root);
        } else {
            rotate_left(root->left);
            rotate_right(root);
        }
    } else if (balance_factor < -1) {
        if (getHeight(root->right->right) >= getHeight(root->right->left)) {
            rotate_left(root);
        } else {
            rotate_right(root->right);
            rotate_left(root);
        }
    }
}


void insertNode(TreeNode*& root, int val) {
    if (root == nullptr) {
        root = new TreeNode(val);
    }else if (val < root->val) {
        insertNode(root->left, val);
    } else {
        insertNode(root->right, val);
    }
}

TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void deleteNode(TreeNode*& root, int val) {
    if (root == nullptr) {
        return;
    }
    if (val < root->val) {
        deleteNode(root->left, val);
    } else if (val > root->val) {
        deleteNode(root->right, val);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        } else {
            TreeNode* temp = findMin(root->right);
            root->val = temp->val;
            deleteNode(root->right, temp->val);
        }
    }
}

void print_tree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    print_tree(root->left);
    cout << root->val << " ";
    print_tree(root->right);
}





int main() {
    TreeNode* root = nullptr;
    vector<int> nums = {5, 1, 4, 6, 3};
    for (int num : nums) {
        insertNode(root, num);
    }
    cout << "Is the tree balanced? " << boolalpha << isBalanced(root) << endl;
    print_tree(root);
    cout << endl;
    balance(root);
    cout << "Is the tree balanced? " << boolalpha << isBalanced(root) << endl;
    print_tree(root);


    return 0;
}
