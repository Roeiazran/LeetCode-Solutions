public class Program
{
    /*
        Problem: Reverse a given string in place. 
        Idea: Walk through the array from both sides with two pointers, and replace the characters.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static void ReverseString(char[] s)
    {
        int n = s.Length;
        int left = 0, right = n - 1;

        while (left < right)
        {
            (s[right], s[left]) = (s[left], s[right]);
            right--;
            left++;
        }
    }

    /*
        Problem: Given a signed 32-bit integer x, return x with its digits reversed.
        If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
        Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

        Idea: Instead of relying on long to indicate overflow, before each operation on the result 
        we store it in a temporary variable and compare it with reverse calculation of the result after the operation.
        
        Note: This works for negative numbers as well, because of the modulo definition:
        a % b = a - (a/b) * b, there for -321 % 10 = -321 - (321 / 10) * 10 = -321 - 320 = -1

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static int Reverse(int x)
    {
        int res = 0, oldRes, tx = x;

        while (true)
        {
            // Save the result before adding last digit
            oldRes = res;

            // Add the last digit to result
            res += tx % 10; 

            // Compare the reversed calculation to the result before the operation
            if (res - oldRes != (tx % 10)) return 0;

            // Drop the last digit from tx
            tx /= 10;

            // If tx equal 0, no digits left in tx.
            if (tx == 0) break;

            // Save the result before multiplying it
            oldRes = res;

            // Multiply the result by 10
            res *= 10;

            // Compare the reversed calculation to the result before the operation
            if (res / 10 != oldRes) return 0;
        }
        return res;
    }

    /*
        Problem: Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
        Idea: Since by the problem definition the input string contains only lower case english letters, instead of using 
        dictionary we use a frequency array of size 26. 
        Time Complexity: O(n)
        Space Complexity: O(1) - Using int array of constant size.
    */
    public static int FirstUniqChar(string s)
    {
        int[] freq = new int[26];

        // Count frequencies
        foreach (char ch in s)  freq[ch - 'a']++;

        // Find first index with count == 1
        for (int i = 0; i < s.Length; i++) if (freq[s[i] - 'a'] == 1) return i;

        // If reached here, no unique character in s
        return -1;
    }

    /*
        Problem: Given two strings s and t, return true if t is an anagram of s, and false otherwise.
        Idea: I choose to use dictionary instead of and array, to provide a solution for Unicode characters instead
        of just alphanumeric ones. We count and compare the frequencies of the characters in both strings.

        Time Complexity: O(n + m)
        Space Complexity: O(n) - not O(1) as with constant size array
    */
    public static bool IsAnagram(string s, string t)
    {
        Dictionary<char, int> dict = [];

        // Count the characters frequencies in s
        foreach (char c in s)
        {
            if (dict.ContainsKey(c)) dict[c] += 1;
            else dict[c] = 1;
        }
        
        foreach (char c in t)
        {
            // If the dictionary doesn't contains the char, s is not anagram of t
            if (!dict.ContainsKey(c)) return false;

            // Decrement the char frequency by 1 if it exists in t
            dict[c] -= 1;
        }

        // Make sure all characters in s appeared in t with same frequency
        foreach (int val in dict.Values)  if (val != 0) return false;

        return true;
    }

    /*
        Problem: A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, 
        it reads the same forward and backward. Alphanumeric characters include letters and numbers.

        Idea: Instead of using a list to filter the string from unwanted characters, we'll use the IsLetterOrDigit method, and with two pointers
        we'll walk trough the string from both sided skipping the unwanted characters.

        Time Complexity: O(n)
        Space Complexity: O(1)
    */
    public static bool IsPalindrome(string s) {

        int n = s.Length, left = 0, right = n - 1;

        while (left < right) {
            
            // Skip non alphanumeric characters on the left and on right
            while (left < right && !char.IsLetterOrDigit(s[right])) right--;
            while (left < right && !char.IsLetterOrDigit(s[left])) left++;

            // Compare both characters on the left and right
            if (char.ToLower(s[left]) != char.ToLower(s[right])) return false;

            left++;
            right--;
        }
        return true;
    }
}