// First Approach: O(N^2) Time Complexity
// In this approach, we check every substring that starts with '('
// and then find the size of the valid parentheses substring starting from that position.
// We keep track of the maximum length found.
class Solution {
public:
    // Function to solve the valid parentheses for a given starting index
    int solve(int ind, string& s) {
        stack<char> st;   // Stack to store opening brackets '('
        int maxi = 0;      // To keep track of the maximum valid parentheses length
        int c = 0;         // To count the number of valid parentheses in the current substring

        // Traverse the substring starting from 'ind'
        for (int i = ind; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(s[i]);   // Push '(' onto the stack
                c++;              // Increment the count of valid parentheses
            } else {
                if (!st.empty()) {
                    st.pop();    // Pop '(' from the stack for a valid pair
                } else {
                    return maxi; // If stack is empty, return the current max length
                }
            }

            // If the stack is empty, it means we have a complete valid substring
            if (st.empty()) {
                maxi = max(maxi, 2 * c); // Update the maximum valid parentheses length
            }
        }
        return maxi;
    }

    // Main function to find the longest valid parentheses
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0; // If string is empty, no valid parentheses exist
        
        int ans = 0; // Variable to store the maximum valid parentheses length

        // Check for valid parentheses substrings starting at each index
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                ans = max(ans, solve(i, s)); // Update the max valid length if a new longer substring is found
            }
        }
        return ans; // Return the final result
    }
};

// Optimal Solution: O(N) Time Complexity
// In this approach, we use two stacks: one for storing the characters 
// and another one for storing the indices of the characters.
// While iterating over the string, we push the opening parentheses and their indices onto the stacks.
// When we encounter a closing parenthesis, we pop the stack if it matches a previous opening parenthesis.
// Later, we calculate the difference between indices in the stack to determine the longest valid parentheses substring.
class Solution {
public:
    // Main function to find the longest valid parentheses
    int longestValidParentheses(string s) {
        stack<char> st;      // Stack to store the characters ('(' or ')')
        stack<int> st1;       // Stack to store the indices of the characters
        
        // Traverse through the string and process each character
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push('(');   // Push '(' to the character stack
                st1.push(i + 1); // Push index to the index stack (i+1 to avoid 0 index issue)
            } else if (s[i] == ')') {
                // If a matching '(' exists in the stack, pop them
                if (!st.empty() && st.top() == '(') {
                    st.pop();
                    st1.pop();
                } else {
                    // If no matching '(' found, push ')' and its index to the stacks
                    st.push(')');
                    st1.push(i + 1);
                }
            }
        }

        // Initialize current value to the top of the index stack
        int curr = 0;
        if (!st1.empty()) curr = st1.top();
        
        // Maximum length of valid parentheses
        int maxi = s.size() - curr;

        // Calculate the difference between the current index and indices in the stack to find the largest valid substring
        while (!st1.empty()) {
            maxi = max(maxi, curr - st1.top() - 1);  // Update the maximum length
            curr = st1.top();  // Set current index to the top of the stack
            st1.pop();          // Pop the top element from the stack
        }

        // Final update to maxi after exiting the loop
        maxi = max(maxi, curr - 1);

        // Return 0 if the maximum length is less than 2 (meaning no valid parentheses)
        if (maxi < 2) return 0;

        return maxi; // Return the final result
    }
};
