#include "FourCard.h"

namespace FourCard
{
	const int VERSION = 10;

	const char* SERVER_IP = "25.37.223.220";
	const int SERVER_PORT = 5807;

	const char* DEFAULT_FONT = "�������";
}

string __stringf(const char* format, ...)
{
	char* __stringf_formatted_str; // ���������� ���˵� ���ڿ��� �����ϴ� ������
	char __stringf_buffer[1024]; // __stringf�� �⺻ ����

	va_list valist;

	va_start(valist, format);

#ifdef WIN32
	int __stringf_sizeof_str = vsnprintf_s(NULL, 0, 0, format, valist);
#else
	int __stringf_sizeof_str = vsnprintf(NULL, 0, format, valist);
#endif
	if(__stringf_sizeof_str >= 1024) // ��� ���ڿ��� ���̰� 1024 �̻��� ��� �޸𸮸� ���� �Ҵ��մϴ�.
		__stringf_formatted_str = new char[__stringf_sizeof_str + 1];
	else
		__stringf_formatted_str = __stringf_buffer;
#ifdef WIN32
	vsprintf_s(__stringf_formatted_str, __stringf_sizeof_str >= 1024 ? __stringf_sizeof_str : 1023, format, valist);
#else
	vsprintf(__stringf_formatted_str, format, valist);
#endif

	string lpszResult(__stringf_formatted_str);

	if(__stringf_sizeof_str >= 1024) // ��� ���ڿ��� ���̰� 1024 �̻��� ��� �޸𸮸� �Ҵ������Ƿ� �������ݴϴ�.
		delete[] __stringf_formatted_str;

	va_end(valist);

	return lpszResult;
}