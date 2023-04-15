#include <iostream>
#include <queue>
using namespace std;
enum Color{BLACK, RED};

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    Color color;

        TreeNode(int v, Color c, TreeNode* p, TreeNode* l, TreeNode* r) {
        val = v;
        color = c;
        parent = p;
        left = l;
        right = r;
    }
};



void left_rotate(TreeNode *&root, TreeNode *node){
    if(node->right == nullptr){
        cout << "右节点为空" << endl;
        exit(1);
    }

    TreeNode *r = node->right;
    node->right = r->left;

    if(r->left != nullptr){
        r->left->parent = node;
    }
    r->parent = node->parent;

    if(node->parent == nullptr){
        root = r;
    }else if(node == node->parent->left){
        node->parent->left = r;
    }else{
        node->parent->right = r;
    }

    r->left = node;
    node->parent = r;
}

void right_rotate(TreeNode *&root, TreeNode *node){
    TreeNode *l = node->left;
    node->left = l->right;
    if (l->right != nullptr) {
        l->right->parent = node;
    }
    l->parent = node->parent;

    if (node->parent == nullptr) {
        root = l;
    } else if (node == node->parent->left){
        node->parent->left = l;
    }else{
        node->parent->right = l;
    }

    l->right = node;
    node->parent = l;
}

void insert_fixup(TreeNode*& root, TreeNode* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            TreeNode* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                // Case 1：父节点和叔节点都为红色
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Case 2：父节点为红色，叔节点为黑色，且当前节点为父节点的右子节点
                    node = node->parent;
                    left_rotate(root, node);
                }
                // Case 3：父节点为红色，叔节点为黑色，且当前节点为父节点的左子节点
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(root, node->parent->parent);
            }
        } else {
            TreeNode* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                // Case 1：父节点和叔节点都为红色
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Case 2：父节点为红色，叔节点为黑色，且当前节点为父节点的左子节点
                    node = node->parent;
                    right_rotate(root, node);
                }
                // Case 3：父节点为红色，叔节点为黑色，且当前节点为父节点的右子节点
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(TreeNode*& root, TreeNode* node) {
    // 插入节点
    TreeNode* p = nullptr;
    TreeNode* x = root;
    while (x != nullptr) {
        p = x;
        if (node->val < x->val) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = p;
    if (p == nullptr) {
        root = node;
    } else if (node->val < p->val) {
        p->left = node;
    } else {
        p->right = node;
    }
    node->color = RED;

    // 修复红黑树
    insert_fixup(root, node);
}

void delete_fixup(TreeNode *&root, TreeNode *x) {
    TreeNode *w;
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
                w = x->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
            if(w->right->color == BLACK){
                w->color = RED;
                right_rotate(root, w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            left_rotate(root, x->parent);
            x = root;
            }
        }else{
            w = x->parent->left;
            if(w->color = RED){
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;

            }else{
                if(w->left->color == BLACK){
                    w->color = RED;
                    left_rotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(root, x->parent);
                x = root;
            }
        }
        

    }
    x->color = BLACK;
}



void transplant(TreeNode *&root, TreeNode *u, TreeNode *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}


TreeNode* search(TreeNode* root, int val) {
    TreeNode* x = root;
    while (x != nullptr) {
        if(x->val == val){
            return x;
        }else if(x->val > val){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    return nullptr;
}

TreeNode *delete_node(TreeNode *&root, int val) {
    TreeNode *cur = search(root, val);
    if(cur == nullptr){
        exit(1);
    }

    if(cur->left != nullptr && cur->right != nullptr){
        TreeNode *pre = cur->left;
        while(pre->left != nullptr){
            pre = pre->right;
        }
        cur->val = pre->val;
        cur = pre;
    }

    TreeNode *child = cur->left != nullptr ? cur->left : cur->right;
    if(child != nullptr){
        child->parent = cur->parent;
        if(cur->parent == nullptr){
            root = child;
        }else{
            if(cur->parent->left == cur){
                cur->parent->left = child;
            }else{
                cur->parent->right = child;
            }
        }

        if(cur->color == BLACK){
            delete_fixup(root, child);
        }
    }else{
        if(cur->color == BLACK){
            delete_fixup(root, cur);
        }
        if(cur->parent->left == cur){
            cur->parent->left = nullptr;
        }else{
            cur->parent->right = nullptr;
        }
    }
    return root;
}






void printTree(TreeNode* root) {
    if (root != nullptr) {
        printTree(root->left);
        std::cout << root->val << "(" << (root->color == RED ? "red" : "black") << ") " << endl;
        printTree(root->right);
    }
}

void printRBTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            TreeNode* cur = q.front();
            q.pop();

            if (cur == nullptr) {
                cout << "N ";
            } else {
                cout << "(" << cur->val << "," << (cur->color == RED ? "R" : "B") << ") ";
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        cout << endl;
    }
}




int main(){
    int arr[] = {1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    TreeNode* root = nullptr;
    for (int i = 0; i < n; i++) {
        TreeNode* node = new TreeNode(arr[i], RED, nullptr, nullptr, nullptr);
        insert(root, node);
        printRBTree(root);
        cout << "-----------------------" << endl;
    }


    printTree(root);



    system("PAUSE");
    return 0;
}