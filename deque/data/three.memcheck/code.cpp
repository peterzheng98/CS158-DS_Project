#include "deque.hpp"

#include <ctime>
#include <iostream>
#include <deque>
#include <random>
#include <string>
#include <vector>
#include <ctime>

//std::default_random_engine randnum(time(NULL));

static const int N = 10000;
static const int N_SPEED = 33500;

typedef std::pair<const char *, std::pair<bool, double> (*)()> CheckerPair;

class Int{
private:
	int data;

public:
	Int() = default;
	Int(const int &data) : data(data) {}
	Int & operator =(const Int &rhs) = default;
	bool operator <(const Int &rhs) = delete;
	bool operator >(const Int &rhs) = delete;
	bool operator <=(const Int &rhs) = delete;
	bool operator >=(const Int &rhs) = delete;
	bool operator ==(const Int &rhs)const {
		return data == rhs.data;
	}
	bool operator !=(const Int &rhs)const {
		return data != rhs.data;
	}

};

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

class Timer{
private:
	long dfnStart, dfnEnd;

public:
	void init() {
		dfnEnd = dfnStart = clock();
	}
	void stop() {
		dfnEnd = clock();
	}
	double getTime() {
		return 1.0 * (dfnEnd - dfnStart) / CLOCKS_PER_SEC;
	}

};

Timer timer;

bool isEqual(std::deque<Int> &a, sjtu::deque<Int> &b) {
	static std::vector<Int> resultA, resultB;
	resultA.clear();
	resultB.clear();
	for (auto x : a) resultA.push_back(x);
	for (auto x : b) resultB.push_back(x);
	if (resultA.size() != resultB.size()) return false;
	for (int i = 0; i < (int)resultA.size(); i++) {
		if (resultA[i] != resultB[i]) return false;
	}
	return true;
}

std::pair<bool, double> pushBackChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> pushFrontChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_front(tmp);
		b.push_front(tmp);
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> insertChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> popBackChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		a.pop_back();
		b.pop_back();
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> popFrontChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		a.pop_front();
		b.pop_front();
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> eraseChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (b.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		int pos = rand() % b.size();
		a.erase(a.begin() + pos);
		b.erase(b.begin() + pos);
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> atChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		if (a.at(i) != b.at(i)) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> constAtChecker() {
	std::deque<Int> basea;
	sjtu::deque<Int> baseb;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (basea.size() + 1);
		int tmp = rand();
		basea.push_back(tmp);
		baseb.push_back(tmp);
	}
	const std::deque<Int> a(basea);
	const sjtu::deque<Int> b(baseb);
	timer.init();
	for (int i = 0; i < N; i++) {
		if (a.at(i) != b.at(i)) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> bracketChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> constBracketChecker() {
	std::deque<Int> basea;
	sjtu::deque<Int> baseb;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (basea.size() + 1);
		int tmp = rand();
		basea.push_back(tmp);
		baseb.push_back(tmp);
	}
	const std::deque<Int> a(basea);
	const sjtu::deque<Int> b(baseb);
	timer.init();
	for (int i = 0; i < N; i++) {
		if (a[i] != b[i]) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> frontChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
		if (a.front() != b.front()) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> backChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
		if (a.back() != b.back()) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorAddNChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		if (*(a.begin() + i) != *(b.begin() + i)) {
			return std::make_pair(false, 0);
		}
		int tmp = rand();
		*(a.begin() + i) = tmp;
		*(b.begin() + i) = tmp;
	}
	for (int i = 1; i <= N; i++) {
		if (*(a.end() + (-i)) != *(b.end() + (-i))) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorRedNChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	for (int i = 1; i <= N; i++) {
		int pos = rand() % (a.size());
		int tmp = rand();
		if (*(a.end() - i) != *(b.end() - i)) {
			return std::make_pair(false, 0);
		}
		*(a.end() - i) = tmp;
		*(b.end() - i) = tmp;
	}
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size());
		if (*(a.begin() - (-i)) != *(b.begin() - (-i))) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorAddENChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() += pos, tmp);
		b.insert(b.begin() += pos, tmp);
	}
	timer.init();
	for (int i = 0; i < N; i++) {
		if (*(a.begin() += i) != *(b.begin() += i)) {
			return std::make_pair(false, 0);
		}
		int tmp = rand();
		*(a.begin() + i) = tmp;
		*(b.begin() + i) = tmp;
	}
	for (int i = 1; i <= N; i++) {
		if (*(a.end() += (-i)) != *(b.end() += (-i))) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorRedENChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() += pos, tmp);
		b.insert(b.begin() += pos, tmp);
	}
	timer.init();
	for (int i = 1; i <= N; i++) {
		int pos = rand() % (a.size());	
		if (*(a.end() -= i) != *(b.end() -= i)) {
			return std::make_pair(false, 0);
		}
		int tmp = rand();
		*(a.end() - i) = tmp;
		*(b.end() - i) = tmp;
	}
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size());
		if (*(a.begin() -= (-i)) != *(b.begin() -= (-i))) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorPAddOneChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	auto itB = b.begin(), tB = itB;
	for (auto itA = a.begin(), tA = itA; itA != a.end(); tA = ++itA, tB = ++itB) {
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
		if (tB != b.end() && *tA != *tB) {
			return std::make_pair(false, 0);
		}
		*tA = *tB = rand();
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorPRedOneChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	auto itB = --b.end(), tB = itB;
	for (auto itA = --a.end(), tA = itA; ; tA = --itA, tB = --itB) {
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
		if (tB != b.end() && *tA != *tB) {
			return std::make_pair(false, 0);
		}
		*tA = *tB = rand();
		if (itA == a.begin()) break;
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorSAddOneChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	auto itB = b.begin(), tB = itB;
	for (auto itA = a.begin(), tA = itA; itA != a.end(); tA = itA++, tB = itB++) {
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
		if (tB != b.end() && *tA != *tB) {
			return std::make_pair(false, 0);
		}
		*tA = *tB = rand();
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorSRedOneChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.insert(a.begin() + pos, tmp);
		b.insert(b.begin() + pos, tmp);
	}
	timer.init();
	auto itB = b.end(), tB = itB;
	auto itA = a.end(), tA = itA;
	tB = itB--;
	tA = itA--;
	for (; ; tA = itA--, tB = itB--) {
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
		if (tB != b.end() && *tA != *tB) {
			return std::make_pair(false, 0);
		}
		*itA = *itB = rand();
		if (itA == a.begin()) break;
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorMinusOperatorChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.init();
	auto itA1 = a.begin(), itA2 = a.begin();
	auto itB1 = b.begin(), itB2 = b.begin();
	int tmp1 = rand() % (a.size() + 1), tmp2 = rand() % (a.size() + 1);
	for (int i = 0; i < tmp1; i++) itA1++, itB1++;
	for (int i = 0; i < tmp2; i++) itA2++, itB2++;
	if (itA2 - itA1 != itB2 - itB1) {
		return std::make_pair(false, 0);
	}
	if (a.end() - a.begin() != b.end() - b.begin()) {
		return std::make_pair(false, 0);
	}
	if (itB1 + (itB2 - itB1) != itB2) {
		return std::make_pair(false, 0);
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> errorBracketChecker() {
	sjtu::deque<Int> a;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
	}
	int successCounter = 0;
	timer.init();
	try{
		a[a.size()] = 0;
	} catch(...) {
		successCounter++;
	}
	try{
		a[-1] = 0;
	} catch(...) {
		successCounter++;
	}
	timer.stop();
	if (successCounter == 2) {
		return std::make_pair(true, timer.getTime());
	} else {
		return std::make_pair(false, 0);
	}
}

std::pair<bool, double> errorAtChecker() {
	sjtu::deque<Int> a;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
	}
	int successCounter = 0;
	timer.init();
	try{
		a.at(a.size()) = 0;
	} catch(...) {
		successCounter++;
	}
	try{
		a.at(-1) = 0;
	} catch(...) {
		successCounter++;
	}
	timer.stop();
	if (successCounter == 2) {
		return std::make_pair(true, timer.getTime());
	} else {
		return std::make_pair(false, 0);
	}
}

std::pair<bool, double> errorIteratorChecker() {
	sjtu::deque<Int> a;
	for (int i = 0; i < N; i++) {
		int pos = rand() % (a.size() + 1);
		int tmp = rand();
		a.push_back(tmp);
	}
	int successCounter = 0;
	timer.init();
	try{
		*a.end() = 0;
	} catch(...) {
		successCounter++;
	}
	try{
		*--a.begin();
	} catch(...) {
		successCounter++;
	}
	try{
		*++a.end();
	} catch(...) {
		successCounter++;
	}
	timer.stop();
	if (successCounter == 3) {
		return std::make_pair(true, timer.getTime());
	} else {
		return std::make_pair(false, 0);
	}
	
}

std::pair<bool, double> errorInsertChecker() {
	sjtu::deque<Int> a, b;
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
	}
	int successCounter = 0;
	timer.init();
	try{
		b.insert(a.begin(), 0);
	} catch(...) {
		successCounter++;
	}
	try{
		b.insert(a.end(), 0);
	} catch(...) {
		successCounter++;
	}
	try{
		b.insert(a.begin() + N / 2, 0);
	} catch(...) {
		successCounter++;
	}
	timer.stop();
	if (successCounter == 3) {
		return std::make_pair(true, timer.getTime());
	} else {
		return std::make_pair(false, 0);
	}
}

std::pair<bool, double> errorEraseChecker() {
	sjtu::deque<Int> a, b;
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
	}
	int successCounter = 0;
	timer.init();
	try{
		b.erase(a.begin());
	} catch(...) {
		successCounter++;
	}
	try{
		b.erase(a.end());
	} catch(...) {
		successCounter++;
	}
	try{
		b.erase(a.begin() + N / 2);
	} catch(...) {
		successCounter++;
	}
	try{
		b.erase(b.end());
	} catch(...) {
		successCounter++;
	}
	timer.stop();
	if (successCounter == 4) {
		return std::make_pair(true, timer.getTime());
	} else {
		return std::make_pair(false, 0);
	}
}

std::pair<bool, double> sizeChecker() {
	sjtu::deque<Int> a;
	std::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
		if (a.size() != b.size()) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> emptyChecker() {
	sjtu::deque<Int> a;
	std::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		if (a.empty() != b.empty()) {
			return std::make_pair(false, 0);
		}
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> copyConstructorChecker() {
	std::deque<DynamicType> a;
	sjtu::deque<DynamicType> b;
	timer.init();
	int stdCounter = 0;
	int srcCounter = 0;
	for (int i = 0; i < N; i++) {
		a.push_back(DynamicType(&stdCounter));
		b.push_back(DynamicType(&srcCounter));
	}
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	std::deque<DynamicType> tmpA(a);
	sjtu::deque<DynamicType> tmpB(b);
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	a.clear();
	b.clear();
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	a = tmpA = tmpA = a;
	b = tmpB = tmpB = b;
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	a.clear();
	b.clear();
	tmpA.clear();
	tmpB.clear();
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> equalOperatorChecker() {
	std::deque<DynamicType> a;
	sjtu::deque<DynamicType> b;
	timer.init();
	int stdCounter = 0;
	int srcCounter = 0;
	for (int i = 0; i < N; i++) {
		a.push_back(DynamicType(&stdCounter));
		b.push_back(DynamicType(&srcCounter));
	}
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	std::deque<DynamicType> tmpA;
	sjtu::deque<DynamicType> tmpB;
	a = tmpA = tmpA = a = tmpA = a = a = a = a;
	b = tmpB = tmpB = b = tmpB = b = b = b = b;
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	a.clear();
	b.clear();
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	tmpA.clear();
	tmpB.clear();
	if (stdCounter != srcCounter) {
		return std::make_pair(false, 0);
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> memoryLeakChecker() {
	sjtu::deque<DynamicType> *a = new sjtu::deque<DynamicType>;
	int srcCounter = 0;
	timer.init();
	for (int i = 0; i < N; i++) {
		a -> push_back(DynamicType(&srcCounter));
		a -> insert(a -> begin() + rand() % (a -> size() + 1), DynamicType(&srcCounter));
		a -> push_front(DynamicType(&srcCounter));
	}
	a -> clear();
	if (srcCounter != 0) {
		return std::make_pair(false, 0);
	}
	for (int i = 0; i < N; i++) {
		a -> push_back(DynamicType(&srcCounter));
		a -> insert(a -> begin() + rand() % (a -> size() + 1), DynamicType(&srcCounter));
		a -> push_front(DynamicType(&srcCounter));
	}
	for (int i = 0; i < 3 * N; i++) {
		a -> pop_front();
	}
	if (srcCounter != 0) {
		return std::make_pair(false, 0);
	}
	for (int i = 0; i < N; i++) {
		a -> push_back(DynamicType(&srcCounter));
		a -> insert(a -> begin() + rand() % (a -> size() + 1), DynamicType(&srcCounter));
		a -> push_front(DynamicType(&srcCounter));
	}
	delete a;
	if (srcCounter != 0) {
		return std::make_pair(false, 0);
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> synthesisChecker() {
	std::deque<Int> a, tA(a), ttA(tA);
	sjtu::deque<Int> b, tB(b), ttB(tB);

	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = 0;
		a.push_back(tmp);
		b.push_back(tmp);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = ttA; tB = ttB;
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = a = a; tB = b = b;
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	a.clear();
	b.clear();
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = a = tA = tA;
	tB = b = tB = tB;
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	}

	const std::deque<Int> cA = a;
	const sjtu::deque<Int> cB = b;

	std::deque<Int>::iterator itA;
	sjtu::deque<Int>::iterator itB;
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		itA = a.insert(itA, tmp);
		itB = b.insert(itB, tmp);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
	}
	tA = a = a = a;
	tB = b = b = b;
	a.clear();
	b.clear();
	ttA = a = a = a;
	ttB = b = b = b;
	std::deque<Int> tttA(tA);
	sjtu::deque<Int> tttB(tB);
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(ttA, ttB)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(tttA, tttB)) {
		return std::make_pair(false, 0);
	}

	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (itA == a.end()) {
			itA--;
			itB--;
		}
		itA = a.erase(itA);
		itB = b.erase(itB);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
	}
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(ttA, ttB)) {
		return std::make_pair(false, 0);
	}

	auto citA = cA.cbegin();
	auto citB = cB.cbegin();
	for (; citA != cA.end(); citA++, citB) {
		if (*citA != *citB) {
			return std::make_pair(false, 0);
		}
	}

	ttA.clear();
	ttB.clear();
	a.clear();
	b.clear();
	ttA.clear();
	ttB.clear();

	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorInsertPersistenceChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	std::deque<Int>::iterator itA;
	sjtu::deque<Int>::iterator itB;
	itA = a.end();
	itB = b.end();
	timer.init();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		itA = a.insert(itA, tmp);
		itB = b.insert(itB, tmp);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (*itA != *itB) {
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

std::pair<bool, double> iteratorErasePersistenceChecker() {
	std::deque<Int> a;
	sjtu::deque<Int> b;
	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	std::deque<Int>::iterator itA;
	sjtu::deque<Int>::iterator itB;
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			printf("Part 1: %d\n", i);
			return std::make_pair(false, 0);
		}
		if (itA == a.end()) {
			itA--;
			itB--;
		}
		itA = a.erase(itA);
		itB = b.erase(itB);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			printf("Part 2: %d\n", i);
			return std::make_pair(false, 0);
		}
	}
	timer.stop();
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	} else {
		return std::make_pair(true, timer.getTime());
	}
}

static CheckerPair TEST_A[] = {
	std::make_pair("Push Series -> push_back operation testing...", pushBackChecker),
	std::make_pair("Push Series -> push_front operation testing...", pushFrontChecker),
	std::make_pair("Pop Series -> pop_back operation testing...", popBackChecker),
	std::make_pair("Pop Series -> pop_front operation testing...", popFrontChecker),
	std::make_pair("Push Series -> insert operation testing...", insertChecker),
	std::make_pair("Pop Series -> erase operation testing...", eraseChecker),
	std::make_pair("Visitation Series -> at operation testing...", atChecker),
	std::make_pair("Visitation Series -> constantly at operation testing...", constAtChecker),
	std::make_pair("Visitation Series -> [] operator testing...", bracketChecker),
	std::make_pair("Visitation Series -> constantly [] operator testing...", constBracketChecker),
	std::make_pair("Visitation Series -> front operation testing...", frontChecker),
	std::make_pair("Visitation Series -> back operator testing...", backChecker),
	std::make_pair("Iterator Series -> +n operator testing...", iteratorAddNChecker),
	std::make_pair("Iterator Series -> -n operator testing...", iteratorRedNChecker),
	std::make_pair("Iterator Series -> +=n operator testing...", iteratorAddENChecker),
	std::make_pair("Iterator Series -> -=n operator testing...", iteratorRedENChecker),
	std::make_pair("Iterator Serise: Prefix ++ operator testing...", iteratorPAddOneChecker),
	std::make_pair("Iterator Series -> Prefix -- operator testing...", iteratorPRedOneChecker),
	std::make_pair("Iterator Series -> Suffix ++ operator testing...", iteratorSAddOneChecker),
	std::make_pair("Iterator Series -> Suffix -- operator testing...", iteratorSRedOneChecker),
	std::make_pair("Iterator Series -> - operator testing...", iteratorMinusOperatorChecker),
	std::make_pair("Iterator Series -> Iterator insert persistence testing...", iteratorInsertPersistenceChecker),
	std::make_pair("Iterator Series -> Iterator erase persistence testing...", iteratorErasePersistenceChecker),
	std::make_pair("Robustness Series -> Invalid visitation by []...", errorBracketChecker),
	std::make_pair("Robustness Series -> Invalid visitation by at...", errorAtChecker),
	std::make_pair("Robustness Series -> Invalid visitation by iterator...", errorIteratorChecker),
	std::make_pair("Robustness Series -> Invalid insert operation...", errorInsertChecker),
	std::make_pair("Robustness Series -> Invalid erase operation...", errorEraseChecker),
	std::make_pair("Basic Series -> size function testing...", sizeChecker),
	std::make_pair("Basic Series -> empty function testing...", emptyChecker),
	std::make_pair("Independence Series -> Copy constructor testing...", copyConstructorChecker),
	std::make_pair("Independence Series -> Operator = testing...", equalOperatorChecker),
	std::make_pair("Memory Series -> Memory leak testing...", memoryLeakChecker),
	std::make_pair("Synthesis Series -> Comprehensive testing...", synthesisChecker)
};

std::pair<bool, double> pushBackTimer() {
	sjtu::deque<int> a;
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.push_back(rand());
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> popBackTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.pop_back();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> pushFrontTimer() {
	sjtu::deque<int> a;
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.push_front(rand());
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> popFrontTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.pop_front();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> frontTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.front();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> backTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.back();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> beginTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.begin();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> endTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.end();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorAddOneTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	auto itA = a.begin();
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		itA++;
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorRedOneTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	auto itA = a.end();
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		itA--;
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorAddNTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	auto itA = a.begin();
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		itA = a.begin() + i;
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> iteratorRedNTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	auto itA = a.end();
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		itA = a.end() - i;
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> insertTimer() {
	sjtu::deque<int> a;
	timer.init();
	auto itA = a.begin();
	for (int i = 0; i < N_SPEED; i++) {
		a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> eraseTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.erase(a.begin() + (rand() % a.size()));
	}
	timer.stop();
	return std::make_pair(true, timer.getTime());
}

std::pair<bool, double> copyConstructorTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	sjtu::deque<int> b(a), c(b), d(c);
	timer.stop();
	return std::make_pair(true, timer.getTime() / 3);
}

std::pair<bool, double> equalOperatorTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	sjtu::deque<int> b, c, d;
	b = a;
	c = b;
	d = c;
	timer.stop();
	return std::make_pair(true, timer.getTime() / 3);
}

std::pair<bool, double> atTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a.at(i) = rand();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime() / 3);
}

std::pair<bool, double> bracketTimer() {
	sjtu::deque<int> a;
	for (int i = 0; i < N_SPEED; i++) {
		int op = rand() % 3;
		if (op == 0) a.push_back(rand());
		else if (op == 1) a.push_front(rand());
		else if (op == 2) a.insert(a.begin() + rand() % (a.size() + 1), rand());
	}
	timer.init();
	for (int i = 0; i < N_SPEED; i++) {
		a[i] = rand();
	}
	timer.stop();
	return std::make_pair(true, timer.getTime() / 3);
}

static CheckerPair TEST_B[] = {
	std::make_pair("push_back", pushBackTimer),
	std::make_pair("pop_back", popBackTimer),
	std::make_pair("push_front", pushFrontTimer),
	std::make_pair("pop_front", popFrontTimer),
	std::make_pair("front", frontTimer),
	std::make_pair("back", backTimer),
	std::make_pair("begin", beginTimer),
	std::make_pair("end", endTimer),
	std::make_pair("at", atTimer),
	std::make_pair("[]", bracketTimer),
	std::make_pair("iterator ++", iteratorAddOneTimer),
	std::make_pair("iterator --", iteratorRedOneTimer),
	std::make_pair("iterator +n", iteratorAddNTimer),
	std::make_pair("iterator -n", iteratorRedNTimer),
	std::make_pair("insert", insertTimer),
	std::make_pair("erase", eraseTimer),
	std::make_pair("Copy Constructor", copyConstructorTimer),
	std::make_pair("Equal Operator", equalOperatorTimer),
};

#define __CORRECT_TEST
#define __OFFICAL

int main() {
#ifndef __OFFICAL
	puts("Deque CheckTool Package Version 1.5");
	puts("PAY SPECIAL ATTENTION: We assume your iterator is correct!!!");
#else
	puts("Deque CheckTool Package Version 1.5 Offical Version");
#endif
	puts("");
#ifdef __CORRECT_TEST
	puts("---------------------------------------------------------------------------");
	try{
		puts("Test Zone A: Correctness Testing...");
		int n = sizeof(TEST_A) / sizeof(CheckerPair);
		for (int i = 0; i < n; i++) {
			printf("Test %d: %-59s", i + 1, TEST_A[i].first);
			std::pair<bool, double> result = TEST_A[i].second();
			if (result.first) {
				puts("PASSED");
			} else {
				puts("FAILED");
			}
		}
	} catch(...) {
		puts("Unknown Error Occured");
	}
	puts("---------------------------------------------------------------------------");
#ifdef __SPEED_TEST
	puts("");
#endif
#endif

#ifdef __SPEED_TEST
	puts("---------------------------------------------------------------------------");
	try{
		puts("Test Zone B: Operation speed individually Testing...");
		printf("Test Size: %d Element(s)\n", N_SPEED);
		Timer global;
		global.init();
		int n = sizeof(TEST_B) / sizeof(CheckerPair);
		for (int i = 0; i < n; i++) {
			printf("Test %d: %-59s", i + 1, TEST_B[i].first);
			std::pair<bool, double> result = TEST_B[i].second();
#ifndef __OFFICAL
			printf("%.2f\n", result.second);
#else
			puts("PASSED");
#endif
		}
		global.stop();
#ifndef __OFFICAL
		printf("Total usage: %.2fs\n", global.getTime());
#else
#ifdef __DEBUG
		printf("Total usage: %.2fs\n", global.getTime());
#endif
#endif
	} catch(...) {
		puts("Unknown Error Occured");
	}
	puts("---------------------------------------------------------------------------");
#endif
    return 0;
}
