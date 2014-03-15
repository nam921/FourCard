#pragma once

enum class Protocol : int32_t
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
#define PROTOCOL_LOGIN_SUCCESS (int32_t) 1
#define PROTOCOL_LOGIN_FAIL (int32_t) 2
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
#define PROTOCOL_REGISTER_SUCCESS (int32_t) 1
#define PROTOCOL_REGISTER_FAIL (int32_t) 2
	// Send : 열 개수(int32_t), 열 이름(string), 값(string), ...
	// Receive : 결과(int32_t), [메시지(string)]
	// Todo : 회원가입을 처리한 후 결과를 보냅니다.
	// Todo : 결과(int32_t)
	// Todo : PROTOCOL_REGISTER_SUCCESS = 성공, PROTOCOL_REGISTER_FAIL = 실패
	// Todo : 실패시 메시지를 보냅니다.
	// Todo : 아이디 (id, 4 ~ 14자 영어, 숫자)
	// Todo : 비밀번호 (password, 4 ~ 14자 영어, 숫자, 특수문자)
	// Todo : 별명 (nickname, 4 ~ 14byte)
	// Todo : 이메일 (email)
	// Todo : 주소 (address)
	// Todo : 연락처 (phone)
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
	VERSION,
#define PROTOCOL_GAME_QUEUE_ENQUEUE_RANK (int32_t) 1
#define PROTOCOL_GAME_QUEUE_ENQUEUE_NORMAL (int32_t) 2
#define PROTOCOL_GAME_QUEUE_ENQUEUE_SUCCESS (int32_t) 1
#define PROTOCOL_GAME_QUEUE_ENQUEUE_ERROR (int32_t) 2
	// Send : 게임 대기열 종류(int32_t), 게임 참가 인원 수(int32_t), 대기열 참가자 아이디(string), ...
	// Receive : 대기열 참가 결과(int32_t)
	// Todo : 대기열에 참가하고 결과를 보냅니다.
	GAME_QUEUE_ENQUEUE,
	// Send : 보내는 값 없음(null)
	// Receive : 결과값 없음(null)
	// Todo : 대기열에서 나옵니다.
	GAME_QUEUE_DEQUEUE,
	// Send : 보내는 값 없음(null)
	// Receive : 게임 식별자(int32_t)
	// Todo : 대기열 참가에 성공했을 때 게임 식별자를 보냅니다.
	GAME_QUEUE_FOUND,
	// Send : 보내는 값 없음(null)
	// Receive : 메시지(string)
	// Todo : 대기열 참가에 실패했을 때 메시지를 보냅니다.
	GAME_QUEUE_ERROR,
};