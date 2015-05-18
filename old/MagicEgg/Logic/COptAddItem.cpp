#include "COptAddItem.h"

#include "../UI/CUIManager.h"
#include "../UI/CContainer.h"
#include "../UI/CTable.h"

COptAddItem::COptAddItem(const COptAddItem &opt): COperator(opt)
{
	memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
	strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);
	
	for (vector_var::const_iterator pos = opt.m_VariableVector.begin();
		 pos != opt.m_VariableVector.end(); pos++)
	{
		CVariable *pVariable = (*pos)->Clone();

		m_VariableVector.push_back(pVariable);
	}
 }

const COptAddItem &COptAddItem::operator =(const COptAddItem &opt)
{
	if (this != &opt)
	{
		COperator::operator =(opt);

		Clear();

		memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);
		strncpy(m_szWindowName, opt.m_szWindowName, VARIABLE_NAME_LENGTH);

		for (vector_var::const_iterator pos = opt.m_VariableVector.begin();
			 pos != opt.m_VariableVector.end(); pos++)
		{
			CVariable *pVariable = (*pos)->Clone();

			m_VariableVector.push_back(pVariable);
		}
	}

	return *this;
}

bool_ COptAddItem::AddVariable(const CVariable *pVariable)
{
	if (!pVariable)
		return false_v;

	m_VariableVector.push_back(pVariable);

	return true_v;
}

void COptAddItem::Initialize(const opt_unit *pUnit)
{
	for (vector_var::const_iterator pos = m_VariableVector.begin();
		 pos != m_VariableVector.end(); pos++)
	{
		CVariable *pVariable = (CVariable *)*pos;

		pVariable->Initialize(pUnit->pData);
	}
}

void COptAddItem::Clear()
{
	memset(m_szWindowName, 0, VARIABLE_NAME_LENGTH);

	for (vector_var::const_iterator pos = m_VariableVector.begin();
		 pos != m_VariableVector.end(); pos++)
	{
		CVariable *pVariable = (CVariable *)*pos;

		_DEL(pVariable);
	}

	m_VariableVector.clear();
}

void COptAddItem::Work(const TMU *pTMU)
{
	CContainer *pContainer = CUIManager::Instance()->GetCurContainer();

	if (!pContainer)
		throw WINDOW_IS_NOT_EXIST;

	CTable *pTable = (CTable *)pContainer->GetChild(m_szWindowName);

	if (!pTable || WINDOW_TABLE != pTable->Type())
		throw WINDOW_IS_NOT_EXIST;

	size_ nSize = (size_)m_VariableVector.size() - 1;

	if (nSize != pTable->GetNum())
		throw WINDOW_DATA_ERROR;

	try
	{
		CVariable *pVar = (CVariable *)m_VariableVector.at(0);
		v_ *pV = pVar->Value(pTMU);

		if (!pV)
			throw VARIABLE_OPERATION_ERROR;
 
		ch_1 **ppszItems = new ch_1 *[nSize];

		for (size_ i = 0; i < nSize; i++)
		{
			CVariable *pVar = (CVariable *)m_VariableVector.at(i + 1);
			v_ *pV = pVar->Value(pTMU);

			if (!pV)
				throw VARIABLE_OPERATION_ERROR;
 
			const ch_1 *psz = (const ch_1 *)*pV;
			size_ nLength = strlen(psz) + 1;

			ppszItems[i] = new ch_1[nLength];
			strncpy(ppszItems[i], psz, nLength);
		}

		if (!pTable->AddItem(*pV, ppszItems, nSize))
			throw WINDOW_DATA_ERROR;

		for (size_ j = 0; j < nSize; j++)
			_DEL_ARR(ppszItems[j]);

		_DEL_ARR(ppszItems);
	} 
	catch (...)
	{
		throw;
	}
}



