/*!
 * \file CRegister.h
 * \brief A category->key->value keeper.
 *
 * One category can container many keys, and one key maps only one value.
 * There are only one instance of the class in the application.
 *
 * \author Rafael Gu(shoutrain.goo@gmail.com)
 * \version 1.0.0
 * \date 02/15/2015
 */

#ifndef SRC_COMMON_CREGISTER_H_
#define SRC_COMMON_CREGISTER_H_

#include "CAutoVar.h"

#include <string>
#include <map>

using namespace std;

typedef map<string, v_ *> MapVariable;
typedef map<string, MapVariable *> MapCategory;

class CRegister {
public:
	static CRegister *instance() {
		if (_instance) {
			return _instance;
		}

		_instance = new CRegister;

		return _instance;
	}

	static void destroy() {
		_DEL(_instance);
	}

	v_ *searchItem(const ch_1 *category, const ch_1 *key);

	b_4 registerItem(const ch_1 *category, const ch_1 *key, const v_ *variable,
			const bool_ isCovered = false_v);

	none_ unregisterItem(const ch_1 *category, const ch_1 *key);

protected:
	CRegister() {
	}

	CRegister(const CRegister &);

	const CRegister &operator=(const CRegister &);

	virtual ~CRegister() {
		stop();
	}

	none_ stop();

private:
	static CRegister *_instance;

	MapCategory _categoryMap;
};

#endif /* SRC_COMMON_CREGISTER_H_ */
