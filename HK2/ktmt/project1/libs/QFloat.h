#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

#define MAX_EXP (1<<14)
#define MIN_EXP (-(1<<14) + 1)
#define NORMAL 0
#define ZERO 1
#define INF 2
#define NAN 3

class QFloat
{
private:
    unsigned int data[4];

    int GetBit(int p) const
    {
        return (data[p / 32] >> (p % 32)) & 1;
    }

    void OnBit(int p)
    {
        data[p / 32] |= 1 << (p % 32);
    }

    void OffBit(int p)
    {
        data[p / 32] &= ~(1 << (p % 32));
    }

    int GetExp() const
    {
        int exp = 0;
        for(int i = 112; i <= 126; ++i) exp |= GetBit(i) << (i - 112);
        return exp - (1 << 14) + 1;
    }

    vector<bool> GetCoefficient() const
    {
        vector<bool> bit;
        for(int i = 0; i < 112; ++i) bit.push_back(GetBit(i));
        if(GetExp() == -(1 << 14) + 1) bit.push_back(0);
        else bit.push_back(1);
        return bit;
    }

    void SetExp(int exp)
    {
        exp += (1 << 14) - 1;
        for(int i = 0; i < 15; ++i)
        {
            if((exp >> i) & 1) OnBit(i + 112);
            else OffBit(i + 112);
        }
    }

    void SetCoefficient(const vector<bool>& bit)
    {
        for(int i = 0; i < 112; ++i)
        {
            if(bit[i]) OnBit(i);
            else OffBit(i);
        }
    }

    int GetDef() const
    {
        int exp = GetExp();
        vector<bool> bit = GetCoefficient();
        bool flag = 0;
        for(auto b: bit) flag |= b;
        if(exp == MIN_EXP && !flag) return ZERO;
        if(exp == MAX_EXP && !flag) return INF;
        if(exp == MAX_EXP && flag) return NAN;
        return NORMAL;
    }

    int Align(vector<bool> &bit_1, int &exp_1, vector<bool> &bit_2, int &exp_2)
    {
        int excessed = 0;
        while(exp_1 < exp_2)
        {
            bit_1.push_back(0);
            exp_1++;
        }
        reverse(bit_1.begin(), bit_1.end());
        while(bit_1.size() > 113)
        {
            if(bit_1.back() == 1) excessed = 1;
            bit_1.pop_back();
        }
        reverse(bit_1.begin(), bit_1.end());
        while(exp_2 < exp_1)
        {
            bit_2.push_back(0);
            exp_2++;
        }
        reverse(bit_2.begin(), bit_2.end());
        while(bit_2.size() > 113)
        {
            if(bit_2.back() == 1) excessed = -1;
            bit_2.pop_back();
        }
        reverse(bit_2.begin(), bit_2.end());

        return excessed;
    }

    QFloat Add(const QFloat& other)
    {
        int exp_1 = GetExp();
        vector<bool> bit_1 = GetCoefficient();
        int exp_2 = other.GetExp();
        vector<bool> bit_2 = other.GetCoefficient();
        Align(bit_1, exp_1, bit_2, exp_2);

        int exp = exp_1;
        vector<bool> bit;

        int carry = 0;
        for(int i = 0; i < (int)bit_1.size(); ++i)
        {
            int val = bit_1[i] + bit_2[i] + carry;
            bit.push_back(val % 2);
            carry = val / 2;
        }
        if(carry)
        {
            exp++;
            reverse(bit.begin(), bit.end());
            bit.pop_back();
            reverse(bit.begin(), bit.end());
        }
        else
        {
            bit.pop_back();
        }

        QFloat res;
        if(GetBit(127)) res.OnBit(127);
        res.SetExp(exp);
        res.SetCoefficient(bit);

        return res;
    }

    QFloat Subtract(const QFloat& other)
    {
        int exp_1 = GetExp();
        vector<bool> bit_1 = GetCoefficient();
        int exp_2 = other.GetExp();
        vector<bool> bit_2 = other.GetCoefficient();
        int excessed = Align(bit_1, exp_1, bit_2, exp_2);

        int exp = exp_1;
        vector<bool> bit;

        int carry = excessed;
        for(int i = 0; i < (int)bit_1.size(); ++i)
        {
            int val = bit_1[i] - bit_2[i] + carry;
            bit.push_back((2 + val) % 2);
            if(val < 0) carry = -1;
            else carry = 0;
        }
        while(bit.size() > 0 && bit.back() == 0)
        {
            exp--;
            bit.pop_back();
        }

        reverse(bit.begin(), bit.end());
        while(bit.size() < 113) bit.push_back(0);
        reverse(bit.begin(), bit.end());

        bit.pop_back();

        QFloat res;
        if(GetBit(127)) res.OnBit(127);
        res.SetExp(exp);
        res.SetCoefficient(bit);

        return res;
    }

public:
    QFloat()
    {
        for(int i = 0; i < 4; ++i) data[i] = 0;
    }

    QFloat(const QFloat& other)
    {
        for(int i = 0; i < 4; ++i) data[i] = other.data[i];
    }

    QFloat(const string& other);
    QFloat(const char* other);

    void PrintBits() const
    {
        cout << GetBit(127) << ' ';
        for(int i = 126; i >= 112; --i) cout << GetBit(i); cout << ' ';
        for(int i = 111; i >= 0; --i) cout << GetBit(i);
        cout << '\n';
    }

    QFloat& operator = (const string& other);
    QFloat& operator = (const char* other);
    QFloat& operator = (const QFloat &other);
    QFloat operator + (const QFloat &other);
    QFloat operator - (const QFloat &other);
    QFloat operator * (const QFloat &other);
    QFloat operator / (const QFloat &other);

    operator string ();

    bool operator < (const QFloat &other);

    friend void ScanQFloat(QFloat &x);
    friend void PrintQFloat(QFloat x, int precision);

    friend string BinToDec(bool *bit);
    friend bool* DecToBin(string x);
};