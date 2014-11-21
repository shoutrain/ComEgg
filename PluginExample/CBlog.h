#ifndef CBLOG_H
#define CBLOG_H

const unsigned int USER_NAME_MAX_LENGTH = 16;
const unsigned int PASSWORD_MAX_LEGNTH = 16;
const unsigned int BIRTHDAY_MAX_LENGTH = 11;
const unsigned int SELF_ESTIMATE_MAX_LENGTH = 128;
const unsigned int BLOG_TITLE_MAX_LENGTH = 32;
const unsigned int BLOG_CONTENT_MAX_LENGTH = 255;
const unsigned int BLOG_COMMENTS_MAX_LENGTH = 128;
const unsigned int CREATE_TIME_MAX_LENGTH = 20;

#define NULL 0

#pragma pack(1)

struct TRegisterUserIn {
    char userName[USER_NAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LEGNTH];
};

struct TRegisterUserOut {
    unsigned int userId;
};

struct TVerifyUserIn {
    char userName[USER_NAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LEGNTH];
};

struct TVerifyUserOut {
    unsigned int userId;
};

struct TUpdateUserInfoIn {
    unsigned int userId;
    bool isMale;
    char birthday[BIRTHDAY_MAX_LENGTH];
    char selfEstimate[SELF_ESTIMATE_MAX_LENGTH];
};

struct TUpdateUserInfoOut {
    bool result;
};

struct TGetUserInfoIn {
    unsigned int userId;
};

struct TGetUserInfoOut {
    bool result;
    bool isMale;
    char birthday[BIRTHDAY_MAX_LENGTH];
    char selfEstimate[SELF_ESTIMATE_MAX_LENGTH];
};

struct TAddBlogIn {
    unsigned int userId;
    char blogTitle[BLOG_TITLE_MAX_LENGTH];
    char blogContent[BLOG_CONTENT_MAX_LENGTH];
};

struct TAddBlogOut {
    bool result;
};

struct TAddCommentsIn {
    unsigned int blogId;
    unsigned int userId;
    char comments[BLOG_COMMENTS_MAX_LENGTH];
};

struct TAddCommentsOut {
    bool result;
};

struct TGetBlogIn {
    unsigned int blogId;
};

struct TComments {
    unsigned int userId;
    char userName[USER_NAME_MAX_LENGTH];
    char blogComments[BLOG_COMMENTS_MAX_LENGTH];
    char createTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogOut {
    unsigned int size;
    bool result;
    char userName[USER_NAME_MAX_LENGTH];
    char blogTitle[BLOG_TITLE_MAX_LENGTH];
    char blogContent[BLOG_CONTENT_MAX_LENGTH];
    char createTime[CREATE_TIME_MAX_LENGTH];
    unsigned int commentsNum;
    // TComments *pCommentsArray;
};

struct TGetBlogListByUserIn {
    unsigned int userId;
};

struct TBlogAbstract {
    unsigned int blogId;
    char blogTitle[BLOG_TITLE_MAX_LENGTH];
    char createTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogListByUserOut {
    unsigned int size;
    bool result;
    unsigned int blogNum;
    // TBlogAbstract *blogArray;
};

struct TGetBlogListIn {
};

struct TBlog {
    unsigned int userId;
    char userName[USER_NAME_MAX_LENGTH];
    unsigned int blogId;
    char blogTitle[BLOG_TITLE_MAX_LENGTH];
    char createTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogListOut {
    unsigned int size;
    bool result;
    unsigned int blogNum;
    // TBlog *blogArray;
};

#pragma pack()

#include <mysql.h>

class CBlog {
public:
    CBlog() :
            _cnn(NULL) {
    }

    virtual ~CBlog() {
        deinit();
    }

    bool init();

    void deinit();

    void registerUser(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void verifyUser(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void updateUserInfo(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void getUserInfo(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void addBlog(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void addComments(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void getBlog(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void getBlogListByUser(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

    void getBlogList(const unsigned char *in, unsigned int inSize,
            unsigned char *&out, unsigned int &outSize);

private:
    MYSQL *_cnn;
};

#endif // CBLOG_H

