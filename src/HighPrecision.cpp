#include "HighPrecision.h"

#include <algorithm>
#include <vector>

std::ostream& operator<<(std::ostream& stream, const HighPrecision& hpnumber) {
    if (hpnumber.number_ == "0") {
        stream << "0";
        return stream;
    }
    if (hpnumber.negative_) {
        stream << "-";
    }
    stream << hpnumber.number_;
    return stream;
}

std::istream& operator>>(std::istream& stream, HighPrecision& hpnumber) {
    std::string input;
    stream >> input;
    if (input[0] == '-') {
        hpnumber.negative_ = true;
        hpnumber.number_ = input.substr(1);
    }
    else {
        hpnumber.negative_ = false;
        hpnumber.number_ = input;
    }
    return stream;
}

HighPrecision& HighPrecision::operator=(const HighPrecision& another) {
    if (*this != another) {
        this->number_ = another.number_;
        this->negative_ = another.negative_;
    }
    return *this;
}

bool HighPrecision::operator==(const HighPrecision& hpnumber) const {
    return this->number_ == hpnumber.number_ && this->negative_ == hpnumber.negative_;
}

bool HighPrecision::operator!=(const HighPrecision& hpnumber) const {
    return !(*this == hpnumber);
}

bool HighPrecision::operator>(const HighPrecision& hpnumber) const {
    if (this->negative_ != hpnumber.negative_) {
        return hpnumber.negative_;
    }
    if (this->negative_) {
        if (this->number_.length() != hpnumber.number_.length()) {
            return this->number_.length() < hpnumber.number_.length();
        }
        return this->number_ < hpnumber.number_;
    }
    else {
        if (this->number_.length() != hpnumber.number_.length()) {
            return this->number_.length() > hpnumber.number_.length();
        }
        return this->number_ > hpnumber.number_;
    }
}

bool HighPrecision::operator<(const HighPrecision& hpnumber) const {
    if (this->negative_ != hpnumber.negative_) {
        return this->negative_;
    }
    if (this->negative_) {
        if (this->number_.length() != hpnumber.number_.length()) {
            return this->number_.length() > hpnumber.number_.length();
        }
        return this->number_ > hpnumber.number_;
    }
    else {
        if (this->number_.length() != hpnumber.number_.length()) {
            return this->number_.length() < hpnumber.number_.length();
        }
        return this->number_ < hpnumber.number_;
    }
}

bool HighPrecision::operator>=(const HighPrecision& hpnumber) const {
    return !(*this < hpnumber);
}

bool HighPrecision::operator<=(const HighPrecision& hpnumber) const {
    return !(*this > hpnumber);
}

HighPrecision HighPrecision::operator+(const HighPrecision& y) const {
    if (this->negative_ == y.negative_) {
        int32_t carry = 0;
        std::vector<int32_t> X, Y, R;

        std::size_t resultLength = 0;
        std::string result = "";

        for (std::size_t i = 0; i < this->number_.length(); i++) {
            X.push_back(this->number_[this->number_.length() - 1 - i] - '0');
        }

        for (std::size_t i = 0; i < y.number_.length(); i++) {
            Y.push_back(y.number_[y.number_.length() - 1 - i] - '0');
        }

        for (; resultLength < X.size() || resultLength < Y.size(); resultLength++) {
            int32_t xValue = (resultLength < X.size()) ? X[resultLength] : 0;
            int32_t yValue = (resultLength < Y.size()) ? Y[resultLength] : 0;
            R.push_back(xValue + yValue + carry);
            carry = R[resultLength] / 10;
            R[resultLength] %= 10;
        }

        if (carry > 0) {
            R.push_back(carry);
        }
        std::reverse(R.begin(), R.end());
        for (int32_t& temp : R) {
            result += std::to_string(temp);
        }

        if (this->negative_) {
            result = "-" + result;
        }

        return HighPrecision(result);
    }
    else {
        HighPrecision abs_this = *this;
        abs_this.negative_ = false;
        HighPrecision abs_y = y;
        abs_y.negative_ = false;

        if (abs_this >= abs_y) {
            HighPrecision result = abs_this - abs_y;
            result.negative_ = this->negative_;
            return result;
        }
        else {
            HighPrecision result = abs_y - abs_this;
            result.negative_ = y.negative_;
            return result;
        }
    }
}

HighPrecision& HighPrecision::operator+=(const HighPrecision& y) {
    *this = *this + y;
    return *this;
}

HighPrecision HighPrecision::operator++(int32_t) {
    HighPrecision temp = *this;
    *this += HighPrecision(1);
    return temp;
}

HighPrecision& HighPrecision::operator++(void) {
    *this += HighPrecision(1);
    return *this;
}

HighPrecision HighPrecision::operator-(const HighPrecision& y) const {
    if (this->negative_ == y.negative_) {
        bool resultNegative = false;
        HighPrecision larger, smaller;

        if (*this >= y) {
            larger = *this;
            smaller = y;
        }
        else {
            larger = y;
            smaller = *this;
            resultNegative = true;
        }

        int32_t borrow = 0;
        std::vector<int32_t> X, Y, R;

        for (std::size_t i = 0; i < larger.number_.length(); i++) {
            X.push_back(larger.number_[larger.number_.length() - 1 - i] - '0');
        }

        for (std::size_t i = 0; i < smaller.number_.length(); i++) {
            Y.push_back(smaller.number_[smaller.number_.length() - 1 - i] - '0');
        }

        for (std::size_t i = 0; i < X.size(); i++) {
            int32_t xValue = X[i];
            int32_t yValue = (i < Y.size()) ? Y[i] : 0;
            int32_t diff = xValue - yValue - borrow;

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }

            R.push_back(diff);
        }

        while (R.size() > 1 && R.back() == 0) {
            R.pop_back();
        }

        std::reverse(R.begin(), R.end());
        std::string result;
        for (int32_t& temp : R) {
            result += std::to_string(temp);
        }

        if (resultNegative) {
            result = "-" + result;
        }

        return HighPrecision(result);
    }
    else {
        HighPrecision abs_this = *this;
        abs_this.negative_ = false;
        HighPrecision abs_y = y;
        abs_y.negative_ = false;

        HighPrecision result = abs_this + abs_y;
        result.negative_ = this->negative_;
        return result;
    }
}

HighPrecision& HighPrecision::operator-=(const HighPrecision& y) {
    *this = *this - y;
    return *this;
}

HighPrecision HighPrecision::operator--(int32_t) {
    HighPrecision temp = *this;
    *this -= HighPrecision(1);
    return temp;
}

HighPrecision& HighPrecision::operator--(void) {
    *this -= HighPrecision(1);
    return *this;
}

HighPrecision& HighPrecision::hpabs(void) {
    if (this->negative_ == false || this->number_ == "0") {
        return *this;
    }
    this->negative_ = false;
    return *this;
}

void hpabs(HighPrecision& hpnumber) {
    if (hpnumber.negative_ == false || hpnumber.number_ == "0") {
        return;
    }
    hpnumber.negative_ = false;
}
