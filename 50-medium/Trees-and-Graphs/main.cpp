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
    TreeNode root;


    vector<int> inorderTraversal(TreeNode* root) {
        
    }

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
};


int main(int argc, char const *argv[])
{
    return 0;
}
