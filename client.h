#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>

#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "api/API.h"

class client
{
private:
	std::shared_ptr<apache::thrift::transport::TSocket> m_socket;
	std::shared_ptr<apache::thrift::transport::TTransport> m_transport;
	std::shared_ptr<apache::thrift::protocol::TProtocol> m_protocol;
	std::shared_ptr<lookfor9::api::ApiClient> m_api;

	void connect();
	void disconnect();

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> strconverter;

public:
	client(std::string ip, int port);
	~client();

	void hello();
	void tree_traverse(int index, int printLayer);
	void ads_by_tree_index(int index, short rowsCount);
};

