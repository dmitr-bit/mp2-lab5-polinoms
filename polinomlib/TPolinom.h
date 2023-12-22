#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <string>
using namespace std;

const int nonDisplayedZeros = 4;
// Количество неотображаемых нулей при выводе коэффициента полинома
// Кол-во символов после запятой = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // присваивание
	TPolinom& operator+(TPolinom& q); // сложение полиномов

	// дополнительно можно реализовать:
	void AddMonom(TMonom newMonom); // добавление монома
	TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom operator*(double coef); // умножение полинома на число
	TPolinom operator* (TPolinom& other); // умножение полиномов
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	string ToString(); // перевод в строку
};


TPolinom::TPolinom() :THeadList<TMonom>::THeadList() {}


TPolinom::TPolinom(TPolinom& other)
{
	pHead = new TNode<TMonom>;
	TNode<TMonom>* h = other.pHead->pNext;
	while (h != other.pStop) {
		this->AddMonom(h->value);
		h = h->pNext;
	}
}

TPolinom::TPolinom(string str)
{
	string a;
	int sz = size(str);
	TMonom mon;

	for (int i = 0; i < sz; i++)
	{
		if (str[i] >= '1' || str[i] <= '9')
		{
			if (i == 0)
			{
				mon.coef = (str[i] - '0');
			}
			else {
				if (str[i - 1] == '+')
				{
					AddMonom(mon);
					mon.coef = (str[i] - '0');
				}
				if (str[i - 1] == '-')
				{
					AddMonom(mon);
					mon.coef = (-1) * (str[i] - '0');
				}
				if (str[i - 1] == '^')
				{
					if ((str[i - 2] == 'x') || (str[i - 2] == 'X'))
					{
						mon.index = (str[i] - '0') * 100;
					}
					if ((str[i - 2] == 'y') || (str[i - 2] == 'Y'))
					{
						mon.index += (str[i] - '0') * 10;
					}
					if ((str[i - 2] == 'z') || (str[i - 2] == 'Z'))
					{
						mon.index += str[i] - '0';
					}

				}
			}
		}
	}

	AddMonom(mon);
}


TPolinom& TPolinom::operator=(TPolinom& other)
{
	if (this != &other) {
		while (!this->IsEmpty()) {
			this->DeleteFirst();
		}
		TNode<TMonom>* current = other.pHead->pNext;
		while (current != nullptr) {
			this->AddMonom(current->value);
			current = current->pNext;
		}
	}
	return *this;
}


void TPolinom::AddMonom(TMonom m)
{
	if (m.coef == 0) throw invalid_argument("Cannot add monom with zero coefficient");
	this->Reset();
	bool isAdded = false;
	while (!this->IsEnd()) {
		if (this->pCurrent->value.index == m.index) {
			this->pCurrent->value.coef += m.coef;
			isAdded = true;
			break;
		}
		this->GoNext();
	}
	if (!isAdded) this->InsertLast(m);
	pHead->pNext = this->pFirst;
}




TPolinom& TPolinom::operator+(TPolinom& other)
{
	if (other.IsEmpty()) throw invalid_argument("Cannot add an empty polynomial");
	TNode<TMonom>* current = other.pHead->pNext;
	while (current != nullptr) {
		this->AddMonom(current->value);
		current = current->pNext;
	}
	return *this;
}




bool TPolinom::operator==(TPolinom& other) {
	if (this->GetLength() != other.GetLength()) return false;
	TNode<TMonom>* thisCurrent = this->pHead->pNext;
	TNode<TMonom>* otherCurrent = other.pHead->pNext;
	while (thisCurrent != nullptr && otherCurrent != nullptr) {
		if (!(thisCurrent->value == otherCurrent->value)) { return false; }
		thisCurrent = thisCurrent->pNext;
		otherCurrent = otherCurrent->pNext;
	}
	return thisCurrent == otherCurrent;
}

string TPolinom::ToString()
{
	string result;
	int sz = GetLength();
	Reset();
	for (int i = 0; i < sz; i++) {
		TMonom mon;
		mon = GetCurrentItem();
		double A = mon.GetCoef();
		int ind = mon.GetIndex();
		result += to_string(mon.GetCoef());
		result += "X^";
		result += to_string((ind - ind % 100) / 100);
		result += " Y^";
		result += to_string(((ind % 100) - (ind % 10)) / 10);
		result += " Z^";
		result += to_string(ind % 10);
		if (i < sz - 1)
			GoNext();
		mon = GetCurrentItem();
		if (i != sz - 1)
			if (mon.GetCoef() > 0)
				result += " + ";
		if (mon.GetCoef() < 0)
			result += " ";

	}
	Reset();
	return result;
}