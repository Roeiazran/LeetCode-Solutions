#pragma warning disable
public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class Program
{
    /*
        Problem: Given the root of a binary tree, return its maximum depth.

        Idea: To determine the depth of the current node compute the depth it's left and right subtrees.

        Time Complexity: O(n)
        Space Complexity: O(h) Where h is the depth of the tree: Balanced tree = O(log(n)), Skewed tree = O(n).
    */
    public static int MaxDepth(TreeNode root) {

        // Base case: if the tree is empty, depth = 0
        if (root == null) return 0;

        // Recursively compute the depth of the left subtree
        int left = MaxDepth(root.left);

        // Recursively compute the depth of the right subtree
        int right = MaxDepth(root.right);

        // Return the depth of the current node
        return Math.Max(left, right) + 1;
    }

    /*
        Problem: Given the root of a binary tree, determine whether it is a valid binary search tree (BST). (left.val < root.val - strictly less)
        
        Time Complexity: O(1)
        Space Complexity: O(1)
    */
    public static bool IsValidBST(TreeNode root) {
        
        // Case: one root node is trivially true
        if (root.left == null && root.right == null) return true;

        // Using long since 2^32 <= node.val <= 2^32 - 1
        return ValidateBST(root, long.MinValue, long.MaxValue);
    }

    /*
        Helper method to IsValidBST.

        Idea: For each node to be valid it's value must be within a specific range.
        Given this range we can recursively compute the validity of the left and right subtrees,
        and making sure a deeper descendent does not violate the BST property.

        Time Complexity: O(n) - Each node must be visited.
        Space Complexity: O(h) Where h is the height of the tree.
    */
    public static bool ValidateBST(TreeNode root, long minVal, long maxVal)
    {
        // Base case: empty subtree is valid
        if (root == null) return true;

        // Current node value must be between minVal and maxVal, else he's invalid
        if (root.val >= maxVal || root.val <= minVal) return false;

        // Recursively validate the left subtree
        bool isLeftValid = ValidateBST(root.left, minVal, root.val);

        // Recursively validate the right subtree
        bool isRightValid = ValidateBST(root.right, root.val, maxVal);

        // Return AND on both sides, both sides must be valid
        return isLeftValid && isRightValid;
    }

    /* 
    =================
    Tests helpers
    =================
    */
    public static TreeNode BuildTree(int?[] arr, int i = 0)
    {
        if (i >= arr.Length || arr[i] == null) return null;

        TreeNode root = new TreeNode(arr[i].Value);
        root.left = BuildTree(arr, 2 * i + 1);
        root.right = BuildTree(arr, 2 * i + 2);

        return root;
    }
}