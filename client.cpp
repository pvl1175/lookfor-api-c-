#include <algorithm>
#include <iomanip>
#include <codecvt>
#include <locale>

#include "client.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace lookfor9::api;

using convert_t = std::codecvt_utf8<wchar_t>;

client::client(std::string ip, int port)
{
	m_socket = std::shared_ptr<TSocket>(new TSocket(ip, port));
	m_transport = std::shared_ptr<TTransport>(new TBufferedTransport(m_socket));
	m_protocol = std::shared_ptr<TProtocol>(new TBinaryProtocol(m_transport));
	m_api = std::shared_ptr<ApiClient>(new ApiClient(m_protocol));
	
	connect();
}

client::~client()
{
	disconnect();
}

void client::hello()
{
	try
	{
		std::string h;
		m_api->Hello(h);
		std::wcout << strconverter.from_bytes(h) << std::endl;
	}
	catch (...)
	{
		throw std::exception("thrift error: failed connect to node");
	}
}

void client::tree_traverse(int index, int printLayer)
{
	std::vector<TreeInfo> list;
	m_api->TreeChildren(list, index);
	
	std::for_each(list.begin(), list.end(), [&](auto& item) 
		{
			std::wcout << std::wstring(printLayer, L'\t') << item.Id << "." << strconverter.from_bytes(item.Name) << std::endl;
			tree_traverse(item.Id, printLayer + 1);
		});
}

void client::ads_by_tree_index(int index, short rowsCount)
{
	std::vector<Ad> list;
	m_api->AdsByTree(list, index, rowsCount);

	std::for_each(list.begin(), list.end(), [&](auto& item)
		{
			std::wcout
				<< std::left << std::setw(7) << item.Id
				<< std::setw(40) << strconverter.from_bytes(item.Title)
				<< std::setw(20) << strconverter.from_bytes(item.Price)
				<< std::setw(10) << strconverter.from_bytes(item.AvitoTime)
				<< std::setw(70) << strconverter.from_bytes(item.Address)
				<< strconverter.from_bytes(item.OwnerPhone)
				<< std::endl;
		});
	std::wcout << L"..." << std::endl;
	std::for_each(list.begin(), list.end(), [&](auto& item)
		{
			std::wcout
				<< std::left << std::setw(11) << strconverter.from_bytes(item.OwnerPhone)
				<< std::setw(60) << strconverter.from_bytes(item.OwnerName)
				<< std::setw(80) << strconverter.from_bytes(item.PhoneInfo)
				<< std::endl;
		});
}

void client::ads_by_query(std::wstring value, short rowsCount)
{
	std::vector<Ad> list;
	m_api->AdsByQuery(list, strconverter.to_bytes(value), rowsCount);

	std::for_each(list.begin(), list.end(), [&](auto& item)
		{
			std::wcout
				<< std::left << std::setw(7) << item.Id
				<< std::setw(40) << strconverter.from_bytes(item.Title)
				<< std::setw(20) << strconverter.from_bytes(item.Price)
				<< std::setw(10) << strconverter.from_bytes(item.AvitoTime)
				<< std::setw(70) << strconverter.from_bytes(item.Address)
				<< strconverter.from_bytes(item.OwnerPhone)
				<< std::endl;
		});
	std::wcout << L"..." << std::endl;
	std::for_each(list.begin(), list.end(), [&](auto& item)
		{
			std::wcout
				<< std::left << std::setw(11) << strconverter.from_bytes(item.OwnerPhone)
				<< std::setw(60) << strconverter.from_bytes(item.OwnerName)
				<< std::setw(80) << strconverter.from_bytes(item.PhoneInfo)
				<< std::endl;
		});
}

void client::connect()
{
	try
	{
		m_transport->open();
	}
	catch (...)
	{
		throw std::exception("thrift error: failed connect to node");
	}
}

void client::disconnect()
{
	try
	{
		m_transport->close();
	}
	catch (...)
	{
		throw std::exception("thrift error: failed disconnect from node");
	}
}

