#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "CBlog.h"

void callDirectly() {
	/////////////////////////////////////
	// Test all interfaces directly.
	CBlog blog;

	if (!blog.init()) {
		printf("Initialize blog error!\n");

		return;
	}

	// RegisterUser
	{
		TRegisterUserIn in;
		TRegisterUserOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TRegisterUserIn));
		strncpy(in.userName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.password, "123456", PASSWORD_MAX_LEGNTH);

		blog.registerUser((const unsigned char *) &in, sizeof(TRegisterUserIn),
				(unsigned char *&) out, outSize);

		if (out && out->userId) {
			printf("RegisterUser ok!\n");
			printf("--user id: %d\n", out->userId);
		} else {
			printf("RegisterUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// VerifyUser
	{
		TVerifyUserIn in;
		TVerifyUserOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TVerifyUserIn));
		strncpy(in.userName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.password, "123456", PASSWORD_MAX_LEGNTH);

		blog.verifyUser((const unsigned char *) &in, sizeof(TVerifyUserIn),
				(unsigned char *&) out, outSize);

		if (out && out->userId) {
			printf("VerifyUser ok!\n");
			printf("--user id: %d\n", out->userId);
		} else {
			printf("VerifyUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// UpdateUserInfo
	{
		TUpdateUserInfoIn in;
		TUpdateUserInfoOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TUpdateUserInfoIn));
		in.userId = 1;
		in.isMale = true;
		strncpy(in.birthday, "1979-11-23", BIRTHDAY_MAX_LENGTH);
		strncpy(in.selfEstimate, "I am Rafel Gu.", SELF_ESTIMATE_MAX_LENGTH);

		blog.updateUserInfo((const unsigned char *) &in,
				sizeof(TUpdateUserInfoIn), (unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("UpdateUserInfo ok!\n");
		} else {
			printf("UpdateUserInfo error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetUserInfo
	{
		TGetUserInfoIn in;
		TGetUserInfoOut *out = NULL;
		unsigned int outSize = 0;

		in.userId = 1;

		blog.getUserInfo((const unsigned char *) &in, sizeof(TGetUserInfoIn),
				(unsigned char *&) out, outSize);

		if (NULL != out && out->result) {
			printf("GetUserInfoOut ok!\n");
			printf("--is male: %d;\n", out->isMale);
			printf("--birthday: %s;\n", out->birthday);
			printf("--self-estimate: %s.\n", out->selfEstimate);
		} else {
			printf("GetUserInfoOut error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// AddBlog
	{
		TAddBlogIn in;
		TAddBlogOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TAddBlogIn));
		in.userId = 1;
		strncpy(in.blogTitle, "My blog title", BLOG_TITLE_MAX_LENGTH);
		strncpy(in.blogContent, "My blog content.", BLOG_CONTENT_MAX_LENGTH);

		blog.addBlog((const unsigned char *) &in, sizeof(TAddBlogIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("AddBlog ok!\n");
		} else {
			printf("AddBlog error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// AddComments
	{
		TAddCommentsIn in;
		TAddCommentsOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TAddCommentsIn));
		in.blogId = 1;
		in.userId = 1;
		strncpy(in.comments, "My blog comments", BLOG_COMMENTS_MAX_LENGTH);

		blog.addComments((const unsigned char *) &in, sizeof(TAddCommentsIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("AddComments ok!\n");
		} else {
			printf("AddComments error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlog
	{
		TGetBlogIn in;
		TGetBlogOut *out = NULL;
		unsigned int outSize = 0;

		in.blogId = 1;

		blog.getBlog((const unsigned char *) &in, sizeof(TGetBlogIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlog ok!\n");
			printf("--user name: %s;\n", out->userName);
			printf("--blog title: %s;\n", out->blogTitle);
			printf("--blog content: %s;\n", out->blogContent);
			printf("--create time: %s;\n", out->createTime);
			printf("--comments num: %d.\n", out->commentsNum);

			if (0 < out->commentsNum) {
				TComments *p = (TComments *) (out + 1);

				for (unsigned int ui = 0; ui < out->commentsNum; ui++) {
					printf("----comments NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->userId);
					printf("------user name: %s\n", p->userName);
					printf("------blog comments: %s\n", p->blogComments);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlog error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlogListByUser
	{
		TGetBlogListByUserIn in;
		TGetBlogListByUserOut *out = NULL;
		unsigned int outSize = 0;

		in.userId = 1;

		blog.getBlogListByUser((const unsigned char *) &in,
				sizeof(TGetBlogListByUserIn), (unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlogListByUser ok!\n");
			printf("--blog num: %d\n", out->blogNum);

			if (0 < out->blogNum) {
				TBlogAbstract *p = (TBlogAbstract *) (out + 1);

				for (unsigned int ui = 0; ui < out->blogNum; ui++) {
					printf("----blog NO. %d:\n", ui + 1);
					printf("------blog id: %d\n", p->blogId);
					printf("------blog title: %s\n", p->blogTitle);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlogListByUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlogList
	{
		TGetBlogListIn in;
		TGetBlogListOut *out = NULL;
		unsigned int outSize = 0;

		blog.getBlogList((const unsigned char *) &in, sizeof(TGetBlogListIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlogList ok!\n");
			printf("--blog num: %d.\n", out->blogNum);

			if (0 < out->blogNum) {
				TBlog *p = (TBlog *) (out + 1);

				for (unsigned int ui = 0; ui < out->blogNum; ui++) {
					printf("----blog NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->userId);
					printf("------user name: %s\n", p->userName);
					printf("------blog id: %d\n", p->blogId);
					printf("------blog title: %s\n", p->blogTitle);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlogList error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	blog.deinit();
	///////////////////////////////////////
}

void callBySO(void *handle) {
	///////////////////////////////////////
	// Test all interface by so.
	void (*callFun)(const unsigned char *, unsigned int, unsigned char *&,
			unsigned int &);

	// RegisterUser
	{
		TRegisterUserIn in;
		TRegisterUserOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TRegisterUserIn));
		strncpy(in.userName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.password, "123456", PASSWORD_MAX_LEGNTH);

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "RegisterUser");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("RegisterUser: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TRegisterUserIn),
				(unsigned char *&) out, outSize);

		if (out && out->userId) {
			printf("RegisterUser ok!\n");
			printf("--user id: %d\n", out->userId);
		} else {
			printf("RegisterUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// VerifyUser
	{
		TVerifyUserIn in;
		TVerifyUserOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TVerifyUserIn));
		strncpy(in.userName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.password, "123456", PASSWORD_MAX_LEGNTH);

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "VerifyUser");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("VerifyUser: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TVerifyUserIn),
				(unsigned char *&) out, outSize);

		if (out && out->userId) {
			printf("VerifyUser ok!\n");
			printf("--user id: %d\n", out->userId);
		} else {
			printf("VerifyUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// UpdateUserInfo
	{
		TUpdateUserInfoIn in;
		TUpdateUserInfoOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TUpdateUserInfoIn));
		in.userId = 1;
		in.isMale = true;
		strncpy(in.birthday, "1979-11-23", BIRTHDAY_MAX_LENGTH);
		strncpy(in.selfEstimate, "I am Rafel Gu.", SELF_ESTIMATE_MAX_LENGTH);

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "UpdateUserInfo");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("UpdateUserInfo: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TUpdateUserInfoIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("UpdateUserInfo ok!\n");
		} else {
			printf("UpdateUserInfo error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetUserInfo
	{
		TGetUserInfoIn in;
		TGetUserInfoOut *out = NULL;
		unsigned int outSize = 0;

		in.userId = 1;

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "GetUserInfo");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("GetUserInfo: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TGetUserInfoIn),
				(unsigned char *&) out, outSize);

		if (NULL != out && out->result) {
			printf("GetUserInfoOut ok!\n");
			printf("--is male: %d;\n", out->isMale);
			printf("--birthday: %s;\n", out->birthday);
			printf("--self-estimate: %s.\n", out->selfEstimate);
		} else {
			printf("GetUserInfoOut error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// AddBlog
	{
		TAddBlogIn in;
		TAddBlogOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TAddBlogIn));
		in.userId = 1;
		strncpy(in.blogTitle, "My blog title", BLOG_TITLE_MAX_LENGTH);
		strncpy(in.blogContent, "My blog content.", BLOG_CONTENT_MAX_LENGTH);

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "AddBlog");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("AddBlog: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TAddBlogIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("AddBlog ok!\n");
		} else {
			printf("AddBlog error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// AddComments
	{
		TAddCommentsIn in;
		TAddCommentsOut *out = NULL;
		unsigned int outSize = 0;

		memset(&in, 0, sizeof(TAddCommentsIn));
		in.blogId = 1;
		in.userId = 1;
		strncpy(in.comments, "My blog comments", BLOG_COMMENTS_MAX_LENGTH);

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "AddComments");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("AddComments: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TAddCommentsIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("AddComments ok!\n");
		} else {
			printf("AddComments error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlog
	{
		TGetBlogIn in;
		TGetBlogOut *out = NULL;
		unsigned int outSize = 0;

		in.blogId = 1;

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "GetBlog");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("GetBlog: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TGetBlogIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlog ok!\n");
			printf("--user name: %s;\n", out->userName);
			printf("--blog title: %s;\n", out->blogTitle);
			printf("--blog content: %s;\n", out->blogContent);
			printf("--create time: %s;\n", out->createTime);
			printf("--comments num: %d.\n", out->commentsNum);

			if (0 < out->commentsNum) {
				TComments *p = (TComments *) (out + 1);

				for (unsigned int ui = 0; ui < out->commentsNum; ui++) {
					printf("----comments NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->userId);
					printf("------user name: %s\n", p->userName);
					printf("------blog comments: %s\n", p->blogComments);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlog error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlogListByUser
	{
		TGetBlogListByUserIn in;
		TGetBlogListByUserOut *out = NULL;
		unsigned int outSize = 0;

		in.userId = 1;

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "GetBlogListByUser");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("GetBlogListByUser: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TGetBlogListByUserIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlogListByUser ok!\n");
			printf("--blog num: %d\n", out->blogNum);

			if (0 < out->blogNum) {
				TBlogAbstract *p = (TBlogAbstract *) (out + 1);

				for (unsigned int ui = 0; ui < out->blogNum; ui++) {
					printf("----blog NO. %d:\n", ui + 1);
					printf("------blog id: %d\n", p->blogId);
					printf("------blog title: %s\n", p->blogTitle);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlogListByUser error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}

	// GetBlogList
	{
		TGetBlogListIn in;
		TGetBlogListOut *out = NULL;
		unsigned int outSize = 0;

		callFun = (void (*)(const unsigned char *, unsigned int,
				unsigned char *&, unsigned int &))
				dlsym(handle, "GetBlogList");

const		char *errMsg = dlerror();

		if (NULL != errMsg) {
			printf("GetBlogList: %s\n", errMsg);

			return;
		}

		callFun((const unsigned char *) &in, sizeof(TGetBlogListIn),
				(unsigned char *&) out, outSize);

		if (out && out->result) {
			printf("GetBlogList ok!\n");
			printf("--blog num: %d.\n", out->blogNum);

			if (0 < out->blogNum) {
				TBlog *p = (TBlog *) (out + 1);

				for (unsigned int ui = 0; ui < out->blogNum; ui++) {
					printf("----blog NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->userId);
					printf("------user name: %s\n", p->userName);
					printf("------blog id: %d\n", p->blogId);
					printf("------blog title: %s\n", p->blogTitle);
					printf("------create time: %s\n", p->createTime);

					p++;
				}
			}
		} else {
			printf("GetBlogList error!\n");
		}

		if (out) {
			delete[] out;
			out = NULL;
		}
	}
	///////////////////////////////////////
}

int main(int args, char *argv[]) {
	if (2 == args && 0 == strcmp(argv[1], "so")) {
		void *handle = dlopen("./libSCSBlog.so", RTLD_NOW);

		if (handle) {
			callBySO(handle);
			dlclose(handle);
		} else {
			printf("%s\n", dlerror());
		}
	} else {
		callDirectly();
	}

	return 0;
}
