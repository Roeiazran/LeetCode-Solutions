#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

int myAtoi(string s);
int strStr(string haystack, string needle);
string longestCommonPrefix(vector<string>& strs);

int main(int argc, char const *argv[])
{   
    vector<string> strs;
    strs.push_back("Banana");
    strs.push_back("Apple");
    strs.push_back("Mango");

    longestCommonPrefix(strs);
    return 0;
}

/*
    Problem: Write a function to find the longest common prefix string amongst an array of strings.

    Idea: Instead of scanning each string row by row, we scan each string column by column.
    In each column indexed i we check str[i] for each str in strs, 
    if one has a mismatch character we stop the search.

    Time Complexity: O(n) Where n is the number of all characters in the input.
    Space Complexity: O(m) Where m is the the number of characters in the longest string in strs.
*/
string longestCommonPrefix(vector<string>& strs) {

    int n = strs.size();
    size_t minLength;   // Store the minimum length of any string in strs
    string prefix = ""; // Store the longest common string
    char ch;            // Store the character at each index

    // Edge case: empty input
    if (n == 0) return "";


    // Find the minimum length of any string in strs
    minLength = strs.at(0).size();
    for (auto& str: strs) minLength = min(str.size(), minLength);

    // Find common prefix string among all the strings in strs
    for (int i = 0; i < minLength; i++)
    {
        ch = strs[0][i]; // Character to compare in this column
        
        // Try finding this character in each string in strs
        for (int j = 1; j < n; j++) if (strs[j][i] != ch) return prefix;

        // All string share ch at index i, append it to the result
        prefix.push_back(ch);
    }

    return prefix;
}


/*
    Problem: Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
    
    Idea: Walk through haystack and search the substring needle in each index.

    Time Complexity: O(nm)
    Space Complexity: O(1)
*/
int strStr(string haystack, string needle) {
    int np = 0, hp = 0; // Indices into haystack and needle
    int hsize = haystack.size(), nsize = needle.size();

    while (hp < hsize)
    {
        // Advance both pointers as long as the characters match
        while (hp < hsize && np < nsize && haystack[hp] == needle[np])
        {
            hp++;
            np++;
        }

        // If needle pointer is located at the end, match the whole needle
        if (np == nsize) return hp - nsize;
        
        hp = hp - np + 1;   // Reset haystack pointer to the next character
        np = 0;             // Reset needle pointer to the start
    }

    // No match found
    return -1;
}

/*
    Problem: Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
    1. Whitespace: Ignore any leading whitespace (" ").
    2. Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
    3. Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
    4. Rounding: If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
    Cases: "42" -> 42, " -042" -> -42, "1337c0d3" -> 1337, "0-1" -> 0 (default to 0 since no digit after 0).
*/
int myAtoi(string s) {
    bool isPositive = true;
    int res = 0;
    size_t i = 0, n = s.length();

    // Skip all white spaces
    while (i < n && s[i] == ' ') i++;

    // Check the sign
    if (i < n && (s[i] == '-' || s[i] == '+')){
        if (s[i] == '-') isPositive = false;
        i++;
    }
    
    while (i < n && isdigit(s[i])) {
        int digit = s[i] - '0';

        // Prevent overflow before multiplying
        if (res > (INT_MAX - digit) / 10) return isPositive? INT_MAX : INT_MIN;

        // Construct the number
        res = res * 10 + (s[i] - '0');
        i++;
    }
    return isPositive? res : -res;
}

