#include "./XMLParser/CXMLLoaderManager.h"

#include "ace/Thread.h"

void *network_run(void *pParam)
{
	CNetworkManager::Instance()->Work();

	return null_v;
}

int main(int argc, char *argv[])
{
	// Load XML first
	if (1 == argc)
	{
		if (SUCCESS != CXMLLoaderManager::Instance()->Load())
			return -1;
	}
	else if (2 == argc)
	{
		if (SUCCESS != CXMLLoaderManager::Instance()->Load(argv[1]))
			return -1;
	}
	else
	{
		printf("Usage: MagicEgg [Directory]\n");

		return 0;
	}

	CXMLLoaderManager::Destory();

	// Create a new thread to run network
	ACE_thread_t id;
    ACE_hthread_t handle;

    ACE_Thread::spawn((ACE_THR_FUNC)network_run,
					  null_v,
					  THR_JOINABLE | THR_NEW_LWP,
					  &id,
					  &handle);

	// Run UI
	CUIManager::Instance()->Run();

	// If UI is closed all, MagicEgg should exit
	CNetworkManager::Instance()->Exit();
	ACE_Thread::join(handle);

	return 0;
}
