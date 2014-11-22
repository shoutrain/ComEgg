#include "CProgram.h"

CProgram::CProgram(const CProgram &opt): COperator(opt)
{
	m_OrnData	= opt.m_OrnData;
	m_Data		= opt.m_Data;

	size_ n = (size_)opt.m_OptVector.size();

	for (size_ i = 0; i < n; i++)
        m_OptVector.push_back(opt.m_OptVector[i]->clone());
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
            m_OptVector.push_back(opt.m_OptVector[i]->clone());
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

void CProgram::reset()
{
	m_Data = m_OrnData;

	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
        ((COperator *) m_OptVector[i])->reset();
}

void CProgram::init(const optUnit *unit)
{
    COperator::init(unit);
    m_Data.SetParent(unit->data);

    optUnit Unit;

    memcpy(&Unit, unit, sizeof(optUnit));
    Unit.data = &m_Data;
    Unit.parent = this;

	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
        ((COperator *) m_OptVector[i])->init(&Unit);
}

void CProgram::work(const TMessageUnit *tmu)
{
	size_ n = (size_)m_OptVector.size();

	for (size_ i = 0; i < n; i++)
	{
		try
		{
            ((COperator *) m_OptVector[i])->work(tmu);
		}
        catch (callBlock)
		{
            reset();

            if (getParent())
				throw;
			else
				return;
		}
		catch (...)
		{
            reset();
			
			throw;
		}
	}

    reset();
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
