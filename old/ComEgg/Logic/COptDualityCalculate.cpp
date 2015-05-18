#include "COptDualityCalculate.h"

void COptDualityCalculate::Work(const TMU *pTMU)
{
	try
	{
		switch (m_Opt)
		{
		case EC_ADD:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				+ (*m_pRightVariable->Value(pTMU));
			return;
		case EC_SUB:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				- (*m_pRightVariable->Value(pTMU));
			return;
		case EC_MUL:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				* (*m_pRightVariable->Value(pTMU));
			return;
		case EC_DIV:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				/ (*m_pRightVariable->Value(pTMU));
			return;
		case EC_MOD:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				% (*m_pRightVariable->Value(pTMU));
			return;
		case EC_AND:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				& (*m_pRightVariable->Value(pTMU));
			return;
		case EC_OR:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				| (*m_pRightVariable->Value(pTMU));
			return;
		case EC_XOR:
			(*m_pResultVariable->Value(pTMU))
				= (*m_pLeftVariable->Value(pTMU))
				^ (*m_pRightVariable->Value(pTMU));
			return;
		default:
			throw OPERATOR_OPERAITON_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}
