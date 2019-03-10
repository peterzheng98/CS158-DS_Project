#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stdexcept>

namespace Util {

const size_t MIN_CAPACITY = 2048;

class Bint {
	class NewSpaceFailed : public std::runtime_error {
	public:
		NewSpaceFailed();
	};
	class BadCast : public std::invalid_argument {
	public:
		BadCast();
	};
	bool isMinus = false;
	size_t length;
	int *data = nullptr;
	size_t capacity = MIN_CAPACITY;
	void _DoubleSpace();
	void _SafeNewSpace(int *&p, const size_t &len);
	explicit Bint(const size_t &capa);
public:
	Bint();
	Bint(int x);
	Bint(long long x);
	Bint(std::string x);
	Bint(const Bint &b);
	Bint(Bint &&b) noexcept;

	Bint &operator=(int rhs);
	Bint &operator=(long long rhs);
	Bint &operator=(const Bint &rhs);
	Bint &operator=(Bint &&rhs) noexcept;

	friend Bint abs(const Bint &x);
	friend Bint abs(Bint &&x);

	friend bool operator==(const Bint &lhs, const Bint &rhs);
	friend bool operator!=(const Bint &lhs, const Bint &rhs);
	friend bool operator<(const Bint &lhs, const Bint &rhs);
	friend bool operator>(const Bint &lhs, const Bint &rhs);
	friend bool operator<=(const Bint &lhs, const Bint &rhs);
	friend bool operator>=(const Bint &lhs, const Bint &rhs);

	friend Bint operator+(const Bint &lhs, const Bint &rhs);
	friend Bint operator-(const Bint &b);
	friend Bint operator-(Bint &&b);
	friend Bint operator-(const Bint &lhs, const Bint &rhs);
	friend Bint operator*(const Bint &lhs, const Bint &rhs);

	friend std::istream &operator>>(std::istream &is, Bint &b);
	friend std::ostream &operator<<(std::ostream &os, const Bint &b);

	~Bint();
};
}

#include <iomanip>
#include <algorithm>

namespace Util {

Bint::NewSpaceFailed::NewSpaceFailed() : std::runtime_error("No Enough Memory Space.") {}
Bint::BadCast::BadCast() : std::invalid_argument("Cannot convert to a Bint object") {}

void Bint::_SafeNewSpace(int *&p, const size_t &len)
{
	if (p != nullptr) {
		delete[] p;
		p = nullptr;
	}
	p = new int[len];
	if (p == nullptr) {
		throw NewSpaceFailed();
	}
	memset(p, 0, len * sizeof(unsigned int));
}

void Bint::_DoubleSpace()
{
	int *newMem = nullptr;
	_SafeNewSpace(newMem, capacity << 1);
	memcpy(newMem, data, capacity * sizeof(int));
	delete[] data;
	data = newMem;
	capacity <<= 1;
}

Bint::Bint()
	: length(1)
{
	_SafeNewSpace(data, capacity);
}

Bint::Bint(int x)
	: length(0)
{
	_SafeNewSpace(data, capacity);
	if (x < 0) {
		isMinus = true;
		x = -x;
	}
	while (x) {
		data[length++] = x % 10000;
		x /= 10000;
	}
	if (!length) {
		length = 1;
	}
}

Bint::Bint(long long x)
	: length(0)
{
	_SafeNewSpace(data, capacity);
	if (x < 0) {
		isMinus = true;
		x = -x;
	}
	while (x) {
		data[length++] = static_cast<unsigned int>(x % 10000);
		x /= 10000;
	}
	if (!length) {
		length = 1;
	}
}

Bint::Bint(const size_t &capa)
	: length(1)
{
	while (capacity < capa) {
		capacity <<= 1;
	}
	_SafeNewSpace(data, capacity);
}

Bint::Bint(std::string x)
{
	while (x[0] == '-') {
		isMinus = !isMinus;
		x.erase(0, 1);
	}
	while ((capacity << 2) <= x.length()) {
		capacity <<= 1;
	}

	_SafeNewSpace(data, capacity);

	size_t mid = x.length() >> 1;
	for (size_t i = 0; i < mid; ++i) {
		std::swap(x[i], x[x.length() - 1 - i]);
	}

	const static unsigned int pow10[4] = {1, 10, 100, 1000};
	for (size_t i = 0; i < capacity; ++i) {
		if ((i << 2) >= x.length()) {
			length = i;
			break;
		}
		for (size_t j = 0; j < 4; ++j) {
			if ((i << 2) + j >= x.length()) {
				break;
			}
			if (x[(i << 2) + j] > '9' || x[(i << 2) + j] < '0') {
				throw BadCast();
			}
			data[i] = data[i] + (x[(i << 2) + j] - '0') * pow10[j];
		}
	}
}

Bint::Bint(const Bint &b)
	: isMinus(b.isMinus), length(b.length), capacity(b.capacity)
{
	_SafeNewSpace(data, capacity);
	memcpy(data, b.data, sizeof(unsigned int) * capacity);
}

Bint::Bint(Bint &&b) noexcept
	: isMinus(b.isMinus), length(b.length), capacity(b.capacity)
{
	data = b.data;
	b.data = nullptr;
}

Bint &Bint::operator=(int x)
{
	memset(data, 0, sizeof(unsigned int) * capacity);
	length = 0;
	if (x < 0) {
		isMinus = true;
		x = -x;
	}
	while (x) {
		data[length++] = x % 10000;
		x /= 10000;
	}
	if (!length) {
		length = 1;
	}
	return *this;
}

Bint &Bint::operator=(long long x)
{
	memset(data, 0, sizeof(unsigned int) * capacity);
	length = 0;
	if (x < 0) {
		isMinus = true;
		x = -x;
	}
	while (x) {
		data[length++] = static_cast<unsigned int>(x % 10000);
		x /= 10000;
	}
	if (!length) {
		length = 1;
	}
	return *this;
}

Bint &Bint::operator=(const Bint &rhs)
{
	if (this == &rhs) {
		return *this;
	}
	if (rhs.capacity > capacity) {
		capacity = rhs.capacity;
		_SafeNewSpace(data, capacity);
	}
	memcpy(data, rhs.data, sizeof(unsigned int) * rhs.capacity);
	length = rhs.length;
	isMinus = rhs.isMinus;
	return *this;
}

Bint &Bint::operator=(Bint &&rhs) noexcept
{
	if (this == &rhs) {
		return *this;
	}
	capacity = rhs.capacity;
	length = rhs.length;
	isMinus = rhs.isMinus;
	data = rhs.data;
	rhs.data = nullptr;
	return *this;
}

std::istream &operator>>(std::istream &is, Bint &b)
{
	std::string s;
	is >> s;
	b = Bint(s);
	return is;
}

std::ostream &operator<<(std::ostream &os, const Bint &b)
{
	if (b.data == nullptr) {
		return os;
	}
	if (b.isMinus && (b.length > 1 || b.data[0] != 0)) {
		os << "-";
	}
	os << b.data[b.length - 1];
	for (long long i = b.length - 2LL; i >= 0; --i) {
		os << std::setw(4) << std::setfill('0') << b.data[i];
	}
	return os;
}

Bint abs(const Bint &b)
{
	Bint result(b);
	result.isMinus = false;
	return result;
}

Bint abs(Bint &&b)
{
	b.isMinus = false;
	return b;
}

bool operator==(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus != rhs.isMinus) {
		return false;
	}
	if (lhs.length != rhs.length) {
		return false;
	}
	for (size_t i = 0; i < lhs.length; ++i) {
		if (lhs.data[i] != rhs.data[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus != rhs.isMinus) {
		return true;
	}
	if (lhs.length != rhs.length) {
		return true;
	}
	for (size_t i = 0; i < lhs.length; ++i) {
		if (lhs.data[i] != rhs.data[i]) {
			return true;
		}
	}
	return false;
}

bool operator<(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus != rhs.isMinus) {
		return !lhs.isMinus;
	}
	if (lhs.isMinus) {
		if (lhs.length != rhs.length) {
			return lhs.length > rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] > rhs.data[i];
			}
		}
		return false;
	} else {
		if (lhs.length != rhs.length) {
			return lhs.length < rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] < rhs.data[i];
			}
		}
		return false;
	}
}

bool operator>(const Bint &lhs, const Bint &rhs)
{
	return rhs < lhs;
}

bool operator<=(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus != rhs.isMinus) {
		return !lhs.isMinus;
	}
	if (lhs.isMinus) {
		if (lhs.length != rhs.length) {
			return lhs.length > rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] > rhs.data[i];
			}
		}
		return true;
	} else {
		if (lhs.length != rhs.length) {
			return lhs.length < rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] < rhs.data[i];
			}
		}
		return true;
	}
}

bool operator>=(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus != rhs.isMinus) {
		return lhs.isMinus;
	}
	if (lhs.isMinus) {
		if (lhs.length != rhs.length) {
			return lhs.length < rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] < rhs.data[i];
			}
		}
		return true;
	} else {
		if (lhs.length != rhs.length) {
			return lhs.length > rhs.length;
		}
		for (long long i = lhs.length - 1; i >= 0; --i) {
			if (lhs.data[i] != rhs.data[i]) {
				return lhs.data[i] > rhs.data[i];
			}
		}
		return true;
	}
}


Bint operator+(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus == rhs.isMinus) {
		size_t maxLen = std::max(lhs.length, rhs.length);
		size_t expectLen = maxLen + 1;
		Bint result(expectLen); // special constructor
		for (size_t i = 0; i < maxLen; ++i) {
			result.data[i] = lhs.data[i] + rhs.data[i];
		}
		for (size_t i = 0; i < maxLen; ++i) {
			if (result.data[i] > 10000) {
				result.data[i] -= 10000;
				++result.data[i + 1];
			}
		}
		result.length = result.data[maxLen] > 0 ? maxLen + 1 : maxLen;
		result.isMinus = lhs.isMinus;
		return result;
	} else {
		if (lhs.isMinus) {
			return rhs - abs(lhs);
		} else {
			return lhs - abs(rhs);
		}
	}
}

Bint operator-(const Bint &b)
{
	Bint result(b);
	result.isMinus = !result.isMinus;
	return result;
}

Bint operator-(Bint &&b)
{
	b.isMinus = !b.isMinus;
	return b;
}

Bint operator-(const Bint &lhs, const Bint &rhs)
{
	if (lhs.isMinus == rhs.isMinus) {
		if (lhs.isMinus) {
			return -(abs(lhs) - abs(rhs));
		} else {
			if (lhs < rhs) {
				return -(rhs - lhs);
			}
			Bint result(std::max(lhs.length, rhs.length));
			for (size_t i = 0; i < lhs.length; ++i) {
				result.data[i] = lhs.data[i] - rhs.data[i];
			}
			for (size_t i = 0; i < lhs.length; ++i) {
				if (result.data[i] < 0) {
					result.data[i] += 10000;
					++result.data[i + 1];
				}
			}
			while (result.length > 1 && result.data[result.length - 1] == 0) {
				--result.length;
			}
			return result;
		}
	} else {
		return lhs + (-rhs);
	}
}

Bint operator*(const Bint &lhs, const Bint &rhs)
{
	size_t expectLen = lhs.length + rhs.length + 2;
	Bint result(expectLen);
	for (size_t i = 0; i < lhs.length; ++i) {
		for (size_t j = 0; j < rhs.length; ++j) {
			long long tmp = result.data[i + j] + static_cast<long long>(lhs.data[i]) * rhs.data[j];
			if (tmp >= 10000) {
				result.data[i + j] = tmp % 10000;
				result.data[i + j + 1] += static_cast<int>(tmp / 10000);
			} else {
				result.data[i + j] = tmp;
			}
		}
	}
	result.length = lhs.length + rhs.length -1;
	while (result.data[result.length] > 0) {
		++result.length;
	}
	while (result.length > 1 && result.data[result.length - 1] == 0) {
		--result.length;
	}
	return result;
}

Bint::~Bint()
{
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}
}
