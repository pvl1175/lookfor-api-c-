#include <iostream>
#include <string>
#include <vector>

#include "client.h"

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);


	try
	{
		client c("127.0.0.1", 9090);

		c.hello();
		// 0 is the root
		std::wcout << L"Tree traverse:" << std::endl;
		std::wcout << L"you can uncomment the tree traverse" << std::endl;
		c.tree_traverse(0, 1);

		std::wcout << std::wstring(100, L'*') << std::endl;
		std::wcout << L"Ads by tree (1 rooms) buy:" << std::endl;
		c.ads_by_tree_index(4547, 10);

		std::wcout << std::wstring(100, L'*') << std::endl;
		std::wcout << L"Ads by tree (1 rooms) rent:" << std::endl;
		c.ads_by_tree_index(4548, 10);

		std::wcout << std::wstring(100, L'*') << std::endl;
		std::wcout << L"Ads by tree (dacha) buy:" << std::endl;
		c.ads_by_tree_index(4374, 10);
	}
	catch (...)
	{
		std::exception("thrift error: failed connect to node\n");
	}
}

