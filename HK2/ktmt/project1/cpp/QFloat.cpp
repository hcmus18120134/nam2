#include "QFloat.h"

string Add(string s, string t, bool isReversed = true)
{
    if(isReversed)
    {
        reverse(s.begin(), s.end());
        reverse(t.begin(), t.end());
    }
    while(s.size() < t.size()) s.push_back('0');
    while(s.size() > t.size()) t.push_back('0');
    if(!isReversed)
    {
        reverse(s.begin(), s.end());
        reverse(t.begin(), t.end());
    }
    string res = "";
    int carry = 0;
    for(int i = 0; i < (int)s.size(); ++i)
    {
        int val = s[i] + t[i] - '0' * 2 + carry;
        res.push_back(val % 10 + '0');
        carry = val / 10;
    }
    if(carry != 0) res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

string Multiply(string s, int d)
{
    reverse(s.begin(), s.end());
    string res = "";
    int carry = 0;
    for(int i = 0; i < (int)s.size(); ++i)
    {
        int val = (s[i] - '0') * d + carry;
        res.push_back(val % 10 + '0');
        carry = val / 10;
    }
    if(carry != 0) res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

bool* DecToBin(string s)
{
    bool *bit = new bool[128];
    reverse(s.begin(), s.end());
    if(s.back() == '-')
    {
        bit[127] = 1;
        s.pop_back();
    }
    else
    {
        bit[127] = 0;
    }
    
    string t = "";

    bool zero_leading = true;

    while(s.size() > 0)
    {
        char ch = s.back();
        s.pop_back();
        if(zero_leading && ch == '0') continue;
        else zero_leading = false;
        if(ch == '.') break;
        t.push_back(ch);
    }
    vector<bool> vbit;

    while(t.size() > 0)
    {
        string tmp = "";
        int carry = 0;
        for(int i = 0; i < (int)t.size(); ++i)
        {
            int val = t[i] - '0';
            val = carry * 10 + val;
            carry = val % 2;
            if(i == 0 && val / 2 == 0) continue;
            tmp.push_back(val / 2 + '0');
        }
        vbit.push_back(carry);
        t = tmp;
    }
    int exp = (int)vbit.size() - 1;

    bool flag = false;
    if(vbit.size() == 0) flag = true;
    else
    {
        vbit.pop_back();
        reverse(vbit.begin(), vbit.end());
    }

    while((int)vbit.size() < 112 && exp > -(1 << 14) + 1)
    {
        string tmp = "";
        int carry = 0;
        for(int i = 0; i < (int)s.size(); ++i)
        {
            int val = s[i] - '0';
            val = val * 2 + carry;
            carry = val / 10;
            tmp.push_back(val % 10 + '0');
        }
        s = tmp;
        if(flag && carry == 0) exp--;
        else
        {
            if(!flag) vbit.push_back(carry);
            else flag = false;
        }
    }
    while((int)vbit.size() < 112)
    {
        vbit.push_back(0);
    }
    exp += (1 << 14) - 1;
    for(int i = 0; i < 15; ++i)
    {
        bit[112 + i] = ((exp >> i) & 1);
    }
    reverse(vbit.begin(), vbit.end());
    for(int i = 0; i < (int)vbit.size(); ++i)
    {
        bit[i] = vbit[i];
    }

    return bit;
}

string BinToDec(bool *bit)
{
    string res;
    int exp = 0;
    for(int i = 112; i <= 126; ++i) exp |= bit[i] << (i - 112);

    exp -= (1 << 14) - 1;

    bool isDenormalized = (exp == MIN_EXP);
    vector<bool> vbit;
    for(int i = 0; i < 112; ++i) vbit.push_back(bit[i]);

    vector<bool> lbit, rbit;
    if(exp >= 0) lbit.push_back(1);
    while(exp > 0)
    {
        lbit.push_back(vbit.back());
        vbit.pop_back();
        exp--;
    }
    while(exp < 0)
    {
        rbit.push_back(0);
        exp++;
    }
    if(lbit.size() == 0 && !isDenormalized)
    {
        rbit.pop_back();
        rbit.push_back(1);
    }
    while(vbit.size() > 0)
    {
        rbit.push_back(vbit.back());
        vbit.pop_back();
    }
    while(rbit.size() > 0 && rbit.back() == 0) rbit.pop_back();
    if(bit[127]) res += "-";
    string s = "0";
    string t = "1";
    while(lbit.size() > 0)
    {
        if(lbit.back())
        {
            s = Add(s, t);
        }
        t = Multiply(t, 2);
        lbit.pop_back();
    }

    res += s;
    res += ".";
    s = "0";
    t = "5";
    for(int i = 0; i < (int)rbit.size(); ++i)
    {
        if(rbit[i])
        {
            s = Add(s, t, false);
        }
        string tmp = Multiply(t, 5);
        if(tmp.size() == t.size())
        {
            t = "0";
            for(auto c: tmp) t.push_back(c);
        }
        else t = tmp;
    }
    res += s;

    return res;
}

void ScanQFloat(QFloat &x)
{
    string s;
    cin >> s;

    bool *bit = DecToBin(s);

    for(int i = 0; i < 128; ++i)
    {
        if(bit[i]) x.OnBit(i);
        else x.OffBit(i);
    }

    delete[]bit;
}

void PrintQFloat(QFloat x, int precision = 9)
{
    int def = x.GetDef();
    if(def == NAN)
    {
        cout << "NaN\n";
        return;
    }
    if(def == INF)
    {
        if(x.GetBit(127)) cout << "-";
        cout << "inf\n";
        return;
    }
    bool *bit = new bool[128];
    for(int i = 0; i < 128; ++i)
    {
        bit[i] = x.GetBit(i);
    }
    string s = BinToDec(bit);
    delete[]bit;
    string res = "";
    for(int i = 0; i < (int)s.size(); ++i)
    {
        res.push_back(s[i]);
        if(s[i] == '.')
        {
            for(int j = i + 1; j <= min((int)s.size()-1, i+precision); ++j)
            {
                res.push_back(s[j]);
            }
            if(i + precision + 1 > (int)s.size() - 1) break;
            if(s[i + precision + 1] >= '5')
            {
                int carry = 1;
                for(int j = (int)res.size()-1; j >= 0; --j)
                {
                    if(res[j] == '.') continue;
                    int val = res[j] - '0' + carry;
                    res[j] = val % 10 + '0';
                    carry = val / 10;
                }
            }
            break;
        }
    }
    while(res.back() == '0') res.pop_back();
    if(res.back() == '.') res.push_back('0');
    reverse(res.begin(), res.end());
    while(res.back() == '0') res.pop_back();
    if(res.back() == '.') res.push_back('0');
    reverse(res.begin(), res.end());

    cout << res << '\n';
}

bool QFloat::operator < (const QFloat& other)
{
    if(GetBit(127) != other.GetBit(127)) return GetBit(127) > other.GetBit(127);
    if(GetExp() != other.GetExp()) return GetExp() < other.GetExp();
    vector<bool> bit_1 = GetCoefficient();
    vector<bool> bit_2 = other.GetCoefficient();
    for(int i = 111; i >= 0; --i)
    {
        if(bit_1[i] != bit_2[i]) return bit_1[i] < bit_2[i];
    }
    return false;
}

QFloat::QFloat(const string& other)
{
    bool *bit = DecToBin(other);
    for(int i = 0; i < 128; ++i)
    {
        if(bit[i]) OnBit(i);
        else OffBit(i);
    }
    delete[]bit;
}

QFloat::QFloat(const char* other)
{
    string s;
    for(int i = 0; i < strlen(other); ++i) s.push_back(other[i]);
    bool *bit = DecToBin(s);
    for(int i = 0; i < 128; ++i)
    {
        if(bit[i]) OnBit(i);
        else OffBit(i);
    }
    delete[]bit;
}

QFloat::operator string ()
{
    bool *bit = new bool[128];
    for(int i = 0; i < 128; ++i) bit[i] = GetBit(i);
    string res = BinToDec(bit);
    delete[]bit;
    return res;
}

QFloat& QFloat::operator = (const string& other)
{
    bool *bit = DecToBin(other);
    for(int i = 0; i < 128; ++i)
    {
        if(bit[i]) OnBit(i);
        else OffBit(i);
    }
    delete[]bit;
    return *this;
}

QFloat& QFloat::operator = (const char* other)
{
    string s;
    for(int i = 0; i < strlen(other); ++i) s.push_back(other[i]);
    bool *bit = DecToBin(s);
    for(int i = 0; i < 128; ++i)
    {
        if(bit[i]) OnBit(i);
        else OffBit(i);
    }
    delete[]bit;
    return *this;
}

QFloat& QFloat::operator = (const QFloat &other)
{
    for(int i = 0; i < 4; ++i) data[i] = other.data[i];
    return *this;
}

QFloat QFloat::operator + (const QFloat& other)
{
    if(GetBit(127) == other.GetBit(127)) return Add(other);
    QFloat x, y;
    if(GetBit(127))
    {
        x = *this;
        y = other;
    }
    else
    {
        x = other;
        y = *this;
    }
    x.OffBit(127);
    if(x < y) return y.Subtract(x);
    
    QFloat res = x.Subtract(y);
    res.OnBit(127);
    return res;
}

QFloat QFloat::operator - (const QFloat& other)
{
    QFloat tmp = other;
    if(tmp.GetBit(127)) tmp.OffBit(127);
    else tmp.OnBit(127);
    return *this + tmp;
}

QFloat QFloat::operator * (const QFloat& other)
{
    int def = GetDef();
    if(def == ZERO || def == NAN) return *this;
    def = other.GetDef();
    if(def == ZERO || def == NAN) return other;

    QFloat res;
    int exp = GetExp() + other.GetExp();
    
    if(GetBit(127) != other.GetBit(127)) res.OnBit(127);

    vector<bool> bit_1 = GetCoefficient();
    vector<bool> bit_2 = other.GetCoefficient();

    vector<bool> bit(bit_1.size() + bit_2.size() - 1);

    for(int i = 0; i < (int)bit_1.size(); ++i)
    {
        int carry = 0;
        if(!bit_1[i]) continue;
        for(int j = 0; j < (int)bit_2.size(); ++j)
        {
            int val = bit[i + j] + bit_2[j] + carry;
            bit[i + j] = val % 2;
            carry = val / 2;
        }
        if(carry != 0)
        {
            if(i == (int)bit_1.size() - 1)
            {
                exp++;
                bit.push_back(carry);
            }
            else bit[i + (int)bit_2.size()] = carry;
        }
    }
    
    exp = min(MAX_EXP, exp);
    exp = max(MIN_EXP, exp);

    reverse(bit.begin(), bit.end());
    while(bit.size() > 113) bit.pop_back();
    reverse(bit.begin(), bit.end());

    res.SetExp(exp);
    res.SetCoefficient(bit);

    return res;
}

QFloat QFloat::operator / (const QFloat& other)
{
    int def = other.GetDef();
    if(def == ZERO)
    {
        QFloat res;
        res.SetExp(MAX_EXP);
        vector<bool> bit(112,1);
        res.SetCoefficient(bit);
        return res;
    }

    QFloat res;
    int exp = GetExp() - other.GetExp();
    if(GetBit(127) != other.GetBit(127)) res.OnBit(127);

    vector<bool> bit_1 = GetCoefficient();
    vector<bool> bit_2 = other.GetCoefficient();
    reverse(bit_1.begin(), bit_1.end());
    reverse(bit_2.begin(), bit_2.end());

    int sz = (int)bit_1.size() + (int)bit_2.size() - 1;
    while(bit_1.size() < sz) bit_1.push_back(0);

    vector<bool> bit;

    int bigCarry = 0;
    for(int i = 0; i < (int)bit_1.size() - (int)bit_2.size() + 1; ++i)
    {
        bool flag = 1;
        if(bigCarry == 0)
        {
            for(int j = 0; j < (int)bit_2.size(); ++j)
            {
                if(bit_1[i+j] < bit_2[j])
                {
                    flag = 0;
                    break;
                }
                if(bit_1[i+j] > bit_2[j]) break;
            }
        }
        bit.push_back(flag);
        if(bit.back() == 1)
        {
            int carry = 0;
            for(int j = (int)bit_2.size() - 1; j >= 0; --j)
            {
                int val = (int)bit_1[i + j] - (int)bit_2[j] + carry;
                bit_1[i + j] = (2 + val) % 2;
                if(val < 0) carry = -1;
                else carry = 0;
            }

            if(carry != 0) bit_1[i-1] = bit_1[i-1] + carry;
        }
        bigCarry = bit_1[i];
    }
    
    if(exp > (1 << 14) - 1)
    {
        res.SetExp((1 << 14));
        return res;
    }

    reverse(bit.begin(), bit.end());
    while(bit.back() != 1)
    {
        bit.pop_back();
        exp--;
    }
    reverse(bit.begin(), bit.end());
    while(bit.size() < 113) bit.push_back(0);
    reverse(bit.begin(), bit.end());

    exp = min(MAX_EXP, exp);
    exp = max(MIN_EXP, exp);

    res.SetExp(exp);
    res.SetCoefficient(bit);

    return res;
}

// #include <chrono>

// using namespace std::chrono;

// int main()
// {
//     ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

//     auto t_start = high_resolution_clock::now();
//     for(int i = 0; i < 1000; ++i)
//     {
//         QFloat x = "12343";
//         QFloat y = "342.4325";
//         x * y;
//     }
//     auto t_end = high_resolution_clock::now();
//     double duration = duration_cast<milliseconds>(t_end - t_start).count();
//     cout << duration / 1000 << '\n';

//     // x.PrintBits();
//     // PrintQFloat(x);
// }