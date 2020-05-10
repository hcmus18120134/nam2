#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class QInt
{
private:
	int data[4];

	int GetQIntBit(int);
	int isPlusOneOverFlow(int);
	int ModWithInt(string, int);
	int GetBit(int, int);

	void SetQIntBit(int, int);
	void ReverseBit();
	void PlusOne();

	string DivBigNum(string, int);
	string PlusBigNum(string, string);
	string MultiplyWithInt(string, int);
	string SubtractBigNum(string, string);

public:
	QInt();
	~QInt();
	QInt(const char *);
	QInt(const string &);

	void ScanQInt(int, string);
	void PrintQInt(int);
	void DecToBin(string);
	void HexToBin(string);
	void BinToBin(string);
	void PrintBin();

	string BinToHex();
	string BinToDec();
	string DecToHex(string);
	string toString(int);

	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	QInt operator/(QInt);
	QInt operator>>(int);
	QInt operator<<(int);
	QInt &operator=(QInt);
	QInt operator&(QInt);
	QInt operator|(QInt);
	QInt operator^(QInt);
	QInt operator~();
	QInt rol(int);
	QInt ror(int);

	QInt &operator=(const char *);
	QInt &operator=(const string &);

	int operator>(QInt);
	int operator<(QInt);
	int operator==(QInt);
	int operator>=(QInt);
	int operator<=(QInt);
};
