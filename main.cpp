#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "api/Api.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace lookfor9::api;

int main()
{
	std::shared_ptr<TSocket> socket = std::shared_ptr<TSocket>(new TSocket("127.0.0.1", 9090));
	std::shared_ptr<TTransport> transport = std::shared_ptr<TTransport>(new TBufferedTransport(socket));
	std::shared_ptr<TProtocol> protocol = std::shared_ptr<TProtocol>(new TBinaryProtocol(transport));
	std::shared_ptr<ApiClient> api = std::shared_ptr<ApiClient>(new ApiClient(protocol));

	try
	{
		transport->open();
		std::cout << "Transport opened" << std::endl;

		std::string h{};
		api->Hello(h);
		std::cout << h << std::endl;

		std::string ph{ "9196315221" };
		std::string ph_info{};
		api->PhoneInfo(ph_info, ph);
		std::cout << ph_info << std::endl;

		std::vector<TreeInfo> ti_list;
		api->TreeChildren(ti_list, 0);

		std::for_each(ti_list.begin(), ti_list.end(), [](auto ti)
		{
			std::cout << ti.Id << ", " << ti.Name << std::endl;
		});
	}
	catch (...)
	{
		printf("thrift error: failed connect to node\n");
	}

	if (transport->isOpen())
	{
		transport->close();
		std::cout << "Transport closed" << std::endl;
	}
}

