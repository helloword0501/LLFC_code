#include "CSession.h"
#include "CServer.h"
#include <iostream>
#include <iomanip>
CSession::CSession(boost::asio::io_context& io_context, CServer* server):
	_socket(io_context), _server(server), _b_close(false),_b_head_parse(false){
	boost::uuids::uuid  a_uuid = boost::uuids::random_generator()();
	_uuid = boost::uuids::to_string(a_uuid);
	_recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
}

CSession::~CSession() {
	cout << "~CSession " << _uuid<< " destruct" << endl;
}

tcp::socket& CSession::GetSocket() {
	return _socket;
}

std::string& CSession::GetUuid() {
	return _uuid;
}

void CSession::Start(){
	::memset(_data, 0, MAX_LENGTH);
	_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), std::bind(&CSession::HandleRead, this, 
		std::placeholders::_1, std::placeholders::_2, SharedSelf()));
}

void CSession::Send(char* msg, int max_length) {
	bool pending = false;
	std::lock_guard<std::mutex> lock(_send_lock);
	if (_send_que.size() > 0) {
		pending = true;
	}
	_send_que.push(make_shared<MsgNode>(msg, max_length));
	if (pending) {
		return;
	}
	auto& msgnode = _send_que.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len), 
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
}

void CSession::Close() {
	_socket.close();
	_b_close = true;
}

std::shared_ptr<CSession>CSession::SharedSelf() {
	return shared_from_this();
}

void CSession::PrintRecvData(char* data, int length) {
	stringstream ss;
	string result = "0x";
	for (int i = 0; i < length; i++) {
		string hexstr;
		ss << hex << std::setw(2) << std::setfill('0') << int(data[i]) << endl;
		ss >> hexstr;
		result += hexstr;
	}
	std::cout << "receive raw data is : " << result << endl;;
}

void CSession::HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self) {

	if (!error) {
		std::lock_guard<std::mutex> lock(_send_lock);
		cout << "send data " << _send_que.front()->_data+HEAD_LENGTH << endl;
		_send_que.pop();
		if (!_send_que.empty()) {
			auto &msgnode = _send_que.front();
			boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
				std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_self));
		}
	}
	else {
		std::cout << "handle write failed, error is " << error.what() << endl;
		Close();
		_server->ClearSession(_uuid);
	}
}

void CSession::HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, std::shared_ptr<CSession> shared_self){
	if (!error) {
		PrintRecvData(_data, bytes_transferred);
		std::chrono::milliseconds dura(2000);
		std::this_thread::sleep_for(dura);
		//�Ѿ��ƶ����ַ���
		int copy_len = 0;
		while (bytes_transferred>0) {
			if (!_b_head_parse) {
				//�յ������ݲ���ͷ����С
				if (bytes_transferred + _recv_head_node->_cur_len < HEAD_LENGTH) {
					memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data+ copy_len, bytes_transferred);
					_recv_head_node->_cur_len += bytes_transferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), 
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
					return;
				}
				//�յ������ݱ�ͷ����
				//ͷ��ʣ��δ���Ƶĳ���
				int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
				memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data+copy_len, head_remain);
				//�����Ѵ�����data���Ⱥ�ʣ��δ�����ĳ���
				copy_len += head_remain;
				bytes_transferred -= head_remain;
				//��ȡͷ������
				short data_len = 0;
				memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);
				cout << "data_len is " << data_len << endl;
				//ͷ�����ȷǷ�
				if (data_len > MAX_LENGTH) {
					std::cout << "invalid data length is " << data_len << endl;
					_server->ClearSession(_uuid);
					return;
				}
				_recv_msg_node = make_shared<MsgNode>(data_len);

				//��Ϣ�ĳ���С��ͷ���涨�ĳ��ȣ�˵������δ��ȫ�����Ƚ�������Ϣ�ŵ����սڵ���
				if (bytes_transferred < data_len) {
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
					_recv_msg_node->_cur_len += bytes_transferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), 
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
					//ͷ���������
					_b_head_parse = true;
					return;
				}

				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
				_recv_msg_node->_cur_len += data_len;
				copy_len += data_len;
				bytes_transferred -= data_len;
				_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
				cout << "receive data is " << _recv_msg_node->_data << endl;
				//�˴����Ե���Send���Ͳ���
				Send(_recv_msg_node->_data, _recv_msg_node->_total_len);
				//������ѯʣ��δ��������
				_b_head_parse = false;
				_recv_head_node->Clear();
				if (bytes_transferred <= 0) {
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), 
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
					return;
				}
				continue;
			}

			//�Ѿ�������ͷ���������ϴ�δ���������Ϣ����
			//���յ������Բ���ʣ��δ������
			int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
			if (bytes_transferred < remain_msg) {
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
				_recv_msg_node->_cur_len += bytes_transferred;
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), 
					std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
				return;
			}
			memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
			_recv_msg_node->_cur_len += remain_msg;
			bytes_transferred -= remain_msg;
			copy_len += remain_msg;
			_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
			cout << "receive data is " << _recv_msg_node->_data << endl;
			//�˴����Ե���Send���Ͳ���
			Send(_recv_msg_node->_data, _recv_msg_node->_total_len);
			//������ѯʣ��δ��������
			_b_head_parse = false;
			_recv_head_node->Clear();
			if (bytes_transferred <= 0) {
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
					std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_self));
				return;
			}
			continue;
		}
	}
	else {
		std::cout << "handle read failed, error is " << error.what() << endl;
		Close();
		_server->ClearSession(_uuid);
	}
}