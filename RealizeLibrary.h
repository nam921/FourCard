#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <regex>
#include <cstdint>

#pragma warning(disable: 4996)
#pragma warning(disable: 4005)

using namespace std;
//#define REALIZE_LIBRARY_USING_MYSQL

#define USING_REALIZE_LIBRARY using namespace Realize;
#define USING_REALIZE_LIBRARY_SOCKET using namespace Realize::Socket;

#ifdef WIN32
	#include <WinSock2.h>
	#include <Windows.h>
	#include <process.h>
	#pragma comment(lib, "ws2_32.lib")
	typedef int				socklen_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <errno.h>
	typedef int				SOCKET;

	//#pragma region define win32 const variable in linux
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
	//#pragma endregion
#endif

namespace Realize {
	// stringf : sprintf와 같은 역할이지만, 결과물을 리턴해줍니다.
	// format : sprintf의 포맷과 같습니다
	string stringf(const char* format, ...);
	
	string _itotstring(int i);

	int stringtoi(const string& lpszString);
#ifdef WIN32
	class CFont
	{
	private:
		HFONT hOldFont;
	public:
		HDC hDC;
		HFONT hFont;
		LOGFONT LogFont;

		// 폰트를 바꿔 주는 클래스 입니다.
		// 소멸자에 의해 자동으로 핸들이 소모되니 메모리 누수에 대한 걱정이 없습니다.
		// 단, 지역변수로 선언하고 윈도우에 핸들을 넘길경우 DeleteObject가 수행되버리니 따로 포인터에 할당하여 윈도우를 파괴할때 이 클래스를 delete하시면 됩니다.
		CFont() { }
		// 폰트만 생성합니다.
		// int cHeight : 폰트의 크기 (픽셀단위)
		// lpszFacename : 폰트 이름 (굴림, ...)
		// cWeight : 폰트 굵기 (FW_ 로 시작)
		// bItalic : 기울임, bUndeline : 밑줄, bStrikeOut : 취소선
		CFont(int cHeight, LPCTSTR lpszFacename, int cWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
		// HDC에 폰트를 자동으로 사용하도록 합니다.
		// int cHeight : 폰트의 크기 (픽셀단위)
		// lpszFacename : 폰트 이름 (굴림, ...)
		// cWeight : 폰트 굵기 (FW_ 로 시작)
		// bItalic : 기울임, bUndeline : 밑줄, bStrikeOut : 취소선
		CFont(HDC hDC, int cHeight, LPCTSTR lpszFacename, int cWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
		// 현재 폰트 클래스의 폰트를 hWnd에 적용합니다.
		void SetFont(HWND hWnd);
		// 현재 클래스의 폰트를 삭제하고 새 폰트를 생성합니다.
		void NewFont(int cHeight, LPCTSTR lpszFacename, int cWeight = FW_NORMAL, BOOL bItalic = FALSE, BOOL bUnderline = FALSE, BOOL bStrikeOut = FALSE);
		~CFont();
	};
#endif
	int send(SOCKET s, const char* buf, int len);
	int recv(SOCKET s, char* buf, int len);
#ifdef WIN32
	void SetConsoleColor(int fontcolor, int bgcolor);

	void ErrorMessage(HWND hWnd, const string& lpszMessage);
	void PrintMessage(HWND hWnd, const string& lpszMessage);

	void AppendWindowText(HWND hWnd, LPCTSTR lpszString);

	void WriteLog(const string& lpszLog, HWND hEdit, fstream& hLogFile);
#endif
	void WriteLog(const string& lpszLog, fstream& hLogFile);

#define Socket_BufferSize 1024
#define Socket_Timeout 60000
#define Socket_Timeout_usec 0

#define Realize_Library_Socket_Read_Listener_Bind(__listener__) std::bind(&__listener__, this, std::placeholders::_1, std::placeholders::_2)

#define CheckSocketError(retval) ((retval) < (int)(Socket_BufferSize * sizeof(char)))
#define HandleThreadSocketError(retval, socket) if(CheckSocketError((retval))) { delete (socket); return 0; }
#ifdef WIN32
	void HandleError(HWND hWnd, const string& lpszString, HWND hEdit, fstream& hLogFile);
	inline bool HandleSocketError(int retval, HWND hWnd, const string& lpszString, HWND hEdit, fstream& hLogFile);
#endif
	string getpeername(SOCKET Socket);

	namespace Socket
	{
#define IO_SEND 1
#define IO_RECV 2
		/*
		패킷 구조

		[ 헤더 섹션 ]
		4바이트 : 패킷 크기를 저장하는 이 부분을 제외한 나머지 패킷의 크기
		4바이트 : 식별자
		4바이트 : 매개변수의 개수

		[ 매개변수 섹션 ]
		4바이트 : 매개변수의 크기
		n바이트 : 매개변수
		*/
		class Packet
		{
		public:
			char* packet;
			long size_of_packet;

			Packet();
			Packet(const int32_t id, const int32_t number_of_data, ...);
			Packet(const Packet& SrcPacket);
			Packet& operator=(const Packet& SrcPacket);
			void Build(const int32_t id, const int32_t number_of_data, ...);
			int Build(SOCKET Socket);
			const int32_t GetID() const;
			vector<string> GetData() const;
			const char* GetPacket() const;
			string ToString() const;
			~Packet();
		};
		struct SOCKET_INFO
		{
			SOCKET Socket;
			void* Info;
		};
#ifdef WIN32
		struct IO_DATA : WSAOVERLAPPED
		{
			WSABUF WSABuf;
			int code;
		};
#endif
		class Client
		{
		private:
			SOCKET Socket;

			fstream& hLogFile;

			function<void(const char*)> listener_error;
		public:
			// 동기 소켓 클라이언트를 생성합니다.
			// hWnd : 오류 메시지를 출력할 윈도우 핸들 입니다.
			Client(const char* ip, int port, fstream& hLogFile, function<void(const char*)> listener_error);
			int GetError();
			int Close();
			int Clean();
			int Send(const Packet& );
			Packet Receive(int* lpError = NULL);
			void setErrorListener(const std::function<void(const char*)>& listener);
			~Client();
		};
#ifdef WIN32
		class Server 
		{
		private:
			WSADATA Wsa;
			SOCKADDR_IN SocketAddress;
			SOCKET Socket;

			HWND hWnd;

			HWND hLog;
			fstream& hLogFile;

			HANDLE* hThreads;
			int dwNumberOfThreads;

			HANDLE hIOCP;
			list<SOCKET_INFO*> Socket_Info_List;
			list<IO_DATA*> IO_Data_List;

			CRITICAL_SECTION CS;

			map<int32_t, std::function<void(SOCKET_INFO*, const Packet&)>> listener_read;
			std::function<void(SOCKET_INFO*)> listener_accept;
			std::function<void(SOCKET_INFO*)> listener_close;
		public:
			void* ParameterEx;

			// 동기 소켓 서버를 생성합니다.
			// hWnd : 에러 메시지를 출력할 윈도우 핸들 입니다.
			// hLog : 로그를 남길 Edit 핸들 (NULL 가능)
			// lpszLogFileName : 로그를 남길 파일의 이름 (NULL 가능)
			// lpOnRead : 소켓이 패킷을 받았을 때 호출되는 콜백 함수 입니다. [] (void*) -> unsigned int __stdcall { } 형식의 lambda를 넘기면 됩니다.
			// lambda의 매개변수로 패킷을 받은 Socket_Info 이 주어집니다. 이 Socket_Info는 꼭 delete해주시기 바랍니다.
			Server(char* ip, int port, HWND hWnd, HWND hLog, fstream& hLogFile);

			static unsigned int __stdcall IOCPThreadRoutine(void* Parameter);
			static unsigned int __stdcall AcceptThreadRoutine(void* Parameter);
			int Send(SOCKET Socket, const Packet& Packet);
			static int Receive(SOCKET Socket, IO_DATA* IO_Data);
			void RemoveSocket(SOCKET_INFO** Socket_Info, IO_DATA** IO_Data);
			void Start();

			void addReadListener(const int32_t id, const std::function<void(SOCKET_INFO*, const Packet&)>& listener);
			void setAcceptListener(const std::function<void(SOCKET_INFO*)>& listener);
			void setCloseListener(const std::function<void(SOCKET_INFO*)>& listener);

			~Server();
		};
#endif
	}

#ifdef REALIZE_LIBRARY_USING_MYSQL

#include "C:\xampp\mysql\include\mysql.h"
#pragma comment(lib, "C:\\xampp\\mysql\\lib\\libmysql.lib")

#define _tmysql_error(MySQL) mysql_error(MySQL).c_str()

#define MySQL_Host "127.0.0.1"
#define MySQL_User "root"
#define MySQL_Password "root"
#define MySQL_DB "SilenceStory"
#define MySQL_Port 3306

	class SilenceStoryMySQL
	{
	private:
		HWND hWnd;

		HWND hLog;
		fstream& hLogFile;

		MYSQL* MySQL_Connection;
	public:
		bool isError;

		SilenceStoryMySQL(HWND hWnd, HWND hLog, fstream& hLogFile);
		vector<map<string, string>> Select(string MySQL_Table, string MySQL_Column, string MySQL_Where, string MySQL_Description = string());
		string Result(string Query);
		bool Update(string MySQL_Table, string MySQL_Set, string MySQL_Where, string MySQL_Description);
		bool Delete(string MySQL_Table, string MySQL_Where, string MySQL_Description);
		bool Insert(string MySQL_Table, string MySQL_Columns, string MySQL_Values);
		~SilenceStoryMySQL();
	};

#endif

}
