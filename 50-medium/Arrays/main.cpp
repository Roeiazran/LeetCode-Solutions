#include <vector>
#include <unordered_set>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

/*
    Problem: Given an array of strings strs, group the anagrams together. You can return the answer in any order.
    Idea: Use unsorted map<string, vector<string>>, the map will have as key the sorted string, and as value
    the vector of all the anagrams of that string.

    Time Complexity: O(n). We have O (n * k log k) where k <= 100, thus O(n) to sort each string in strs.
    Then another O(n) to push the groups into the result.
    Space complexity: O(). The map stores n strings as keys and another n strings as values, each 
    string of size k <= 100, thus in total we have O(nk) = O(n) space complexity.
    Note: The groups don't get copied into the result array, rather they are transferred as the same
    object, so no extra space is required.
 */
vector<vector<string>> FastGroupAnagrams(vector<string>& strs) {

    unordered_map<string,vector<string>> mp;
    vector<vector<string>> res;

    for (auto& str: strs) {
        string sortedStr = str;                 
        sort(sortedStr.begin(), sortedStr.end()); 
        mp[sortedStr].push_back(str);
    }

    for (auto& [key, group]: mp) {
        res.push_back(move(group)); // Move the group (do not make a copy) into res
    }

    return res;
}

/*
    Problem: Given an array of strings strs, group the anagrams together. You can return the answer in any order.
    Idea: Sort each string alphabetically, use a sorted array of pairs in the form (str, sortedstr), for each str in strs
    do a linear pass on the array and group together the same strings.
    
    Time Complexity: O(nlog(n)): We have O(n * k * log(k)) where k <= 100, thus O(n) to sort each string in strs,
    then sorting strs itself will is O(n log(n) * k) time, because compering the two sorted string will take O(k)
    but because k <= 100 we get time complexity of O(n log(n)), next we compare the string again n times therefor 
    another O(nk), and in total we get the time complexity of O(n log(n)).

    Space complexity: O(n): sortedCopy stores n pairs of strings each of length k, thus O(nk), then res
    stores n strings (as groups) each has length k, thus we get O(nk) as well, and because k <= 100 the total space
    used is O(n).
 */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    vector<pair<string,string>> sortedCopy;
    size_t n = strs.size();
    
    if (n == 0) return res;

    // Populate sortedCopy
    for (auto str:strs) {
        string original = str;                      // Save str before sorting it
        sort(str.begin(), str.end());               // Sort str
        sortedCopy.push_back({ str , original });   // Store the pair (sortedStr, str)    
    }

    sort(sortedCopy.begin(), sortedCopy.end()); // Sort the pairs by first and then by second

    vector<string> group;                   // Stores group of anagrams
    group.push_back(sortedCopy[0].second);  // Add the first str to the group

    for (int i = 1; i < n; i++) {

        // Two consecutive strings are not equal, create new group 
        if (sortedCopy[i].first != sortedCopy[i - 1].first) {
            res.push_back(group);    // Insert the group to the result
            group.clear();           // Clear the group         
        }

        group.push_back(sortedCopy[i].second); // Insert next string to the group
    }

    // Insert the last group into the result array
    res.push_back(group);
    return res;
}

/*
    Problem: Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
    Idea: Use the first row and columns as markers vector for the the remaining rows and columns of the matrix.
    We set each row i in the submatrix M[1,1] to zero if M[i][0] = 0, and we do so for the column if M[0][j] = 0.
    We then come back to the first row and column and handle them.

    Note: Any zero mark on the first row and column during marking will be currect in respect to the final answer.

    Time Complexity: O(nm) Where n is the  number of rows and m is the number of columns in the input matrix.
    Space Complexity: O(1) - We don't use and extra space. 
*/
void setZeroes(vector<vector<int>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    bool firstRowZero = false, firstColZero = false; // Booleans indicators whether the first row and column should be zeros

    // Search for a zero in the first row and column of the matrix
    for (int i = 0; i < cols; i++) if (matrix[0][i] == 0) firstRowZero = true;
    for (int i = 0; i < rows; i++) if (matrix[i][0] == 0) firstColZero = true;

    // Fill the first row and column with marks
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    
    // Fill the matrix according to the marks
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        }
    }

    // Check if the first column should be set to zero
    if (firstColZero) {
        for (int i = 0; i < rows; i++) matrix[i][0] = 0;
    }
    // Check if the first row should be set to zero
    if (firstRowZero) {
        for (int i = 0; i < cols; i++) matrix[0][i] = 0;
    }
}


/*
    Problem: Return all the subarrays of size 3 in nums that sums to 0.

    Idea: For each index i fix nums[i] and check in [i + 1, .. n] subarray for the complement (-nums[i])
    with the 2sum approach. We avoid returning duplicates by advancing left and right pointers
    when a 2Sum match is found, and by advencing the index i when two consecutive numbers are equal.

    Time Complexity: O(n^2) - 2Sum takes O(n) time due to the fact that the array is sorted,
    we computing 2Sum for each index, thus we get O(n^2) as the total time complexity.

    Space Complexity: O(n^2) - We ask how many unique triplets (i, j, k) such that nums[i] + nums[j] + nums[k] = 0
    can exists in the array. Notice that for each triplet (i,j,k) once we fixed two elements (say nums[i] and nums[j])
    the third element is uniquely determined as nums[k] = -(nums[i] + nums[j]), and because we only store 
    unique triplets, this means that every valid triplets is uniquely determined by a pair.
    Therefor the total number of unique triplets is bounded by the number of pairs in thr array.
    (Think about it as a function that takes a pair (i,j) and returns a triplet (i,j,k) such that nums[i] + nums[j] + nums[k] = 0,
    so if you want to determine how many triplets there are you can simply find how many pairs there are)

    From combinatorics the number of pair has an upper bound of O(n^2), thus the maximum number of unique triplets is O(n^2).
*/
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size(), l, r;
    vector<vector<int>> v;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && nums[i - 1] == nums[i]) continue; // Skip all duplicates

        l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[l] + nums[r] + nums[i]; 
            if (sum == 0) {
                v.push_back({nums[l], nums[r], nums[i]});
                while (l < r && nums[l] == nums[l + 1]) l++; // Skip duplicates
                while (r > l && nums[r] == nums[r - 1]) r--; // Skip duplicates
                l++; r--; // Advance left and right pointer
            } else if (sum > 0) { // Advance only the right pointer
                r--;
            } else { // Advance left only
                l++;
            }
        }
    }
    return v;
}