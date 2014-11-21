#include "CProgram.h"

CProgram::CProgram(const CProgram &opt): COperator(opt)
{
	m_OrnData	= opt.m_OrnData;
	m_Data		= opt.m_Data;

	size_ n = (size_)opt.m_OptVector.size();

	for (size_ i = 0; i < n; i++)
		m_OptVector.push_back(opt.m_OptVector[i]->Clone());
}

const CProgram &CProgram::operator =(const CProgram &opt)
{
	if (this != &opt)
	{
		COperator::operator =(opt);

		Clear();

		m_OrnData	= opt.m_OrnData;
		m_Data		= opt.m_Data;

		size_ n = (size_)opt.m_OptVector.size();

		for (size_ i = 0; i < n; i++)
			m_OptVector.push_back(opt.m_OptVector[i]->Clone());
	}

	return *this;
}

bool_ CProgram::AddOperator(const COperator *pOperator)
{
#ifdef _DEBUG_
	if (!pOperator)
		return false_v;
#endif

	m_OptVector.push_back(pOperator);

	return true_v;
}

void CProgram::Reset()
{
	m_Data = m_OrnData;

	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
		((COperator *)m_OptVector[i])->Reset();
}

void CProgram::Initialize(const opt_unit *pUnit)
{
	COperator::Initialize(pUnit);
	m_Data.SetParent(pUnit->pData);

	opt_unit Unit;

	memcpy(&Unit, pUnit, sizeof(opt_unit));
	Unit.pData		= &m_Data;
	Unit.pParent	= this;

	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
		((COperator *)m_OptVector[i])->Initialize(&Unit);
}

void CProgram::Work(const TMessageUnit *pTMU)
{
	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
	{
		try
		{
			((COperator *)m_OptVector[i])->Work(pTMU);
		}
		catch (call_block)
		{
			Reset();

			if (GetParent())
				throw;
			else
				return;
		}
		catch (...)
		{
			Reset();
			
			throw;
		}
	}

	Reset();
}

void CProgram::Clear()
{
    m_Data.clear();
    m_OrnData.clear();

	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
		_DEL(m_OptVector[i]);

	m_OptVector.clear();
}
