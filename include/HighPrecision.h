#ifndef HIPRION_H
#define HIPRION_H

#include <iostream>
#include <stdint.h>
#include <string>

class HighPrecision {
public:
    HighPrecision(const std::string& number) {
        if (number[0] == '-') {
            negative_ = true;
            number_ = number.substr(1);
        }
        else {
            negative_ = false;
            number_ = number;
        }
    }

    // 适用于char (1 byte)
    HighPrecision(const int8_t& number) {
        if (number < 0) {
            negative_ = true;
            number_ = std::to_string(-number);
        }
        else {
            negative_ = false;
            number_ = std::to_string(number);
        }
    }
    HighPrecision(const uint8_t& number) : HighPrecision(std::to_string(number)) {}

    // 适用于short (2 byte)
    HighPrecision(const int16_t& number) {
        if (number < 0) {
            negative_ = true;
            number_ = std::to_string(-number);
        }
        else {
            negative_ = false;
            number_ = std::to_string(number);
        }
    }
    HighPrecision(const uint16_t& number) : HighPrecision(std::to_string(number)) {}

    // 适用于int (4 byte)
    HighPrecision(const int32_t& number) {
        if (number < 0) {
            negative_ = true;
            number_ = std::to_string(-number);
        }
        else {
            negative_ = false;
            number_ = std::to_string(number);
        }
    }
    HighPrecision(const uint32_t& number) : HighPrecision(std::to_string(number)) {}

    // 适用于long long (8 byte)
    HighPrecision(const int64_t& number) {
        if (number < 0) {
            negative_ = true;
            number_ = std::to_string(-number);
        }
        else {
            negative_ = false;
            number_ = std::to_string(number);
        }
    }
    HighPrecision(const uint64_t& number) : HighPrecision(std::to_string(number)) {}

    HighPrecision(void) : HighPrecision(0) {} // 不作任何赋值，初始化0

    HighPrecision(const HighPrecision& hpnumber) : number_(hpnumber.number_) {}

    ~HighPrecision() {}

public:
    friend std::ostream& operator<<(std::ostream& stream, const HighPrecision& hpnumber);
    friend std::istream& operator>>(std::istream& stream, HighPrecision& hpnumber);

    HighPrecision& operator=(const HighPrecision& another);

    bool operator==(const HighPrecision& hpnumber) const;
    bool operator!=(const HighPrecision& hpnumber) const;
    bool operator>(const HighPrecision& hpnumber) const;
    bool operator<(const HighPrecision& hpnumber) const;
    bool operator>=(const HighPrecision& hpnumber) const;
    bool operator<=(const HighPrecision& hpnumber) const;

public:
    // 数学
    friend void hpabs(HighPrecision& hpnumber);
    HighPrecision& hpabs(void);

public:
    // 加法
    HighPrecision operator+(const HighPrecision& y) const;
    HighPrecision& operator+=(const HighPrecision& y);
    HighPrecision& operator++(void);
    HighPrecision operator++(int32_t);

    // 减法
    HighPrecision operator-(const HighPrecision& y) const;
    HighPrecision& operator-=(const HighPrecision& y);
    HighPrecision& operator--(void);
    HighPrecision operator--(int32_t);

    // 乘法
    HighPrecision operator*(const HighPrecision& y) const;
    HighPrecision& operator*=(const HighPrecision& y);

    // 除法
    HighPrecision operator/(const HighPrecision& y) const;
    HighPrecision& operator/=(const HighPrecision& y);
private:
    std::string number_;
    bool negative_;
};

#endif // HIPRION_H