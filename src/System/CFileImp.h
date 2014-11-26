#ifndef _C_FILE_IMP_H_
#define _C_FILE_IMP_H_

#include "../Common/BaseType.h"

class CFileImp {
public:
    virtual bool_ openFile(const ch_1 *fullPath, bool_ isRead) = 0;

    virtual none_ closeFile() = 0;

    virtual bool_ readFile(ub_1 *&buffer, size_ bufferSize, size_ &readSize) = 0;

    virtual bool_ writeFile(const ub_1 *buffer, size_ bufferSize) = 0;

    virtual bool_ delFile(const ch_1 *fullPath) = 0;
};

#endif // _C_FILE_IMP_H_
