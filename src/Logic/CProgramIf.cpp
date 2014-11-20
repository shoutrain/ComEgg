#include "CProgramIf.h"

CProgramIf::CProgramIf(const CProgramIf &opt): CProgram(opt)
{
	size_ nNum = (size_)opt.m_ExpVector.size();

	for (size_ n = 0; n < nNum; n++)
		m_ExpVector.push_back(opt.m_ExpVector[n]->Clone());
}

const CProgramIf &CProgramIf::operator =(const CProgramIf &opt)
{
	if (this != &opt)
	{
		Clear();

		CProgram::operator =(opt);

		size_ nNum = (size_)opt.m_ExpVector.size();

		for (size_ n = 0; n < nNum; n++)
			m_ExpVector.push_back(opt.m_ExpVector[n]->Clone());
	}

	return *this;
}

bool_ CProgramIf::AddOperator(const COperator *pOperator)
{
#ifdef _DEBUG_
	if (!pOperator)
		return false_v;
#endif

	if (OT_PROGRAM != pOperator->GetType())
		return false_v;

	m_OptVector.push_back(pOperator);

	return true_v;
}

bool_ CProgramIf::AddExpression(const CExpression *pExpression)
{
#ifdef _DEBUG_
	if (!pExpression)
		return false_v;
#endif

	m_ExpVector.push_back(pExpression);

	return true_v;
}

void CProgramIf::Initialize(const opt_unit *pUnit)
{
	CProgram::Initialize(pUnit);

	opt_unit Unit;

	memcpy(&Unit, pUnit, sizeof(opt_unit));
	Unit.pData		= &m_Data;
	Unit.pParent	= this;

	size_ nNum = (size_)m_ExpVector.size();

	for (size_ n = 0; n < nNum; n++)
		((CExpression *)m_ExpVector[n])->Initialize(&Unit);
}

void CProgramIf::Work(const TMessageUnit *pTMU)
{
	size_ nNum = (size_)m_ExpVector.size();

	try
	{
		for (size_ n = 0; n < nNum; n++)
			if (m_ExpVector[n]->Evaluate(pTMU))
			{
				((COperator *)m_OptVector[n])->Work(pTMU);
				Reset();

				return;
			}

		if (nNum < (size_)m_OptVector.size())
			((COperator *)m_OptVector[nNum])->Work(pTMU);
	}
	catch (...)
	{
		Reset();

		throw;
	}

	Reset();
}

void CProgramIf::Clear()
{
	CProgram::Clear();

	for (vector_exp::iterator pos = m_ExpVector.begin();
		pos != m_ExpVector.end(); pos++)
	{
		_DEL(*pos);
	}

	m_ExpVector.clear();
}

