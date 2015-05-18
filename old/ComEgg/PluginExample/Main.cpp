#include "CSCSBlog.h"
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

void CallDirectly()
{
	/////////////////////////////////////
	// Test all interfaces directly.
	CSCSBlog blog;

	if (!blog.Initialize())
	{
		printf("Initialize blog error!\n");

		return;
	}

	// RegisterUser
	{
		TRegisterUserIn in;
		TRegisterUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TRegisterUserIn));
		strncpy(in.szUserName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.szPassword, "123456", PASSWORD_MAX_LEGNTH);

		blog.RegisterUser((const unsigned char *)&in, sizeof(TRegisterUserIn),
						  (unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->uiUserID)
		{
			printf("RegisterUser ok!\n");
			printf("--user id: %d\n", pOut->uiUserID);
		}
		else
		{
			printf("RegisterUser error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// VerifyUser
	{
		TVerifyUserIn in;
		TVerifyUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TVerifyUserIn));
		strncpy(in.szUserName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.szPassword, "123456", PASSWORD_MAX_LEGNTH);

		blog.VerifyUser((const unsigned char *)&in, sizeof(TVerifyUserIn),
						(unsigned char *&)pOut, uiOutSize);
		
		if (pOut && pOut->uiUserID)
		{
			printf("VerifyUser ok!\n");
			printf("--user id: %d\n", pOut->uiUserID);
		}
		else
		{
			printf("VerifyUser error!\n");
		}
		
		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// UpdateUserInfo
	{
		TUpdateUserInfoIn in;
		TUpdateUserInfoOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TUpdateUserInfoIn));
		in.uiUserID = 1;
		in.bIsMale = true;
		strncpy(in.szBirthday, "1979-11-23", BIRTHDAY_MAX_LENGTH);
		strncpy(in.szSelfEstimate, "I am Rafel Gu.", SELF_ESTIMATE_MAX_LENGTH);

		blog.UpdateUserInfo((const unsigned char *)&in,
							sizeof(TUpdateUserInfoIn),
							(unsigned char *&)pOut,
							uiOutSize);
		
		if (pOut && pOut->bResult)
		{
			printf("UpdateUserInfo ok!\n");
		}
		else
		{
			printf("UpdateUserInfo error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetUserInfo
	{
		TGetUserInfoIn in;
		TGetUserInfoOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiUserID = 1;

		blog.GetUserInfo((const unsigned char *)&in, sizeof(TGetUserInfoIn), 
					(unsigned char *&)pOut, uiOutSize);

		if (NULL != pOut && pOut->bResult)
		{
			printf("GetUserInfoOut ok!\n");
			printf("--is male: %d;\n", pOut->bIsMale);
			printf("--birthday: %s;\n", pOut->szBirthday);
			printf("--self-estimate: %s.\n", pOut->szSelfEstimate);
		}
		else
		{
			printf("GetUserInfoOut error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// AddBlog
	{
		TAddBlogIn in;
		TAddBlogOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TAddBlogIn));
		in.uiUserID = 1;
		strncpy(in.szBlogTitle, "My blog title", BLOG_TITLE_MAX_LENGTH);
		strncpy(in.szBlogContent, "My blog content.", BLOG_CONTENT_MAX_LENGTH);

		blog.AddBlog((const unsigned char *)&in, sizeof(TAddBlogIn), 
					 (unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("AddBlog ok!\n");
		}
		else
		{
			printf("AddBlog error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// AddComments
	{
		TAddCommentsIn in;
		TAddCommentsOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TAddCommentsIn));
		in.uiBlogID = 1;
		in.uiUserID = 1;
		strncpy(in.szComments, "My blog comments", BLOG_COMMENTS_MAX_LENGTH);

		blog.AddComments((const unsigned char *)&in, sizeof(TAddCommentsIn),
						 (unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("AddComments ok!\n");
		}
		else
		{
			printf("AddComments error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlog
	{
		TGetBlogIn in;
		TGetBlogOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiBlogID = 1;

		blog.GetBlog((const unsigned char *)&in, sizeof(TGetBlogIn),
					 (unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlog ok!\n");
			printf("--user name: %s;\n", pOut->szUserName);
			printf("--blog title: %s;\n", pOut->szBlogTitle);
			printf("--blog content: %s;\n", pOut->szBlogContent);
			printf("--create time: %s;\n", pOut->szCreateTime);
			printf("--comments num: %d.\n", pOut->uiCommentsNum);

			if (0 < pOut->uiCommentsNum)
			{
				TComments *p = (TComments *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiCommentsNum; ui++)
				{
					printf("----comments NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->uiUserID);
					printf("------user name: %s\n", p->szUserName);
					printf("------blog comments: %s\n", p->szBlogComments);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlog error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlogListByUser
	{
		TGetBlogListByUserIn in;
		TGetBlogListByUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiUserID = 1;

		blog.GetBlogListByUser((const unsigned char *)&in,
							   sizeof(TGetBlogListByUserIn),
							   (unsigned char *&)pOut,
							   uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlogListByUser ok!\n");
			printf("--blog num: %d\n", pOut->uiBlogNum);

			if (0 < pOut->uiBlogNum)
			{
				TBlogAbstract *p = (TBlogAbstract *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiBlogNum; ui++)
				{
					printf("----blog NO. %d:\n", ui + 1);
					printf("------blog id: %d\n", p->uiBlogID);
					printf("------blog title: %s\n", p->szBlogTitle);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlogListByUser error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlogList
	{
		TGetBlogListIn in;
		TGetBlogListOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		blog.GetBlogList((const unsigned char *)&in, sizeof(TGetBlogListIn),
						 (unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlogList ok!\n");
			printf("--blog num: %d.\n", pOut->uiBlogNum);

			if (0 < pOut->uiBlogNum)
			{
				TBlog *p = (TBlog *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiBlogNum; ui++)
				{
					printf("----blog NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->uiUserID);
					printf("------user name: %s\n", p->szUserName);
					printf("------blog id: %d\n", p->uiBlogID);
					printf("------blog title: %s\n", p->szBlogTitle);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlogList error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}
	
	blog.Uninitialize();
	///////////////////////////////////////
}

void CallBySO(void *handle)
{
	///////////////////////////////////////
	// Test all interface by so.
	void (*CallFun)(const unsigned char *,
					unsigned int,
					unsigned char *&,
					unsigned int &);

	// RegisterUser
	{
		TRegisterUserIn in;
		TRegisterUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TRegisterUserIn));
		strncpy(in.szUserName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.szPassword, "123456", PASSWORD_MAX_LEGNTH);

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "RegisterUser");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("RegisterUser: %s\n", pszErrMsg);

			return;
		}
		
		CallFun((const unsigned char *)&in, sizeof(TRegisterUserIn),
				(unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->uiUserID)
		{
			printf("RegisterUser ok!\n");
			printf("--user id: %d\n", pOut->uiUserID);
		}
		else
		{
			printf("RegisterUser error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// VerifyUser
	{
		TVerifyUserIn in;
		TVerifyUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TVerifyUserIn));
		strncpy(in.szUserName, "goo", USER_NAME_MAX_LENGTH);
		strncpy(in.szPassword, "123456", PASSWORD_MAX_LEGNTH);

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "VerifyUser");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("VerifyUser: %s\n", pszErrMsg);

			return;
		}
		
		CallFun((const unsigned char *)&in, sizeof(TVerifyUserIn),
				(unsigned char *&)pOut, uiOutSize);
		
		if (pOut && pOut->uiUserID)
		{
			printf("VerifyUser ok!\n");
			printf("--user id: %d\n", pOut->uiUserID);
		}
		else
		{
			printf("VerifyUser error!\n");
		}
		
		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// UpdateUserInfo
	{
		TUpdateUserInfoIn in;
		TUpdateUserInfoOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TUpdateUserInfoIn));
		in.uiUserID = 1;
		in.bIsMale = true;
		strncpy(in.szBirthday, "1979-11-23", BIRTHDAY_MAX_LENGTH);
		strncpy(in.szSelfEstimate, "I am Rafel Gu.", SELF_ESTIMATE_MAX_LENGTH);

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "UpdateUserInfo");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("UpdateUserInfo: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TUpdateUserInfoIn),
				(unsigned char *&)pOut, uiOutSize);
		
		if (pOut && pOut->bResult)
		{
			printf("UpdateUserInfo ok!\n");
		}
		else
		{
			printf("UpdateUserInfo error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetUserInfo
	{
		TGetUserInfoIn in;
		TGetUserInfoOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiUserID = 1;

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "GetUserInfo");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("GetUserInfo: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TGetUserInfoIn),
				(unsigned char *&)pOut, uiOutSize);

		if (NULL != pOut && pOut->bResult)
		{
			printf("GetUserInfoOut ok!\n");
			printf("--is male: %d;\n", pOut->bIsMale);
			printf("--birthday: %s;\n", pOut->szBirthday);
			printf("--self-estimate: %s.\n", pOut->szSelfEstimate);
		}
		else
		{
			printf("GetUserInfoOut error!\n");
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// AddBlog
	{
		TAddBlogIn in;
		TAddBlogOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TAddBlogIn));
		in.uiUserID = 1;
		strncpy(in.szBlogTitle, "My blog title", BLOG_TITLE_MAX_LENGTH);
		strncpy(in.szBlogContent, "My blog content.", BLOG_CONTENT_MAX_LENGTH);

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "AddBlog");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("AddBlog: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TAddBlogIn),
				(unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("AddBlog ok!\n");
		}
		else
		{
			printf("AddBlog error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// AddComments
	{
		TAddCommentsIn in;
		TAddCommentsOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		memset(&in, 0, sizeof(TAddCommentsIn));
		in.uiBlogID = 1;
		in.uiUserID = 1;
		strncpy(in.szComments, "My blog comments", BLOG_COMMENTS_MAX_LENGTH);

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "AddComments");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("AddComments: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TAddCommentsIn),
				(unsigned char *&)pOut, uiOutSize);
		
		if (pOut && pOut->bResult)
		{
			printf("AddComments ok!\n");
		}
		else
		{
			printf("AddComments error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlog
	{
		TGetBlogIn in;
		TGetBlogOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiBlogID = 1;

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "GetBlog");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("GetBlog: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TGetBlogIn),
				(unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlog ok!\n");
			printf("--user name: %s;\n", pOut->szUserName);
			printf("--blog title: %s;\n", pOut->szBlogTitle);
			printf("--blog content: %s;\n", pOut->szBlogContent);
			printf("--create time: %s;\n", pOut->szCreateTime);
			printf("--comments num: %d.\n", pOut->uiCommentsNum);

			if (0 < pOut->uiCommentsNum)
			{
				TComments *p = (TComments *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiCommentsNum; ui++)
				{
					printf("----comments NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->uiUserID);
					printf("------user name: %s\n", p->szUserName);
					printf("------blog comments: %s\n", p->szBlogComments);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlog error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlogListByUser
	{
		TGetBlogListByUserIn in;
		TGetBlogListByUserOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		in.uiUserID = 1;

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "GetBlogListByUser");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("GetBlogListByUser: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TGetBlogListByUserIn),
				(unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlogListByUser ok!\n");
			printf("--blog num: %d\n", pOut->uiBlogNum);

			if (0 < pOut->uiBlogNum)
			{
				TBlogAbstract *p = (TBlogAbstract *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiBlogNum; ui++)
				{
					printf("----blog NO. %d:\n", ui + 1);
					printf("------blog id: %d\n", p->uiBlogID);
					printf("------blog title: %s\n", p->szBlogTitle);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlogListByUser error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}

	// GetBlogList
	{
		TGetBlogListIn in;
		TGetBlogListOut *pOut = NULL;
		unsigned int uiOutSize = 0;

		CallFun = (void (*)(const unsigned char *, unsigned int,
							unsigned char *&, unsigned int &))
			dlsym(handle, "GetBlogList");

		const char *pszErrMsg = dlerror();

		if (NULL != pszErrMsg)
		{
			printf("GetBlogList: %s\n", pszErrMsg);

			return;
		}

		CallFun((const unsigned char *)&in, sizeof(TGetBlogListIn),
				(unsigned char *&)pOut, uiOutSize);

		if (pOut && pOut->bResult)
		{
			printf("GetBlogList ok!\n");
			printf("--blog num: %d.\n", pOut->uiBlogNum);

			if (0 < pOut->uiBlogNum)
			{
				TBlog *p = (TBlog *)(pOut + 1);

				for (unsigned int ui = 0; ui < pOut->uiBlogNum; ui++)
				{
					printf("----blog NO. %d:\n", ui + 1);
					printf("------user id: %d\n", p->uiUserID);
					printf("------user name: %s\n", p->szUserName);
					printf("------blog id: %d\n", p->uiBlogID);
					printf("------blog title: %s\n", p->szBlogTitle);
					printf("------create time: %s\n", p->szCreateTime);

					p++;
				}
			}
		}
		else
		{
			printf("GetBlogList error!\n");			
		}

		if (pOut)
		{
			delete[] pOut;
			pOut = NULL;
		}
	}
	///////////////////////////////////////
}

int main(int args, char *argv[])
{
	if (2 == args && 0 == strcmp(argv[1], "so"))
	{
		void *handle = dlopen("./libSCSBlog.so", RTLD_NOW);

		if (handle)
		{
			CallBySO(handle);
			dlclose(handle);
		}
		else
		{
			printf("%s\n", dlerror());
		}
	}
	else
	{
		CallDirectly();
	}
	return 0;
}
