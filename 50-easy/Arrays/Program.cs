public class Program
{
    public static void Main()
    {
    }

    /*
        Problem: Given an array nums sorted in non-decreasing order, bring to front al the unique values in nums to appear only once
        Idea: Increment right until nums[right] != nums[right + 1] and store nums[right] into nums[left]
        Complexity: O(n)
    */
    public static int RemoveDuplicates(int[] nums)
    {

        int left = 0; int n = nums.Length;

        for (int right = 0; right < n; right++)
        {
            while (right < n - 1 && nums[right] == nums[right + 1]) right++;
            nums[left] = nums[right];
            left++;
        }

        return left;
    }

    /*
        Problem: You have an array prices[] where prices[i] is the stock price on day i.
        You can buy and sell multiple times, but you cannot hold more than one stock at a time.
        Goal: maximize total profit.
        Insight: Any sequence where the price goes up from one day to the next is an opportunity to earn.
        You don’t need to pick the absolute minima or maxima.
        Idea: Loop through the prices from day 1 to day N - 1 and compare today's price with yesterday, if it's a profit add it 
        to the total profit otherwise do nothing. “Every time the price goes up, capture that increase.”
        Complexity: O(n).
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
        Problem: Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
        Idea: Reverse the array then reverse the [1,..,k] and [k + 1,..,n] individually.
        Complexity: O(n)
    */
    public static void Rotate(int[] nums, int k)
    {
        int n = nums.Length;

        while (k > n) k -= n;

        Array.Reverse(nums);
        Array.Reverse(nums, 0, k);
        Array.Reverse(nums, k, n - k);
    }

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
        Complexity O(n)
    */
    public static int SingalNumber(int[] nums)
    {
        int n = nums.Length, res = 0;

        for (int i = 0; i < n; i++) res ^= nums[i];
        return res;
    }

    /*
        Problem: Given two integer arrays nums1 and nums2, return an array of their intersection.
        Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.
    */
    public static int[] Intersect(int[] nums1, int[] nums2) {

        int p1 = 0, p2 = 0, n1 = nums1.Length, n2 = nums2.Length;
        List<int> res = [];
        Array.Sort(nums1);
        Array.Sort(nums2);

        while (p1 < n1 && p2 < n2)
        {
            if (nums1[p1] < nums2[p2]) p1++;
            else if (nums1[p1] > nums2[p2]) p2++;
            else
            {
                res.Add(nums1[p1]);
                p1++;
                p2++;
            }
        }

        return [.. res];
    }

    /*
        Problem: You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order.
        Increment the large integer by one and return the resulting array of digits.
        Complexity: O(n)
    */
    public static int[] PlusOne(int[] digits) {

        int n = digits.Length, carry = 0;
        int add;

        for (int i = n - 1; i >= 0; i--)
        {
            add = digits[i] + carry;

            if (i == n - 1)  add++;
     
            if (add == 10)
            {
                carry = 1;
                digits[i] = 0;
            }
            else
            {
                digits[i]++;
                carry = 0;
                break;
            }
        }

        if (carry == 1)  return [1, .. digits];
        return digits;
    }

    /*
        Problem: Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
        Note that you must do this in-place without making a copy of the array.
        Idea: Two pointer approach.
        Complexity: O(n)
    */
    public static void MoveZeroes(int[] nums) {

        int n = nums.Length, right, left = 0, temp;

        while (left < n && nums[left] != 0) left++;

        right = left + 1;
        while (right < n && nums[right] == 0) right++;

        while (right < n && left < n)
        {
            if (nums[left] != 0) left++;
            else if (nums[right] == 0) right++;
            else 
            {
                temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                left++;
                right++;
            }
        }
    }

    /*
        Problem: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target. 
        You may assume that each input would have exactly one solution, and you may not use the same element twice.
        Idea: Use Dictionary <item, index> looking for target - item in the dictionary.
        Complexity: O(n)
    */
    public static int[] TwoSum(int[] nums, int target) {
        Dictionary<int, int> map = [];
        int n = nums.Length;

        for (int i = 0; i < n; i++)
        {
            int key = target - nums[i];
            if (map.TryGetValue(key, out int value)) return [value, i];
            else map.TryAdd(nums[i], i);
        }

        return [];
    }
    /*
        Problem: Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the rules.
        Complexity: O(n^2)
    */
    public static bool IsValidSudoku(char[][] board) {
        HashSet<int> set = [];
        int n = 9;

        // check rows
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.') continue;

                if (set.Contains(board[i][j])) return false;
                set.Add(board[i][j]);
            }

            set.Clear();
        }

        // check columns
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

        // check squares
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int ji = j + i / 3 * 3;
                    int ki = k + i % 3 * 3;
                    int b = board[ji][ki];

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