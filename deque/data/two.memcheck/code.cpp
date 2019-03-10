// provided by your new friend Mercy. Enjoy!

#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <random>

#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include "deque.hpp"

std::default_random_engine randnum(time(NULL));

static const int MAX_N = 15000;

template <typename Ans, typename Test>
bool isEqual(Ans &ans, Test &test) {
    if (ans.size() != test.size())
        return false;

    if (ans.empty()) return true;

    for (int i = 0; i < ans.size(); i++) {
        if (randnum() % 2) {
            if (ans[i] != test[i]) return false;
        } else {
            if (ans.at(i) != test.at(i)) return false;
        }
    }

    if (ans.empty() != test.empty() || ans.front() != test.front() ||
        ans.back() != test.back())
        return false;

    return true;
}

template <typename Ans, typename Test>
void randnumFill(Ans &ans, Test &test, int n = 2e5) {
    for (int i = 0; i < n; i++) {
        int x = randnum();
        if (randnum() % 2) {
            ans.push_back(x);
            test.push_back(x);
        } else {
            ans.push_front(x);
            test.push_front(x);
        }
    }
}

bool pushTest() {
    std::deque<int> ans;
    sjtu::deque<int> deq;

    for (int i = 0; i < MAX_N; i++) {
        int x = randnum();
        switch (randnum() % 2) {
            case 0: deq.push_front(x); ans.push_front(x);
                    break;
            case 1: deq.push_back(x);  ans.push_back(x);
                    break;
        }
    }

    return isEqual(ans, deq);
}

bool popTest() {
    std::deque<long long> ans;
    sjtu::deque<long long> deq;

    randnumFill(ans, deq);

    for (int i = 0; i < MAX_N / 2; i++) {
        switch (randnum() % 2) {
            case 0: deq.pop_front(); ans.pop_front();
                    break;
            case 1: deq.pop_back();  ans.pop_back();
                    break;
        }
    }

    return isEqual(ans, deq);
}

bool insertTest() {
    std::deque<int> ans, ans2, ans3;
    sjtu::deque<int> deq, deq2, deq3;

    for (int i = 0; i < 100; i++) {
        int x = randnum();
        int pos = (ans.size() == 0 ? 0 : randnum() % ans.size());

        switch (randnum() % 2) {
            case 0: deq.insert(deq.begin() + pos, x);
                    ans.insert(ans.begin() + pos, x);
                    break;
            case 1: deq.insert(deq.end() - pos, x);
                    ans.insert(ans.end() - pos, x);
                    break;
        }
    }

    ans2.insert(ans2.begin(), 0x5d); ans3.insert(ans3.end(), 93);
    deq2.insert(deq2.begin(), 0x5d); deq3.insert(deq3.end(), 93);

    if (!isEqual(ans2, deq2) || !isEqual(ans3, deq3))
        return false;

    return isEqual(ans, deq);
}
bool iteratorTest() {
    std::deque<int> ans;
    sjtu::deque<int> deq;

    randnumFill(ans, deq);

    auto ansIter = ans.begin() + ans.size() / 2;
    auto myIter  = deq.begin() + deq.size() / 2;

    // iter++, iter--
    for (int i = 0; i < MAX_N; i++) {
        switch(randnum() % 2) {
            case 0: ansIter++; myIter++;
                    break;
            case 1: ansIter--; myIter--;
                    break;
        }

        if (*ansIter != *myIter)
            return false;
    }

    // iter += n,  iter -= n
    for (int i = 0; i < MAX_N; i++) {
        std::deque<int>::iterator ansIter[] = { ans.begin(), ans.end() };
        sjtu::deque<int>::iterator myIter[]  = { deq.begin(), deq.end() };

        int offset = randnum() % (ans.size() / 3) + 1;

        ansIter[0] += offset; ansIter[1] -= offset;
        myIter[0]  += offset; myIter[1]  -= offset;

        for (int j = 0; j < 2; j++)
            if (*ansIter[j] != *myIter[j])
                return false;

        if (ansIter[1] - ansIter[0] != myIter[1] - myIter[0])
            return false;
    }

    // iter +=n, iter -= n, iter += -n, iter -= -n
    int index = ans.size() / 2;
    ansIter = ans.begin() + index;
    myIter  = deq.begin() + index;
    for (int i = 0; i < MAX_N * 2; i++) {
        int offset = randnum() % (ans.size() / 2);
        switch (randnum() % 4) {
            case 0:  // iter += n
                if (index + offset < ans.size()) {
                    index += offset;
                    ansIter += offset; myIter += offset;
                }
                break;
            case 1: // iter -= n
                if (index - offset >= 0) {
                    index -= offset;
                    ansIter -= offset; myIter -= offset;
                }
                break;
            case 2:  // iter += -n
                if (index - offset >= 0) {
                    index += -offset;
                    ansIter += -offset; myIter += -offset;
                }
                break;
            case 3: // iter -= -n
                if (index + offset < ans.size()) {
                    index -= -offset;
                    ansIter -= -offset; myIter -= -offset;
                }
                break;
        }
        if (*ansIter != *myIter)
            return false;
        *ansIter = *myIter = randnum();
    }

    // traverse
    ansIter = ans.begin(); myIter = deq.begin();
    while (ansIter != ans.end()) {
        if (*ansIter++ != *myIter++)
            return false;
    }
    //  reversal traverse
    ansIter = ans.end() - 1; myIter = deq.end() - 1;
    while (ansIter != ans.begin()) {
        if (*ansIter-- != *myIter--)
            return false;
    }

    return *ansIter == *myIter;
}

bool eraseTest() {
    std::deque<int> ans;
    sjtu::deque<int> deq;

    randnumFill(ans, deq);

    for (int i = 0; i < 100; i++) {
        int pos = randnum() % ans.size();

        switch (randnum() % 2) {
            case 0: deq.erase(deq.begin() + pos);
                    ans.erase(ans.begin() + pos);
                    break;
            case 1: deq.erase(deq.end() - 1 - pos);
                    ans.erase(ans.end() - 1 - pos);
                    break;
        }
    }

    return isEqual(ans, deq);
}

int ansCounter = 0, myCounter = 0, noUseCounter = 0;
// you should construct and deconstruct this class correctly
class DynamicType {
public:
    int *pct;
    double *data;
    DynamicType (int *p) : pct(p) , data(new double[2]) {
        (*pct)++;
    }
    DynamicType (const DynamicType &other) : pct(other.pct), data(new double[2]) {
        (*pct)++;
    }
    DynamicType &operator =(const DynamicType &other) {
        if (this == &other) return *this;
        (*pct)--;
        pct = other.pct;
        (*pct)++;
        delete [] data;
        data = new double[2];
        return *this;
    }
    ~DynamicType() {
        delete [] data;
        (*pct)--;
    }
    bool operator != (const DynamicType &rhs) const { return false; }
};

bool copyAndClearTest() {
    // you should call the constructor and deconstructor correctly
    {
        std::deque<DynamicType> ans;
        sjtu::deque<DynamicType> deq, deq2 = deq, deq3(deq2);

        // empty copy and clear
        deq.clear(); deq2.clear();  deq3.clear();
        deq = deq = deq; deq2 = deq3; deq3 = deq = deq3 = deq2;

        for (int i = 0; i < MAX_N; i++) {
            ans.push_back(DynamicType(&ansCounter));
            deq.push_back(DynamicType(&myCounter));
        }
        if (myCounter != ansCounter) return false;

        deq = deq = deq = deq;
        if (myCounter != ansCounter) return false;

        deq = deq2 = deq2 = deq;
        if (myCounter != 2 * ansCounter) return false;
        if (!isEqual(deq, deq2)) return false;

        deq2 = deq = deq = deq2 = deq2 = deq3;
        if (myCounter != 0) return false;
        if (!isEqual(deq, deq2)) return false;

        for (int i = 0; i < MAX_N; i++)
            deq.push_back(DynamicType(&myCounter));

        deq2 = deq3 = deq;
        if (myCounter != 3 * ansCounter) return false;

        deq.clear();
        sjtu::deque<DynamicType> deq4(deq), deq5(deq2);
        if (myCounter != 3 * ansCounter) return false;
        if (isEqual(deq, deq2)) return false;
    }

    return myCounter == ansCounter;
}

bool memoryTest() {
    // you should call the constructor and deconstructor correctly
    std::deque<DynamicType> ans;
    sjtu::deque<DynamicType> deq;

    for (int i = 0; i < MAX_N; i++) {
        ans.push_back(DynamicType(&ansCounter));
        deq.push_back(DynamicType(&myCounter));
    }

    for (int i = 0; i < MAX_N / 10; i++) {
        int index = randnum() % ans.size();
        switch(randnum() % 6) {
            case 0: ans.push_back(DynamicType(&ansCounter));
                    deq.push_back(DynamicType(&myCounter));
                    break;
            case 1: ans.push_front(DynamicType(&ansCounter));
                    deq.push_front(DynamicType(&myCounter));
                    break;
            case 2: ans.pop_back(); deq.pop_back();
                    break;
            case 3: ans.pop_front(); deq.pop_front();
                    break;
            case 4: ans.insert(ans.begin() + index, DynamicType(&ansCounter));
                    deq.insert(deq.begin() + index, DynamicType(&myCounter));
                    break;
            case 5: ans.erase(ans.begin() + index);
                    deq.erase(deq.begin() + index);
                    break;
            default : break;
        }

        if (ansCounter != myCounter)
            return false;
    }

    return isEqual(ans, deq);
}

bool exceptionTest() {
    sjtu::deque<int> deq, deq2;
    int ct = 0;

    try { deq.front(); } catch (...) { ct++; }
    try { deq.back(); }  catch (...) { ct++; }
    try { deq[0]; }      catch (...) { ct++; }

    deq.push_back(1); deq.push_back(2);
    deq2.push_back(1); deq2.push_back(2);

    try { deq.end() - deq.begin(); }  catch (...) { ct--; }
    try { deq2.end() - deq.begin(); } catch (...) { ct++; }

    try { deq2[-1]; }    catch (...) { ct++; }
    try { deq2[2]; }     catch (...) { ct++; }
    try { deq2.at(-1); } catch (...) { ct++; }
    try { deq2.at(1); }  catch (...) { ct--; }

    return ct == 7;
}

template <typename T>
bool dfs(int deep, std::deque<T> ans, sjtu::deque<T> deq) {
    if (deep == 0)
        return true;

    int x = randnum();
    switch (randnum() % 5) {
        case 0: ans.insert(++ans.begin(), x);
                deq.insert(++deq.begin(), x);
                break;
        case 1: ans.erase(--ans.end());
                deq.erase(--deq.end());
                break;
        case 2: *(ans.begin() - (-5)) = x;
                *(deq.begin() - (-5)) = x;
                break;
        case 3: *(ans.end() + (-5)) = x;
                *(deq.end() + (-5)) = x;
                break;
    }

    if (isEqual(ans, deq) && ansCounter == myCounter)
        return dfs(deep / 2, ans, deq);
    else
        return false;
}

bool dfs2(int deep, std::deque<DynamicType> ans, sjtu::deque<DynamicType> deq) {
    if (deep == 0)
        return true;

    DynamicType tmp(&noUseCounter), tmp2(&noUseCounter);
    switch (randnum() % 6) {
        case 0: ans.insert(++ans.begin(), DynamicType(&ansCounter));
                deq.insert(++deq.begin(), DynamicType(&myCounter));
                break;
        case 1: ans.erase(--ans.end());
                deq.erase(--deq.end());
                break;
        case 2: *(ans.begin() - (-5)) = DynamicType(&ansCounter);
                *(deq.begin() - (-5)) = DynamicType(&myCounter);
                break;
        case 3: *(ans.end() + (-5)) = DynamicType(&ansCounter);
                *(deq.end() + (-5)) = DynamicType(&myCounter);
                break;
        case 4: {
                    int a = randnum() % ans.size(), b = randnum() % ans.size();
                    tmp = deq[a]; deq[a] = deq[b]; deq[b] = tmp;
                    tmp = ans[a]; ans[a] = ans[b]; ans[b] = tmp;
                    tmp = tmp2;
                }
                break;
        case 5: (*ans.begin()->pct)++;
                (*deq.begin()->pct)++;
                break;
    }

    if (isEqual(ans, deq) && ansCounter == myCounter)
        return dfs2(deep / 2, ans, deq);
    else
        return false;
}

bool nomercyTest() {
    // it is an easy test with bluffing name...
    ansCounter = myCounter = 0;
    {
        std::deque<int> ans;
        sjtu::deque<int> deq;
        randnumFill(ans, deq, 10000);
        if (!dfs(19960904, ans, deq))
            return false;

        std::deque<DynamicType> ans2;
        sjtu::deque<DynamicType> deq2;
        for (int i = 0; i < 10000; i++) {
            ans2.push_front(DynamicType(&ansCounter));
            deq2.push_front(DynamicType(&myCounter));
        }
        if (!dfs2(19960904, ans2, deq2))
            return false;
    }
    return ansCounter == myCounter;
}

int main() {
    bool (*testFunc[])()= {
        pushTest, popTest, insertTest, iteratorTest,
        eraseTest, copyAndClearTest, memoryTest,
        nomercyTest,
    };

    const char *testMessage[] = {
        "Testing push...", "Testing pop...", "Testing insert...", "Testing iterator...",
        "Testing erase...", "Testing copy and clear...", "Testing memory...",
        "Final test without mercy...",
    };

    bool error = false;
    for (int i = 0; i < sizeof(testFunc) / sizeof(testFunc[0]); i++) {
        printf("%-40s", testMessage[i]);
        if (testFunc[i]())
            printf("Passed\n");
        else {
            error = true;
            printf("Failed !!!\n");
        }
    }

    if (error)
        printf("\nUnfortunately, you failed in this test\n\a");
    else
        printf("\nCongratulations, your deque passed all the tests!\n");

    return 0;
}

