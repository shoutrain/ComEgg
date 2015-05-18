#include "./XMLParser/CXMLLoaderManager.h"

int main(int argc, char *argv[])
{
	// Load XML first
	if (1 == argc)
	{
		if (SUCCESS != _ERR(CXMLLoaderManager::Instance()->Load()))
			return -1;
	}
	else if (2 == argc)
	{
		if (SUCCESS != _ERR(CXMLLoaderManager::Instance()->Load(argv[1])))
			return -1;
	}
	else
	{
		printf("Usage: ComEgg [Directory]\n");

		return 0;
	}

	CXMLLoaderManager::Destory();

	// Working...
	if (SUCCESS != _ERR(CNetworkManager::Instance()->Work()))
		return -2;

	return 0;
}

