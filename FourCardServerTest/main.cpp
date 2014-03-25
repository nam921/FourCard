#include <iostream>
#include "RealizeClient.h"

using namespace std;
USING_NS_REALIZE;

class FourCardServerTestClient : public Client
{
private:
public:
	void onError(const char* message)
	{
		cout<<"error: "<<message<<endl;
	}

	void onWarning(const char* message)
	{
		cout<<"warning: "<<message<<endl;
	}

	void onLog(const char* message)
	{
		cout<<"Log: "<<message<<endl;
	}
};

void main()
{
	FourCardServerTestClient client;
	client.connect("127.0.0.1", 5807);

	while(true)
	{
		int32_t id;
		char type;

		Packet packet(0);

		cout << "��Ŷ ID�� �Է��ϼ��� : ";
		cin >> id;

		packet.setID(id);

		while(true)
		{
			cout << "��Ŷ ������ �Է��ϼ��� (0 to end) : ";
			cin >> type;

			if(type == '0') {
				client.sync_send(packet);
				break;
			}


			cin.ignore();

			cout << "��Ŷ �����͸� �Է��ϼ��� : ";
			switch(type)
			{
			case 's':
				{
					char _string[255];
					cin.getline(_string, 255, '\n');
					packet << string(_string);
					break;
				}
			case '4':
				{
					int32_t _int32_t;
					cin >> _int32_t;
					packet << _int32_t;
				break;
				}
			case '8':
				{
					int64_t _int64_t;
					cin >> _int64_t;
					packet << _int64_t;
				break;
				}
			case 'f':
				{
					float _float;
					cin >> _float;
					packet << _float;
					break;
				}
			case 'd':
				{
					double _double;
					cin >> _double;
					packet << _double;
					break;
				}
			}
		}

		if(client.sync_recv(packet)) 
		{
			string type;

			cout << endl << "��Ŷ�� �޾ҽ��ϴ�." << endl;
			cout << "���� �Է� : ";
			cin >> type;

			cout << packet.toString(type.c_str());

			cout << endl;
		}
		else
		{
			cout << endl << "��Ŷ�� ���� ���߽��ϴ�." << endl;
		}
	}

	client.disconnect();
}