#pragma once

enum class Protocol
{
	// Send : 쿼리(string)
	// Receive : 결과값 없음(null)
	// Todo : 쿼리를 처리합니다.
	DB_QUERY,
	// Send : 쿼리(string)
	// Receive : 열 개수(int32_t), 열 이름(string), 값(string), ...
	// Todo : 쿼리를 처리한 후 결과값을 보냅니다.
	DB_RESULT,
	// Send : 쿼리(string)
	// Receive : 행 개수(int32_t), 열 개수(int32_t), 열 이름(string), 값 (string), ..., 열 개수(int32_t), ...
	// Todo : 쿼리를 처리한 후 결과값을 보냅니다.
	DB_RESULT_ROWS,
#define PROTOCOL_LOGIN_SUCCESS 1
#define PROTOCOL_LOGIN_FAIL 2
	// Send : 아이디(string), 비밀번호(string)
	// Receive : 결과(int32_t), [메시지(string)]
	// Todo : 로그인을 처리한 후 결과를 보냅니다.
	// Todo : 결과(int32_t)
	// Todo : PROTOCOL_LOGIN_SUCCESS = 성공, PROTOCOL_LOGIN_FAIL = 실패
	// Todo : 실패시 메시지를 보냅니다.
	LOGIN,
	// Send : 아이디(string)
	// Receive : 결과값 없음(null)
	// Todo : 로그아웃을 처리합니다.
	LOGOUT,
#define PROTOCOL_REGISTER_SUCCESS 1
#define PROTOCOL_REGISTER_FAIL 2
	// Send : 열 개수(int32_t), 열 이름(string), 값(string), ...
	// Receive : 결과(int32_t), [메시지(string)]
	// Todo : 회원가입을 처리한 후 결과를 보냅니다.
	// Todo : 결과(int32_t)
	// Todo : PROTOCOL_REGISTER_SUCCESS = 성공, PROTOCOL_REGISTER_FAIL = 실패
	// Todo : 실패시 메시지를 보냅니다.
	REGISTER,
	// Send : 보내는 값 없음(null)
	// Receive : 행 개수(int32_t), 별명(string), 승률(float), ...
	// Todo : 랭킹 정보(승률)를 보냅니다. (10위 까지, 30승 이상 집계)
	RANK_WINRATE,
	// Send : 보내는 값 없음(null)
	// Receive : 행 개수(int32_t), 별명(string), 승수(int32_t), ...
	// Todo : 랭킹 정보(다승)를 보냅니다. (10위 까지)
	RANK_WIN,
	// Send : 보내는 값 없음(null)
	// Receive : 행 개수(int32_t), 별명(string), 총 게임 수(int32_t), ...
	// Todo : 랭킹 정보(다전)를 보냅니다. (10위 까지)
	RANK_TOTAL,
	// Send : 보내는 값 없음(null)
	// Receive : 버전(int32_t)
	// Todo : 최신 버전을 보냅니다.
	VERSION
};