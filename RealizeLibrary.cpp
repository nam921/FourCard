#include "RealizeLibrary.h"

namespace Realize {

	string stringf(const char* format, ...)
	{
		char* stringf_formatted_str; // 최종적으로 포맷된 문자열을 저장하는 포인터
		char stringf_buffer[1024]; // stringf의 기본 버퍼

		va_list valist;

		va_start(valist, format);

		int stringf_sizeof_str = vsnprintf(NULL, 0, format, valist);
		if(stringf_sizeof_str >= 1024) // 결과 문자열의 길이가 1024 이상일 경우 메모리를 새로 할당합니다.
			stringf_formatted_str = new char[stringf_sizeof_str + 1];
		else
			stringf_formatted_str = stringf_buffer;

		vsprintf(stringf_formatted_str, format, valist);

		string lpszResult(stringf_formatted_str);

		if(stringf_sizeof_str >= 1024) // 결과 문자열의 길이가 1024 이상일 경우 메모리를 할당했으므로 삭제해줍니다.
			delete[] stringf_formatted_str;

		va_end(valist);

		return lpszResult;
	}

	string _itotstring(int i)
	{
		return stringf("%d", i);
	}

	int stringtoi(const string& lpszString)
	{
		return atoi(lpszString.c_str());
	}

#ifdef WIN32
	void SetConsoleColor(int fontcolor, int bgcolor)
	{
		bgcolor &= 0xf ;
		fontcolor &= 0xf ;

		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , fontcolor | ( bgcolor << 4 ) ) ;  
	}

	void ErrorMessage(HWND hWnd, const string& lpszMessage)
	{
		if(hWnd == NULL) { 
			SetConsoleColor(0xf, 0x4);
			cout << lpszMessage.c_str() << endl;
			SetConsoleColor(0xf, 0x2);
		}
		else
			MessageBox(hWnd, lpszMessage.c_str(), ("SilenceStory"), MB_ICONERROR);
	}
	void PrintMessage(HWND hWnd, const string& lpszMessage)
	{
		if(hWnd == NULL) {
			SetConsoleColor(0xf, 0x3);
			cout << lpszMessage.c_str() << endl;
			SetConsoleColor(0xf, 0x2);
		}
		else
			MessageBox(hWnd, lpszMessage.c_str(), ("SilenceStory"), MB_ICONINFORMATION);
	}

	void AppendWindowText(HWND hWnd, LPCSTR lpszString)
	{
		int nOldStringLength = GetWindowTextLength(hWnd);
		SendMessage(hWnd, EM_SETSEL, nOldStringLength, nOldStringLength);
		SendMessage(hWnd, EM_REPLACESEL, TRUE, (LPARAM)lpszString);
	}

	CFont::CFont(int cHeight, LPCSTR lpszFacename, int cWeight, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
	{
		LOGFONT _LogFont = {cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE};
		::ZeroMemory(_LogFont.lfFaceName, sizeof(char) * LF_FACESIZE);
		strcpy(_LogFont.lfFaceName, lpszFacename);
		memcpy(&LogFont, &_LogFont, sizeof(LOGFONT));

		hFont = CreateFont(cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE, lpszFacename);
		hOldFont = NULL;
		hDC = NULL;
	}
	CFont::CFont(HDC hDC, int cHeight, LPCSTR lpszFacename, int cWeight, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut) : hDC(hDC)
	{
		LOGFONT _LogFont = {cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE};
		::ZeroMemory(_LogFont.lfFaceName, sizeof(char) * LF_FACESIZE);
		strcpy(_LogFont.lfFaceName, lpszFacename);
		memcpy(&LogFont, &_LogFont, sizeof(LOGFONT));

		hFont = CreateFont(cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE, lpszFacename);
		hOldFont = (HFONT)SelectObject(hDC, hFont);
	}
	void CFont::SetFont(HWND hWnd)
	{
		SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, NULL);
	}
	void CFont::NewFont(int cHeight, LPCSTR lpszFacename, int cWeight, BOOL bItalic, BOOL bUnderline, BOOL bStrikeOut)
	{
		if(hDC != NULL)
			DeleteObject(SelectObject(hDC, hOldFont));
		else
			DeleteObject(hFont);

		LOGFONT _LogFont = {cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE};
		::ZeroMemory(_LogFont.lfFaceName, sizeof(char) * LF_FACESIZE);
		strcpy(_LogFont.lfFaceName, lpszFacename);
		memcpy(&LogFont, &_LogFont, sizeof(LOGFONT));

		hFont = CreateFont(cHeight, 0, 0, 0, cWeight, bItalic, bUnderline, bStrikeOut, DEFAULT_CHARSET, 0, 0, 0, DEFAULT_PITCH | FF_DONTCARE, lpszFacename);

		if(hDC != NULL)
			hOldFont = (HFONT)SelectObject(hDC, hFont);
	}
	CFont::~CFont()
	{
		if(hOldFont != NULL)
			DeleteObject(SelectObject(hDC, hOldFont));
		else
			DeleteObject(hFont);
	}
#endif
	int send(SOCKET s, const char* buf, int len)
	{	
		int bytes_to_send = len;
		int bytes_sent = 0;

		while(bytes_to_send > 0) {
			int sent_bytes = ::send(s, buf, bytes_to_send, 0);

			if(sent_bytes < 0)
				return sent_bytes;

			bytes_to_send -= sent_bytes;
			bytes_sent += sent_bytes;

			buf += sent_bytes;
		}

		return bytes_sent;
	}
	int recv(SOCKET s, char* buf, int len)
	{
		int bytes_to_receive = len;
		int bytes_received = 0;

		while(bytes_to_receive > 0) {
			int receive_bytes = ::recv(s, buf, bytes_to_receive, 0);

			if(receive_bytes <= 0)
				return receive_bytes;

			bytes_to_receive -= receive_bytes;
			bytes_received += receive_bytes;

			buf += receive_bytes;
		}

		return bytes_received;
	}
#ifdef WIN32
	void HandleError(HWND hWnd, const string& lpszString, HWND hEdit, fstream& hLogFile)
	{
		ErrorMessage(hWnd, lpszString);
		WriteLog(lpszString, hEdit, hLogFile);
		DestroyWindow(hWnd);
	}
	inline bool HandleSocketError(int retval, HWND hWnd, const string& lpszString, HWND hEdit, fstream& hLogFile)
	{
		if(CheckSocketError(retval)) {
			HandleError(hWnd, lpszString, hEdit, hLogFile);
			return true;
		}
		else
			return false;
	}

	void WriteLog(const string& lpszLog, HWND hEdit, fstream& hLogFile)
	{ 
		time_t rawtime;
		struct tm * timeinfo;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		string lpszString = stringf(("%4d-%02d-%02d %02d:%02d:%02d @ %s\n"), timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, lpszLog.c_str());
		AppendWindowText(hEdit, lpszString.c_str());
		hLogFile << lpszString;
	}

#endif

	void WriteLog(const string& lpszLog, fstream& hLogFile)
	{
		time_t rawtime;
		struct tm * timeinfo;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		string lpszString = stringf(("%4d-%02d-%02d %02d:%02d:%02d @ %s\n"), timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, lpszLog.c_str());
		hLogFile << lpszString;
	}

	string getpeername(SOCKET Socket)
	{
		sockaddr_in SocketAddress;
		int namelen = sizeof(SocketAddress);
		::getpeername(Socket, reinterpret_cast<::sockaddr*> (&SocketAddress), &namelen);

#ifdef UNICODE
		return stringf(("%hs"), inet_ntoa(SocketAddress.sin_addr));
#else
		return inet_ntoa(SocketAddress.sin_addr);
#endif
	}

	namespace Socket
	{/*
			Packet();
			Packet(const Packet& SrPacket);
			Packet& operator=(const Packet& SrPacket);
			void Build(const int32_t id, const int32_t number_of_data, ...);
			int Build(SOCKET Socket);
			const int32_t GetID() const;
			vector<string> GetData() const;
			const char* GetPacket() const;
			string ToString() const;
			~Packet();*/

		Packet::Packet()
		{
			packet = NULL;
		}
		
		Packet::Packet(const int32_t id, const int32_t number_of_data, ...)
		{
			packet = NULL;
			va_list valist;
			va_start(valist, number_of_data);

			unsigned long PacketSize = 4 + 4 + 4; // 남은 패킷 크기 + 패킷 클래스 + 매개변수 개수

			vector<char*> Parameters;
			for(int i=0; i<number_of_data; i++) {
				Parameters.push_back(va_arg(valist, char*));
				PacketSize += 4 + strlen(Parameters.back()) + 1; // 매개변수 크기 + 데이터 + 널 문자
			}

			if(packet != NULL)
				delete[] packet;

			size_of_packet = PacketSize;
			packet = new char[PacketSize];

			PacketSize -= 4;
			memcpy(&packet[0], &PacketSize, 4); // 남은 패킷 크기

			memcpy(&packet[4], &id, 4); // 패킷 클래스

			memcpy(&packet[8], &number_of_data, 4); // 매개변수 개수

			int Packet_Offset = 12;
			for(auto it = Parameters.begin(); it != Parameters.end(); it++) {
				int32_t Parameter_Size = strlen(*it) + 1;
				memcpy(&packet[Packet_Offset], &Parameter_Size, 4);
				Packet_Offset += 4;

				memcpy(&packet[Packet_Offset], *it, Parameter_Size);
				Packet_Offset += Parameter_Size;
			}

			va_end(valist);
		}

		Packet::Packet(const Packet& SrPacket)
		{
			packet = new char[SrPacket.size_of_packet];
			memcpy(packet, SrPacket.packet, SrPacket.size_of_packet);

			size_of_packet = SrPacket.size_of_packet;
		}
		Packet& Packet::operator=(const Packet& SrPacket)
		{
			packet = new char[SrPacket.size_of_packet];
			memcpy(packet, SrPacket.packet, SrPacket.size_of_packet);

			size_of_packet = SrPacket.size_of_packet;

			return *this;
		}
		void Packet::Build(const int32_t Classes, const int32_t nParameter, ...)
		{
			va_list valist;
			va_start(valist, nParameter);

			unsigned long PacketSize = 4 + 4 + 4; // 남은 패킷 크기 + 패킷 클래스 + 매개변수 개수

			vector<char*> Parameters;
			for(int i=0; i<nParameter; i++) {
				Parameters.push_back(va_arg(valist, char*));
				PacketSize += 4 + strlen(Parameters.back()) + 1; // 매개변수 크기 + 데이터 + 널 문자
			}

			if(packet != NULL)
				delete[] packet;

			size_of_packet = PacketSize;
			packet = new char[PacketSize];

			PacketSize -= 4;
			memcpy(&packet[0], &PacketSize, 4); // 남은 패킷 크기

			memcpy(&packet[4], &Classes, 4); // 패킷 클래스

			memcpy(&packet[8], &nParameter, 4); // 매개변수 개수

			int Packet_Offset = 12;
			for(auto it = Parameters.begin(); it != Parameters.end(); it++) {
				int32_t Parameter_Size = strlen(*it) + 1;
				memcpy(&packet[Packet_Offset], &Parameter_Size, 4);
				Packet_Offset += 4;

				memcpy(&packet[Packet_Offset], *it, Parameter_Size);
				Packet_Offset += Parameter_Size;
			}

			va_end(valist);
		}
		int Packet::Build(SOCKET Socket)
		{
			int Error;

			if(packet != NULL)
				delete[] packet;

			int32_t bytes_to_receive;
			if((Error = recv(Socket, (char*) &bytes_to_receive, 4)) < 4)
				return Error;

			packet = new char[bytes_to_receive + 4];
			memcpy(&packet[0], &bytes_to_receive, 4);

			size_of_packet = bytes_to_receive + 4;

			if((Error = recv(Socket, (char*) packet + 4, bytes_to_receive)) < bytes_to_receive)
				return Error;

			return size_of_packet;
		}
		const int32_t Packet::GetID() const
		{
			unsigned long Classes;
			memcpy(&Classes, &packet[4], 4);

			return Classes;
		}
		vector<string> Packet::GetData() const
		{
			vector<string> Parameters;

			int32_t nParameter;
			memcpy(&nParameter, &packet[8], 4);

			int Packet_Offset = 12;
			for(int i=0; i<nParameter; i++) {
				int32_t Parameter_Size;
				memcpy(&Parameter_Size, &packet[Packet_Offset], 4);

				Packet_Offset += 4;

				char* TempString = (char*) malloc(Parameter_Size);
				memcpy(TempString, &packet[Packet_Offset], Parameter_Size);

				Packet_Offset += Parameter_Size;

				Parameters.push_back(TempString);

				free(TempString);
			}

			return Parameters;
		}
		string Packet::ToString() const
		{
			if(packet != NULL) {
				string lpszString;

				lpszString += stringf(("#패킷 크기 = %d, 식별자 = %08x, 데이터 = "), size_of_packet, GetID());

				vector<string> Parameters = GetData();
				for(auto it = Parameters.begin(); it != Parameters.end(); it++) {
					lpszString += ('"') + *it + ("\", ");
				}
				if(Parameters.size() >= 1) {
					lpszString.pop_back();
					lpszString.pop_back();
				}

				lpszString += ('#');

				return lpszString;
			}
			else
				return ("패킷이 NULL 입니다.");
		}
		Packet::~Packet()
		{
			if(packet != NULL)
				delete[] packet;
		}
		Client::Client(const char* ip, int port, fstream& hLogFile, function<void(const char*)> listener_error) : hLogFile(hLogFile), listener_error(listener_error)
		{
			int ret;
#ifdef WIN32
			WSADATA wsaData;
			//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
			WORD version = MAKEWORD(2, 0);
			ret = WSAStartup(version, &wsaData);//win sock start up
			if ( ret ) {
				WriteLog(stringf(("Client::Client : Error %lu -> WinSock 초기화에 실패했습니다."), GetError()), hLogFile);
				listener_error(stringf(("Client::Client : Error %lu -> WinSock 초기화에 실패했습니다."), GetError()).c_str());
				return;
			}
#endif
			Socket = socket(AF_INET, SOCK_STREAM, 0);
			if ( Socket == INVALID_SOCKET ) {
				WriteLog(stringf(("Client::Client : Error %lu -> 소켓 생성에 실패했습니다."), GetError()), hLogFile);
				listener_error(stringf(("Client::Client : Error %lu -> 소켓 생성에 실패했습니다."), GetError()).c_str());
				return;
			}

			struct timeval tv; 
			tv.tv_sec = Socket_Timeout / 1000; 
			tv.tv_usec = Socket_Timeout_usec;

			setsockopt(this->Socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&tv), sizeof(tv)); 

			struct sockaddr_in svraddr;
			svraddr.sin_family = AF_INET;
			svraddr.sin_addr.s_addr = inet_addr(ip);
			svraddr.sin_port = htons(port);
			ret = connect(Socket, (struct sockaddr*)&svraddr, sizeof(svraddr));
			if ( ret == SOCKET_ERROR ) {
				WriteLog(stringf(("Client::Client : Error %lu -> 연결에 실패했습니다."), GetError()), hLogFile);
				listener_error(stringf(("Client::Client : Error %lu -> 연결에 실패했습니다."), GetError()).c_str());
				return;
			}
		}
		int Client::GetError() {
#ifdef WIN32
			return (WSAGetLastError());
#else
			return (errno);
#endif
		}
		int Client::Close()
		{
#ifdef WIN32
			return (closesocket(Socket));
#else
			return (close(Socket));
#endif
		}
		int Client::Clean()
		{
#ifdef WIN32
				return (WSACleanup());
#endif
				return 0;
		}
		int Client::Send(const Packet& Packet)
		{
			int Error;
			if(send(Socket, Packet.packet, Packet.size_of_packet) == SOCKET_ERROR) {
				WriteLog(stringf(("Client::Send : Error %lu -> 패킷을 보내는데에 실패했습니다."), Error = GetError()), hLogFile);
				listener_error(stringf(("Client::Send : Error %lu -> 패킷을 보내는데에 실패했습니다."), Error = GetError()).c_str());
				return Error;
			}

			return 0;
		}
		Packet Client::Receive(int* lpError)
		{
			int Error;
			Packet Packet;

			Error = Packet.Build(Socket);

			if(Error == GetError())
			{
				if(lpError != NULL)
					*lpError = Error;
				WriteLog(stringf(("Client::Receive : Error %lu -> 패킷을 받는데에 실패했습니다."), *lpError), hLogFile);
				listener_error(stringf(("Client::Receive : Error %lu -> 패킷을 받는데에 실패했습니다."), *lpError).c_str());
				return Packet;
			}

			if(lpError != NULL)
				*lpError = 0;

			return Packet;
		}
		void Client::setErrorListener(const std::function<void(const char*)>& listener) {
			listener_error = listener;
		}
		Client::~Client()
		{
			Close();
			Clean();
		}
#ifdef WIN32
		Server::Server(char* ip, int port, HWND hWnd, HWND hLog, fstream& hLogFile) : hWnd(hWnd), hLog(hLog), hLogFile(hLogFile)
		{
			InitializeCriticalSection(&CS);

			if(WSAStartup(MAKEWORD(2, 2), &Wsa) != 0) {
				ErrorMessage(hWnd, stringf(("Server::Server : Error %lu -> WSADATA 초기화에 실패하였습니다."), GetLastError()));
				DestroyWindow(hWnd);
			}

			SYSTEM_INFO SystemInfo;
			GetSystemInfo(&SystemInfo);

			dwNumberOfThreads = SystemInfo.dwNumberOfProcessors * 2 + 2;

			if((hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0)) == NULL) {
				ErrorMessage(hWnd, stringf(("Server::Server : Error %lu -> IO Completion Port를 생성하는데 실패했습니다."), GetLastError()));
				DestroyWindow(hWnd);
			}

			hThreads = new HANDLE[dwNumberOfThreads + 1];

			for(int i=1; i <= dwNumberOfThreads; i++)
				hThreads[i] = (HANDLE) _beginthreadex(NULL, 0, IOCPThreadRoutine, this, 0, NULL);

			if((Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
				ErrorMessage(hWnd, stringf(("Server::Server : Error %lu -> 소켓 생성에 실패하였습니다."), GetLastError()));
				DestroyWindow(hWnd);
			}

			ZeroMemory(&SocketAddress, sizeof(SOCKADDR_IN));

			SocketAddress.sin_family = AF_INET;
			SocketAddress.sin_port = htons(port);
			SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

			if(::bind(Socket, (SOCKADDR*) &SocketAddress, sizeof(SocketAddress)) == SOCKET_ERROR) {
				ErrorMessage(hWnd, stringf(("Server::Server : Error %lu -> 소켓 바인딩에 실패했습니다."), GetLastError()));
				DestroyWindow(hWnd);
			}

			if(listen(Socket, SOMAXCONN) == SOCKET_ERROR) {
				ErrorMessage(hWnd, stringf(("Server::Server : Error %lu -> 서버 연결 받기를 시작하는데에 실패하였습니다."), GetLastError()));
				DestroyWindow(hWnd);
			}

			WriteLog(("Server::Server() -> Listen을 시작했습니다."), hLog, hLogFile);

			hThreads[0] = (HANDLE) _beginthreadex(0, 0, AcceptThreadRoutine, this, CREATE_SUSPENDED, 0);
		}
		unsigned int __stdcall Server::IOCPThreadRoutine(void* Parameter)
		{
			Server* server = (Server*) Parameter;

			int Error;

			DWORD NumberOfBytesTransferred = 0;
			while(1) {
				SOCKET_INFO* Socket_Info = NULL;
				IO_DATA* IO_Data = NULL;

				Packet ReceivedPacket;

				Error = GetQueuedCompletionStatus(server->hIOCP, &NumberOfBytesTransferred, (PULONG_PTR) &Socket_Info, (LPOVERLAPPED*) &IO_Data, INFINITE);
				if(!Error) {
					if((Error = GetLastError()) != ERROR_NETNAME_DELETED) {
						EnterCriticalSection(&server->CS);
						HandleError(server->hWnd, stringf(("Server::IOCPThreadRoutine() : Error %lu\n -> IO Completion Port의 큐에서 데이터를 얻어오는데에 실패했습니다."), Error), server->hLog, server->hLogFile);
						LeaveCriticalSection(&server->CS);
						break;
					}
					else {
						EnterCriticalSection(&server->CS);
						WriteLog(stringf(("Server::IOCPThreadRoutine() : Error %lu\n -> 연결이 끊어졌습니다. (%s)"), Error, getpeername(Socket_Info->Socket).c_str()), server->hLog, server->hLogFile);
						server->RemoveSocket(&Socket_Info, &IO_Data);
						LeaveCriticalSection(&server->CS);
						continue;
					}
				}

				if(IO_Data->code != IO_RECV)
					continue;

				Error = ReceivedPacket.Build(Socket_Info->Socket);
				if(Error <= 0) {
					EnterCriticalSection(&server->CS);
					if(Error == 0)
						WriteLog(stringf(("Server::IOCPThreadRoutine() : Error %lu\n -> 우아하게 연결이 끊어졌습니다. (%s)"), Error, getpeername(Socket_Info->Socket).c_str()), server->hLog, server->hLogFile);
					else
						WriteLog(stringf(("Server::IOCPThreadRoutine() : Error %lu\n -> 패킷을 읽는데에 실패했습니다."), GetLastError()), server->hLog, server->hLogFile);
					server->RemoveSocket(&Socket_Info, &IO_Data);
					LeaveCriticalSection(&server->CS);
					continue;
				}
				
				EnterCriticalSection(&server->CS);
				WriteLog(stringf(("Server::IOCPThreadRoutine() -> 패킷을 받는데에 성공했습니다.\n -> %s"), ReceivedPacket.ToString().c_str()), server->hLog, server->hLogFile);
				LeaveCriticalSection(&server->CS);

				EnterCriticalSection(&server->CS);

				if(server->listener_read.find(ReceivedPacket.GetID()) != server->listener_read.end())
					server->listener_read[ReceivedPacket.GetID()](Socket_Info, ReceivedPacket);

				LeaveCriticalSection(&server->CS);

				ZeroMemory(IO_Data, sizeof(IO_DATA));

				if(server->Receive(Socket_Info->Socket, IO_Data) == SOCKET_ERROR && (Error = GetLastError()) != WSA_IO_PENDING ) {
					EnterCriticalSection(&server->CS);
					WriteLog(stringf(("Server::IOCPThreadRoutine() : Error %lu\n -> 패킷을 받도록 요청하는데에 실패하였습니다."), Error), server->hLog, server->hLogFile);
					server->RemoveSocket(&Socket_Info, &IO_Data);
					LeaveCriticalSection(&server->CS);
					continue;
				}
			}

			return 0;
		}
		unsigned int __stdcall Server::AcceptThreadRoutine(void* Parameter)
		{
			Server* server = (Server*) Parameter;

			while(1) {
				SOCKET_INFO* CompletionKey = new SOCKET_INFO;
				ZeroMemory(CompletionKey, sizeof(SOCKET_INFO));

				if((CompletionKey->Socket = accept(server->Socket, NULL, 0)) == INVALID_SOCKET) {
					EnterCriticalSection(&server->CS);
					WriteLog(stringf(("Server::AcceptThreadRoutine() : Error %lu\n -> 클라이언트와 연결하는데에 실패했습니다."), GetLastError()), server->hLog, server->hLogFile);
					LeaveCriticalSection(&server->CS);
					delete CompletionKey;
					break;
				}

				if(!CreateIoCompletionPort((HANDLE) CompletionKey->Socket, server->hIOCP, (ULONG_PTR) CompletionKey, 0)) {
					EnterCriticalSection(&server->CS);
					WriteLog(stringf(("Server::AcceptThreadRoutine() : Error %lu\n -> 연결에 성공한 소켓과 IO Completion Port를 연결하는데에 실패했습니다."), GetLastError()), server->hLog, server->hLogFile);
					LeaveCriticalSection(&server->CS);
					closesocket(CompletionKey->Socket);
					delete CompletionKey;
					continue;
				}

				IO_DATA* IO_Data = new IO_DATA;
				DWORD Error;
				if(server->Receive(CompletionKey->Socket, IO_Data) == SOCKET_ERROR && (Error = GetLastError()) != WSA_IO_PENDING) {
					EnterCriticalSection(&server->CS);
					WriteLog(stringf(("Server::AcceptThreadRoutine() : Error %lu\n -> 패킷을 받도록 요청하는데에 실패하였습니다."), Error), server->hLog, server->hLogFile);
					LeaveCriticalSection(&server->CS);
					closesocket(CompletionKey->Socket);
					delete IO_Data;
					delete CompletionKey;
					continue;
				}

				server->listener_accept(CompletionKey);

				EnterCriticalSection(&server->CS);
				server->Socket_Info_List.push_back(CompletionKey);
				server->IO_Data_List.push_back(IO_Data);
				WriteLog(stringf(("Server::AcceptThreadRoutine() -> 클라이언트 연결 (%s)"), getpeername(CompletionKey->Socket).c_str()), server->hLog, server->hLogFile);
				LeaveCriticalSection(&server->CS);

			}

			return 0;
		}
		int Server::Send(SOCKET Socket, const Packet& Packet)
		{
			IO_DATA IO_Data;
			ZeroMemory(&IO_Data, sizeof(IO_Data));

			IO_Data.code = IO_SEND;

			WSABUF WSABuf;
			WSABuf.len = Packet.size_of_packet;
			WSABuf.buf = (char*) Packet.packet;

			DWORD NumberOfBytesSent = 0;
			DWORD Error;

			if(WSASend(Socket, &WSABuf, 1, &NumberOfBytesSent, NULL, &IO_Data, NULL) == SOCKET_ERROR && (Error = GetLastError()) != WSA_IO_PENDING) {
				WriteLog(stringf(("Server::WSASend : Error %lu -> 패킷을 보내는데에 실패했습니다."), GetLastError()), hLog, hLogFile);
				return Error;
			}

			WriteLog(stringf(("Server::WSASend() -> 패킷을 보내는데에 성공했습니다.\n -> %s"), Packet.ToString().c_str()), hLog, hLogFile);

			return 0;
		}
		int Server::Receive(SOCKET Socket, IO_DATA* IO_Data)
		{
			DWORD NumberOfBytesRecvd = 0, Flags = 0;

			ZeroMemory(IO_Data, sizeof(IO_DATA));
			IO_Data->code = IO_RECV;

			return WSARecv(Socket, &IO_Data->WSABuf, 1, &NumberOfBytesRecvd, &Flags, IO_Data, NULL);
		}
		void Server::RemoveSocket(SOCKET_INFO** Socket_Info, IO_DATA** IO_Data)
		{
			listener_close(*Socket_Info);

			closesocket((*Socket_Info)->Socket);

			if(*Socket_Info != NULL) {
				Socket_Info_List.remove(*Socket_Info);
				delete *Socket_Info;
				*Socket_Info = NULL;
			}
			if(*IO_Data != NULL) {
				IO_Data_List.remove(*IO_Data);
				delete *IO_Data;
				*IO_Data = NULL;
			}
		}
		void Server::Start()
		{
			ResumeThread(hThreads[0]);
		}
		void Server::addReadListener(const int32_t id, const std::function<void(SOCKET_INFO*, const Packet&)>& listener)
		{
			listener_read[id] = listener;
		}
		void Server::setAcceptListener(const std::function<void(SOCKET_INFO*)>& listener)
		{
			listener_accept = listener;
		}
		void Server::setCloseListener(const std::function<void(SOCKET_INFO*)>& listener)
		{
			listener_close = listener;
		}
		Server::~Server()
		{
			for(auto it = Socket_Info_List.begin(); it != Socket_Info_List.end(); it++) {
				closesocket((*it)->Socket);
				delete *it;
			}
			for(auto it = IO_Data_List.begin(); it != IO_Data_List.end(); it++) {
				delete *it;
			}
			closesocket(Socket);
			CloseHandle(hIOCP);

			WriteLog(("Server::~Server() -> 스레드들이 완전히 종료될 때 까지 기다리고 있습니다.."), hLog, hLogFile);
			WaitForMultipleObjects(dwNumberOfThreads + 1, hThreads, TRUE, INFINITE);
			for(int i=0; i<dwNumberOfThreads + 1; i++)
				CloseHandle(hThreads[i]);

			delete[] hThreads;

			WSACleanup();

			WriteLog(("Server::~Server() -> 서버가 종료되었습니다."), hLog, hLogFile);

			DeleteCriticalSection(&CS);
		}
#endif
	}


#ifdef REALIZE_LIBRARY_USING_MYSQL
	SilenceStoryMySQL::SilenceStoryMySQL(HWND hWnd, HWND hLog, fstream& hLogFile) : hWnd(hWnd), hLog(hLog), hLogFile(hLogFile)
	{
		MySQL_Connection = mysql_init(NULL);

		if(mysql_real_connect(MySQL_Connection, MySQL_Host, MySQL_User, MySQL_Password, MySQL_DB, MySQL_Port, NULL, NULL) != MySQL_Connection) {
			WriteLog(stringf(("SilenceStoryMySQL::SilenceStoryMySQL() : Error %lu\n -> MySQL에 연결하는데에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			return;
		}

		WriteLog(stringf(("SilenceStoryMySQL::SilenceStoryMySQL() -> MySQL에 연결하는데에 성공했습니다.")), hLog, hLogFile);
	}
	vector<map<string, string>> SilenceStoryMySQL::Select(string MySQLable, string MySQL_Column, string MySQL_Where, string MySQL_Description)
	{
		string MySQL_Query = stringf(("SELECT %s FROM %s WHERE %s %s"), MySQL_Column.c_str(), MySQLable.c_str(), MySQL_Where.c_str(), MySQL_Description.c_str());
		vector<map<string, string>> MySQL_Result;

		if(mysql_query(MySQL_Connection, MySQL_Query.c_str())) {
			WriteLog(stringf(("SilenceStoryMySQL::Select() : Error %u\n -> 쿼리 실행에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			isError = true;
			return MySQL_Result;
		}
		else {
			MYSQL_RES* MySQL_Res = mysql_store_result(MySQL_Connection);

			if(MySQL_Res == NULL) {
				WriteLog(stringf(("SilenceStoryMySQL::Select() : Error %u\n -> 쿼리 결과를 저장하는데에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
				isError = true;
				return MySQL_Result;
			}

			MYSQL_ROW MySQL_Row;
			MYSQL_FIELD* MySQL_Field = mysql_fetch_fields(MySQL_Res);
			int MySQL_Num_Fields = mysql_num_fields(MySQL_Res);

			while((MySQL_Row = mysql_fetch_row(MySQL_Res)) != NULL) {
				map<string, string> MySQL_Row_Result;

				for(int i=0; i<MySQL_Num_Fields; i++)
					MySQL_Row_Result[MySQL_Field[i].name] = MySQL_Row[i];

				MySQL_Result.push_back(MySQL_Row_Result);
			}

			mysql_free_result(MySQL_Res);
		}

		isError = false;
		return MySQL_Result;
	}
	string SilenceStoryMySQL::Result(string Query)
	{
		string MySQL_Query = Query;
		string MySQL_Result;

		if(mysql_query(MySQL_Connection, MySQL_Query.c_str())) {
			WriteLog(stringf(("SilenceStoryMySQL::Result() : Error %u\n -> 쿼리 실행에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			isError = true;
			return MySQL_Result;
		}
		else {
			MYSQL_RES* MySQL_Res = mysql_store_result(MySQL_Connection);

			if(MySQL_Res == NULL) {
				WriteLog(stringf(("SilenceStoryMySQL::Result() : Error %u\n -> 쿼리 결과를 저장하는데에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
				isError = true;
				return MySQL_Result;
			}

			MYSQL_ROW MySQL_Row;

			if((MySQL_Row = mysql_fetch_row(MySQL_Res)) != NULL)
				MySQL_Result = MySQL_Row[0];

			mysql_free_result(MySQL_Res);
		}

		isError = false;
		return MySQL_Result;
	}
	bool SilenceStoryMySQL::Update(string MySQLable, string MySQL_Set, string MySQL_Where, string MySQL_Description)
	{
		string MySQL_Query = stringf(("UPDATE %s SET %s WHERE %s %s"), MySQLable.c_str(), MySQL_Set.c_str(), MySQL_Where.c_str(), MySQL_Description.c_str());

		if(mysql_query(MySQL_Connection, MySQL_Query.c_str())) {
			WriteLog(stringf(("SilenceStoryMySQL::Update() : Error %u\n -> 쿼리 실행에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			return false;
		}
		else {
			return true;
		}
	}
	bool SilenceStoryMySQL::Delete(string MySQLable, string MySQL_Where, string MySQL_Description)
	{
		string MySQL_Query = stringf(("DELETE FROM %s WHERE %s %s"), MySQLable.c_str(), MySQL_Where.c_str(), MySQL_Description.c_str());

		if(mysql_query(MySQL_Connection, MySQL_Query.c_str())) {
			WriteLog(stringf(("SilenceStoryMySQL::Delete() : Error %u\n -> 쿼리 실행에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			return false;
		}
		else {
			return true;
		}
	}
	bool SilenceStoryMySQL::Insert(string MySQLable, string MySQL_Columns, string MySQL_Values)
	{
		string MySQL_Query = stringf(("INSERT into %s (%s) VALUES (%s)"), MySQLable.c_str(), MySQL_Columns.c_str(), MySQL_Values.c_str());

		if(mysql_query(MySQL_Connection, MySQL_Query.c_str())) {
			WriteLog(stringf(("SilenceStoryMySQL::Insert() : Error %u\n -> 쿼리 실행에 실패했습니다. (%s)"), mysql_errno(MySQL_Connection), mysql_error(MySQL_Connection)), hLog, hLogFile);
			return false;
		}
		else {
			return true;
		}
	}
	SilenceStoryMySQL::~SilenceStoryMySQL()
	{
		mysql_close(MySQL_Connection);
	}

#endif

}