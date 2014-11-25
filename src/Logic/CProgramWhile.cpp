#include "CProgramWhile.h"

void CProgramWhile::work(const TMessageUnit *tmu) {
    try {
        if (_judgeHead) {
            while (_expression->evaluate(tmu)) {
                try {
                    CProgram::work(tmu);
                } catch (callBreak) {
                    break;
                } catch (callContinue) {
                    continue;
                } catch (...) {
                    throw;
                }
            }
        } else {
            do {
                try {
                    CProgram::work(tmu);
                } catch (callBreak) {
                    break;
                } catch (callContinue) {
                    continue;
                } catch (...) {
                    throw;
                }
            } while (_expression->evaluate(tmu));
        }
    } catch (...) {
        reset();

        throw;
    }

    reset();
}
