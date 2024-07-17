//
// Created by shiqing on 19-5-18.
//

#include <cassert>
#include "../../common/CommonHeaders.h"
#include "../include/Stack.h"
#include <cmath>
#include <sstream>

namespace oj {

/*
 * Question: LightHouse
 * Description
 * As shown in the following figure, If another lighthouse is in gray area, they can beacon each other.
 * For example, in following figure, (B, R) is a pair of lighthouse which can beacon each other, while (B, G), (R, G) are NOT.
 * Input
 * 1st line: N
 * 2nd ~ (N + 1)th line: each line is X Y, means a lighthouse is on the point (X, Y).
 * Output
 * How many pairs of lighthourses can beacon each other
 * ( For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same )
 * Example
 * Input
 * 3
 * 2 2
 * 4 3
 * 5 1
 * Output
 * 1
 * Restrictions
 * For 90% test cases: 1 <= n <= 3 * 10^5
 * For 95% test cases: 1 <= n <= 10^6
 * For all test cases: 1 <= n <= 4 * 10^6
 * For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same.
 * 1 <= x, y <= 10^8
 * Time: 2 sec
 * Memory: 256 MB
 * Hints
 * The range of int is usually [-2^31, 2^31 - 1], it may be too small.
 */

namespace LightHouse {
struct Point
{
    int x;
    int y;
};

inline bool isBeaconed(const Point &lhs, const Point &rhs) noexcept
{
    return (lhs.x < rhs.x && lhs.y < rhs.y) || (lhs.x > rhs.x && lhs.y > rhs.y);
}

std::vector<Point> readInputs()
{
    int n = 0, x = 0, y = 0;
    scanf("%d", &n);
    std::vector<Point> vp;
    for (int i = 0; i != n; ++i)
    {
        scanf("%d %d", &x, &y);
        vp.push_back({x, y});
    }
    return vp;
}

int64_t countIf(const std::vector<Point> &vp) noexcept
{
    int64_t cnt = 0;
    size_t sz = vp.size();
    for (size_t i = 0; i != sz; ++i)
    {
        for (size_t j = i + 1; j != sz; ++j)
        {
            if (isBeaconed(vp[i], vp[j]))
            {
                ++cnt;
            }
        }
    }
    return cnt;
}

}

void testingLightHouse()
{
    int64_t cnt = LightHouse::countIf(LightHouse::readInputs());
    printf("%ld\n", cnt);
}


/*
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */

namespace TwoSum {

std::vector<int> twoSum(std::vector<int> &nums, int target)
{
    size_t sz = nums.size();
    for (size_t i = 0; i != sz; ++i)
    {
        for (size_t j = i + 1; j != sz; ++j)
        {
            if (nums[i] + nums[j] == target)
            {
                return {static_cast<int>(i), static_cast<int>(j)};
            }
        }
    }
    return {};
}
}

namespace Add_Two_Numbers {

// * Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr)
    {
    }
};

string parseToStrNumbs(ListNode *head)
{
    string r;
    if (head)
    {
        ListNode *curr = head;
        while (curr != nullptr)
        {
            r.append(std::to_string(curr->val));
            curr = curr->next;
        }
    }
    return string(r.rbegin(), r.rend());
}

string addToStr(string a, string b)
{
    size_t sz = a.size() < b.size() ? b.size() : a.size();
    if (sz == a.size() && sz != b.size())
    {
        auto n = sz - b.size();
        while (n--)
        {
            b.insert(b.begin(), '0');
        }
    }
    if (sz == b.size() && sz != a.size())
    {
        auto n = sz - a.size();
        while (n--)
        {
            a.insert(a.begin(), '0');
        }
    }
    string result;
    int carryDigit = 0;
    for (string::difference_type i = sz - 1; i > -1; --i)
    {
        int r = std::stoi(string(1, a[i])) + std::stoi(string(1, b[i])) + carryDigit;
        result.insert(0, std::to_string(r % 10));
        carryDigit = r / 10;
    }
    if (carryDigit)
    {
        result.insert(0, std::to_string(carryDigit));
    }
    return result;
}

ListNode *transToListNode(string s)
{
    assert(s.size() > 0);
    ListNode *head = new ListNode(99);
    ListNode *curr = head, *next;
    for (string::difference_type i = s.size() - 1; i > -1; --i)
    {
        next = new ListNode(std::stoi(string(1, s[i])));
        curr->next = next;
        curr = next;
    }
    return head->next;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    string a = parseToStrNumbs(l1), b = parseToStrNumbs(l2);
    return transToListNode(addToStr(a, b));
}

}

void testingAddToStr()
{
    string a("3429"), b("465");
    using namespace Add_Two_Numbers;
    ListNode *l1 = new ListNode(2), *l2 = new ListNode(4), *l3 = new ListNode(3);
    l1->next = l2;
    l2->next = l3;

    ListNode *r1 = new ListNode(5), *r2 = new ListNode(6), *r3 = new ListNode(4);
    r1->next = r2;
    r2->next = r3;

    cout << parseToStrNumbs(l1) << ", " << parseToStrNumbs(r1) << endl;
    cout << Add_Two_Numbers::addToStr(parseToStrNumbs(l1), parseToStrNumbs(r1)) << endl;

    cout << parseToStrNumbs(transToListNode(a)) << endl;
    cout << parseToStrNumbs(addTwoNumbers(l1, r1)) << endl;

}

int lengthOfLongestSubstring(string s)
{
    int max = 0;
    string::size_type i, j, k;
    for (i = 0; i < s.size(); ++i)
    {
        int cnt = 1;
        j = i;
        while (++j < s.size())
        {
            for (k = i; k < j; ++k)
            {
                if (s[k] == s[j]) goto label;
            }
            ++cnt;
        }
        label:
        if (max < cnt) max = cnt;
        if (i == 0 && j == s.size()) break;
    }
    return max;
}

void testingLengthOfLongestSubstring()
{
    cout << "abcabcbb: " << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << "bbbbb: " << lengthOfLongestSubstring("bbbbb") << endl;
    cout << "pwwkew: " << lengthOfLongestSubstring("pwwkew") << endl;
}

double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
{
    std::vector<int> vi;
    auto sz1 = nums1.size(), sz2 = nums2.size();
    if (sz1 == 0) return (sz2 & 1) ? nums2[sz2 / 2] : (nums2[sz2 / 2] + nums2[sz2 / 2 - 1]) * 1.0 / 2;
    if (sz2 == 0) return (sz1 & 1) ? nums1[sz1 / 2] : (nums1[sz1 / 2] + nums1[sz1 / 2 - 1]) * 1.0 / 2;
    for (std::vector<int>::size_type i = 0, j = 0; i < sz1 || j < sz2;)
    {
        nums1[i] <= nums2[j] ? vi.push_back(nums1[i++]) : vi.push_back(nums2[j++]);
        while (i == sz1 && j < sz2) vi.push_back(nums2[j++]);
        while (j == sz2 && i < sz1) vi.push_back(nums1[i++]);
    }

    if (vi.size() & 1)
    {
        return vi[vi.size() / 2];
    }
    return (vi[vi.size() / 2] + vi[vi.size() / 2 - 1]) * 1.0 / 2;
}

void testingFindMedianSortedArrays()
{
    std::vector<int> n1{1, 2}, n2{3, 4};
    cout << findMedianSortedArrays(n1, n2) << endl;
}

string longestPalindrome(string s)
{
    int len = s.size();
    if (len < 2) return s;
    int start = 0, max = 1;
    for (int k = 0, i = 0, j = 0; k < len;)
    {
        i = j = k;
        while (j < len && s[i] == s[j]) ++j;
        k = j;
        --i;
        while (i > -1 && j < len && s[i] == s[j])
        {
            --i;
            ++j;
        }

        if (j - i - 1 > max)
        {
            start = i + 1;
            max = j - i - 1;
        }
    }

    return s.substr(start, max);
}

string getLCSLength(string s1, string s2)
{
    int len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<int>> arr(len1, std::vector<int>(len2));
    int rs1 = 0, maxLen = 0;
    for (int i = 0; i != len1; ++i)
    {
        for (int j = 0; j != len2; ++j)
        {
            if (s1[i] == s2[j])
            {
                if (i > 0 && j > 0)
                {
                    arr[i][j] = arr[i - 1][j - 1] + 1;
                }
                else
                {
                    arr[i][j] = 1;
                }
                if (maxLen < arr[i][j])
                {
                    maxLen = arr[i][j];
                    rs1 = i;
                }
            }
        }
    }
    if (maxLen > 0)
    {
        return s1.substr(rs1 - maxLen + 1, maxLen);
    }
    return string();
}

void testingLongestPalindrome()
{
    string s("babaddtattarrattatddetartrateedredividerb");
    cout << longestPalindrome(s) << endl;
    string s1("acbcbcef"), s2("abcbced");
    cout << getLCSLength(s1, s2) << endl;
}

/*
 * calc 24;
 */

constexpr double EPS = 1e-6;

bool isZero(double x)
{
    return std::fabs(x) < EPS;
}

bool count24(double a[], int n)
{
    if (n == 1)
    {
        if (isZero(a[0] - 24)) return true;
        else return false;
    }
    double b[5];
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int m = 0;
            for (int k = 0; k != n; ++k)
            {
                if (k != i && k != j)
                {
                    b[m++] = a[k];
                }
            }
            b[m] = a[i] + a[j];
            if (count24(b, m + 1)) return true;
            b[m] = a[i] - a[j];
            if (count24(b, m + 1)) return true;
            b[m] = a[j] - a[i];
            if (count24(b, m + 1)) return true;
            b[m] = a[i] * a[j];
            if (count24(b, m + 1)) return true;
            if (!isZero(a[j]))
            {
                b[m] = a[i] / a[j];
                if (count24(b, m + 1)) return true;
            }
            if (!isZero(a[i]))
            {
                b[m] = a[j] / a[i];
                if (count24(b, m + 1)) return true;
            }
        }
    }
    return false;
}

void testingCount24()
{
    double a[6];
    string line;
    while (getline(cin, line))
    {
        std::istringstream iss(line);
        double d = 0;
        int i = 0;
        while (iss >> d) a[i++] = d;
        if (count24(a, 4)) cout << "YES\n";
        else cout << "NO\n";
    }
}

/*
 * 1
 * 2 3
 * 4 5 6
 * 7 8 9 10
 * 11 12 13 14 15
 * ...
 *
 *
 * total  = 0 - 100 rows
 * total = (1 + n)n / 2
 * Question: please calculate the max sum of nums from top to toe?
 */

constexpr int MAX = 101;
int maxSum[MAX][MAX];
int inpusArray[MAX][MAX];

int initInputsArray()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            cin >> inpusArray[i][j];
            maxSum[i][j] = -1;
        }
    }
    return n;
}

int maxSumFunction(int i, int j, int n)
{
    if (maxSum[i][j] != -1)
    {
        return maxSum[i][j];
    }
    if (i == n)
    {
        maxSum[i][j] = inpusArray[i][j];
    }
    else
    {
        int x = maxSumFunction(i + 1, j, n);
        int y = maxSumFunction(i + 1, j + 1, n);
        maxSum[i][j] = std::max(x, y) + inpusArray[i][j];
    }
    return maxSum[i][j];
}

void testingMaxSumFunction()
{
    int n = initInputsArray();
    cout << maxSumFunction(1, 1, n) << endl;
}



/*
 * Description
 * Let's play the game Zuma!
 * There are a sequence of beads on a track at the right beginning. All the beads are colored but no three adjacent ones are allowed to be with a same color. You can then insert beads one by one into the sequence. Once three (or more) beads with a same color become adjacent due to an insertion, they will vanish immediately.
 * Note that it is possible for such a case to happen for more than once for a single insertion. You can't insert the next bead until all the eliminations have been done.
 * Given both the initial sequence and the insertion series, you are now asked by the fans to provide a playback tool for replaying their games. In other words, the sequence of beads after all possible eliminations as a result of each insertion should be calculated.
 * Input
 * The first line gives the initial bead sequence. Namely, it is a string of capital letters from 'A' to 'Z', where different letters correspond to beads with different colors.
 * The second line just consists of a single interger n, i.e., the number of insertions.
 * The following n lines tell all the insertions in turn. Each contains an integer k and a capital letter Σ, giving the rank and the color of the next bead to be inserted respectively. Specifically, k ranges from 0 to m when there are currently m beads on the track.
 * Output
 * n lines of capital letters, i.e., the evolutionary history of the bead sequence.
 * Specially, "-" stands for an empty sequence.
 * Example
 * Input
 * ACCBA
 * 5
 * 1 B
 * 0 A
 * 2 B
 * 4 C
 * 0 A
 * Output
 * ABCCBA
 * AABCCBA
 * AABBCCBA
 * -
 * A
 * Restrictions
 * 0 <= n <= 10^4
 * 0 <= length of the initial sequence <= 10^4
 * Time: 2 sec
 * Memory: 256 MB
 */




namespace zuma {

int eliminatePos(string &s, int k)
{
    int l = k, cnt = 0;
    while (l > -1 && (s[--l] == s[k])) ++cnt;
    if (cnt == 2) return l;
    int r = k;
    cnt = 0;
    while (r < s.size() && (s[++r] == s[k])) ++cnt;
    if (cnt == 2) return r;
    l = r = k;
    if (l > -1 && r < s.size() && s[--l] == s[k] && s[k] == s[++r]) return l;
    return k;
}

void doEliminate(string &s, int &k)
{
    int pos;
    while ((pos = eliminatePos(s, k)) != k)
    {
        if (pos < k)
        {
            s.erase(pos, 3);
            k = pos, --k;
        }
        else
        {
            s.erase(k--, 3);
        }
    }
}

void processing()
{
    string initStr;
    int n = 0;
    cin >> initStr >> n;
    for (int i = 0; i < n; ++i)
    {
        int k;
        string c;
        if (cin >> k >> c)
        {
            initStr.insert(k, c);
            doEliminate(initStr, k);
            if (!initStr.empty())
            {
                if (i != n - 1) cout << "\n" << initStr;
                else cout << "\n" << initStr << std::flush;
            }
            else
            {
                if (i != n - 1) cout << "\n" << "-";
                else cout << "\n" << "-" << std::flush;
            }
        }
        else
        {
            cout << "input error" << endl;
            break;
        }
    }
}

void testingZuma()
{
    processing();
}

}


/*
* Question: Range
* Descriptioin
* Let s be a set of n integral points on the x-axis. For each given interval [a, b], you are asked to count the points lying inside.
* Input
* The first line contains two integers: n (size of s) and m (the number of queries).
* The second line enumerates all the n points in s.
* Each of the following m lines consists of two integers a and b and defines an query interval [a, b].
* Output
* The number of points in s lying inside each of the m query intervals.
* Example
* Input
* 5 2
* 1 3 7 9 11
* 4 6
* 7 12
* Output
* 0
* 3
* Restrictions
* 0 <= n, m <= 5 * 10^5
* For each query interval [a, b], it is guaranteed that a <= b.
* Points in s are distinct from each other.
* Coordinates of each point as well as the query interval boundaries a and b are non-negative integers not greater than 10^7.
* Time: 2 sec
* Memory: 256 MB
*/



namespace range {

int search(const std::vector<int> &vi, int left, int right, int e)
{
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        e < vi[mid] ? right = mid : left = mid + 1;
    }
    return --left;
}

void testingRanges()
{
    int n = 0, m = 0;
    if (!(cin >> n >> m)) return;
    std::vector<int> vi;
    int e;
    for (int i = 0; i < n; ++i)
    {
        if (cin >> e)
        {
            vi.push_back(e);
        }
        else
        {
            cout << "inputs error" << endl;
            break;
        }
    }
    for (int j = 0; j < m; ++j)
    {
        int a, b;
        if (cin >> a >> b)
        {
            int lo = search(vi, 0, vi.size(), a);
            int hi = search(vi, 0, vi.size(), b);
            if (lo == hi) cout << "\n0";
            else cout << "\n" << hi - lo + 1;
        }
    }
    cout << std::flush;
}

}

namespace train {
/*
 * 列车调度(Train)
 */
void testingTrain()
{
    int n = 0, m = 0;
    if (!(cin >> n >> m)) return;
    std::vector<int> vi;
    int x = 0;
    vi.push_back(x);
    while (cin >> x)
    {
        vi.push_back(x);
    }
    linear::Stack<int> transfer;
    std::vector<string> vOut;
    for (int i = 1, j = 1; i <= n;)
    {
        if (j <= n && transfer.size() <= m && vi[i] >= j)
        {
            transfer.push(j++);
            vOut.emplace_back("push");
        }
        else
        {
            if (vi[i] == transfer.top())
            {
                transfer.pop();
                vOut.emplace_back("pop");
                ++i;
            }
            else break;
        }
    }
    if (vOut.size() == 2 * n)
    {
        for (int i = 0; i < 2 * n; ++i)
        {
            cout << "\n" << vOut[i];
        }
    }
    else
    {
        cout << "\n" << "no";
    }
    cout << std::flush;
}
}
}


int main(int argc, char *argv[])
{
    oj::testingLengthOfLongestSubstring();
    oj::testingAddToStr();
    oj::testingLightHouse();
    oj::testingFindMedianSortedArrays();
    oj::testingLongestPalindrome();
    oj::testingCount24();
    oj::testingMaxSumFunction();
    oj::zuma::testingZuma();
    oj::range::testingRanges();
    oj::train::testingTrain();

}






