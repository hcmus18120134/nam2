#include "QInt.h"
#include <cmath>

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}
QInt::~QInt()
{
}

int QInt::GetBit(int x, int i)
{
	return (x >> 31 - i) & 1;
}

int QInt::GetQIntBit(int i)
{
	return QInt::GetBit(data[i / 32], i % 32);
}

void QInt::SetQIntBit(int i, int value)
{
	if (value)
		data[i / 32] |= 1 << ((127 - i) % 32);
	else
		data[i / 32] &= ~(1 << ((127 - i) % 32));
}

void QInt::ReverseBit()
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = ~data[i];
	}
}
int QInt::isPlusOneOverFlow(int x)
{
	int idx = 0;
	if (~x == 0)
		return true;
	return false;
}

void QInt::PlusOne()
{
	for (int i = 0; i < 4; i++)
	{
		data[3 - i] += 1;
		if (!isPlusOneOverFlow(data[3 - i] - 1))
			break;
	}
}

string QInt::DivBigNum(string DecStr, int base)
{
	int hold = 0, s = 0;
	string res = "";
	for (int i = 0; i < DecStr.length(); i++)
	{
		hold = hold * 10 + int(DecStr[i]) - 48;
		s = hold / base;
		hold %= base;
		res += char(s + 48);
	}
	while (res.length() > 0 && res[0] == '0')
	{
		res.erase(0, 1);
	}
	return res;
}

int QInt::ModWithInt(string DecStr, int base)
{
	int hold = 0;
	for (int i = 0; i < DecStr.length(); i++)
	{
		hold = (hold * 10 + int(DecStr[i] - 48)) % base;
	}
	return hold;
}

void QInt::DecToBin(string DecStr)
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
	int minus = 0, res, idx = 127;
	if (DecStr.length() == 0)
		return;
	if (DecStr[0] == '-')
	{
		minus = 1;
		DecStr.erase(0, 1);
	}
	try
	{
		while (DecStr.length() > 0)
		{
			res = int(DecStr[DecStr.length() - 1] - 48) % 2;
			if (res)
				QInt::SetQIntBit(idx, 1);
			idx--;

			DecStr = QInt::DivBigNum(DecStr, 2);
			if (idx < 0)
			{
				string error = "Overflow!";
				throw error;
			}
		}
		if (minus)
		{
			ReverseBit();
			PlusOne();
		}
	}
	catch (string error)
	{
		cout << error << endl;
		cout << "Reset to zero!" << endl;
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}
}

void QInt::HexToBin(string DecStr)
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
	int minus = 0, res, idx = 127, l;
	if (DecStr.length() == 0)
		return;
	if (DecStr[0] == '-')
	{
		minus = 1;
		DecStr.erase(0, 1);
	}
	l = DecStr.length();
	while (l > 0)
	{
		res = int(DecStr[l - 1]);
		if (res >= 'A')
		{
			res = 10 + int(res - 'A');
		}
		else
		{
			res = int(res - '0');
		}
		int count = 4;
		while (count > 0)
		{
			SetQIntBit(idx, res % 2);
			res /= 2;
			count--;
			idx--;
		}
		l--;
	}
	if (minus)
	{
		ReverseBit();
		PlusOne();
	}
}

void QInt::BinToBin(string DecStr)
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
	int res, idx = 127, l;
	if (DecStr.length() == 0)
		return;
	l = DecStr.length();
	while (l > 0)
	{
		res = int(DecStr[l - 1] - 48);
		SetQIntBit(idx, res);
		l--;
		idx--;
	}
}

string QInt::PlusBigNum(string a, string b)
{
	int carry = 0, sum, x, y;
	string res = "";
	while (a.length() < b.length())
		a = "0" + a;
	while (b.length() < a.length())
		b = "0" + b;

	for (int i = a.length() - 1; i >= 0; i--)
	{
		x = int(a[i] - 48);
		y = int(b[i] - 48);
		sum = x + y + carry;
		carry = sum / 10;
		res = char(sum % 10 + 48) + res;
	}
	if (carry > 0)
		res = "1" + res;
	return res;
}

string QInt::MultiplyWithInt(string a, int b)
{
	int carry = 0, s;
	string res = "";
	for (int i = a.length() - 1; i >= 0; i--)
	{
		s = int(a[i] - 48) * b + carry;
		carry = s / 10;
		res = char(s % 10 + 48) + res;
	}
	if (carry > 0)
	{
		// convert int to string
		string tmp = "";
		while (carry)
		{
			tmp = char(carry % 10 + 48) + tmp;
			carry /= 10;
		}
		res = tmp + res;
	}
	return res;
}

string QInt::SubtractBigNum(string a, string b)
{
	string res = "";
	int s, borrow = 0;
	while (a.length() < b.length())
		a = "0" + a;
	while (b.length() < a.length())
		b = "0" + b;

	for (int i = a.length() - 1; i >= 0; i--)
	{
		s = int(a[i] - b[i]) - borrow;
		if (s < 0)
		{
			s += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		res = char(s + 48) + res;
	}
	while (res.length() > 0 && res[0] == '0')
	{
		res.erase(0, 1);
	}
	return res;
}

string QInt::BinToDec()
{
	string power2 = "1", res = "0";
	for (int i = 127; i > 0; i--)
	{
		if (GetQIntBit(i))
		{
			res = PlusBigNum(res, power2);
		}
		power2 = MultiplyWithInt(power2, 2);
	}
	if (GetQIntBit(0))
	{
		res = "-" + SubtractBigNum(power2, res);
	}
	return res;
}

void QInt::PrintBin()
{
	for (int i = 0; i < 128; i++)
	{
		cout << GetQIntBit(i);
	}
	cout << endl;
}

string QInt::BinToHex()
{
	string res = "";
	int minus = 0;
	if (GetQIntBit(0))
	{
		minus = 1;
		ReverseBit();
		PlusOne();
	}
	int idx = 127;
	while (idx >= 0)
	{
		int count = 0, temp_res = 0;
		while (count < 4)
		{
			if (GetQIntBit(idx))
			{
				temp_res += int(pow(2, count));
			}
			count++;
			idx--;
		}
		if (temp_res >= 10)
		{
			res = char(temp_res % 10 + 'A') + res;
		}
		else
			res = char(temp_res + '0') + res;
	}
	while (res.length() > 1 && res[0] == '0')
	{
		res.erase(0, 1);
	}
	if (minus)
	{
		ReverseBit();
		PlusOne();
		res = "-" + res;
	}
	return res;
}

string QInt::DecToHex(string DecStr)
{
	int minus = 0, residual, idx = 127;
	string res = "";
	if (DecStr.length() == 0)
		return "";
	if (DecStr[0] == '-')
	{
		minus = 1;
		DecStr.erase(0, 1);
	}
	while (DecStr.length() > 0)
	{
		residual = ModWithInt(DecStr, 16);
		if (residual >= 10)
		{
			res = char(residual % 10 + 'A') + res;
		}
		else
			res = char(residual + '0') + res;
		DecStr = QInt::DivBigNum(DecStr, 16);
	}
	if (minus)
	{
		res = "-" + res;
	}
	return res;
}

QInt QInt::operator+(QInt b)
{
	QInt res, B;
	int carry = 0, sum;

	for (int i = 127; i >= 0; i--)
	{
		int x = this->GetQIntBit(i);
		int y = b.GetQIntBit(i);
		sum = (x + y + carry);
		carry = sum / 2;
		if (sum % 2)
		{
			res.SetQIntBit(i, 1);
		}
	}
	if (((this->GetQIntBit(0) + b.GetQIntBit(0)) % 2 == 0) && (res.GetQIntBit(0) != b.GetQIntBit(0)) && !(res == B))
	{
		cout << "Plus operator overflow! Result is default set to zero\n";
		return B;
	}
	return res;
}

QInt QInt::operator-(QInt b)
{
	int borrow = 0, s;
	QInt res, B;
	// for (int i = 127; i >= 0; i--) {
	// 	s = this->GetQIntBit(i) - b.GetQIntBit(i) - borrow;
	// 	if (s < 0) {
	// 		s += 2;
	// 		borrow = 1;
	// 	}
	// 	else borrow = 0;
	// 	if (s) {
	// 		res.SetQIntBit(i, 1);
	// 	}
	// }
	b.ReverseBit();
	b.PlusOne();
	res = *this + b;
	if (((this->GetQIntBit(0) + b.GetQIntBit(0)) % 2 == 0) && (res.GetQIntBit(0) != b.GetQIntBit(0)) && !(res == B))
	{
		cout << "Subtract operator overflow! Result is default set to zero\n";
		return B;
	}
	return res;
}

QInt QInt::operator*(QInt M)
{
	int count = 128, Q_1 = 0, Q_0, A_0;
	QInt A, B, Q = *this;
	while (count > 0)
	{
		Q_0 = Q.GetQIntBit(127);
		if (Q_0 - Q_1 > 0)
		{
			A = A - M;
		}
		else if (Q_0 - Q_1 < 0)
		{
			A = A + M;
		}
		Q_1 = Q_0;
		A_0 = A.GetQIntBit(127);
		Q = Q >> 1;
		A = A >> 1;
		Q.SetQIntBit(0, A_0);

		count--;
	}
	// A.PrintBin();
	QInt temp = A;
	temp.ReverseBit();
	if (temp == B)
		return Q;
	if (!(A == B))
	{
		cout << "Multiply operator overflow! Result is default set to zero\n";
		return B;
	}
	return Q;
}

QInt QInt::operator/(QInt M)
{
	QInt A, Q = *this;
	if (M == A)
	{
		cout << "Divide 0!\n";
		return A;
	}
	int sign = 0, count = 128;
	if (Q.GetQIntBit(0))
	{
		sign = !sign;
		Q.ReverseBit();
		Q.PlusOne();
	}
	if (M.GetQIntBit(0))
	{
		sign = !sign;
		M.ReverseBit();
		M.PlusOne();
	}
	while (count > 0)
	{

		A = A << 1;
		A.SetQIntBit(127, Q.GetQIntBit(0));
		Q = Q << 1;

		A = A - M;
		if (A.GetQIntBit(0))
		{
			Q.SetQIntBit(127, 0);
			A = A + M;
		}
		else
		{
			Q.SetQIntBit(127, 1);
		}
		count--;
	}

	if (sign)
	{
		Q.ReverseBit();
		Q.PlusOne();
	}
	return Q;
}

QInt &QInt::operator=(QInt a)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = a.data[i];
	}
	return *this;
}

QInt QInt::operator>>(int k)
{
	QInt res = *this;
	int sign = GetQIntBit(0);
	for (int i = 127; i >= 0; i--)
	{
		if (i >= k)
		{
			res.SetQIntBit(i, GetQIntBit(i - k));
		}
		else
		{
			res.SetQIntBit(i, sign);
		}
	}
	return res;
}

QInt QInt::operator<<(int k)
{
	QInt res = *this;
	for (int i = 0; i < 128; i++)
	{
		if (i < 128 - k)
		{
			res.SetQIntBit(i, GetQIntBit(i + k));
		}
		else
		{
			res.SetQIntBit(i, 0);
		}
	}
	return res;
}

int QInt::operator<(QInt a)
{
	if ((*this - a).GetQIntBit(0))
	{
		return true;
	}
	return false;
}
int QInt::operator>(QInt a)
{
	if (*this == a)
	{
		return false;
	}
	if (!(*this - a).GetQIntBit(0))
	{
		return true;
	}
	return false;
}
int QInt::operator==(QInt a)
{
	QInt res = *this - a;
	for (int i = 0; i < 4; i++)
	{
		if (res.data[i])
			return false;
	}
	return true;
}

int QInt::operator>=(QInt a)
{
	return *this > a || *this == a;
}

int QInt::operator<=(QInt a)
{
	return *this < a || *this == a;
}

QInt QInt::operator&(QInt a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = this->data[i] & a.data[i];
	}
	return res;
}
QInt QInt::operator|(QInt a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = this->data[i] | a.data[i];
	}
	return res;
}

QInt QInt::operator^(QInt a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = this->data[i] ^ a.data[i];
	}
	return res;
}

QInt QInt::operator~()
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = ~this->data[i];
	}
	return res;
}
QInt QInt::rol(int k)
{
	QInt res = *this;
	vector<int> temp;
	for (int i = 0; i < k; i++)
		temp.push_back(GetQIntBit(i));
	res = res << k;
	for (int i = 0; i < k; i++)
		res.SetQIntBit(128 - k + i, temp[i]);
	return res;
}

QInt QInt::ror(int k)
{
	QInt res = *this;
	vector<int> temp;
	for (int i = 0; i < k; i++)
		temp.push_back(GetQIntBit(127 - i));
	res = res >> k;
	for (int i = 0; i < k; i++)
		res.SetQIntBit(k - 1 - i, temp[i]);
	return res;
}

void QInt::ScanQInt(int type, string Str)
{
	if (type == 10)
	{
		DecToBin(Str);
	}
	else if (type == 16)
	{
		HexToBin(Str);
	}
	else
	{
		BinToBin(Str);
	}
}
void QInt::PrintQInt(int type)
{
	if (type == 10)
	{
		cout << BinToDec() << endl;
	}
	else if (type == 16)
	{
		cout << BinToHex() << endl;
	}
	else
	{
		PrintBin();
	}
}

string QInt::toString(int type)
{
	if (type == 10)
	{
		return BinToDec();
	}
	else if (type == 16)
	{
		return BinToHex();
	}
}

QInt::QInt(const string &other)
{
	DecToBin(other);
}

QInt::QInt(const char *other)
{
	string s = string(other);
	DecToBin(s);
}

QInt &QInt::operator=(const string &other)
{
	DecToBin(other);
	return *this;
}

QInt &QInt::operator=(const char *other)
{
	string s = string(other);
	DecToBin(s);
	return *this;
}

/*
int main() {
	QInt q1, q2, q;
	string HexStr;
	//q1.DecToBin("-123456789123456789123456789123456789");
	//cout << q1.BinToHex() << endl;
	//cout << q1.BinToDec() << endl;
	//HexStr = q1.DecToHex("-123456789123456789123456789123456789");
	//cout << HexStr << endl;
	//q1.PrintQInt(10);
	//q2.HexToBin(HexStr);
	//cout << q2.BinToDec() << endl;

	//q.DecToBin("-123456000000000000000000");
	//cout << q.BinToDec() << endl;

	// q1.BinToBin("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	// //q1.PrintQInt(10);
	// q2.BinToBin("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	q1.DecToBin("-10000000000000000");
	q2.DecToBin("40000000000000000");
	//q2.PrintBin();
	QInt q3 = q1 * q2;
	//q3.PrintBin();
	q3.PrintQInt(10);
	// q3.PrintQInt(2);
	// q3.PrintQInt(16);
}
*/
