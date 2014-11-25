#ifndef _C_FILE_H_
#define _C_FILE_H_

#include "CSysFactory.h"

class CFile {
public:
    CFile() {
        _file = CSysFactory::instance()->makeFile();
    }

    virtual ~CFile() {
        _DEL(_file);
    }

    bool_ readFile(const ch_1 *fullPath,
            ub_1 *&buffer,
            size_ bufferSize,
            size_ &readSize) {
        if (!_file->openFile(fullPath, true_v)) {
            return false_v;
        }

        if (!_file->readFile(buffer, bufferSize, readSize)) {
            return false_v;
        }

        _file->closeFile();

        return true_v;
    }


    bool_ writeFile(const ch_1 *fullPath,
            const ub_1 *buffer,
            size_ bufferSize) {
        if (!_file->openFile(fullPath, false_v)) {
            return false_v;
        }

        if (!_file->writeFile(buffer, bufferSize)) {
            return false_v;
        }

        _file->closeFile();

        return true_v;
    }

    bool_ delFile(const ch_1 *fullPath) {
        return _file->delFile(fullPath);
    }

private:
    CFileImp *_file;
};

#endif // _C_FILE_H_
