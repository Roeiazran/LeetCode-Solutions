#include <iostream>
#include <vector>
using namespace std;

// Given util function for firstBadVersion
bool isBadVersion(int version);

/*
    Problem: Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
    Idea: We use binary search to narrowing down the search by half each time.
    Time Complexity: O(log(n)).
    Space Complexity: O(1)
*/
int firstBadVersion(int n) {
    int left = 1, right = n, middle;

    while (left < right) {
        /* 
        Warning: possible overflow when assigning middle = (left + right) / 2.
        Right and left are ints therefor (left + right) could potentially overflow.
        Use the equivalent expression left + (right - left) / 2 is Safe!
        */
        middle = left + (right - left) / 2;

        if (isBadVersion(middle)) right = middle;   // Cut the search by half
        else left = middle + 1;                     // Skip the good version
    
    }
    return left; // left == right == first bad version
}

/*
    Problem: You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n,
    representing the number of elements in nums1 and nums2 respectively.
    Merge nums1 and nums2 into a single array sorted in non-decreasing order.

    Idea: We walk through both arrays from the end usign two pointers.
    Time Complexity: O(n + m)
    Space Complexity: O(1)
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    
    int m1 = m - 1; // Pointer to the last item of nums1
    int n2 = n - 1; // Pointer to the last item of nums2
    int nm = n + m - 1; // Pointer to last insert position in nums1

    while (n2 >= 0 && m1 >= 0)
    {
        if (nums1.at(m1) >= nums2.at(n2))
        {
            nums1[nm] = nums1.at(m1);
            m1 -= 1;
        } else {
            nums1[nm] = nums2.at(n2);
            n2 -= 1;
        }
        nm -= 1;
    }

    // Insert into nums1 what's left in nums2
    while (n2 >= 0)
    {
        nums1[nm] = nums2.at(n2);
        nm -= 1;
        n2 -= 1;
    }
}


int main(int argc, char const *argv[])
{
    cout << firstBadVersion(212675);
    return 0;
}




