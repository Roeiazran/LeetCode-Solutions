#include <iostream>
#include <vector>
using namespace std;

bool isBadVersion(int version);

/*
    Problem: Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
    Idea: Use binary search to narrowing down the search by half each time.
    Complexity: O(log(n)).
*/
int firstBadVersion(int n) {

    int left = 1, right = n;
    long middle;

    while (left < right) {
        /* 
        Note: possible overflow when middle = (left + right) / 2.
        Because right and left are ints (left + right) could potentially overflow.
        The equivalent expression left + (right - left) / 2 is Safe!
        */
        middle = left + (right - left) / 2;

        if (isBadVersion(middle)) 
        {
            right = middle; // Shrink the search
        }
        else 
        {
            left = middle + 1; // Skip the good version
        }
    }
    return left; // left == right == first bad version
}


/*
    Problem: You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively
    Merge nums1 and nums2 into a single array sorted in non-decreasing order.
    Idea: Merge the arrays by compering elements from the end.
    Complexity: O(n + m)
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    
    int m1 = m - 1; // index to the last (non-zero) item of nums1
    int n2 = n - 1; // index to the last item of nums2
    int nm = n + m - 1; // index used to insert items into nums1

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




