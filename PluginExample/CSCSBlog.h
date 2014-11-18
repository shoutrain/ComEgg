#ifndef CSCS_BLOG_H
#define CSCS_BLOG_H

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

struct TRegisterUserIn
{
	char szUserName[USER_NAME_MAX_LENGTH];
	char szPassword[PASSWORD_MAX_LEGNTH];
};

struct TRegisterUserOut
{
	unsigned int uiUserID;
};

struct TVerifyUserIn
{
	char szUserName[USER_NAME_MAX_LENGTH];
	char szPassword[PASSWORD_MAX_LEGNTH];
};

struct TVerifyUserOut
{
	unsigned int uiUserID;
};

struct TUpdateUserInfoIn
{
	unsigned int uiUserID;
	bool bIsMale;
	char szBirthday[BIRTHDAY_MAX_LENGTH];
	char szSelfEstimate[SELF_ESTIMATE_MAX_LENGTH];
};

struct TUpdateUserInfoOut
{
	bool bResult;
};

struct TGetUserInfoIn
{
	unsigned int uiUserID;
};

struct TGetUserInfoOut
{
	bool bResult;
	bool bIsMale;
	char szBirthday[BIRTHDAY_MAX_LENGTH];
	char szSelfEstimate[SELF_ESTIMATE_MAX_LENGTH];
};

struct TAddBlogIn
{
	unsigned int uiUserID;
	char szBlogTitle[BLOG_TITLE_MAX_LENGTH];
	char szBlogContent[BLOG_CONTENT_MAX_LENGTH];
};

struct TAddBlogOut
{
	bool bResult;
};

struct TAddCommentsIn
{
	unsigned int uiBlogID;
	unsigned int uiUserID;
	char szComments[BLOG_COMMENTS_MAX_LENGTH];
};

struct TAddCommentsOut
{
	bool bResult;
};

struct TGetBlogIn
{
	unsigned int uiBlogID;
};

struct TComments
{
	unsigned int uiUserID;
	char szUserName[USER_NAME_MAX_LENGTH];
	char szBlogComments[BLOG_COMMENTS_MAX_LENGTH];
	char szCreateTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogOut
{
	unsigned int uiSize;
	bool bResult;
	char szUserName[USER_NAME_MAX_LENGTH];
	char szBlogTitle[BLOG_TITLE_MAX_LENGTH];
	char szBlogContent[BLOG_CONTENT_MAX_LENGTH];
	char szCreateTime[CREATE_TIME_MAX_LENGTH];
	unsigned int uiCommentsNum;
	// TComments *pCommentsArray;
};

struct TGetBlogListByUserIn
{
	unsigned int uiUserID;
};

struct TBlogAbstract
{
	unsigned int uiBlogID;
	char szBlogTitle[BLOG_TITLE_MAX_LENGTH];
	char szCreateTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogListByUserOut
{
	unsigned int uiSize;
	bool bResult;
	unsigned int uiBlogNum;
	// TBlogAbstract *pBlogArray;
};

struct TGetBlogListIn
{
};

struct TBlog
{
	unsigned int uiUserID;
	char szUserName[USER_NAME_MAX_LENGTH];
	unsigned int uiBlogID;
	char szBlogTitle[BLOG_TITLE_MAX_LENGTH];
	char szCreateTime[CREATE_TIME_MAX_LENGTH];
};

struct TGetBlogListOut
{
	unsigned int uiSize;
	bool bResult;
	unsigned int uiBlogNum;
	// TBlog *pBlogArray;
};

#pragma pack()

#include <mysql.h>

class CSCSBlog
{
public:
	CSCSBlog(): m_pCnn(NULL) {}

	virtual ~CSCSBlog() 
	{
		Uninitialize();
	}

	bool Initialize();
	void Uninitialize();

	void RegisterUser(const unsigned char *pIn, unsigned int uiInSize,
					  unsigned char *&pOut, unsigned int &uiOutSize);
	void VerifyUser(const unsigned char *pIn, unsigned int uiInSize,
					unsigned char *&pOut, unsigned int &uiOutSize);
	void UpdateUserInfo(const unsigned char *pIn, unsigned int uiInSize,
						unsigned char *&pOut, unsigned int&uiOutSize);
	void GetUserInfo(const unsigned char *pIn, unsigned int uiInSize,
					 unsigned char *&pOut, unsigned int &uiOutSize);
	void AddBlog(const unsigned char *pIn, unsigned int uiInSize,
				 unsigned char *&pOut, unsigned int &uiOutSize);
	void AddComments(const unsigned char *pIn, unsigned int uiInSize,
					 unsigned char *&pOut, unsigned int &uiOutSize);
	void GetBlog(const unsigned char *pIn, unsigned int uiInSize,
				 unsigned char *&pOut, unsigned int &uiOutSize);
	void GetBlogListByUser(const unsigned char *pIn, unsigned int uiInSize,
						   unsigned char *&pOut, unsigned int &uiOutSize);
	void GetBlogList(const unsigned char *pIn, unsigned int uiInSize,
					 unsigned char *&pOut, unsigned int &uiOutSize);

private:
	MYSQL *m_pCnn;
};

#endif // CSCS_BLOG_H

