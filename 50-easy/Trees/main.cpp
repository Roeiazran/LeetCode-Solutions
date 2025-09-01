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
    TreeNode *tree;
    Solution() {};

    /*
        Util: Build binary tree from array (heap style).
    */
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

    /*
        Helper for sortedArrayToBst.
        We exploit the fact the array nums is sorted, which means we can
        turn the array into BFS by making the middle value as the root and 
        recursively construct the left and right subtrees.
        Time Complexity: O(n) - In the recursive tree we have n nodes, at level k we have 2^k calls for creating new node.
        So it's basically Geometric series: 2^0 + 2^1 + ... + 2^k, where k = log(n), which is actually: 1 + 2 + 4 + .. + n = O(n).
        Another way with the Master Therem: T(n) = 2T(n/2) + O(1) = O(n).
        Space Complexity: O(log(n)) For the recursive calls
    */
   TreeNode* sortedArrayToBSTHelper(vector<int>& nums, int left, int right) {

        // Base: no elements left in the subarray of nums
        if (left > right) return nullptr;

        int middle = left + (right - left) / 2;

        TreeNode * root = new TreeNode;
        root->val = nums[middle];
        
        // Recursive step: continue left and right with [1,...,middle - 1], [middle + 1, ..., n] subarrays.
        root->left = sortedArrayToBSTHelper(nums, left, middle - 1);
        root->right = sortedArrayToBSTHelper(nums, middle + 1, right);

        return root;
   }

    /*
        Idea: Recursively, like binary search.
    */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n = nums.size();

        return sortedArrayToBSTHelper(nums, 0, n - 1);
    }

    /*
        Like BFS, we use a queue. While traversing the current level, we store its values into an array.
        At the same time, we enqueue the left and right children, which belong to the next level.
        Since we know the number of nodes in the current level (the queue’s size before processing),
        we can iterate exactly that many times, ensuring that one level is fully processed before moving to the next.
        Complexity: O(n)
    */
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> res;
        TreeNode *cur;

        if (!root) return res;

        q.push(root);
        while (!q.empty()) {
            int n = q.size(); // Store the size of the current level
            vector<int> v;    // Store the nodes value of the current level

            for (int i = 0; i < n; i++) {
                cur = q.front();        // Get the node in the front of the queue
                q.pop();                // Pop that node
                v.push_back(cur->val);  // Insert into the values array

                // Process next level
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res.push_back(v);   // Insert the level into the final result
        }

        return res;
    }
    /*
        Helper method for isSymmetric.
        Compares left and right nodes values and checks any subtree for symmetric.
    */
   bool isMirror(TreeNode *left, TreeNode *right)
   {
        if (left == NULL && right == NULL) return true;

        if (right == NULL || left != NULL) return false;

        return (left->val == right->val) 
            && isMirror(left->left, right->right) 
            && isMirror(left->right, right->left); 
   }
    /*
        Problem: Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
        Idea: Use a helper method for the left and right child nodes.
    */
    bool isSymmetric(TreeNode* root) {

        if (root == NULL) return true;

        return isMirror(root->left, root->right);
    }
};

int main(int argc, char const *argv[])
{
    Solution sol = Solution();
    vector<optional<int>> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(NULL);
    v.push_back(4);

    sol.tree = sol.BuildTree(v);

    vector<vector<int>> res = sol.levelOrder(sol.tree);

    for (auto& v : res) {
        for (auto& b : v) {
            cout << b << " ";
        }

        cout << endl;
    }
    return 0;
}
