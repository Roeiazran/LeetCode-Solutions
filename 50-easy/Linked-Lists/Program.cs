public class ListNode {
    public int val;
    public ListNode? next;
    public ListNode(int x) { val = x; }
}


public class Program
{
    public static void Main()
    {
        ListNode? list = CreateListFromArray(new int[] { 2, 4, 5, 7, 1 });
        if (list == null) return;

        list = RemoveNthFromEnd(list, 1);
        PrintList(list);
    }
    
    /*
        Utils: Creates a list from integers array.
    */
    public static ListNode? CreateListFromArray(int[] arr)
    {
        int n = arr.Length;
        if (n == 0) return null;

        ListNode head = new ListNode(arr[0]);
        ListNode tempHead = head;
        for (int i = 1; i < n; i++)
        {
            tempHead.next = new ListNode(arr[i]);
            tempHead = tempHead.next;
        }

        tempHead.next = null;
        return head;
    }

    public static void PrintList(ListNode? list)
    {
        while (list != null) 
        {
            Console.WriteLine(list.val);
            list = list.next;
        }
    }

    /*
        Problem: There is a singly-linked list head and we want to delete a node node in it.
        You are given the node to be deleted node. You will not be given access to the first node of head.
        Idea: Since we getting the node itself we can't just change it's prev next ptr thus we need to replace
        the given node with the node to it's right.
        Complexity: O(1)
    */
    public static void DeleteNode(ListNode node) {
        
        if (node == null || node.next == null) return;

        node.val = node.next.val;
        node.next = node.next.next;
    }

    /*
        Problem: Given the head of a linked list, remove the nth node from the end of the list and return its head.
        Idea: Use two pointers that has gap of n between them, and when the last is at the end of the list 
        the first will be at the deleted node.
        Complexity: O(n)
    */
    public static ListNode RemoveNthFromEnd(ListNode head, int n) {
        ListNode first = head, last = head, prev;

        // only one node in the list
        if (head.next == null) 
        {
            head = null;
            return head;
        }

        // deleting the last on the list
        if (n == 1)
        {
            while (last.next.next != null) last = last.next;
            last.next = null;
            return head;
        }

        // moving last forward so that first will point to the deleted node
        while (n > 0) 
        {
            n--;
            last = last.next;
        }
        
        // moving last and first together
        while (last != null) (last, first) = (last.next, first.next);

        // deleting a node that is not the last on the list, in a list that has more than one node
        first.val = first.next.val;
        first.next = first.next.next;
        return head;
    }
}