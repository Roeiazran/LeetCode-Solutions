#include <vector>
#include <unordered_set>
#include <iostream>
#include <set>
using namespace std;


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
    vector<vector<int>> v;

    v.push_back({1,2,3,4});
    v.push_back({5,0,7,8});
    v.push_back({0,10,11,12});
    v.push_back({13,14,15,0});
    setZeroes(v);

    for (auto& row: v) {
        for (auto& col : row) {
            cout << col << " ";
        }
    }

    return 0;
}
