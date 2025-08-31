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
    
    public static void Main()
    {
        int?[] arr = { 5, 1, 10, null, null, 3, 6 };
        TreeNode tree = BuildTree(arr);

        Console.WriteLine(IsValidBST(tree));
    }

    /*
        Util: Build binary tree from array (heap style).
    */
    public static TreeNode BuildTree(int?[] arr, int i = 0)
    {
        if (i >= arr.Length || arr[i] == null) return null;

        TreeNode root = new TreeNode(arr[i].Value);
        root.left = BuildTree(arr, 2 * i + 1);
        root.right = BuildTree(arr, 2 * i + 2);

        return root;
    }

    /*
        Problem: Given the root of a binary tree, return its maximum depth.
        Idea: The depth of any node is the maximum depth between it's left and right
        child nodes + 1.
        Complexity: O(n)
    */
    public static int MaxDepth(TreeNode root) {

        if (root == null) return 0;

        int left = MaxDepth(root.left);
        int right = MaxDepth(root.right);
        return Math.Max(left, right) + 1;
    }

    /*
        Problem: Given the root of a binary tree, determine whether it is a valid binary search tree (BST). (left.val < root.val - strictly less)
        Idea: Use a helper function, pass to it the range of values [min, max] that the subtree must be in. On left traversal update max and on
        right traversal update min.
        Complexity: O(n)
    */
    public static bool IsValidBST(TreeNode root) {
        
        // Case: one root node is trivially true
        if (root.left == null && root.right == null) return true;

        // Using long since 2^32 <= node.val <= 2^32 - 1
        return ValidateBST(root, long.MinValue, long.MaxValue);
    }

    /*
        Helper method to IsValidBST(TreeNode root)
    */
    public static bool ValidateBST(TreeNode root, long minVal, long maxValue)
    {
        // Base case: the bottom of the tree
        if (root == null) return true;

        // Check if the node value is in it's value boundaries
        if (root.val >= maxValue || root.val <= minVal) return false;

        // Recursively continue to left and right subtrees
        bool isLeftValid = ValidateBST(root.left, minVal, root.val);
        bool isRightValid = ValidateBST(root.right, root.val, maxValue);

        // Return the operation AND on both sides
        return isLeftValid && isRightValid;
    }

}