#include <vector>
#include <optional>
#include <queue>
#include <iostream>

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
        Helper for sortedArrayToBst.

        We exploit the sorted property of the array, by picking the middle element
        as the root, then we recursively construct the left and right subtrees 
        using the left and right halves of the array.

        Time Complexity: O(n) - The recursive tree has n nodes in it, that's because each node 
        must be created in a it's own recursive call.
   
        So it's basically a Geometric series: 
        Level 0 (root level): at most 2^0 calls.
        Level 1: at most 2^1 calls.
        Level k: at most 2^k calls.

        where k = the height of the tree = O(log(n)).

        so basically we get: 1 + 2 + 4 + .. + n = 2n - 1 = O(n).

        Another way of looking at it is with the Master Therem: T(n) = 2T(n/2) + O(1) = O(n).

        Space Complexity: O(log(n)) - For the recursive calls, where in each call we use O(1) space.
    */
    TreeNode* sortedArrayToBSTHelper(vector<int>& nums, int left, int right) {

            // Base case: empty subarray
            if (left > right) return nullptr;

            // Find the middle element index
            int middle = left + (right - left) / 2;

            // Create a new tree node with the middle element value
            TreeNode * root = new TreeNode;
            root->val = nums[middle];
            
            // Recursively build the left subtree from [1,...,middle - 1] subarray
            root->left = sortedArrayToBSTHelper(nums, left, middle - 1);

            // Recursively build the left subtree from [middle + 1, ..., n] subarray
            root->right = sortedArrayToBSTHelper(nums, middle + 1, right);

            return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n = nums.size();

        return sortedArrayToBSTHelper(nums, 0, n - 1);
    }

    /*
        Like BFS, we use a queue. While traversing the current level, we store it's values into an array
        and at the same time, we enqueue the left and right children, which belong to the next level.
        Since we know the number of nodes in the current level,
        we can iterate exactly that many times, ensuring that one level is fully processed before moving to the next.

        Time Complexity: O(n)
        Space Complexity: O(n)
    */
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;         // Store all the nodes
        vector<vector<int>> res;    // Used as the result vector
        TreeNode *cur;              // Used as a temporary node pointer 

        // Edge case: empty tree, return empty array
        if (!root) return res;

        q.push(root);       // Start with the root
        while (!q.empty()) {
            int n = q.size(); // Store the size of the current level
            vector<int> v;    // Initialize empty vector to store the current level values

            for (int i = 0; i < n; i++) {
                cur = q.front();        // Pop the first node
                q.pop();                // Dequeue the first node
                v.push_back(cur->val);  // Insert value into the values array

                // Enqueue the nodes of the next level
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res.push_back(v);   // Append the level's values array to the result
        }
        return res;
    }

    /*
        Helper method for isSymmetric.
        We recursively compare left.left with right.right and left.right with right.left. 

        Time Complexity: O(n)
        Space Complexity: O(h) - The height of the tree.
    */
    bool isMirror(TreeNode *left, TreeNode *right)
    {
        // Edge case: both nulls, valid
        if (left == NULL && right == NULL) return true;

        // Edge case: one is null and the other is not, invalid
        if (right != NULL || left != NULL) return false;

        return (left->val == right->val) 
            && isMirror(left->left, right->right) 
            && isMirror(left->right, right->left); 
    }
    /*
        Problem: Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
    */
    bool isSymmetric(TreeNode* root) {

        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }

    /* 
    =================
    Tests helpers
    =================
    */
    TreeNode *tree;
    TreeNode * BuildTree(vector<optional<int>> arr, int i = 0)
    {
        // Bast case: out of the array bounds, null pointer
        if (i >= arr.size() || !arr.at(i).has_value()) return NULL;

        TreeNode * root = new TreeNode; // Create a node on the heap
        root->val = arr.at(i).value();  // Assign value 

        // Build child nodes
        root->left = BuildTree(arr, 2 * i + 1);
        root->right = BuildTree(arr, 2 * i + 2);
        return root;
    }

};
