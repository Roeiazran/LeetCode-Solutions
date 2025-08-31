#include <vector>
#include <unordered_set>
#include <iostream>
#include <set>
using namespace std;

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
    vector<int> v = {-1,0,1,2,-1,-4};
    vector<vector<int>> a = threeSum(v);
    for (auto& v1 : a){
        for (auto& v2 : v1)
        {
            cout << v2 << " ";
        }
        cout << endl;
    }
    return 0;
}
