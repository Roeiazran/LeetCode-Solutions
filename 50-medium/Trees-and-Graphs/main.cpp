#include <vector>
#include <iostream>
#include <optional>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {

public:

    /*
        Problem: Given the root of a binary tree, return the inorder traversal of its nodes' values.

        Idea: Inorder traverse the tree (i.e left, insert, right).

        Time Complexity: O(n)
        Space Complexity: O(h) - Where h is the height of the tree.
    */
    void helperInorderTraversal(TreeNode * root, vector<int>& inorder) {

        // Base case: empty tree, retrun from the recursion
        if (root == nullptr) return;

        // Travel the left subtree
        helperInorderTraversal(root->left, inorder);

        // When the left subtree return, just before going the right subtree, add the current node value
        inorder.push_back(root->val);

        // Travel the right subtree
        helperInorderTraversal(root->right, inorder);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> v;

        helperInorderTraversal(root, v);
        return v;
    }

    /*
        Util: Build binary tree from array (heap style).

        We follow the convention, where for the node at index i the left child
        is at index 2 * i + 1, and the right is at index 2 * i + 2.

        Time Complexity: O(n) - Each item in the array is visited only once.
        Space Complexity: O(h) Where h is the height of the array.
    */
    TreeNode root;
    TreeNode * BuildTree(vector<optional<int>> arr, int i = 0)
    {
        // Base case: out of bounds, return null
        if (i >= arr.size() || !arr.at(i).has_value()) return NULL;

        TreeNode * root = new TreeNode;     // Create a node on the heap
        root->val = arr.at(i).value();      // Assign value 

        // Build child nodes
        root->left = BuildTree(arr, 2 * i + 1);
        root->right = BuildTree(arr, 2 * i + 2);
        return root;
    }
};


int main(int argc, char const *argv[])
{
    
    vector<int> v;
    vector<optional<int>> tree = {1, 2, 3, 4, 5, nullopt, 8, nullopt, nullopt, 6, 7, nullopt, nullopt, 9};

    Solution sol = Solution();

    TreeNode * head = sol.BuildTree(tree);

    v = sol.inorderTraversal(head);

    for (auto a :v){
        cout << a << " ";
    }

    return 0;
}


