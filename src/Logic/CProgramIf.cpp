#include "CProgramIf.h"

CProgramIf::CProgramIf(const CProgramIf &opt): CProgram(opt)
{
	size_ nNum = (size_)opt.m_ExpVector.size();

	for (size_ n = 0; n < nNum; n++)
        m_ExpVector.push_back(opt.m_ExpVector[n]->clone());
}

const CProgramIf &CProgramIf::operator =(const CProgramIf &opt)
{
	if (this != &opt)
	{
		Clear();

		CProgram::operator =(opt);

		size_ nNum = (size_)opt.m_ExpVector.size();

		for (size_ n = 0; n < nNum; n++)
            m_ExpVector.push_back(opt.m_ExpVector[n]->clone());
	}

	return *this;
}

bool_ CProgramIf::AddOperator(const COperator *pOperator)
{
#ifdef _DEBUG_
	if (!pOperator)
		return false_v;
#endif

    if (OT_PROGRAM != pOperator->getType())
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

void CProgramIf::init(const optUnit *unit)
{
    CProgram::init(unit);

    optUnit Unit;

    memcpy(&Unit, unit, sizeof(optUnit));
    Unit.data = &m_Data;
    Unit.parent = this;

	size_ nNum = (size_)m_ExpVector.size();

	for (size_ n = 0; n < nNum; n++)
        ((CExpression *) m_ExpVector[n])->init(&Unit);
}

void CProgramIf::work(const TMessageUnit *tmu)
{
	size_ nNum = (size_)m_ExpVector.size();

	try
	{
		for (size_ n = 0; n < nNum; n++)
            if (m_ExpVector[n]->evaluate(tmu))
			{
                ((COperator *) m_OptVector[n])->work(tmu);
                reset();

				return;
			}

		if (nNum < (size_)m_OptVector.size())
            ((COperator *) m_OptVector[nNum])->work(tmu);
	}
	catch (...)
	{
        reset();

		throw;
	}

    reset();
}

void CProgramIf::Clear()
{
	CProgram::Clear();

    for (vectorExp::iterator pos = m_ExpVector.begin();
		pos != m_ExpVector.end(); pos++)
	{
		_DEL(*pos);
	}

	m_ExpVector.clear();
}

