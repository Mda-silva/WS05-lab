/***********************************************************************
// OOP244 Workshop #5 Lab (part 1)
//
// File  bankaccount.cpp
// Version v0.8 Oct 21st 2023
// Author  Jitesh Arora
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "bankaccount.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

namespace seneca
{
	bankAccount::bankAccount(const char* name, bool checking)
	{

		m_userName[0] = '\0';

		setup(name, checking);

	}

	bool bankAccount::setup(const char* name, bool checking)
	{
		if (isOpen())
			return false;
		if (name == nullptr)
			return false;

		strcpy(m_userName, name);

		m_monthlyTransactions = 0;

		m_checking = checking;

		m_funds = 0;

		return true;
	}

	bool bankAccount::isOpen() const
	{

		return (m_userName[0] != '\0');

	}

	bankAccount::operator bool() const
	{

		return isOpen();

	}

	bankAccount::operator double() const
	{

		return m_funds;

	}


	bankAccount& bankAccount::operator++()
	{
		double interest = 0;

		if (isOpen() && m_funds > 0)

		{
			if (m_checking)
			{

				interest = m_funds * 0.005;

			}
			else
			{

				interest = m_funds * 0.025;

			}

			m_funds += interest;

		}
		
		return *this;
	}

	bankAccount& bankAccount::operator--()
	{
		double fee = 0;

		if (isOpen())
		{
			if (m_checking)
			{

				fee = m_monthlyTransactions * 1.25;

			}
			else
			{

				fee = m_monthlyTransactions * 3.5;

			}
			m_funds -= fee;
		}

		return *this;
	}

	 

	bool bankAccount::operator+=(double val)
	{
		if (isOpen())
		{

			m_funds += val;

			m_monthlyTransactions++;

			cout.setf(ios::fixed);

			cout.precision(2);

			cout << "Deposit $" << val << " for " << m_userName << endl;

			return true;

		}

		return false;
	}

	bool bankAccount::operator-=(double val)
	{
		if (isOpen())
		{

			val *= -1;

			m_funds += val;

			m_monthlyTransactions++;

			cout.setf(ios::fixed);

			cout.precision(2);

			cout << "Withdraw $" << -1 * val << " for " << m_userName << endl;

			return true;

		}
		return false;
	}

	bool bankAccount::operator==(const bankAccount& spec) const
	{
		if (spec.m_funds == m_funds && strcmp(spec.m_userName, m_userName) == 0
			  && spec.m_checking == m_checking)
		{

			return true;

		}

		return false;
	}

	bool bankAccount::operator>(double val) const
	{
		if (isOpen())
		{

			if (m_funds > val) return true;

		}
		return false;
	}

	bool bankAccount::operator<=(double val) const
	{
		if (isOpen())
		{

			if (!(m_funds > val)) return true;

		}
		return false;
	}


	bool bankAccount::operator<<(bankAccount& source)
	{
		if (this->isOpen() && source.isOpen())
		{
			if (source.m_funds > 0)
			{
				cout.setf(ios::fixed);

				cout.precision(2);

				cout << "Transfer $" << source.m_funds << " from " << source.m_userName << " to " << this->m_userName << endl;

				*this += source.m_funds;

				source -= source.m_funds;

				return true;

			}

		}
		return false;
	}

	void bankAccount::display(void) const
	{
		if (isOpen())
		{
			cout.precision(2);
			cout << "Display Account -> User:";
			cout.fill('-');
			cout.width(16);
			cout << m_userName;
			cout.fill(' ');
			cout << " | ";
			cout.setf(ios::right);
			cout.width(8);
			if (m_checking)
			{

				cout << "Checking";

				cout.fill(' ');

			}

			else
			{

				cout << "Savings";

				cout.fill(' ');

			}
			cout.unsetf(ios::right);
			cout << " | Balance: $";
			cout.setf(ios::right);
			cout.width(8);
			cout << m_funds;
			cout.unsetf(ios::right);
			cout << " | Transactions:";
			cout.width(3);
			cout.fill('0');
			cout << m_monthlyTransactions << endl;
			cout.fill(' ');
			
		}
		else
		{

			cout << "Display Account -> User:------- NOT OPEN" << endl;

		}
	}

	

	bool operator>(double lhs, const bankAccount& rhs)
	{
		if ((bool)rhs)
		{

			if (lhs > (double)rhs) return true;

		}

		return false;
	}

	bool operator<=(double lhs, const bankAccount& rhs)
	{

		if (!(lhs > (double)rhs)) return true;

		return false;

	}

}