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

    ListNode * head;
    Solution(){};
    /*
        Utils: Creates a list from integers array.
    */
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

    /*
        Problem: Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
        Idea: Find the middle of the list and reverse each node up until the middle node, then traverse the list from
        the middle to both directions and compare values.
        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    bool isPalindrome(ListNode* head) {

        ListNode *fast, * prev = nullptr, *curr = head, *next;

        if (head == nullptr || head->next == nullptr) return true;

        fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;   // advance fast pointer
            next = curr->next;   // save next
            curr->next = prev;   // reverse link
            prev = curr;         // advance prev
            curr = next;         // advance curr
        }
     
        if (fast != nullptr) curr = curr->next;
        
        while (curr != nullptr)
        {
            if (curr->val != prev->val) return false;
            curr = curr->next;
            prev = prev->next;
        }

        return true;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol = Solution();

    vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    sol.CreateListFromArray(v);
    return 0;
}