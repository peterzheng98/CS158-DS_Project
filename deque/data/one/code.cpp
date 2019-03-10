//Provided by desire2020/Steve Lu

/***********************************************************************
Hint: This test case almost completely tests the correctness of your deque.
So if all tests are passed, feel free to enhance your performance! :)
Yours Sincerely. Rabbit.
***********************************************************************/
#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include "deque.hpp"

long long randNum(long long x,long long maxNum)
{
	x = (x * 10007) % maxNum;
	return x + 1; 
} 
const size_t N = 10005LL;

void error()
{
	std::cout << "Error, mismatch found." << std::endl;
	exit(0);
}

void TestInteger()
{
	std::cout << "Test 1 : Test for classes without default constructor...";
	sjtu::deque<Integer> dInt;
	std::vector<Integer> vInt;
	for (int i = 0; i < N; ++i) {
		vInt.push_back(Integer(randNum(i, N + 17)));
		dInt.push_back(vInt[i]);
	}
	for (int i = 0; i < N; ++i) {
		if (!(vInt[i] == dInt[i]))
			error();
	}
	std::cout << "Correct." << std::endl;
}
void TestMatrix()
{
	std::cout << "Test 2 : Test for Matrix, a class with dynamic members...";
	sjtu::deque<Diamond::Matrix<double>> dM;
	std::vector<Diamond::Matrix<double>> vM;
	for (int i = 0; i < N; ++i) {
		vM.push_back(Diamond::Matrix<double>(randNum(i + 1, 10 + 7), randNum(i + 2, 10 + 7), randNum(i + 3, (100 + 17)) * 1.0 / randNum(i, 17)));
		dM.push_back(vM[i]);
	}
	for (int i = 0; i < N; ++i) {
		if (!(vM[i] == dM[i]))
			error();
	}
	std::cout << "Correct." << std::endl;
}

void TestBint()
{
	std::cout << "Test 3 : Test for big integer...";
	sjtu::deque<Util::Bint> dBint;
	std::vector<Util::Bint> vBint;
	for (long long i = 1LL << 50; i < (1LL << 50) + N; ++i) {
		vBint.push_back(Util::Bint(i) * randNum(i, (1 << 25) ));
		dBint.push_back(vBint.back());
	}
	
	for (int i = 0; i < N; ++i) {
		if (!(vBint[i] == dBint[i]))
			error();
	}
	std::cout << "Correct." << std::endl;
}

void TestCopyConstructorAndOperatorEqu()
{
	std::cout << "Test 4 : Test for copy constructor and operator=...";
	sjtu::deque<long long> *pInt;
	pInt = new sjtu::deque<long long>;
	for (long long i = 0; i < N; ++i) {
		pInt -> push_back(i);
	}
	sjtu::deque<long long> &dInt = *pInt;
	sjtu::deque<long long> dualInt(dInt);
	sjtu::deque<long long> dualInt_oper;
	dualInt_oper = dInt;
	for (long long i = 0; i < N; ++i)
	{
		if (dualInt[i] != dInt[i] || dualInt_oper[i] != dInt[i])
			error();
	}
	dualInt_oper = dualInt_oper;
	delete pInt;
	for (long long i = 0; i < N; ++i)
	{
		if (dualInt_oper[i] != dualInt[i])
			error();
	}
	std::cout << "Correct." << std::endl;
}

void TestIteratorSequenceAccess()
{
	std::cout << "Test 5 : Test for accessing the container in the order of the sequence, using iterator...";
	sjtu::deque<long long> dInt;
	for (long long i = 0; i < N; ++i) {
		dInt.push_back(i);
	}
	sjtu::deque<long long> :: iterator it;
	it = dInt.begin();
	for (long long i = 0; i < N; ++i) {
		if (!(*it == dInt[i]))
			error();
		++it;
	}
	if (it != dInt.end())
		error();
	std::cout << "Correct." << std::endl;
}

void TestIteratorRandomAccess()
{
	std::cout << "Test 6 : Test for accessing the container randomly, using iterator...";
	sjtu::deque<long long> dInt;
	std::vector<long long> vInt;
	for (long long i = 0; i < N; ++i) {
		dInt.push_back(i);
		vInt.push_back(i);
	}
	for (long long i = 0; i < N; ++i) {
		if (!(*(dInt.begin() + i) == vInt[i]))
			error();
	}
	std::cout << "Correct." << std::endl;
}

void TestInsertAndErase()
{
	std::cout << "Test 7 : Test for random erase and insert...";
	sjtu::deque<long long> dInt;
	std::vector<long long> vInt;
	for (long long i = 0; i < N; ++i) {
		dInt.push_back(i);
		vInt.push_back(i);
	}
	vInt.insert(vInt.begin() + 2, 2);
	dInt.insert(dInt.begin() + 2, 2);
	vInt.insert(vInt.begin() + 23, 23);
	dInt.insert(dInt.begin() + 23, 23);
	vInt.insert(vInt.begin() + 233, 233);
	dInt.insert(dInt.begin() + 233, 233);
	vInt.erase(vInt.begin() + 2333);
	dInt.erase(dInt.begin() + 2333);
	for (long long i = 0; i < N; ++i) {
		if (!(*(dInt.begin() + i) == vInt[i]))
			error();
	}
	std::cout << "Correct." << std::endl;
}

void TestPopAndPush()
{
	std::cout << "Test 8 : Test for pop() and push()...";
	sjtu::deque<long long> dInt, drInt;
	std::vector<long long> vInt;
	std::vector<long long> rInt;
	for (size_t i = 0; i < 1114LL; ++i)
	{
		dInt.push_back(i);
		vInt.push_back(i);
	}
	for (size_t i = 0; i < 107LL; ++i)
	{
		dInt.pop_back();
		vInt.pop_back();
	}
	for (size_t i = 0; i < 1114LL; ++i)
	{
		drInt.push_front(i);
		rInt.push_back(i);
	}
	for (size_t i = 0; i < 107LL; ++i)
	{
		drInt.pop_front();
		rInt.pop_back();
	}
	for (size_t i = 0; i < 1007LL; ++i)
	{
		if (!(dInt[i] == vInt[i]))
			error();
		if (!(drInt[1006LL - i] == rInt[i]))
			error();
	}
	
	std::cout << "Correct." << std::endl;
	
}

int main()
{
	TestInteger();
	TestMatrix();
	TestBint();
	TestCopyConstructorAndOperatorEqu();
	TestIteratorSequenceAccess();
	TestIteratorRandomAccess();
	TestInsertAndErase();
	TestPopAndPush();
	std::cout << "Congratulations. Your submission has passed all correctness tests. Use valgrind to ensure that there ain't any memory leaks in your deque. Good job! :)" << std::endl;
	return 0;
}