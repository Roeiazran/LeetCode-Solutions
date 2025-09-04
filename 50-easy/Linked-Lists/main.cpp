#include <iostream>
#include <vector>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {

public:
    
    /*
        Problem: Given head, the head of a linked list, determine if the linked list has a cycle in it.
        Idea: Use slow and fast pointer, if there is a cycle it is guaranteed that fast and slow will meet.

        Complexity: O(n) - If a cycle exists it means fast and slow will meet after at most O(n) steps.

        When both slow and fast in the cycle, fast advance towards slow one step at a time. This mean
        that after C steps they'll meet.

        Lets denote with l the number of nodes in the list that are outside the cycle, and by C the node in it.
        So there are (n - m) steps until slow goes inside the cycle, and another C steps until both will meet.
    */
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        
        // If list is empty or has only one node, no cycle possible
        if (head == nullptr || head->next == nullptr) return false;

        // Keep moving until fast pointer reaches the end
        while (fast != nullptr && fast->next != nullptr)
        {
            // Move slow one step
            slow = slow->next;

            // Move fast two steps
            fast = fast->next->next;

            // If they meet, cycle exists
            if (slow == fast) return true;
        }

        // Fast reached the end, no cycle
        return false;
    }

    /*
        Problem: Given the head of a singly linked list, return true if it is a palindrome or false otherwise.

        Idea: Find the middle node with the help of slow and fast pointers, doing so while also 
        reversing the first half of the list. Then Compare the two halves node by node.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    bool isPalindrome(ListNode* head) {

        ListNode *fast, * prev = nullptr, *curr = head, *next;

        // If the list is empty or has only one node, it is already palindrome
        if (head == nullptr || head->next == nullptr) return true;
        fast = head;

        // Find middle node
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;   // advance fast pointer
            next = curr->next;   // save next
            curr->next = prev;   // reverse link
            prev = curr;         // advance prev
            curr = next;         // advance curr
        }
    
        // If the list has odd length, the middle node needs to be skipped
        if (fast != nullptr) curr = curr->next;
        
        // Compare both halves of the list
        while (curr != nullptr)
        {
            if (curr->val != prev->val) return false;
            curr = curr->next;
            prev = prev->next;
        }
        return true;
    }

    /* 
    =================
    Tests helpers
    =================
    */
    ListNode * head;
    void CreateListFromArray(vector<int> arr)
    {
        int n = arr.size();
        if (n == 0) return;

        head = new ListNode(arr[0], nullptr);
        ListNode* thead = head;
        for (int i = 1; i < n; i++)
        {
           (*head).next = new ListNode(arr[i], nullptr);
            head = head->next;
        }
        head = thead;
    }
    void printList(ListNode *head)
    {
        while (head != nullptr)
        {
            cout << (*head).val << " ";
            head = head->next;
        }
    }
};