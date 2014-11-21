#ifndef EXPORT_H
#define EXPORT_H

extern "C" {
void registerUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void verifyUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void updateUserInfo(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void getUserInfo(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void addBlog(const unsigned char *in, unsigned int inSize, unsigned char *&out,
        unsigned int &outSize);
void addComments(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void getBlog(const unsigned char *in, unsigned int inSize, unsigned char *&out,
        unsigned int &outSize);
void getBlogListByUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
void getBlogList(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize);
}

#endif // EXPORT_H

