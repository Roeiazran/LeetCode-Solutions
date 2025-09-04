#pragma warning disable
public class ListNode {
    public int val;
    public ListNode? next;
    public ListNode(int x) { val = x; }
}

public class Program
{
    /*
        Problem: There is a singly-linked list head and we want to delete a node in it.
        You are given the node to be deleted. You will not be given access to the first node of the list.

        Idea: Since we getting the node itself we can't simply relink the nodes, we need to create
        a chain effect bringing the next node forwards.

        Time Complexity: O(1)
    */
    public static void DeleteNode(ListNode node) {
        
        if (node == null || node.next == null) return;

        node.val = node.next.val;
        node.next = node.next.next;
    }

    /*
        Problem: Given the head of a linked list, remove the n'th node from the end of the list and return its head.

        Idea: We use two pointers that has gap of n nodes between them. We use a dummy node y serving as a previous
        pointer to the head to simplify the deletion.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static ListNode RemoveNthFromEnd(ListNode head, int n) {
        // Create a dummy previous head
        ListNode dummy = new ListNode(0);
        dummy.next = head;

        ListNode first = dummy, last = head;

        // Move last pointer n steps so the first stops before the node to delete
        for (int i = 0; i < n; i++) last = last.next;
        
        // Move both until last reached the end
        while (last != null) {
            last = last.next;
            first = first.next;
        }

        first.next = first.next.next; // Skip the deleted node
        return dummy.next;
    }

    /*
        Problem: Given the head of a singly linked list, reverse the list, and return the reversed list.

        Idea: Traverse the list with prev, next and curr. keep the next and redirect curr.next to prev.

        Time Complexity: O(n)
        Space Complexity: O(1)
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

        Idea: We use a dummy node to help with the new list building logic. We initialize a tail node
        to dummy, and advance the tail node to the list node with the lower value.
        Repeating that login we create a list and returning dummy.next.
        
        Time Complexity: O(n + m)
        Space Complexity: O(1)
    */
    public static ListNode MergeTwoLists(ListNode list1, ListNode list2) {

        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (list1 != null && list2 != null) {

            if (list1.val > list2.val) {
                tail.next = list1;
                list1 = list1.next;
            }
            else {
                tail.next = list2;
                list2 = list2.next;
            }
            tail = tail.next;
        }
        tail.next = (list1 == null) ? list2 : list1;

        return dummy.next;
    }

    /* 
    =================
    Tests helpers
    =================
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
}