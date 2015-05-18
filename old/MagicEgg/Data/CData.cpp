#include "CData.h"

#include <stdio.h>
#include <string.h>

CData::CData(const CData &Data)
{
	for (map_variable::const_iterator pos = Data.m_VariableMap.begin();
		 pos != Data.m_VariableMap.end(); pos++)
	{
		v_ *p = new v_(*(pos->second));

		m_VariableMap.insert(map_variable::value_type(pos->first, p));
	}

	for (map_data::const_iterator pos_ = Data.m_DataMap.begin();
		 pos_ != Data.m_DataMap.end(); pos_++)
	{
		TFieldGroup *pData = new TFieldGroup;

		memset(pData, 0, sizeof(TFieldGroup));
		m_DataMap.insert(map_data::value_type(pos_->first, pData));

		if (pos_->second->nSize && pos_->second->pData)
		{
			pData->nSize= pos_->second->nSize;
			pData->pData = new ub_1[pos_->second->nSize];
		}
	}
}

const CData &CData::operator =(const CData &Data)
{
	if (&Data != this)
	{
		Clear();

		for (map_variable::const_iterator pos = Data.m_VariableMap.begin();
			 pos != Data.m_VariableMap.end(); pos++)
		{
			v_ *p = new v_(*(pos->second));

			m_VariableMap.insert(map_variable::value_type(pos->first, p));
		}

		for (map_data::const_iterator pos_ = Data.m_DataMap.begin();
			 pos_ != Data.m_DataMap.end(); pos_++)
		{
			TFieldGroup *pData = new TFieldGroup;

			memset(pData, 0, sizeof(TFieldGroup));
			m_DataMap.insert(map_data::value_type(pos_->first, pData));

			if (pos_->second->nSize && pos_->second->pData)
			{
				pData->nSize= pos_->second->nSize;
				pData->pData = new ub_1[pos_->second->nSize];
			}
		}
	}

	return *this;
}

bool_ CData::Define(const ch_1 *pszName, evt_ Type)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = null_v;

	switch (Type)
	{
	case B_1:
		{
			b_1 v = 0;

			pVar = new v_(v);
		}
		break;
	case UB_1:
		{
			ub_1 v = 0;

			pVar = new v_(v);
		}
		break;
	case B_2:
		{
			b_2 v = 0;

			pVar = new v_(v);
		}
		break;
	case UB_2:
		{
			ub_2 v = 0;

			pVar = new v_(v);
		}
		break;
	case B_4:
		{
			b_4 v = 0;

			pVar = new v_(v);
		}
		break;
	case UB_4:
		{
			ub_4 v = 0;

			pVar = new v_(v);
		}
		break;
	case B_8:
		{
			b_8 v = 0;

			pVar = new v_(v);
		}
		break;
	case UB_8:
		{
			ub_8 v = 0;

			pVar = new v_(v);
		}
		break;
	case FB_4:
		{
			fb_4 v = 0;

			pVar = new v_(v);
		}
		break;
	case FB_8:
		{
			fb_8 v = 0;

			pVar = new v_(v);
		}
		break;
	case STR:
		try
		{
			pVar = new v_("", 0);
		}
		catch (...)
		{
			return false_v;
		}
		break;
	case OBJ:
		{
			obj_ v = null_v;

			pVar = new v_(v);
		}
		break;
	default:
		return false_v;
	}

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, evt_ Type, b_4 Data)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = null_v;

	switch (Type)
	{
	case B_1:
		pVar = new v_((b_1)Data);
		break;
	case UB_1:
		pVar = new v_((ub_1)Data);
		break;
	case B_2:
		pVar = new v_((b_2)Data);
		break;
	case UB_2:
		pVar = new v_((ub_2)Data);
		break;
	case B_4:
		pVar = new v_((b_4)Data);
		break;
	case UB_4:
		pVar = new v_((ub_4)Data);
		break;
	default:
		return false_v;
	}

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, b_8 Data)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_(Data);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, ub_8 Data)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_(Data);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, fb_4 Data)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_(Data);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, fb_8 Data)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_(Data);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, const ch_1 *pszValue)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_((const ch_1*)pszValue, 0);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const ch_1 *pszName, obj_ Object)
{
	if (m_VariableMap.end() != m_VariableMap.find(pszName))
		return false_v;

	v_ *pVar = new v_(Object);

	m_VariableMap.insert(map_variable::value_type(pszName, pVar));

	return true_v;
}

bool_ CData::Define(const CFieldGroupDefined *pFieldGroup)
{
	if (!pFieldGroup)
		return false_v;

	v_ *pSize = Value(pFieldGroup->GetSizeName());

	if (!pSize)
		return false_v;

	if (m_VariableMap.end() != m_VariableMap.find(pFieldGroup->Name()))
		return false_v;

	m_VariableMap.insert(map_variable::value_type(pFieldGroup->Name(), 
												  new v_((obj_)pFieldGroup)));

	TFieldGroup *pGroupData = new TFieldGroup;

	memset(pGroupData, 0, sizeof(TFieldGroup));
	m_DataMap.insert(map_data::value_type(pFieldGroup->Name(),
										  pGroupData));

	size_ nSize = (size_)*pSize;

	if (nSize)
	{
		pGroupData->nSize= nSize;
		pGroupData->pData = new ub_1[pGroupData->nSize];
		memset(pGroupData->pData, 0, pGroupData->nSize);
	}

	const CField *pField = pFieldGroup->GetSubField();

	while (pField)
	{
		ch_1 pszName[VARIABLE_NAME_LENGTH * 2] = {0};

		sprintf(pszName, "%s.%s", pFieldGroup->Name(), pField->Name());

		if (m_VariableMap.end() != m_VariableMap.find(pszName))
			return false_v;

		m_VariableMap.insert(map_variable::value_type(pszName, 
													  new v_((obj_)pField)));
		pField = pField->GetNextField();
	}

	return true_v;
}

v_ *CData::Value(const ch_1 *pszName) const 
{
	map_variable::const_iterator pos = m_VariableMap.find(pszName);

	if (m_VariableMap.end() != pos)
		return pos->second;
	else if (m_pParent)
		return m_pParent->Value(pszName);
	else
		return null_v;
}

v_ *CData::Value(const ch_1 *pszGroupName, 
				 const ch_1 *pszSubName, 
				 TFieldGroup *&pData) const
{
	if (!pszGroupName || 0 == pszGroupName[0] || pData)
		return null_v;

	ch_1 pszName[VARIABLE_NAME_LENGTH * 2] = {0};

	if (!pszSubName || 0 == pszSubName[0])
		strncpy(pszName, pszGroupName, VARIABLE_NAME_LENGTH);
	else
		sprintf(pszName, "%s.%s", pszGroupName, pszSubName);

	map_variable::const_iterator pos = m_VariableMap.find(pszName);

	if (m_VariableMap.end() != pos)
	{
		map_data::const_iterator pos_ = m_DataMap.find(pszGroupName);

		if (m_DataMap.end() != pos_)
		{
			pData = pos_->second;

			return pos->second;
		}
		else
		{
			return null_v;
		}
	}
	else if (m_pParent)
	{
		return m_pParent->Value(pszGroupName, pszSubName, pData);
	}
	else
	{
		return null_v;
	}
}

void CData::Clear()
{
	for (map_variable::iterator pos = m_VariableMap.begin(); 
		 pos != m_VariableMap.end(); pos++)
	{
		_DEL(pos->second);
	}

	for (map_data::iterator pos_ = m_DataMap.begin();
		 pos_ != m_DataMap.end(); pos_++)
	{
		if (pos_->second->nSize && pos_->second->pData)
		{
			_DEL_ARR(pos_->second->pData);
			pos_->second->nSize = 0;
		}

		_DEL(pos_->second);
	}

	m_VariableMap.clear();
	m_DataMap.clear();
}
