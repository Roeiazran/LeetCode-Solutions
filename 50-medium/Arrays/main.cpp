#include <vector>
#include <unordered_set>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

/*
    Problem: Given an array of strings strs, group the anagrams together. You can return the answer in any order.
    Idea: Use unsorted map<string, vector<string>>. Sort each string in strs and use it as a key of the map, where the value is a vector 
    that stores all the anagrams of the key. Finally iterate the map and group the string by the key.
    Complexity: O(n). We have O (n * k log k) where k <= 100, thus O(n) to store each string in strs.
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
    Idea: Sort each string alphabetically, use a sorted array of pairs in the form (str, sortedstr) for each str in strs
    to do a linear pass on the array and group together the same strings.
    Complexity: O(n log n), We have O (n * k log k) where k <= 100, thus O(n) to store each string in strs, then sorting strs in O(n log n).
 */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    vector<pair<string,string>> sortedCopy;
    size_t n = strs.size();
    
    if (n == 0) return res;

    // Populate sortedCopy with pairs
    for (auto str:strs) {
        string temp = str;                      // Save str before sorting it
        sort(str.begin(), str.end());           // sort str
        sortedCopy.push_back({ str , temp});    // Store the pair (str, sortedStr)    
    }

    sort(sortedCopy.begin(), sortedCopy.end()); // Sort the pairs by first and then by second

    vector<string> temp; // Used to store each groupe of strings
    temp.push_back(sortedCopy[0].second); // Add to first group the first item in the sorted copy

    for (int i = 1; i < n; i++) {

        // Check whether to start a new group
        if (sortedCopy[i].first != sortedCopy[i - 1].first) {
            res.push_back(temp);    // Insert the group to the result
            temp.clear();           // Clear the group vector         
        }

        temp.push_back(sortedCopy[i].second); // Insert new string to the group
    }
    res.push_back(temp); // Remember to insert last group into the result
    return res;
}


/*
    Problem: Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
    Idea: Use the first row and columns as markers vector for the rows and columns respectively.
    For each row and column in the submatrix M[1,1] check M[i][0] and M[0][j] respectively.
    Also remember to check if the first row or column should be set to zero before making any changes on them.
    Note that any zero mark on the first row and column will be currect for the final answer in any case.
    Complexity: O(nm) where n - rows number, m - column number.
*/
void setZeroes(vector<vector<int>>& matrix) {
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    bool firstRowZero = false, firstColZero = false; // Booleans indicates whether the first row and column should be zeros

    for (int i = 0; i < cols; i++) if (matrix[0][i] == 0) firstRowZero = true;
    for (int i = 0; i < rows; i++) if (matrix[i][0] == 0) firstColZero = true;

    // Fill first row and columns with marks
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

    // Check if the first row or column should be set to zero
    if (firstColZero) {
        for (int i = 0; i < rows; i++) matrix[i][0] = 0;
    }
    if (firstRowZero) {
        for (int i = 0; i < cols; i++) matrix[0][i] = 0;
    }
}


/*
    Problem: Return all the subarrays of size 3 in nums that sums to 0.
    Idea: For each index i fix nums[i] and check for the complement (-nums[i]) with left and right pointers.
    If found a triplet (nums[l], nums[r], nums[i]) add it to the result and skip duplicates by advancing left and right pointers.
    Also skip if nums[i] == nums[i + 1].
    Complexity: O(n^2)
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
                l++; r--; // Advance left and right for the next pair
            } else if (sum > 0) { // Advance right only
                r--;
            } else { // Advance left only
                l++;
            }
        }
    }

    return v;
}

int main(int argc, char const *argv[])
{
    vector<string> v;

    v.push_back("eat");
    v.push_back("aet");
    v.push_back("tan");
    v.push_back("tea");
    v.push_back("nat");
    v.push_back("bat");

    vector<vector<string>> res = groupAnagrams(v);

    for (auto& s: res) {
        for (auto& b: s) {
            cout << b << "- - ";
        }
        cout << endl;
    }
    return 0;
}
