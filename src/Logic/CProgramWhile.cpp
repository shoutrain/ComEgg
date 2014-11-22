#include "CProgramWhile.h"

void CProgramWhile::work(const TMessageUnit *tmu)
{
	try
	{
		if (m_bJudgeHead)
		{
            while (m_pExpression->evaluate(tmu))
			{
				try
				{
                    CProgram::work(tmu);
				}
                catch (callBreak)
				{
					break;
				}
                catch (callContinue)
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
                    CProgram::work(tmu);
				}
                catch (callBreak)
				{
					break;
				}
                catch (callContinue)
				{
					continue;
				}
				catch (...)
				{
					throw;
				}
            } while (m_pExpression->evaluate(tmu));
		}
	}
	catch (...)
	{
        reset();

		throw;
	}

    reset();
}
