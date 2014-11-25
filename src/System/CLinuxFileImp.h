#ifndef _C_LINUX_FILE_IMP_H_
#define _C_LINUX_FILE_IMP_H_

#include "CFileImp.h"

class CLinuxFileImp : CFileImp {
public:
    CLinuxFileImp() : _file(-1) {
    }

    virtual ~CLinuxFileImp() {
        closeFile();
    }

    virtual bool_ openFile(const ch_1 *fullPath, bool_ isRead);

    virtual none_ closeFile();

    virtual bool_ readFile(ub_1 *&buffer, size_ bufferSize, size_ &readSize);

    virtual bool_ writeFile(const ub_1 *buffer, size_ bufferSize);

    virtual bool_ delFile(const ch_1 *fullPath);

private:
    b_4   _file;
    bool_ _isRead;
};

#endif // _C_LINUX_FILE_IMP_H_
