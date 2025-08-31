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
    Complexity: O(n) Where n is the number of all characters in the input
*/
string longestCommonPrefix(vector<string>& strs) {

    int n = strs.size();
    size_t minLength;
    string prefix = "";

    char ch; // temporary variable used to stores the character at index i
    if (n == 0) return "";
    minLength = strs.at(0).size();
    // find the minimum length of any string in strs
    for (auto& str: strs) minLength = min(str.size(), minLength);

    for (int i = 0; i < minLength; i++)
    {
         ch = strs[0][i];
        // check for common prefix on all string in strs
        for (int j = 1; j < n; j++) if (strs[j][i] != ch) return prefix;

        // append the common character
        prefix.push_back(ch);
    }

    return prefix;
}


/*
    Problem: Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
    Idea: Check each possibility like sliding window.
    Complexity: O(n*m)
*/
int strStr(string haystack, string needle) {
    int np = 0, hp = 0, hsize = haystack.size(), nsize = needle.size();

    while (hp < hsize)
    {
        // advance both pointers when there content match
        while (hp < hsize && np < nsize && haystack[hp] == needle[np])
        {
            hp++;
            np++;
        }

        // check if needle pointer is located at the end of the string
        if (np == nsize) return hp - nsize;

        // initialize values for the next iteration
        hp = hp - np + 1;
        np = 0;
    }

    // default case of not found
    return -1;
}

/*
    Problem: Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
    1. Whitespace: Ignore any leading whitespace (" ").
    2. Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
    3. Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
    4. Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
    Cases: "42" -> 42, " -042" -> -42, "1337c0d3" -> 1337, "0-1" -> 0 (default to 0 since no digit after 0).
*/
int myAtoi(string s) {
    bool is_positive = true, seen_zero = false;
    long res = 0;
    size_t i = 0, n = s.length();

    if (n == 0) return 0;
    
    // skip all spaces
    while (i < n && s[i] == ' ') i++;

    //skip all zeros and note if you saw zero
    while (i < n && s[i] == '0') 
    {
        i++;
        seen_zero = true;
    } 

    // in case of all zeros return 0
    if (i == n) return 0;

    // check the sign (if exists)
    if (s[i] == '-') 
    {
        if (seen_zero) return 0; // if saw zero next must be digit
        i++;
        is_positive = false;
        s = s.substr(i); // skip the sign
    } else if (s[i] == '+') 
    {
        if (seen_zero) return 0; // same
        i++;
        s = s.substr(i);
    } else 
    {
        s = s.substr(i);
    }
    
    i = 0, n = s.size();
    for (; i < n; i++)
    {
        // in case of a non-digit stop and return the number constructed
        if (s[i] > '9' || s[i] < '0') return is_positive? res : - res;
        
        // construct the number from the string
        res *= 10;
        res = res + s[i] - '0';

        // there is must be overflowing number
        if (res > INT_MAX) return is_positive? INT_MAX : INT_MIN;        
    }
    return is_positive? res : - res;
}

