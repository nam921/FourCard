#pragma once

enum class Protocol : int32_t
{
	// Send : ����(string)
	// Receive : ����� ����(null)
	// Todo : ������ ó���մϴ�.
	DB_QUERY,
	// Send : ����(string)
	// Receive : �� ����(int32_t), �� �̸�(string), ��(string), ...
	// Todo : ������ ó���� �� ������� �����ϴ�.
	DB_RESULT,
	// Send : ����(string)
	// Receive : �� ����(int32_t), �� ����(int32_t), �� �̸�(string), �� (string), ..., �� ����(int32_t), ...
	// Todo : ������ ó���� �� ������� �����ϴ�.
	DB_RESULT_ROWS,
#define PROTOCOL_LOGIN_SUCCESS (int32_t) 1
#define PROTOCOL_LOGIN_FAIL (int32_t) 2
	// Send : ���̵�(string), ��й�ȣ(string)
	// Receive : ���(int32_t), [�޽���(string)]
	// Todo : �α����� ó���� �� ����� �����ϴ�.
	// Todo : ���(int32_t)
	// Todo : PROTOCOL_LOGIN_SUCCESS = ����, PROTOCOL_LOGIN_FAIL = ����
	// Todo : ���н� �޽����� �����ϴ�.
	LOGIN,
	// Send : ������ �� ����(null)
	// Receive : ����� ����(null)
	// Todo : �α׾ƿ��� ó���մϴ�.
	LOGOUT,
#define PROTOCOL_REGISTER_SUCCESS (int32_t) 1
#define PROTOCOL_REGISTER_FAIL (int32_t) 2
	// Send : �� ����(int32_t), �� �̸�(string), ��(string), ...
	// Receive : ���(int32_t), [�޽���(string)]
	// Todo : ȸ�������� ó���� �� ����� �����ϴ�.
	// Todo : ���(int32_t)
	// Todo : PROTOCOL_REGISTER_SUCCESS = ����, PROTOCOL_REGISTER_FAIL = ����
	// Todo : ���н� �޽����� �����ϴ�.
	// Todo : ���̵� (id, 4 ~ 14�� ����, ����)
	// Todo : ��й�ȣ (password, 4 ~ 14�� ����, ����, Ư������)
	// Todo : ���� (nickname, 4 ~ 14byte)
	// Todo : �̸��� (email)
	// Todo : �ּ� (address)
	// Todo : ����ó (phone)
	REGISTER,
	// Send : ������ �� ����(null)
	// Receive : �� ����(int32_t), ����(string), �·�(float), ...
	// Todo : ��ŷ ����(�·�)�� �����ϴ�. (10�� ����, 30�� �̻� ����)
	RANK_WINRATE,
	// Send : ������ �� ����(null)
	// Receive : �� ����(int32_t), ����(string), �¼�(int32_t), ...
	// Todo : ��ŷ ����(�ٽ�)�� �����ϴ�. (10�� ����)
	RANK_WIN,
	// Send : ������ �� ����(null)
	// Receive : �� ����(int32_t), ����(string), �� ���� ��(int32_t), ...
	// Todo : ��ŷ ����(����)�� �����ϴ�. (10�� ����)
	RANK_TOTAL,
	// Send : ������ �� ����(null)
	// Receive : ����(int32_t)
	// Todo : �ֽ� ������ �����ϴ�.
	VERSION,
#define PROTOCOL_GAME_QUEUE_ENQUEUE_RANK (int32_t) 1
#define PROTOCOL_GAME_QUEUE_ENQUEUE_NORMAL (int32_t) 2
#define PROTOCOL_GAME_QUEUE_ENQUEUE_SUCCESS (int32_t) 1
#define PROTOCOL_GAME_QUEUE_ENQUEUE_ERROR (int32_t) 2
	// Send : ���� ��⿭ ����(int32_t), ���� ���� �ο� ��(int32_t), ��⿭ ������ ���̵�(string), ...
	// Receive : ��⿭ ���� ���(int32_t)
	// Todo : ��⿭�� �����ϰ� ����� �����ϴ�.
	GAME_QUEUE_ENQUEUE,
	// Send : ������ �� ����(null)
	// Receive : ����� ����(null)
	// Todo : ��⿭���� ���ɴϴ�.
	GAME_QUEUE_DEQUEUE,
	// Send : ������ �� ����(null)
	// Receive : ���� �ĺ���(int32_t)
	// Todo : ��⿭ ������ �������� �� ���� �ĺ��ڸ� �����ϴ�.
	GAME_QUEUE_FOUND,
	// Send : ������ �� ����(null)
	// Receive : �޽���(string)
	// Todo : ��⿭ ������ �������� �� �޽����� �����ϴ�.
	GAME_QUEUE_ERROR,
};