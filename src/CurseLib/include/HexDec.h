#pragma once
#include <iostream>
#include <string>

// File Work
namespace fw 
{
	// HecDec
	namespace hd
	{

		// ��������� hex-������ � ���������� �������
		std::string HexTranslate(std::string s);

		// ��������� ����� � hex-������
		std::string DecTranslate(char s);

		// �������� � �������
		unsigned long Degree(unsigned long num, unsigned long ind);

		// ��������� ���������� ���� � hex-������
		std::string ToHex(unsigned long n);

		// ��������� hex-������ � ���������� �������
		size_t ToDec(std::string nh);
	}
}
