#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

const unsigned long long MAX_DP = 100000;

const unsigned long long BASEP = 9;
const unsigned long long BASE = 1000000000;

using namespace std;

class BigInt {
public:
    BigInt() {
        number.push_back(0);
    }

    BigInt(string inputNum) {
        for (int i = inputNum.size(); i > 0; i -= BASEP) {
            if (i < BASEP) {
                number.push_back(atoi(inputNum.substr(0, i).c_str()));
            } else {
                number.push_back(atoi(inputNum.substr(i-BASEP, BASEP).c_str()));
            }
        }
        while (number.size() > 1 && number.back() == 0) {
	        number.pop_back();
        }
        if (size() > (MAX_DP / BASEP + 1)) {
            throw("overflow");
        }
    }
    BigInt(const BigInt &in) {
        number = in.number;
    }

    BigInt& operator= (const BigInt &in) {
        number = in.number;
        return *this;
    }

    bool operator== (const BigInt &in) {
        if (number.size() != in.number.size()) {
            return false;
        }
        for (int i = 0; i < number.size(); i++) {
            if (number[i] != in.number[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator> (const BigInt &in) {
        if (number.size() > in.number.size()) {
            return true;
        } else if (number.size() < in.number.size()) {
            return false;
        }
        for (int i = number.size() - 1; i >= 0; i--) {
            if (number[i] > in.number[i]) {
                return true;
            } else if (number[i] < in.number[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator< (const BigInt &in) {
        if (number.size() < in.number.size()) {
            return true;
        } else if (number.size() > in.number.size()) {
            return false;
        }
        for (int i = number.size() - 1; i >= 0; i--) {
            if (number[i] < in.number[i]) {
                return true;
            } else if (number[i] > in.number[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator>= (const BigInt &in) {
        if (number.size() > in.number.size()) {
            return true;
        } else if (number.size() < in.number.size()) {
            return false;
        }
        for (int i = number.size() - 1; i >= 0; i--) {
            if (number[i] > in.number[i]) {
                return true;
            } else if (number[i] < in.number[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<= (const BigInt &in) {
        if (number.size() < in.number.size()) {
            return true;
        } else if (number.size() > in.number.size()) {
            return false;
        }
        for (int i = number.size() - 1; i >= 0; i--) {
            if (number[i] < in.number[i]) {
                return true;
            } else if (number[i] > in.number[i]) {
                return false;
            }
        }
        return true;
    }

    BigInt& operator+= (BigInt &in) {
        int carry = 0;
        for(int i = 0; i < fmax(number.size(), in.number.size()) || carry; i++) {
            if (i == number.size()) {
		        number.push_back(0);
            }
            number[i] += (i < in.number.size() ? in.number[i] : 0) + carry;
            if (number[i] >= BASE) {
                carry = 1;
                number[i] -= BASE;
            } else {
                carry = 0;
            }
        }
        if (size() > (MAX_DP / BASEP + 1)) {
            throw("overflow");
        }
        return *this;
    }

    BigInt operator+ (BigInt &in) {
        BigInt out = *this;
        return out += in;
    }

    BigInt& operator-= (BigInt &in) {
        if (number.size() < in.size()) {
            throw "a < b";
        }
        int carry = 0;
        for (int i = 0; (i < in.size() || carry) && i < number.size(); ++i) {
            number[i] -= carry + (i < in.size() ? in[i] : 0);
            if (number[i] < 0) {
                carry = 1;
                number[i] += BASE;
            } else {
                carry = 0;
            }
        }
        if (carry) {
            throw "a < b";
        }
        while (number.size() > 1 && number.back() == 0) {
            number.pop_back();
        }
        return *this;
    }

    BigInt operator- (BigInt &in) {
        BigInt out = *this;
        return out -= in;
    }

    BigInt& operator*= (unsigned int in) {
        unsigned long long carry = 0;
        unsigned long long cur;
        for (int i = 0; i < size() || carry; ++i) {
            if (i == number.size()) {
                number.push_back (0);
            }
            cur = carry + (unsigned long long)number[i] * in;
            carry = cur / BASE;
            number[i] = cur - BASE * carry;
        }
        while (size() > 1 && number.back() == 0) {
            number.pop_back();
        }
        if (size() > (MAX_DP / BASEP + 1)) {
            throw("overflow");
        }
        return *this;
    }

    BigInt operator* (unsigned int in) {
        BigInt out = *this;
        return out *= in;
    }

    BigInt operator* (BigInt &in) {
        BigInt out;
        out.number.resize(size() + in.size());
        if (out.size() > (MAX_DP / BASEP + 1)) {
            throw("overflow");
        }
        unsigned long long cur;
        unsigned long long carry = 0;
        for (int i = 0; i < size(); ++i) {
            carry = 0;
            for (int j = 0; j < in.size() || carry; ++j) {
                cur = (unsigned long long)out[i + j] + (unsigned long long)number[i] * (j < (int)in.size() ? in[j] : 0) + carry;
                carry = (unsigned long long)cur / BASE;
                out[i + j] = (unsigned long long)cur - carry * BASE;
            }
        }
        while (out.size() > 1 && out.number.back() == 0) {
            out.number.pop_back();
        }
        return out;
    }

    BigInt operator^ (BigInt &in) {
        unsigned long long power = (unsigned long long)in;
        if (power == 0) {
            if (size() == 1 && number[0] == 0) {
                throw("0^0");
            }
            BigInt out("1");
            return out;
        }
        if (size() == 1) {
            if (number[0] == 0) {
                BigInt out;
                return out;
            } else if (number[0] == 1){
                BigInt out("1");
                return out;
            }
        }

        vector<BigInt> pows;
        pows.push_back(*this);
        for(int i = 1; pow(2 ,i) <= power; i++) {
            pows.push_back(pows[i - 1] * pows[i - 1]);
        }
        BigInt out("1");
        for(int i = 0; i < 64; i++) {
            if (1ull << i & power) {
                out = out * pows[i];
            }
        }
        return out;
    }

    BigInt operator/= (unsigned long long in) {
        if (in == 0) {
            throw("dev by zero");
        }
        unsigned long long carry = 0;
        unsigned long long cur;
        for (int i = (int)size()-1; i >= 0; i--) {
            cur = (unsigned long long)number[i] + carry * BASE;
            number[i] = cur / in;
            carry = cur - in * (unsigned long long)number[i];
        }
        while (size() > 1 && number.back() == 0) {
            number.pop_back();
        }
        return *this;
    }

    BigInt operator/ (BigInt &in) {
        BigInt out;
        int n = in.size();
        if (n == 1) {
            out = *this;
            return (out /= in[0]);
        }
        if (*this < in) {
            return out;
        }
        int m = size() - n;
        //cout << "m " << m << '\n';
        int d = BASE / (in[n - 1] + 1);
        //cout << "d " << d << '\n';
        BigInt u = *this;
        u *= d;
        u.number.push_back(0);
        BigInt v = in;
        v *= d;
        out.number.resize(m + 1);
        BigInt qv;
        unsigned long long q;
        unsigned long long r;
        for (int j = m; j >=0; j--) {
            q = ((unsigned long long)u[j + n] * BASE + u[n + j - 1]) / v[n - 1];
            r = ((unsigned long long)u[j + n] * BASE + u[n + j - 1]) - v[n - 1] * q; //mod
            while ((q == BASE || (q * v[n - 2]) > (BASE * r + u[j + n - 2])) && r < BASE) {
                q -= 1;
                r += v[n - 1];
            }
            qv = v;
            qv *= q;
            qv.shift(j);
            if (u < qv) {
                u.number.push_back(1);
                q -= 1;
            }
            u -= qv;
            out[j] = q;
        }
        while (out.size() > 1 && out.number.back() == 0) {
            out.number.pop_back();
        }
        return out;
    }

    operator unsigned long long() {
        unsigned long long out = 0;
        for(int i = 0; i < size(); i++) {
            out += (unsigned long long)number[i] * (unsigned long long)pow(BASE, i);
        }
        return out;
    }

    void shift(int sh) {
        if (size() == 1 && number[0] == 0) {
            return;
        }
        BigInt new_num;
        new_num.number.resize(size() + sh, 0);
        copy(number.begin(), number.end(), new_num.number.begin() + sh);
        swap(new_num, *this);
    }

    friend istream& operator>> (istream &in, BigInt &inN) {
        string inputNum;
        in >> inputNum;
        BigInt outN(inputNum);
        swap(inN, outN);
        return in;
    }

    friend ostream& operator<< (ostream &out, const BigInt &outN) {
        out << outN.number[outN.number.size() - 1];
        for (int i = (int)outN.number.size() - 2; i >= 0; i--) {
            out << setfill('0') << setw(BASEP) << outN.number[i];
        }
        return out;
    }

    friend void swap(BigInt &a, BigInt &b) {
        swap(a.number, b.number);
    }

private:
    vector<int> number;

    size_t size() {
        return number.size();
    }

    int& operator[] (int pos) {
        return number[pos];
    }
};

#endif
