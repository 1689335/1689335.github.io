---
sort: 6
---

```
/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */

// @lc code=start
class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> ret(numRows, string(""));
        int j = 0;
        
        
        while (j < s.length()) {
            for (int i = 0; i < numRows && j < s.length(); ++i) {
                //ret[i].append(string(1, s[j++]));
                ret[i].push_back(s[j++]);
                //cout << "11:" << i << " " << j << " " << ret[i] << endl;
            }

            for (int i = numRows - 2; i > 0 && j < s.length(); i--) {
                ret[i].push_back(s[j++]);
                //cout << "22:" << i << " " << j << " " << ret[i] << endl;
            }
        }
        
        string r;
        for (int i = 0; i < numRows; ++i) {
            r += ret[i];
        }
        
        return r;
    }
};
// @lc code=end


```
