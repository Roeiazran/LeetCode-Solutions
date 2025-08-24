#pragma warning disable
public class ListNode {
    public int val;
    public ListNode? next;
    public ListNode(int x) { val = x; }
}


public class Program
{
    public static void Main()
    {
        ListNode? list2 = CreateListFromArray(new int[] {0, 0, 1, 2});
        ListNode? list1 = CreateListFromArray(new int[] {1, 1, 2, 3 });

        ListNode list = MergeTwoLists(list1, list2);

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

    /*
        Problem: Given the head of a singly linked list, reverse the list, and return the reversed list.
        Idea: Traverse the list with prev, next and curr. keep the next and redirect curr.next to prev.
        Complexity: O(n)
    */
    public static ListNode ReverseList(ListNode head) {
        ListNode prev = null, curr = head, next = head?.next;

        while (curr != null)
        {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    /*
        Problem: You are given the heads of two sorted linked lists list1 and list2.
        Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
        Return the head of the merged linked list.
        Idea: Use two pointers to merge the lists like merge sort algorithm.
        Complexity: O(n)
    */
    public static ListNode MergeTwoLists(ListNode list1, ListNode list2) {
        ListNode curr1, curr2, prev;

        if (list1 == null) return list2;
        if (list2 == null) return list1;

        // after this prev.val <= curr2.val
        if (list1.val < list2.val)
        {
            prev = list1;
            curr1 = prev.next;
            curr2 = list2;
        } else 
        {
            prev = list2;
            curr1 = prev.next;
            curr2 = list1;
        }

        while (curr2 != null)
        {
            // advance both curr1 and prev until prev.val <= curr2.val < curr1.val
            while (curr1 != null && curr1.val <= curr2.val)
            {
                prev = curr1;
                curr1 = curr1.next;
            }

            // order curr2 to go between prev and curr1 and advance prev to curr2
            prev.next = curr2;
            prev = prev.next;

            // move curr2 to it's next and change it to curr1.
            curr2 = prev.next;
            prev.next = curr1;
        }

        return (list1.val < list2.val) ? list1 : list2;
    }
}