public class Program
{
    public static void Main()
    {
    }

    /*
        Problem desc: Given a sorted array nums, remove the duplicates in-place such that
        each element appears only once and return the new length.
        Do not allocate extra space; modify the array in-place with O(1) extra memory.

        Idea: Loop through nums array and skip duplicates by checking nums[r] and nums[r - 1],
        only insert into nums[l] if nums[r] != nums[r - 1].

        Time Complexity: O(n) - We iterate through the array with one time with r pointer.
        Space Complexity: O(1).
    */
    public static int RemoveDuplicates(int[] nums)
    {
        int n = nums.Length;
        if (n == 0) return 0;

        int l = 1;

        for (int r = 1; r < n; r++)
        {
            if (nums[r] != nums[r - 1]) {
                nums[l] = nums[r];
                l++;
            }
        }
        return l;
    }

    /*
        Problem desc: You are given an integer array prices where prices[i] is the price of a stock on the ith day.
        You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times),
        but you must sell before you buy again. Return the maximum profit you can achieve.

        Idea: Instead of trying to find valleys and peaks we sum up all the positive 
        differences between consecutive days.

        Time Complexity: O(n) - One loop on the prices array.
        Space Complexity: O(1).
    */
    public static int MaxProfit(int[] prices)
    {
        int n = prices.Length, maxProfit = 0;

        for (int i = 0; i < n - 1; i++)
        {
            if (prices[i + 1] - prices[i] > 0) maxProfit += prices[i + 1] - prices[i];
        }
        return maxProfit;
    }

    /*
        Problem: Given an array, rotate the array to the right by k steps, where k is non-negative.
        You must do it in-place with O(1) extra space.

        Idea: Reverse the array then reverse the subarray [1,..,k] and the subarray [k + 1,..,n] individually.

        Time Complexity: O(n)
        Space complexity: O(1)
    */
    public static void Rotate(int[] nums, int k)
    {
        int n = nums.Length;

        k %= n;

        Array.Reverse(nums);
        Array.Reverse(nums, 0, k);
        Array.Reverse(nums, k, n - k);
    }


    /*
        Problem desc: Given an integer array nums, return true if any value appears at least twice in the array,
        and return false if every element is distinct.

        Idea: Use HashSet to keep track of numbers we've already seen.
        Time Complexity: O(n)
        Space Complexity: O(n)
    */
    public static bool ContainsDuplicate(int[] nums)
    {
        HashSet<int> dict = [];
        int n = nums.Length;

        for (int i = 0; i < n; i++)
        {
            int number = nums[i];
            if (dict.Contains(number)) return true;

            dict.Add(number);
        }
        return false;
    }

    /*
        Problem: Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
        You must implement a solution with a linear runtime complexity and use only constant extra space.

        Idea: Xor operation properties are: commutativity, associativity, a^a = 0, a^0 = a.
        Time Complexity O(n)
        Space Complexity: O(1)
    */
    public static int SingleNumber(int[] nums)
    {
        int n = nums.Length, res = 0;

        for (int i = 0; i < n; i++) res ^= nums[i];
        return res;
    }

    /*
        Problem: Given two integer arrays nums1 and nums2, return an array of their intersection.
        Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

        Idea: Count frequencies using a Dictionary, and compare that frequencies with the other array.

        Time Complexity: O(n + m)
        Space Complexity: O(min(n,m))
    */
    public static int[] Intersect(int[] nums1, int[] nums2) {

        // We want to create a dictionary with the smallest size
        if (nums1.Length > nums2.Length) Intersect(nums2, nums1);

        Dictionary<int, int> freq = [];
        List<int> res = [];

        // Prepare the dictionary from nums1
        foreach (int num in nums1) {
            if (!freq.ContainsKey(num)) freq[num] = 0;
            freq[num]++;
        }

        foreach (int num in nums2) {

            // Check if the number appears in num1 with frequency larger then 0
            if (freq.ContainsKey(num) && freq[num] > 0) {
                res.Add(num);
                freq[num]--;
            }
        }

        return [.. res]; // Return the List<int> result as an int[].
    }

    /*
        Problem: You are given a large integer represented as an integer array digits,
        where each digits[i] is the i'th digit of the integer. The digits are ordered
        from most significant to least significant in left-to-right order.
        Increment the large integer by one and return the resulting array of digits.

        Idea: Walk through the digits array from right to left and compute the digits[i] and the carry.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static int[] PlusOne(int[] digits) {

        int n = digits.Length;

        int carry = 1;  // Start with carry = 1 to perform the +1 operation
        int sum;        // Used to sum the value of digits[i]

        for (int i = n - 1; i >= 0; i--)
        {
            sum = digits[i] + carry;
            digits[i] = sum % 10; 
            carry = sum / 10;

            if (carry == 0) break; // No need to continue.
        }

        if (carry == 1)  return [1, .. digits];
        return digits;
    }

    /*
        Problem: Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
        Note that you must do this in-place without making a copy of the array.

        Idea: Walk through nums and insert to the start each non-zero item, then fill the rest with zeros.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static void MoveZeroes(int[] nums) {

        int n = nums.Length, left = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] != 0) 
            {
                nums[left] = nums[right];
                left++;
            }
        }
        while (left < n) {
            nums[left] = 0;
            left++;
        }
    }

    /*
        Problem: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target. 
        You may assume that each input would have exactly one solution, and you may not use the same element twice.
        Idea: Use Dictionary <item, index>, iterate through nums looking for target - item in the dictionary.

        Time Complexity: O(n)
        Space Complexity: O(n)
    */
    public static int[] TwoSum(int[] nums, int target) {
        Dictionary<int, int> map = [];
        int n = nums.Length;

        for (int i = 0; i < n; i++)
        {
            int complement = target - nums[i];
            if (map.TryGetValue(complement, out int value)) return [value, i];
            else map.TryAdd(nums[i], i);
        }

        return [];
    }

    /*
        Problem: Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the rules.
        Complexity: O(n^2)
    */
    public static bool IsValidSudoku(char[][] board) {
        HashSet<char> set = [];
        int n = 9;

        // Check rows
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.') continue;               // Skip '.'
                if (set.Contains(board[i][j])) return false;    // Already ween this number
                set.Add(board[i][j]);                           // Number wasn't seen so far
            }

            set.Clear(); // Clear for the next row
        }

        // Check columns
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[j][i] == '.') continue;
                if (set.Contains(board[j][i])) return false;
                set.Add(board[j][i]);
            }
            set.Clear();
        }

        // Check squares
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int ji = j + i / 3 * 3;
                    int ki = k + i % 3 * 3;
                    char b = board[ji][ki];

                    if (b == '.') continue;

                    if (set.Contains(b)) return false;
                    set.Add(b);
                }
            }
            set.Clear();
        }

        return true;
    }
}