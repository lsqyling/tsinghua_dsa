#include "../utilities.hpp"

namespace leetcode_006 {
// Z 字形变换
class Solution {
public:
    static std::string convert(std::string s, int numRows) {
        if (numRows < 2) {
            return s;
        }
        std::vector<std::string> rows(numRows);
        int i = 0, flag = -1;
        for (auto c : s) {
            rows[i] += c;
            if (i == 0 || i == numRows - 1) {
                flag = -flag;
            }
            i += flag;
        }

        std::string res;
        for (auto &str : rows) {
            res += str;
        }
        return res;
    }
};
}

namespace leetcode_007 {
// 7. 整数反转
class Solution {
public:
    static int reverse(int x) {
        if (x == 0) {
            return 0;
        }
        std::string sx = std::to_string(x);
        if (sx[0] == '+') {
            sx.erase(sx.begin());
        }
        if (sx[0] != '-') {
            std::reverse(sx.begin(), sx.end());
            int n0 = 10 - static_cast<int>(sx.size());
            if (n0 > 0) {
                sx.insert(sx.begin(), n0, '0');
            }
            if (sx > std::string("2147483647")) {
                return 0;
            }
            else {
                return std::stoi(sx);
            }
        }
        else {
            std::string sx_(sx.begin() + 1, sx.end());
            std::reverse(sx_.begin(), sx_.end());
            int n0 = 10 - static_cast<int>(sx_.size());
            if (n0 > 0) {
                sx_.insert(sx_.begin(), n0, '0');
            }
            if (sx_ > std::string("2147483648")) {
                return 0;
            }
            else {
                sx_.insert(sx_.begin(), '-');
                return std::stoi(sx_);
            }
        }
    }
};
void test()
{
    int x = std::numeric_limits<int>::min();
    int res = Solution::reverse(x);
    std::cout << res << std::endl;
}
}
namespace leetcode_008 {
// 8. 字符串转换整数 (atoi)
class Solution {
public:
    static int myAtoi(const std::string &s) {
        int res = 0;
        int sign = 1;
        int i = 0;
//        1. 空格情况
        while (s[i] == ' ') {
            ++i;
        }
//        2. 正负号情况
        if (s[i] == '-') {
            sign = -1;
        }
        if (s[i] == '+' || s[i] == '-') {
            ++i;
        }
//        3. 处理数字情况
        while (i < s.size() && std::isdigit(s[i])) {
            int r = s[i] - '0';
            if (res > IntMax / 10 || (res == IntMax/10 && r > 7)) {
                return sign > 0 ? IntMax : IntMin;
            }
            res = res * 10 + r;
            ++i;
        }
        return res * sign;
    }
    /*
     * 有限状态机方式
     */
    static int myAtoi_v(const std::string &s) {
        std::string state{"start"};
        int res = 0;
        int sign = 1;
        int r = 0;
        for (char c : s) {
            state = table[state][get_column(c)];
            if (state == "signed") {
                sign = c == '+' ? 1 : -1;
            }
            else if (state == "number") {
                r = c - '0';
                if (res > IntMax/10 || (res == IntMax/10 && r > 7)) {
                    return sign > 0 ? IntMax : IntMin;
                }
                res = res * 10 + r;
            }
        }
        return res * sign;
    }

    inline static std::map<std::string, std::vector<std::string>> table {
            {"start", {"start", "signed", "number", "end"}},
            {"signed", {"end", "end", "number", "end"}},
            {"number", {"end", "end", "number", "end"}},
            {"end", {"end", "end", "end", "end"}},
    };
    static constexpr int get_column(char c)
    {
        if (std::isspace(c)) {
            return 0;
        }
        if (c == '+' || c== '-') {
            return 1;
        }
        if (std::isdigit(c)) {
            return 2;
        }
        return 3;
    }

    static constexpr int IntMax = std::numeric_limits<int>::max();
    static constexpr int IntMin = std::numeric_limits<int>::min();
};
void test()
{
    std::cout << Solution::myAtoi("           ") << std::endl;
    std::cout << Solution::myAtoi_v("      -042") << std::endl;
}
}
namespace leetcode_010 {
// 10. 正则表达式匹配
class Solution
{
public:
    static bool isMatch(std::string s, std::string p)
    {
        int m = static_cast<int>(s.size());
        int n = static_cast<int>(p.size());
        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j-1] == '.') {
                return true;
            }
            return s[i-1] == p[j-1];
        };
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == '*') {
                    dp[i][j] |= dp[i][j-2];
                    if (matches(i, j - 1)) {
                        dp[i][j] |= dp[i-1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        dp[i][j] |= dp[i-1][j-1];
                    }
                }
            }
        }
        return dp[m][n];
    }
};
}

namespace leetcode_012 {
// 12. 整数转罗马数字
class Solution {
public:
    static std::string intToRoman(int num) {
        std::string roman;
        for (const auto &[value, symbol] : value_symbols) {
            while (num >= value) {
                num -= value;
                roman += symbol;
            }
            if (num == 0) {
                break;
            }
        }
        return roman;
    }
private:
    inline static const std::pair<int, std::string> value_symbols[] {
            {1000, "M"},
            {900, "CM"},
            {500, "D"},
            {400, "CD"},
            {100, "C"},
            {90, "XC"},
            {50, "L"},
            {40, "XL"},
            {10, "X"},
            {9, "IX"},
            {5, "V"},
            {4, "IV"},
            {1, "I"},
    };
};
}

namespace leetcode_013 {
// 13. 罗马数字转整数
class Solution {
public:
    static int romanToInt(std::string s) {
        int n = static_cast<int>(s.size());
        int num = 0;
        for (int i = 0; i < n; ++i) {
            int value = symbol_values[s[i]];
            if (i < n - 1 && value < symbol_values[s[i+1]] ) {
                num -= value;
            }
            else {
                num += value;
            }
        }
        return num;
    }

private:
    inline static std::unordered_map<char, int> symbol_values {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
    };
};
}

namespace leetcode_014 {
// 14. 最长公共前缀
class Solution {
public:
    [[maybe_unused]] static std::string longestCommonPrefix(std::vector<std::string>& strs) {
        int n = static_cast<int>(strs.size());
        std::string ans = strs[0];
        for (int i = 1; i < n; ++i) {
            ans = longestCommonPrefix(ans, strs[i]);
            if (ans.empty()) {
                break;
            }
        }
        return ans;
    }
    static std::string longestCommonPrefix(std::string_view s1, std::string_view s2) {
        int n = static_cast<int>(std::min(s1.size(), s2.size()));
        int index = 0;
        while (index < n && s1[index] == s2[index]) {
            ++index;
        }
        return std::string(s1.substr(0, index));
    }
};
}

namespace leetcode_015 {
// 15. 三数之和
class Solution {
public:
    static std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<std::vector<int>> res;
        if (n < 3) {
            return res;
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return res;
            }
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j = i + 1, k = n - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    while (j < k && nums[j] == nums[j+1]) {
                        ++j;
                    }
                    while (j < k && nums[k] == nums[k-1]) {
                        --k;
                    }
                    ++j;
                    --k;
                }
                else if (nums[i] + nums[j] + nums[k] > 0) {
                    --k;
                }
                else {
                    ++j;
                }
            }
        }
        return res;
    }
};
}
namespace leetcode_016 {
// 16. 最接近的三数之和
class Solution {
public:
    static int threeSumClosest(std::vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());
        int ans = nums[0] + nums[1] + nums[2];
        std::sort(nums.begin(), nums.end());
        for (int i = 0;i < n; ++i) {
            int j = i + 1, k = n - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (std::abs(target - sum) < std::abs(target - ans)) {
                    ans = sum;
                }
                if (sum > target) {
                    --k;
                }
                else if (sum < target) {
                    ++j;
                }
                else {
                    return ans;
                }
            }
        }
        return ans;
    }
};
}

namespace leetcode_017 {
// 17. 电话号码的字母组合
class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> combinations;
        if (digits.empty()) {
            return combinations;
        }
        std::string combination;
        backtrace(0, digits, combination, combinations);
        return combinations;
    }
    void backtrace(int index, std::string_view digits, std::string &combination, std::vector<std::string> &combinations)
    {
        if (index == digits.size()) {
            combinations.push_back(combination);
            return ;
        }
        char digit = digits[index];
        const std::string &letters = phone_map.at(digit);
        for (char letter : letters) {
            combination.push_back(letter);
            backtrace(index + 1, digits, combination, combinations);
            combination.pop_back();
        }
    }
private:
    inline static const std::unordered_map<char, std::string> phone_map {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
    };
};
}

namespace leetcode_018 {
// 18. 四数之和
class Solution {
public:
    static std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        std::vector<std::vector<int>> ans;
        if (nums.size() < 4) {
            return ans;
        }
        std::sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        for (int a = 0; a < n - 3; ++a) {
            long x = nums[a];
            if (a > 0 && x == nums[a-1]) {
                continue;
            }
            if (x + nums[a+1] + nums[a+2] + nums[a+3] > target) {
                break;
            }
            if (x + nums[n-3] + nums[n-2] + nums[n-1] < target) {
                continue;
            }
            for (int b = a + 1; b < n - 2; ++b) {
                long y = nums[b];
                if (b > a + 1 && y == nums[b-1]) {
                    continue;
                }
                if (x + y + nums[b+1] + nums[b+2] > target) {
                    break;
                }
                if (x + y + nums[n-2] + nums[n-1] < target) {
                    continue;
                }
                int c = b + 1, d = n - 1;
                while (c < d) {
                    long sum = x + y + nums[c] + nums[d];
                    if (sum < target) {
                        ++c;
                    }
                    else if (sum > target) {
                        --d;
                    }
                    else {
                        ans.push_back({int(x), int(y), nums[c], nums[d]});
                        for (++c; c < d && nums[c] == nums[c - 1]; ++c);
                        for (--d; c < d && nums[d] == nums[d + 1]; --d);
                    }
                }
            }
        }

        return ans;
    }
};
}


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace leetcode_019 {
// 19. 删除链表的倒数第 N 个结点
class Solution {
public:
    static int get_len(ListNode *head) {
        int num = 0;
        while (head) {
            head = head->next;
            ++num;
        }
        return num;
    }

    static ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto *dummy = new ListNode(0, head);
        int len = get_len(head);
        ListNode *cur = dummy;
        for (int i = 0; i < len - n; ++i) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        auto newhead = dummy->next;
        delete dummy;
        return newhead;
    }
    static ListNode* removeNthFromEnd_v(ListNode* head, int n) {
        auto dummy = new ListNode(0, head);
        auto first = head;
        auto second = dummy;
        for (int i = 0; i < n; ++i) {
            first = first->next;
        }
        while (first) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        auto ans = dummy->next;
        delete dummy;
        return ans;
    }
};
}

namespace leetcode_020 {
// 20. 有效的括号
class Solution {
public:
    static bool isValid(const std::string &s) {
        std::stack<char> stack;
        for (auto c : s) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            }
            else {
                if (stack.empty()) {
                    return false;
                }
                char top = stack.top();
                stack.pop();
                if (!match(c, top)) {
                    return false;
                }
            }
        }
        return stack.empty();
    }
private:
    static bool match(char c, char other) {
        if (c == ')') {
            return other == '(';
        }
        if (c == ']') {
            return other == '[';
        }
        if (c == '}') {
            return other == '{';
        }
        return false;
    }
};
void test()
{
    std::string s{"()[]{}"};
    std::cout << std::format("s={}, isValid: {}\n", s, Solution::isValid(s));
}
}

namespace leetcode_021 {
// 21. 合并两个有序链表
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }
        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
}

namespace leetcode_022 {
// 22. 括号生成
class Solution {
public:
    static std::vector<std::string> generateParenthesis(int n) {
        if (n == 0) {
            return {};
        }
        std::vector<std::vector<std::string>> dp;
        // 0组括号
        dp.emplace_back(1, "None");
        // 1组括号"()"
        dp.emplace_back(1, "()");
        // 开始计算i组括号时的括号组合
        for (int i = 2; i <= n; ++i) {
            std::vector<std::string> tmp_list;
            // 开始遍历 p q ，其中p+q=i-1 , j 作为索引
            for (int j = 0; j < i; ++j) {
                auto &l1 = dp[j];
                auto &l2 = dp[i-1-j];
                for (auto &k1 : l1) {
                    for (auto &k2: l2) {
                        if (k1 == "None") {
                            k1 = "";
                        }
                        if (k2 == "None") {
                            k2 = "";
                        }
                        tmp_list.emplace_back("(" + k1 + ")" + k2);
                    }
                }
            }
            dp.push_back(tmp_list);
        }
        return dp[n];
    }
};
}

namespace leetcode_024 {
// 24. 两两交换链表中的节点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        ListNode *newhead = head->next;
        head->next = swapPairs(newhead->next);
        newhead->next = head;
        return newhead;
    }
};
}

namespace leetcode_025 {
// 25. K 个一组翻转链表
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k < 2) {
            return head;
        }
        ListNode *tail = head;
        for (int i = 0; i < k; ++i) {
            if (tail == nullptr) {
                return head;
            }
            tail = tail->next;
        }
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur != tail) {
            auto tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        head->next = reverseKGroup(tail, k);
        return pre;
    }
};
}

namespace leetcode_026 {
// 26. 删除有序数组中的重复项
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int len = 0;
        for (int i = 0, j = 0; j < n; ) {
            nums[len++] = nums[i];
            while (j < n && nums[i] == nums[j]) {
                ++j;
            }
            i = j;
        }
        return len;
    }
};
}

namespace leetcode_027 {
// 27. 移除元素
class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int n = static_cast<int>(nums.size());
        int len = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == val) {
                continue;
            }
            nums[len++] = nums[i];
        }
        return len;
    }
};
}

namespace leetcode_030 {
// 30. 串联所有单词的子串
class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
    }
};
}































int main()
{
//    leetcode_007::test();
//    leetcode_008::test();
    leetcode_020::test();
    return 0;
}