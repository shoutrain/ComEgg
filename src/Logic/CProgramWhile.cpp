#include "CProgramWhile.h"

void CProgramWhile::Work(const TMessageUnit *pTMU)
{
	try
	{
		if (m_bJudgeHead)
		{
			while (m_pExpression->Evaluate(pTMU))
			{
				try
				{
					CProgram::Work(pTMU);
				}
				catch (call_break)
				{
					break;
				}
				catch (call_continue)
				{
					continue;
				}
				catch (...)
				{
					throw;
				}
			}
		}
		else
		{
			do
			{
				try
				{
					CProgram::Work(pTMU);
				}
				catch (call_break)
				{
					break;
				}
				catch (call_continue)
				{
					continue;
				}
				catch (...)
				{
					throw;
				}
			} while (m_pExpression->Evaluate(pTMU));
		}
	}
	catch (...)
	{
		Reset();

		throw;
	}

	Reset();
}
