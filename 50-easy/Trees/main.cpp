#include <vector>
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
    TreeNode tree;
    Solution() {};

    /*
        Util: Build binary tree from array (heap style).
    */
    TreeNode * BuildTree(vector<optional<int>> arr, int i = 0)
    {
        // Bast case: out of the array bounds, null pointer
        if (i >= arr.size() || !arr.at(i).has_value()) return NULL;

        TreeNode * root = new TreeNode; // create a node on the heap
        root->val = arr.at(i).value();  // assign value 

        // build child nodes
        root->left = BuildTree(arr, 2 * i + 1);
        root->right = BuildTree(arr, 2 * i + 2);
        return root;
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


    return 0;
}
