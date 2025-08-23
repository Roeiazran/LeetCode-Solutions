using System.Security.Cryptography.X509Certificates;

public class Program
{
    public static void Main()
    {
        string s = "listen2: 2 n :etsil";

        Console.WriteLine(IsPalindrome(s));
    }

    /*
        Problem: Reverse a given string in place.
        Idea: Two pointers technique.
        Complexity: O(n)
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
        Problem: Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
        Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
        Idea: Store the value on int32 (i.e int) and check for overflow by checking change at each digit reverse.
        Complexity: O(n)
    */
    public static int Reverse(int x)
    {

        int res = 0, oldRes, tx = x;

        while (true)
        {
            oldRes = res;
            res += tx % 10;
            if (res - oldRes != (tx % 10)) return 0;

            tx /= 10;
            if (tx == 0) break;

            oldRes = res;
            res *= 10;
            if (res / 10 != oldRes) return 0;
        }

        // Note: a % b = a - (a/b) * b, there for -321 % 10 = -321 - (321 / 10) * 10 = -321 - 320 = -1
        return res;
    }

    /*
        Problem: Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
        Idea: Use dictionary.
        Complexity: O(n)
    */
    public static int FirstUniqChar(string s)
    {
        Dictionary<char, int> dict = [];

        foreach (char ch in s)
        {
            if (dict.ContainsKey(ch)) dict[ch] += 1;
            else dict[ch] = 1;
        }

        for (int i = 0; i < s.Length; i++)
        {
            char ch = s[i];
            if (dict[ch] == 1) return i;
        }

        return -1;
    }

    /*
        Problem: Given two strings s and t, return true if t is an anagram of s, and false otherwise.
        Idea: Use dictionary.
        Complexity: O(n)
    */
    public static bool IsAnagram(string s, string t)
    {

        Dictionary<char, int> dict = [];

        foreach (char c in s)
        {
            if (dict.ContainsKey(c)) dict[c] += 1;
            else dict[c] = 1;
        }

        foreach (char c in t)
        {
            if (!dict.ContainsKey(c)) return false;
            dict[c] -= 1;
        }

        foreach (int val in dict.Values)
        {
            if (val != 0) return false;
        }

        return true;
    }

    /*
        Problem: A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.
        Idea: Use list to remove unwanted characters and two pointers to check for palindrome.
        Complexity: O(n)
    */
    public static bool IsPalindrome(string s) {

        int n = s.Length, left = 0, right;
        List<char> list = [];

        for (int i = 0; i < n; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z' 
            || s[i] >= 'a' && s[i] <= 'z' 
            || s[i] >= '0' && s[i] <= '9')
            {
                list.Add(char.ToLower(s[i]));
            }
        }
        right = list.Count - 1;

        while (left < right)
        {
            if (list[left] != list[right]) return false;
            left++;
            right--;
        }

        return true;
    }
}