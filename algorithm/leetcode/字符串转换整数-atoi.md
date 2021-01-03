---
sort: 8
---

```
/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

// @lc code=start
class Solution {
public:
    int myAtoi(string str) {
        int idx = 0;
        
        long long val = 0;
        
        char flag = 0;
        int start = 0;
        for (; idx < str.length(); ++idx) {
            if (str[idx] == ' ') {
                if (start) {
                    return 0;
                }
                continue;
            }
            if (str[idx] == '+') {
                if (start == 0) {
                    start = 1;
                    continue;
                }
                
                return 0;     
            }
            if (str[idx] == '-') {
                if (start == 0) {
                    start = 1;
                    flag = 1;
                    continue;
                }
                
                return 0;
            }
            
            if (str[idx] >= '0' && str[idx] <= '9') {
                break;
            }
            
            return 0;
        }
        
         for (; idx < str.length(); ++idx) {
             if (str[idx] >= '0' && str[idx] <= '9') {
                val = val * 10 + str[idx] - '0';
                if (val > INT_MAX) {
                     if (flag)
                        return INT_MIN;
                     else 
                        return INT_MAX;
                 }
                continue;
             }
             
             break;
         }
        
         if (flag) {
             val = -val;
         }
        
        
         return val;
    }
};
// @lc code=end


```
