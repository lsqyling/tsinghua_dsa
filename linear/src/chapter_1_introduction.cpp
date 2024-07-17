//
// Created by shiqing on 2020/5/5.
//
#include <Fib.h>
#include <cstring>
#include "../../common/CommonHeaders.h"

/*
 * 2020/5/6
 * Lesson 48 Did you want to tell me something?
 * First listen and then answer the question
 * Why did the writer become very worried?
 * Dentists always ask questions when it is impossible for to answer.My dentist had just pulled out one of my teeth and had
 * told me to rest for a while.I tried to say something, but my mouth was full of cotton wool.He knew I collected match
 * boxes and asked me whether my collection was growing.He then asked me how my brother was and whether I liked my new job
 * in London.In answer to these questions, I either nodded or made strange noises.Meanwhile, my tongue was busy searching out
 * the hole where the tooth had been.I suddenly felt very worried, but could not say anything.When the dentist at last removed
 * the cotton wool from my mouth, I was able to tell him that he had pulled out the wrong tooth.
 *
 * Dear Terry,
 * Hi!I'm Zhangwen, monitor of Class 4.I'm writing to ask if you will be free on Saturday.Our class students have made an English
 * textbook play.We are going to put it on at the school hall on Saturday.Time is 4:00 p.m.The play is about a famous English
 * story.I'm sure you will enjoy it.We all hope you can come, and we do hope you can give a speech at the end of the performance.
 * We'd like you to give us some tips about English learning.If you can come,please let me know.
 * We are all looking forward to your coming.
 * Yours,
 * Zhangwen
 *
 * 2020/5/7
 * Lesson 49 The end of dream
 * First listen and then answer the question
 * How did the dream end?
 * Tired of sleeping on the floor, a young man in Teheran saved up for years to buy a real bed.For the first time in his life,
 * he become the proud owner of a bed which had springs and mattress.Become the weather was very hot,he carried the bed on
 * to the roof of his house.He slept very well for the first two nights, but on the third night a storm blew up.A gust wind
 * of wind swept the bed off the roof and sent it crashing into the courtyard below.The young man did not wake up until the bed
 * had struck the ground.Although the bed was smashed to pieces,the man was miraculously unhurt.When he the woke up, he was
 * still on the mattress.Glancing at the bits of wood and metal that lay around him, the man was sadly picked up the mattress and
 * carried it into his house.After he had put it on the floor,he promptly went to sleep again.
 *
 * Dear editor,
 *      I am writing to tell you about how children from different counties choose gifts for their mothers on Mother's Day.
 *      Anita is from England.She'd like to give a green scarf as a gift to her mother.Her mother's favourite colour is green,
 * and she really needs a scarf.Jacob comes from USA.He'd like to give her mother a hand-made card,because it's easy to make
 * and it means a lot.
 *      I'm from China.My mother is a worker.I want to give her a nice cup.Then she can use it to drink a cup of tea and
 * have a rest after work.
 * Looking forward to your reply.
 * Yours,
 * Lin Chao
 *
 *
 *
 */


constexpr int kLen = 0xffff;

void bubbleSort1A(int A[], int n)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < n; ++i)
        {
            if (A[i] < A[i - 1])
            {
                std::swap(A[i], A[i - 1]);
                sorted = false;
            }
        }
        --n;
    }
}

void testingBubbleSort1A()
{
    auto &p = generateRandomArray<6>();
    auto &p1 = generateRandomArray<kLen>();
    printArray(cout, p) << endl;
    calledCostTime(bubbleSort1A, "bubbleSort[6]", p, 6);
    calledCostTime(bubbleSort1A, "bubbleSort[k]", p1, kLen);
    cout << "bubble sorted of Ap is sorted: " << isSorted(p) << endl;
    cout << "bubble sorted of Ap1 is sorted: " << isSorted(p1) << endl;
}

int countOnes(unsigned n)
{
    int ones = 0;
    while (n)
    {
        ones += (n & 1);
        n >>= 1;
    }
    return ones;
}

/*
 * what is n when 1.0001^n bigger than n^1.0001?
 */
void solveAboveQuestion()
{
    int i = 2;
    while (std::pow(1.0001, i) < std::pow(i, 1.0001)) ++i;
    cout << "i = " << i << endl;
}

void testingCountOnesAndSolveAboveQuestion()
{
    cout << countOnes(1023) << endl;
    solveAboveQuestion();
}

namespace recursive_1_4 {
int sum(int A[], int n)
{
    if (n == 0) return 0;
    return A[n - 1] + sum(A, n - 1);
}

void reverse(int A[], int lo, int hi)
{
    if (lo < hi)
    {
        std::swap(A[lo], A[hi]);
        reverse(A, lo + 1, hi - 1);
    }
}

long pow2(int n)
{
    if (n == 0) return 1;
    return (n & 1 ? 2 * pow2(n / 2) : pow2(n / 2)) * pow2(n / 2);
}

int sum(int A[], int lo, int hi)
{
    if (lo == hi) return A[lo];
    int mid = (lo + hi) / 2;
    return sum(A, lo, mid) + sum(A, mid + 1, hi);
}

inline int fib(int n) noexcept
{
    int f = 1, g = 0;
    while (n--)
    {
        g += f;
        f = g - f;
    }
    return g;
}

void testingRecursiveCall()
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto r = sum(A, 10);
    cout << r << endl;
    reverse(A, 0, 9);
    printArray(cout, A);
    auto r1 = sum(A, 0, 9);
    printf("r1 = %d\n", r1);
    for (int i = 0; i < 34; ++i)
    {
        printf("fib(%d) = %d\n", i, fib(i));
    }
}
}

namespace exercise_1 {
namespace _1_2 {
constexpr double islandHeight(double d1, double d2, double d, double h)
{
    return h * d / (d1 - d2) + h;
}

constexpr double islandDistance(double d1, double d2, double d)
{
    return d * d2 / (d1 - d2);
}

void testingHD()
{
    printf("H = %f\n", islandHeight(127, 123, 1000, 3));
    printf("D = %f\n", islandDistance(127, 123, 1000));
}
}

namespace _1_3 {
void bubbleSort(int A[], int n)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < n; ++i)
        {
            if (A[i] < A[i - 1])
            {
                sorted = false;
                std::swap(A[i], A[i - 1]);
            }
        }
        --n;
    }
}

void testingBubbleSort()
{
    auto &A = generateRandomArray<kLen / 4>();
    calledCostTime(bubbleSort, "bubbleSort", A, kLen / 4);
    cout << "A is Sorted: " << isSorted(A) << endl;
}
}

namespace _1_12_14 {
constexpr int countOnes(unsigned n)
{
    int cnt = 0;
    while (n)
    {
        if (n & 1) ++cnt;
        n >>= 1;
    }
    return cnt;
}

constexpr int countOnes_1(unsigned n)
{
    int cnt = 0;
    while (n)
    {
        ++cnt;
        n &= n - 1;
    }
    return cnt;
}

constexpr int pow2BF(int n) noexcept
{
    return n < 1 ? 1 : pow2BF(n - 1) << 1;
}

constexpr int pow(int a, int n) noexcept
{
    int r = 1;
    while (n)
    {
        if (n & 1) r *= a;
        a *= a;
        n >>= 1;
    }
    return r;
}

void testingPow()
{
    printf("pow2BF(30) = %d\n", pow2BF(30));
    printf("pow(2, 30) == pow2BF(30) ? %d\n", pow(2, 30) == pow2BF(30));
}

void testingCountOnes()
{
    unsigned x = 0xffff'ffff;
    printf("countOnes(x) = %d\n", countOnes(x));
    printf("countOnes(x) == countOnes_1(x) ? = %d\n", countOnes(x) == countOnes_1(x));
}
}

namespace _1_15 {
int maxI(int A[], int n)
{
    int max = A[0];
    for (int i = 0; i < n; ++i)
    {
        if (max < A[i]) max = A[i];
    }
    return max;
}

int maxII(int A[], int n)
{
    if (n <= 1) return A[n - 1];
    return std::max(maxII(A, n - 1), A[n - 1]);
}

/*
 * What is max of A[lo, hi);
 */
int maxR(int A[], int lo, int hi)
{
    if (lo + 1 == hi) return A[lo];
    int mid = (lo + hi) / 2;
    return std::max(maxR(A, lo, mid), maxR(A, mid, hi));
}

void testingMaxOfNums()
{
    auto &A = generateRandomArray<kLen>();
    printf("maxI = %d\n", maxI(A, kLen));
    printf("maxI == maxII ? %d\n", maxI(A, kLen) == maxII(A, kLen));
    printf("maxI == maxR ? %d\n", maxI(A, kLen) == maxR(A, 0, kLen));
}

/*
 * Find all subsets of a set
 */
std::vector<std::vector<int>> findAllSubsets(int A[], int n)
{
    std::vector<std::vector<int>> ans;
    int s = 1 << n, i, mask;
    for (int j = 0; j < s; ++j)
    {
        i = 0;
        mask = j;
        std::vector<int> set;
        while (mask)
        {
            if (mask & 1)
            {
                set.push_back(A[i]);
            }
            ++i;
            mask >>= 1;
        }
        ans.push_back(std::move(set));
    }
    return ans;
}

void testingFindAllSubsets()
{
    int A[] = {0, 1, 2, 3};
    auto r = findAllSubsets(A, 4);
    for (const auto &set : r)
    {
        for (auto e : set)
        {
            printf("%d ", e);
        }
        printf("\n");
    }
    printf("the total sets is %zu\n", r.size());
}
}

namespace _1_23 {

void testingFib()
{
    Fib fib(90);
    cout << "fib(90) = get" << fib.get() << endl;
    cout << "fib(90) = next" << fib.next() << endl;
    cout << "fib(90) = pre" << fib.pre() << endl;
}
}

namespace _1_25 {
long gcdCN(long a, long b)
{
    int r = 0;
    while ((a & 1) == 0 && (b & 1) == 0)
    {
        a >>= 1;
        b >>= 1;
        ++r;
    }
    for (;;)
    {
        if (a == 0) return b << r;
        if (b == 0) return a << r;
        while ((a & 1) == 0) a >>= 1;
        while ((b & 1) == 0) b >>= 1;
        a > b ? a -= b : b -= a;
    }
}

/*
 * gcd(a, b) = gcd(b, a % b);
 */
int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

void testingGcd()
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, 0xffff);
    for (int i = 0; i < 10; ++i)
    {
        int a = u(e), b = u(e);
        printf("gcd = gcdCN ? %d\n", gcd(a, b) == gcdCN(a, b));
    }
}
}

namespace _1_26 {
/*
 * reverse A[lo, hi)
 */
void reverse(int A[], int lo, int hi)
{
    for (int i = lo, j = hi - 1; i < j; ++i, --j)
    {
        std::swap(A[i], A[j]);
    }
}

int shift(int A[], int n, int k)
{
    k %= n;
    reverse(A, 0, k);
    reverse(A, k, n);
    reverse(A, 0, n);
    return 3 * n;
}

void testingShift()
{
    auto &A = generateRandomArray<15>();
    bubbleSort1A(A, 15);
    printArray(cout, A) << endl;
    shift(A, 15, 7);
    printArray(cout, A) << endl;
}
}

namespace _1_27_29 {
int Ackermann(int m, int n)
{
    if (m == 0) return n + 1;
    if (n == 0) return Ackermann(m - 1, 1);
    return Ackermann(m - 1, Ackermann(m, n - 1));
}

void testingAckermann()
{
    printf("Ackermann(%d, %d) = %d\n", 2, 2, Ackermann(2, 2));
}

int hailstone(int n)
{
    int s = 0;
    while (n > 1)
    {
        n & 1 ? n = 3 * n + 1 : n /= 2;
        ++s;
    }
    return s;
}

void testingHailstone()
{
    for (int i = 1; i < 10; ++i)
    {
        printf("hailstone(%d)'s steps is %d\n", i, hailstone(i));
    }
}

/*
 * 2020/5/7 Lesson 50 Taken for a ride
 * First listen and then answer the question
 * Why did the writer not get off the bus at Woodford Green?
 * I love travelling in the country but I don't like losing my way.I went on an excursion recently,but my trip took me longer
 * than I expected.'I am going to Woodford Green' I said to the conductor as I got on the bus, 'But I don't know where
 * it is?' 'I'll tell you where to get off.' answered the conductor.I sat in the front of the bus to get a good view of the
 * countryside.After some time, the bus stopped. Looking around, I realized with a shocked that I was the only passenger left on the
 * bus.'You'll have to get off here' the conductor said, 'this's as far as we go.' 'Is this Woodford Green?' I asked.'Oh, dear
 * ' said the conductor suddenly,'I forget to put you off.' 'It doesn't matter.' I said, 'I'll get off here.' 'We are going back now'
 * said the conductor. 'Well, in that case, I prefer to stay on the bus.' I answered.
 *
 * My free time
 * I have lots of things to do in my free time.Usually I take exercise after school so that I can keep healthy and study better.
 * Sometimes I listen to the music for a while, which is a good way to relax myself.Of course, I help my parents with
 * the housework at the weekends too.When I get tired, I would like to sit by balcony and read books such as a novel, a
 * science fiction, or even a poem.Reading calms my heart down and satisfies my hunger for knowledge.I love my free times
 * because I enjoy the freedom.
 *
 * 2020/5/9
 * Lesson 51 Reward for virtue
 * First listen and then answer the question
 * Why did Hugh's diet not work?
 * My friend Hugh, has always been fat, but things got so bad recently that he decided to go on a diet.He began his diet
 * a week ago.First of all, he wrote out a long list of all foods which were forbidden.The list included most of the things
 * Hugh loves:butter,potatoes,rice,beer, milk, chocolate,and sweets.Yesterday, I paid him a visit.I rang the bell and was
 * not surprised to see that Hugh was still as fat as ever.He led me into his room and hurriedly hid a large parcel under
 * his desk.It was obvious that he was so embarrassed. When I asked him what he was doing, he smiled guiltily and then put the
 * parcel on the desk.He explained that his diet was so strict that he had to reward himself occasionally.Then he showed
 * me the contents of the parcel.It contained five large bars of chocolate and three bags of sweets.
 *
 * June 3, Friday Fine
 * On  my way home on the bus, I saw an old man get on with his grandson of about ten. The old man was carrying the boy's
 * schoolbag and violin.I gave my seat to the old man at once.However, the boy sat down at first.The old man had to stand
 * nearby.After a while, the boy shouted to his grandpa for water and then dropped the empty bottle on the bus.When I saw
 * this, I got very angry.I think the boy should not only respect and take care of the old man but also keep the environment clean.
 */
}

/*
 * LCS
 */
int getLCS(const char *A, const char *B)
{
    int n = strlen(A), m = strlen(B);
    int N = std::max(n, m) + 1;
    int dp[N][N];
//    base
    for (int i = 0; i <= n; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; ++j)
    {
        dp[0][j] = 0;
    }
//    state transition equation
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (A[i] == B[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

void testingLCS()
{
    const char s1[] = "sadstory";
    const char s2[] = "adminsorry";
    printf("the LCS %s and %s = %d\n", s1, s2, getLCS(s1, s2));
}


}

int main(int argc, char *argv[])
{
//    testingBubbleSort1A();
//    testingCountOnesAndSolveAboveQuestion();
//    recursive_1_4::testingRecursiveCall();
    exercise_1::_1_2::testingHD();
    exercise_1::_1_3::testingBubbleSort();
    exercise_1::_1_12_14::testingCountOnes();
    exercise_1::_1_12_14::testingPow();
    exercise_1::_1_15::testingMaxOfNums();
    exercise_1::_1_15::testingFindAllSubsets();
    exercise_1::_1_23::testingFib();
    exercise_1::_1_25::testingGcd();
    exercise_1::_1_26::testingShift();
    exercise_1::_1_27_29::testingAckermann();
    exercise_1::_1_27_29::testingHailstone();
    exercise_1::testingLCS();
    return 0;
}

