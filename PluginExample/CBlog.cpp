#include "CConfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CBlog.h"

bool CBlog::init() {
    if (_cnn) {
        return false;
    }

    CConfig config;

    if (!config.init()) {
        return false;
    }

    _cnn = mysql_init(NULL);

    if (!mysql_real_connect(_cnn, config.getServer(), config.getUser(),
            config.getPassword(), config.getDatabase(), 0,
            NULL, 0)) {
        mysql_close(_cnn);
        _cnn = NULL;

        return false;
    }

    return true;
}

void CBlog::deinit() {
    if (_cnn) {
        mysql_close(_cnn);
        _cnn = NULL;
    }
}

void CBlog::registerUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TRegisterUserIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TRegisterUserOut;
    memset(out, 0, sizeof(TRegisterUserOut));
    outSize = sizeof(TRegisterUserOut);

    TRegisterUserIn *p = (TRegisterUserIn *) in;
    TRegisterUserOut *q = (TRegisterUserOut *) out;
    char sql[1024] = {0};
    char password[PASSWORD_MAX_LEGNTH * 2 + 1] = {0};

    mysql_real_escape_string(_cnn, password, p->password, strlen(p->password));
    sprintf(sql, "insert into user (user_name, password) values ('%s', '%s')",
            p->userName, password);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    q->userId = mysql_insert_id(_cnn);

    MYSQL_RES *res = mysql_store_result(_cnn);

    mysql_free_result(res);
}

void CBlog::verifyUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TVerifyUserIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TVerifyUserOut;
    memset(out, 0, sizeof(TVerifyUserOut));
    outSize = sizeof(TVerifyUserOut);

    TVerifyUserIn *p = (TVerifyUserIn *) in;
    TVerifyUserOut *q = (TVerifyUserOut *) out;
    char sql[1024] = {0};
    char password[PASSWORD_MAX_LEGNTH * 2 + 1] = {0};

    mysql_real_escape_string(_cnn, password, p->password, strlen(p->password));
    sprintf(sql,
            "select * from user where user_name = '%s' and password = '%s'",
            p->userName, password);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    MYSQL_ROW row = mysql_fetch_row(res);

    if (!row) {
        return;
    }

    q->userId = atoi(row[0]);

    mysql_free_result(res);
}

void CBlog::updateUserInfo(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TUpdateUserInfoIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TUpdateUserInfoOut;
    memset(out, 0, sizeof(TUpdateUserInfoOut));
    outSize = sizeof(TUpdateUserInfoOut);

    TUpdateUserInfoIn *p = (TUpdateUserInfoIn *) in;
    TUpdateUserInfoOut *q = (TUpdateUserInfoOut *) out;
    char sql[1024] = {0};

    sprintf(sql, "select * from user_info where user_id = %d", p->userId);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    unsigned int num = mysql_num_rows(res);

    mysql_free_result(res);
    memset(sql, 0, 1024);

    char sex[8] = {0};
    char birthday[BIRTHDAY_MAX_LENGTH * 2 + 1] = {0};
    char selfEstimate[SELF_ESTIMATE_MAX_LENGTH * 2 + 1] = {0};

    if (p->isMale) {
        strncpy(sex, "male", 8);
    } else {
        strncpy(sex, "female", 8);
    }

    mysql_real_escape_string(_cnn, birthday, p->birthday, strlen(p->birthday));
    mysql_real_escape_string(_cnn, selfEstimate, p->selfEstimate,
            strlen(p->selfEstimate));

    if (0 == num) {
        sprintf(sql,
                "insert into user_info (user_id, sex, birthday, self_estimate) "
                        "values (%d, '%s', '%s', '%s')", p->userId, sex,
                birthday, selfEstimate);
    } else {
        sprintf(sql, "update user_info set sex = '%s', birthday = '%s', "
                        "self_estimate = '%s' where user_id = '%d'", sex, birthday,
                selfEstimate, p->userId);
    }

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    q->result = true;

    res = mysql_store_result(_cnn);
    mysql_free_result(res);
}

void CBlog::getUserInfo(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TGetUserInfoIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TGetUserInfoOut;
    memset(out, 0, sizeof(TGetUserInfoOut));
    outSize = sizeof(TGetUserInfoOut);

    TGetUserInfoIn *p = (TGetUserInfoIn *) in;
    TGetUserInfoOut *q = (TGetUserInfoOut *) out;
    char sql[1024] = {0};

    sprintf(sql, "select sex, birthday, self_estimate from user_info "
            "where user_id = %d", p->userId);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    MYSQL_ROW row = mysql_fetch_row(res);

    if (!row) {
        return;
    }

    q->result = true;

    if ('m' == row[0][0]) {
        q->isMale = true;
    } else {
        q->isMale = false;
    }

    strncpy(q->birthday, row[1], BIRTHDAY_MAX_LENGTH);
    strncpy(q->selfEstimate, row[2], SELF_ESTIMATE_MAX_LENGTH);

    mysql_free_result(res);
}

void CBlog::addBlog(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TAddBlogIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TAddBlogOut;
    memset(out, 0, sizeof(TAddBlogOut));
    outSize = sizeof(TAddBlogOut);

    TAddBlogIn *p = (TAddBlogIn *) in;
    TAddBlogOut *q = (TAddBlogOut *) out;
    char sql[1024] = {0};
    char blogTitle[BLOG_TITLE_MAX_LENGTH * 2 + 1] = {0};
    char blogContent[BLOG_CONTENT_MAX_LENGTH * 2 + 1] = {0};

    mysql_real_escape_string(_cnn, blogTitle, p->blogTitle,
            strlen(p->blogTitle));
    mysql_real_escape_string(_cnn, blogContent, p->blogContent,
            strlen(p->blogContent));
    sprintf(sql, "insert into blog (user_id, title, content) values "
            "(%d, '%s', '%s')", p->userId, blogTitle, blogContent);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    q->result = true;

    MYSQL_RES *res = mysql_store_result(_cnn);

    mysql_free_result(res);
}

void CBlog::addComments(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TAddCommentsIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TAddCommentsOut;
    memset(out, 0, sizeof(TAddCommentsOut));
    outSize = sizeof(TAddCommentsOut);

    TAddCommentsIn *p = (TAddCommentsIn *) in;
    TAddCommentsOut *q = (TAddCommentsOut *) out;
    char sql[1024] = {0};
    char comments[BLOG_COMMENTS_MAX_LENGTH * 2 + 1] = {0};

    mysql_real_escape_string(_cnn, comments, p->comments, strlen(p->comments));
    sprintf(sql,
            "insert into blog_comments (blog_id, user_id, comments) values "
                    "(%d, '%d', '%s')", p->blogId, p->userId, comments);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    q->result = true;

    MYSQL_RES *res = mysql_store_result(_cnn);

    mysql_free_result(res);
}

void CBlog::getBlog(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TGetBlogIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TGetBlogOut;
    memset(out, 0, sizeof(TGetBlogOut));
    outSize = sizeof(TGetBlogOut);

    TGetBlogIn *p = (TGetBlogIn *) in;
    TGetBlogOut *q = (TGetBlogOut *) out;
    char sql[1024] = {0};

    sprintf(sql,
            "select user.user_name, blog.title, blog.content, blog.create_time "
                    "from user, blog where user.id = blog.user_id and "
                    "blog.id = %d", p->blogId);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    MYSQL_ROW row = mysql_fetch_row(res);

    if (!row) {
        return;
    }

    q->size = sizeof(TGetBlogOut);
    strncpy(q->userName, row[0], USER_NAME_MAX_LENGTH);
    strncpy(q->blogTitle, row[1], BLOG_TITLE_MAX_LENGTH);
    strncpy(q->blogContent, row[2], BLOG_CONTENT_MAX_LENGTH);
    strncpy(q->createTime, row[3], CREATE_TIME_MAX_LENGTH);

    mysql_free_result(res);

    // Get comments list
    memset(sql, 0, 1024);
    sprintf(sql, "select user.id, user.user_name, blog_comments.comments, "
            "blog_comments.create_time "
            "from user, blog, blog_comments where "
            "user.id = blog_comments.user_id and "
            "blog_comments.blog_id = blog.id and "
            "blog.id = %d order by blog_comments.create_time", p->blogId);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    q->result = true;

    res = mysql_store_result(_cnn);
    q->commentsNum = mysql_num_rows(res);

    if (0 < q->commentsNum) {
        TGetBlogOut tmp;

        memset(&tmp, 0, sizeof(TGetBlogOut));
        memcpy(&tmp, q, sizeof(TGetBlogOut));
        delete out;
        outSize = tmp.size = sizeof(TGetBlogOut)
                + tmp.commentsNum * sizeof(TComments);

        out = new unsigned char[tmp.size];
        memcpy(out, &tmp, sizeof(TGetBlogOut));

        TComments *o = (TComments *) (out + sizeof(TGetBlogOut));

        while ((row = mysql_fetch_row(res))) {
            o->userId = atoi(row[0]);
            strncpy(o->userName, row[1], USER_NAME_MAX_LENGTH);
            strncpy(o->blogComments, row[2], BLOG_COMMENTS_MAX_LENGTH);
            strncpy(o->createTime, row[3], CREATE_TIME_MAX_LENGTH);

            o = (TComments *) (((unsigned char *) o) + sizeof(TComments));
        }
    }

    mysql_free_result(res);
}

void CBlog::getBlogListByUser(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (!in || out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    if (sizeof(TGetBlogListByUserIn) != inSize) {
        return;
    }

    out = (unsigned char *) new TGetBlogListByUserOut;
    memset(out, 0, sizeof(TGetBlogListByUserOut));
    outSize = sizeof(TGetBlogListByUserOut);

    TGetBlogListByUserIn *p = (TGetBlogListByUserIn *) in;
    TGetBlogListByUserOut *q = (TGetBlogListByUserOut *) out;
    char sql[1024] = {0};

    sprintf(sql, "select id, title, create_time from blog where user_id = %d "
            "order by create_time", p->userId);

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    MYSQL_ROW row;

    q->size = sizeof(TGetBlogListByUserOut);
    q->result = true;
    q->blogNum = mysql_num_rows(res);

    if (0 < q->blogNum) {
        TGetBlogListByUserOut tmp;

        memset(&tmp, 0, sizeof(TGetBlogListByUserOut));
        memcpy(&tmp, q, sizeof(TGetBlogListByUserOut));
        delete[] out;
        outSize = tmp.size = sizeof(TGetBlogListByUserOut)
                + tmp.blogNum * sizeof(TBlogAbstract);

        out = new unsigned char[tmp.size];
        memcpy(out, &tmp, sizeof(TGetBlogListByUserOut));

        TBlogAbstract *o = (TBlogAbstract *) (out
                + sizeof(TGetBlogListByUserOut));

        while ((row = mysql_fetch_row(res))) {
            o->blogId = atoi(row[0]);
            strncpy(o->blogTitle, row[1], BLOG_TITLE_MAX_LENGTH);
            strncpy(o->createTime, row[2], CREATE_TIME_MAX_LENGTH);

            o =
                    (TBlogAbstract *) (((unsigned char *) o)
                            + sizeof(TBlogAbstract));
        }
    }

    mysql_free_result(res);
}

void CBlog::getBlogList(const unsigned char *in, unsigned int inSize,
        unsigned char *&out, unsigned int &outSize) {
    if (out || outSize) {
        return;
    }

    if (!_cnn) {
        return;
    }

    out = (unsigned char *) new TGetBlogListOut;
    memset(out, 0, sizeof(TGetBlogListOut));
    outSize = sizeof(TGetBlogListOut);

    TGetBlogListOut *q = (TGetBlogListOut *) out;
    char sql[1024] = {0};

    sprintf(sql, "select user.id, user.user_name, blog.id, blog.title, "
            "blog.create_time from user, blog where user.id = blog.user_id "
            "order by blog.create_time");

    if (mysql_real_query(_cnn, sql, strlen(sql))) {
        return;
    }

    MYSQL_RES *res = mysql_store_result(_cnn);
    MYSQL_ROW row;

    q->size = sizeof(TGetBlogListOut);
    q->result = true;
    q->blogNum = mysql_num_rows(res);

    if (0 < q->blogNum) {
        TGetBlogListOut tmp;

        memset(&tmp, 0, sizeof(TGetBlogListOut));
        memcpy(&tmp, q, sizeof(TGetBlogListOut));
        delete[] out;
        outSize = tmp.size = sizeof(TGetBlogListOut)
                + tmp.blogNum * sizeof(TBlog);

        out = new unsigned char[tmp.size];
        memcpy(out, &tmp, sizeof(TGetBlogListOut));

        TBlog *o = (TBlog *) (out + sizeof(TGetBlogListOut));

        while ((row = mysql_fetch_row(res))) {
            o->userId = atoi(row[0]);
            strncpy(o->userName, row[1], USER_NAME_MAX_LENGTH);
            o->blogId = atoi(row[2]);
            strncpy(o->blogTitle, row[3], BLOG_TITLE_MAX_LENGTH);
            strncpy(o->createTime, row[4], CREATE_TIME_MAX_LENGTH);

            o = (TBlog *) (((unsigned char *) o) + sizeof(TBlog));
        }
    }

    mysql_free_result(res);
}

