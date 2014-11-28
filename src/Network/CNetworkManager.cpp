#include "CNetworkManager.h"

CNetworkManager *CNetworkManager::_instance = null_v;

ret_ CNetworkManager::Stop()
{
	_START(STOP);

    for (MapNode::iterator pos = _nodeMap.begin();
         pos != _nodeMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif

		_DEL(pos->second);
	}

    _nodeMap.clear();

	_RET(SUCCESS);
}

ret_ CNetworkManager::AddNetwork(const ch_1 *pszName,
								 ENetworkType Type,
        const CNode *pNetwork)
{
	_START(ADD_NETWORK);

#ifdef _DEBUG_
	if (GetNetwork(pszName))
		_RET(ELEMENT_EXIST_IN_CONTAINER);
#endif

    _nodeMap.insert(MapNode::value_type(pszName, pNetwork));

	_RET(SUCCESS);
}

ret_ CNetworkManager::work()
{
	_START(WORK);

    for (MapNode::iterator pos = _nodeMap.begin();
         pos != _nodeMap.end(); pos++)
	{
#ifdef _DEBUG_
		if (!pos->second)
			_RET(ELEMENT_NULL_IN_CONTAINER);
#endif
        CNode *pNetwork = (CNode *) pos->second;

		if (pNetwork->isAutoStart())
			pNetwork->work();
	}

	ACE_Reactor::instance()->owner(ACE_OS::thr_self());
	ACE_Reactor::instance()->run_reactor_event_loop();

	_RET(SUCCESS);
}
