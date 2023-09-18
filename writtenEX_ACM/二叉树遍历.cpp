#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : val(val), left(nullptr), right(nullptr) {}
};

// 根据输入数据构造二叉树
TreeNode* buildTree(unordered_map<char, pair<char, char>>& nodeMap, char rootValue) {
    if (rootValue == '0') {
        return nullptr;
    }

    TreeNode* root = new TreeNode(rootValue);
    int leftChild = nodeMap[rootValue].first;
    int rightChild = nodeMap[rootValue].second;

    root->left = buildTree(nodeMap, leftChild);
    root->right = buildTree(nodeMap, rightChild);

    return root;
}

// 前序遍历二叉树
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val;
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序遍历二叉树
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << root->val;
    inorderTraversal(root->right);
}

// 后序遍历二叉树
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->val;
}

int main() {
    int n;
    cin >> n;
    unordered_map<char, std::pair<char, char>> nodeMap;

    // 先保存输入的数据 
    vector<char> index = vector<char>(n + 1, '0'); 
    vector<vector<int>> nums = vector<vector<int>>(n + 1, vector<int>(2, 0));
    for (int i = 1; i <= n; i++) {
        cin >> index[i] >> nums[i][0] >> nums[i][1];
    }

    // 生成二叉树 
    for (int i = 1; i <= n; i++) {
        nodeMap[index[i]] = make_pair(index[nums[i][0]], index[nums[i][1]]);
    }
    TreeNode* root = buildTree(nodeMap, index[1]);

    preorderTraversal(root);
    cout << std::endl;

    inorderTraversal(root);
    cout << std::endl;

    postorderTraversal(root);
    cout << std::endl;

    return 0;
}



