#include <vector>
#include <iostream>
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

    /*
        Idea: First, compute the lengths of both lists. Then, traverse them so that 
        the longer list starts |lenA – lenB| steps ahead. This way, if the lists 
        share an intersection point, both pointers will arrive at the same 
        node during the second traversal.

        An elegant way of doing that is by letting each pointer switch to the other list’s head when they reach the
        end of their lists. In such a way the pointer to the shorter list will finish first and will be placed
        at the beginning of the largest one making the exact |lenA - lenB| steps until the pointer of the largest will point
        to the start of the shortest and begin traversing the shortest list.
        If both lists do not share a common intersection point then after making n + m steps both pointer will point to null.
        Complexity: O(n + m)
    */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    
        ListNode * A = headA, * B = headB;

        while (A != B)
        {
            if (A == B) return A;
            A = A ? A->next : headB;
            B = B ? B->next : headA;
        }

        return A;
    }

    /*
        Idea: Treat the list as two list , odd and even. Traverse the original list with odd and even pointers,
        relinking each other next pointers.
        Complexity: O(n)
    */
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode * odd = head, *even = head->next, *evenHead = head->next;

        while (even && even->next) { // Stop when odd pointer at the end of odd lists

            odd->next = even->next; // Skip even nodes in the odd list
            odd = odd->next;
            
            even->next = odd->next; // Skip odd nodes in the even list
            even = even->next;
        }

        odd->next = evenHead; // Link the two lists together
        return head;
    }

    /*
        Idea: Traverse both the lists at the same paste, at each step sum the total value of the nodes and the carry,
        then compute new carry and append a new node to the tail of the new list.
        Use a dummy node created on the stack, then point to it with a pointer, then create the new nodes on the heap.
        With the use of the dummy.next pointer we avoid loosing the new list head.
        Note: If l1 or l2 are null we continue the loop all while the carry is not 0, and it is the same process as
        if l1 and l2 weren't null.
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        int carry = 0;
        ListNode dummy(0);
        ListNode * tail = &dummy;
    

        while (l1 != nullptr || l2 != nullptr || carry) {
            int sum = carry;

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }

        return dummy.next;
    }



    /*
        Utils: Creates a list from integers array.
    */
    void createListFromArray(vector<int> v) {

        int n = v.size();
        if (n == 0) return;

        head = new ListNode;
        ListNode *temp = head;
        head->val = v.at(0);

        for (int i = 1; i < n; i++) {
            ListNode * next = new ListNode;
            next->val = v.at(i);
            head->next = next;
            head = next;
        }

        head->next = nullptr;
        head = temp;
    }

    void printList() {

        while (head != nullptr) {
            cout << head->val << " ";
            head = head->next;
        }
    }
};


int main(int argc, char const *argv[])
{
    vector<int> v = {1,2,3,4,5,6};
    Solution sol = Solution();
    sol.createListFromArray(v);
    ListNode * t = sol.oddEvenList(sol.head);

    sol.printList();
    return 0;
}