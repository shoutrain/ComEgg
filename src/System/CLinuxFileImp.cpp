#include "CLinuxFileImp.h"

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

bool_ CLinuxFileImp::openFile(const ch_1 *fullPath, bool_ isRead) {
    if (!fullPath || null_v == fullPath[0]) {
        return false_v;
    }

    if (0 <= _file) {
        closeFile();
    }

    _isRead = isRead;

    b_4 flags = O_RDONLY;

    if (!isRead) {
        flags = O_CREAT | O_TRUNC | O_WRONLY;
    }

    _file = open(fullPath, flags, 0644);

    if (_file < 0) {
        return false_v;
    }

    return true_v;
}

void CLinuxFileImp::closeFile() {
    if (0 <= _file) {
        close(_file);
    }

    _file = -1;
}

bool_ CLinuxFileImp::readFile(ub_1 *&buffer, size_ bufferSize, size_ &readSize) {
    if (0 > _file || !_isRead) {
        return false_v;
    }

    readSize = read(_file, buffer, bufferSize);

    if (0 > readSize) {
        return false_v;
    }

    return true_v;
}

bool_ CLinuxFileImp::writeFile(const ub_1 *buffer, size_ bufferSize) {
    if (0 > _file || _isRead) {
        return false_v;
    }

    if (0 > write(_file, buffer, bufferSize)) {
        return false_v;
    }

    return true_v;
}

bool_ CLinuxFileImp::delFile(const ch_1 *fullPath) {
    ch_1 command[512];

    memset(command, 0, 512);
    sprintf(command, "rm -dfr %s", fullPath);

    b_4 ret = system(command);

    if (-1 == ret || 127 == ret) {
        return false_v;
    }

    return true_v;
}
