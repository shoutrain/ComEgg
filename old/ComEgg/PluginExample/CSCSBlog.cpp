#include "CSCSBlog.h"
#include "CConfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool CSCSBlog::Initialize()
{
	if (m_pCnn)
		return false;

	CConfig Config;

	if (!Config.Initialize())
		return false;

	m_pCnn = mysql_init(NULL);

	if (!mysql_real_connect(m_pCnn,
							Config.GetServer(),
							Config.GetUser(),
							Config.GetPassword(),
							Config.GetDatabase(),
							0, 
							NULL,
							0))
	{
		mysql_close(m_pCnn);
		m_pCnn = NULL;

		return false;
	}

	return true;
}

void CSCSBlog::Uninitialize()
{
	if (m_pCnn)
	{
		mysql_close(m_pCnn);
		m_pCnn = NULL;
	}
}

void CSCSBlog::RegisterUser(const unsigned char *pIn, unsigned int uiInSize,
							unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TRegisterUserIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TRegisterUserOut;
	memset(pOut, 0, sizeof(TRegisterUserOut));
	uiOutSize = sizeof(TRegisterUserOut);

	TRegisterUserIn *p = (TRegisterUserIn *)pIn;
	TRegisterUserOut *q = (TRegisterUserOut *)pOut;
	char szSQL[1024] = {0};
	char szPassword[PASSWORD_MAX_LEGNTH * 2 + 1] = {0};

	mysql_real_escape_string(m_pCnn, szPassword,
							 p->szPassword,
							 strlen(p->szPassword));
	sprintf(szSQL, 
			"insert into user (user_name, password) values ('%s', '%s')", 
			p->szUserName,
			szPassword);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	q->uiUserID = mysql_insert_id(m_pCnn);
	
	MYSQL_RES *res = mysql_store_result(m_pCnn);
	
	mysql_free_result(res);
}

void CSCSBlog::VerifyUser(const unsigned char *pIn, unsigned int uiInSize,
						  unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;
	
	if (!m_pCnn)
		return;

	if (sizeof(TVerifyUserIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TVerifyUserOut;
	memset(pOut, 0, sizeof(TVerifyUserOut));
	uiOutSize = sizeof(TVerifyUserOut);

	TVerifyUserIn *p = (TVerifyUserIn *)pIn;
	TVerifyUserOut *q = (TVerifyUserOut *)pOut;
	char szSQL[1024] = {0};
	char szPassword[PASSWORD_MAX_LEGNTH * 2 + 1] = {0};

	mysql_real_escape_string(m_pCnn,
							 szPassword,
							 p->szPassword,
							 strlen(p->szPassword));
	sprintf(szSQL, 
			"select * from user where user_name = '%s' and password = '%s'", 
			p->szUserName,
			szPassword);

	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	MYSQL_ROW row = mysql_fetch_row(res);

	if (!row)
		return;
	
	q->uiUserID = atoi(row[0]);

	mysql_free_result(res);
}

void CSCSBlog::UpdateUserInfo(const unsigned char *pIn, unsigned int uiInSize,
							  unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TUpdateUserInfoIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TUpdateUserInfoOut;
	memset(pOut, 0, sizeof(TUpdateUserInfoOut));
	uiOutSize = sizeof(TUpdateUserInfoOut);
	
	TUpdateUserInfoIn *p = (TUpdateUserInfoIn *)pIn;
	TUpdateUserInfoOut *q = (TUpdateUserInfoOut *)pOut;
	char szSQL[1024] = {0};

	sprintf(szSQL, 
			"select * from user_info where user_id = %d", 
			p->uiUserID);

	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	unsigned int uiNum = mysql_num_rows(res);
	
	mysql_free_result(res);
	memset(szSQL, 0, 1024);
	
	char szSex[8] = {0};
	char szBirthday[BIRTHDAY_MAX_LENGTH * 2 + 1] = {0};
	char szSelfEstimate[SELF_ESTIMATE_MAX_LENGTH * 2 + 1] = {0};
	
	if (p->bIsMale)
		strncpy(szSex, "male", 8);
	else
		strncpy(szSex, "female", 8);

	mysql_real_escape_string(m_pCnn,
							 szBirthday,
							 p->szBirthday,
							 strlen(p->szBirthday));
	mysql_real_escape_string(m_pCnn,
							 szSelfEstimate,
							 p->szSelfEstimate,
							 strlen(p->szSelfEstimate));
	
	if (0 == uiNum)
	{
		sprintf(szSQL, 
				"insert into user_info (user_id, sex, birthday, self_estimate) "
				"values (%d, '%s', '%s', '%s')",
				p->uiUserID,
				szSex,
				szBirthday,
				szSelfEstimate);
	}
	else
	{
		sprintf(szSQL,
				"update user_info set sex = '%s', birthday = '%s', "
				"self_estimate = '%s' where user_id = '%d'",
				szSex,
				szBirthday,
				szSelfEstimate,
				p->uiUserID);
	}

	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	q->bResult = true;

	res = mysql_store_result(m_pCnn);
	mysql_free_result(res);
}

void CSCSBlog::GetUserInfo(const unsigned char *pIn, unsigned int uiInSize,
						   unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TGetUserInfoIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TGetUserInfoOut;
	memset(pOut, 0, sizeof(TGetUserInfoOut));
	uiOutSize = sizeof(TGetUserInfoOut);

	TGetUserInfoIn *p = (TGetUserInfoIn *)pIn;
	TGetUserInfoOut *q = (TGetUserInfoOut *)pOut;
	char szSQL[1024] = {0};

	sprintf(szSQL, 
			"select sex, birthday, self_estimate from user_info "
			"where user_id = %d",
			p->uiUserID);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	MYSQL_ROW row = mysql_fetch_row(res);

	if (!row)
		return;

	q->bResult = true;

	if ('m' == row[0][0])
		q->bIsMale = true;
	else
		q->bIsMale = false;
	
	strncpy(q->szBirthday, row[1], BIRTHDAY_MAX_LENGTH);
	strncpy(q->szSelfEstimate, row[2], SELF_ESTIMATE_MAX_LENGTH);

	mysql_free_result(res);
}

void CSCSBlog::AddBlog(const unsigned char *pIn, unsigned int uiInSize,
					   unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TAddBlogIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TAddBlogOut;
	memset(pOut, 0, sizeof(TAddBlogOut));
	uiOutSize = sizeof(TAddBlogOut);
		
	TAddBlogIn *p = (TAddBlogIn *)pIn;
	TAddBlogOut *q = (TAddBlogOut *)pOut;
	char szSQL[1024] = {0};
	char szBlogTitle[BLOG_TITLE_MAX_LENGTH * 2 + 1] = {0};
	char szBlogContent[BLOG_CONTENT_MAX_LENGTH * 2 + 1] = {0};

	mysql_real_escape_string(m_pCnn,
							 szBlogTitle,
							 p->szBlogTitle,
							 strlen(p->szBlogTitle));
	mysql_real_escape_string(m_pCnn,
							 szBlogContent,
							 p->szBlogContent,
							 strlen(p->szBlogContent));
	sprintf(szSQL, 
			"insert into blog (user_id, title, content) values "
			"(%d, '%s', '%s')",
			p->uiUserID,
			szBlogTitle,
			szBlogContent);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	q->bResult = true;
	
	MYSQL_RES *res = mysql_store_result(m_pCnn);
	
	mysql_free_result(res);
}

void CSCSBlog::AddComments(const unsigned char *pIn, unsigned int uiInSize,
						   unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TAddCommentsIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TAddCommentsOut;
	memset(pOut, 0, sizeof(TAddCommentsOut));
	uiOutSize = sizeof(TAddCommentsOut);

	TAddCommentsIn *p = (TAddCommentsIn *)pIn;
	TAddCommentsOut *q = (TAddCommentsOut *)pOut;
	char szSQL[1024] = {0};
	char szComments[BLOG_COMMENTS_MAX_LENGTH * 2 + 1] = {0};

	mysql_real_escape_string(m_pCnn,
							 szComments,
							 p->szComments,
							 strlen(p->szComments));
	sprintf(szSQL, 
			"insert into blog_comments (blog_id, user_id, comments) values "
			"(%d, '%d', '%s')",
			p->uiBlogID,
			p->uiUserID,
			szComments);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	q->bResult = true;
	
	MYSQL_RES *res = mysql_store_result(m_pCnn);
	
	mysql_free_result(res);
}

void CSCSBlog::GetBlog(const unsigned char *pIn, unsigned int uiInSize,
					   unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TGetBlogIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TGetBlogOut;
	memset(pOut, 0, sizeof(TGetBlogOut));
	uiOutSize = sizeof(TGetBlogOut);

	TGetBlogIn *p = (TGetBlogIn *)pIn;
	TGetBlogOut *q = (TGetBlogOut *)pOut;
	char szSQL[1024] = {0};

	sprintf(szSQL, 
			"select user.user_name, blog.title, blog.content, blog.create_time "
			"from user, blog where user.id = blog.user_id and "
			"blog.id = %d",
			p->uiBlogID);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	MYSQL_ROW row = mysql_fetch_row(res);

	if (!row)
		return;

	q->uiSize = sizeof(TGetBlogOut);
	strncpy(q->szUserName, row[0], USER_NAME_MAX_LENGTH);
	strncpy(q->szBlogTitle, row[1], BLOG_TITLE_MAX_LENGTH);
	strncpy(q->szBlogContent, row[2], BLOG_CONTENT_MAX_LENGTH);
	strncpy(q->szCreateTime, row[3], CREATE_TIME_MAX_LENGTH);

	mysql_free_result(res);

	// Get comments list
	memset(szSQL , 0, 1024);
	sprintf(szSQL,
			"select user.id, user.user_name, blog_comments.comments, "
			"blog_comments.create_time "
			"from user, blog, blog_comments where "
			"user.id = blog_comments.user_id and "
			"blog_comments.blog_id = blog.id and "
			"blog.id = %d order by blog_comments.create_time",
			p->uiBlogID);

	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;

	q->bResult = true;

	res = mysql_store_result(m_pCnn);
	q->uiCommentsNum = mysql_num_rows(res);

	if (0 < q->uiCommentsNum)
	{
		TGetBlogOut tmp;

		memset(&tmp, 0, sizeof(TGetBlogOut));
		memcpy(&tmp, q, sizeof(TGetBlogOut));
		delete pOut;
		uiOutSize = tmp.uiSize = sizeof(TGetBlogOut) 
			+ tmp.uiCommentsNum * sizeof(TComments);
	
		pOut = new unsigned char[tmp.uiSize];
		memcpy(pOut, &tmp, sizeof(TGetBlogOut));
		
		TComments *o = (TComments *)(pOut + sizeof(TGetBlogOut));

		while ((row = mysql_fetch_row(res)))
		{
			o->uiUserID = atoi(row[0]);
			strncpy(o->szUserName, row[1], USER_NAME_MAX_LENGTH);
			strncpy(o->szBlogComments, row[2], BLOG_COMMENTS_MAX_LENGTH);
			strncpy(o->szCreateTime, row[3], CREATE_TIME_MAX_LENGTH);

			o = (TComments *)(((unsigned char *)o) + sizeof(TComments));
		}
	}

	mysql_free_result(res);	
}

void CSCSBlog::GetBlogListByUser(const unsigned char *pIn, unsigned int uiInSize,
								 unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (!pIn || pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;

	if (sizeof(TGetBlogListByUserIn) != uiInSize)
		return;
	
	pOut = (unsigned char *)new TGetBlogListByUserOut;
	memset(pOut, 0, sizeof(TGetBlogListByUserOut));
	uiOutSize = sizeof(TGetBlogListByUserOut);

	TGetBlogListByUserIn *p = (TGetBlogListByUserIn *)pIn;
	TGetBlogListByUserOut *q = (TGetBlogListByUserOut *)pOut;
	char szSQL[1024] = {0};

	sprintf(szSQL, 
			"select id, title, create_time from blog where user_id = %d "
			"order by create_time",
			p->uiUserID);
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	MYSQL_ROW row;

	q->uiSize = sizeof(TGetBlogListByUserOut);
	q->bResult = true;
	q->uiBlogNum = mysql_num_rows(res);

	if (0 < q->uiBlogNum)
	{
		TGetBlogListByUserOut tmp;

		memset(&tmp, 0, sizeof(TGetBlogListByUserOut));
		memcpy(&tmp, q, sizeof(TGetBlogListByUserOut));
		delete[] pOut;
		uiOutSize = tmp.uiSize = sizeof(TGetBlogListByUserOut)
			+ tmp.uiBlogNum * sizeof(TBlogAbstract);
	
		pOut = new unsigned char[tmp.uiSize];
		memcpy(pOut, &tmp, sizeof(TGetBlogListByUserOut));
		
		TBlogAbstract *o = 
			(TBlogAbstract *)(pOut + sizeof(TGetBlogListByUserOut));

		while ((row = mysql_fetch_row(res)))
		{
			o->uiBlogID = atoi(row[0]);
			strncpy(o->szBlogTitle, row[1], BLOG_TITLE_MAX_LENGTH);
			strncpy(o->szCreateTime, row[2], CREATE_TIME_MAX_LENGTH);

			o = (TBlogAbstract *)(((unsigned char *)o) + sizeof(TBlogAbstract));
		}
	}

	mysql_free_result(res);	
}

void CSCSBlog::GetBlogList(const unsigned char *pIn, unsigned int uiInSize,
						   unsigned char *&pOut, unsigned int &uiOutSize)
{
	if (pOut || uiOutSize)
		return;

	if (!m_pCnn)
		return;
	
	pOut = (unsigned char *)new TGetBlogListOut;
	memset(pOut, 0, sizeof(TGetBlogListOut));
	uiOutSize = sizeof(TGetBlogListOut);

	TGetBlogListOut *q = (TGetBlogListOut *)pOut;
	char szSQL[1024] = {0};

	sprintf(szSQL, 
			"select user.id, user.user_name, blog.id, blog.title, "
			"blog.create_time from user, blog where user.id = blog.user_id "
			"order by blog.create_time");
	
	if (mysql_real_query(m_pCnn, szSQL, strlen(szSQL)))
		return;	

	MYSQL_RES *res = mysql_store_result(m_pCnn);
	MYSQL_ROW row;

	q->uiSize = sizeof(TGetBlogListOut);
	q->bResult = true;
	q->uiBlogNum = mysql_num_rows(res);

	if (0 < q->uiBlogNum)
	{
		TGetBlogListOut tmp;

		memset(&tmp, 0, sizeof(TGetBlogListOut));
		memcpy(&tmp, q, sizeof(TGetBlogListOut));
		delete[] pOut;
		uiOutSize = tmp.uiSize = sizeof(TGetBlogListOut)
			+ tmp.uiBlogNum * sizeof(TBlog);
	
		pOut = new unsigned char[tmp.uiSize];
		memcpy(pOut, &tmp, sizeof(TGetBlogListOut));
		
		TBlog *o = (TBlog *)(pOut + sizeof(TGetBlogListOut));

		while ((row = mysql_fetch_row(res)))
		{
			o->uiUserID = atoi(row[0]);
			strncpy(o->szUserName, row[1], USER_NAME_MAX_LENGTH);			
			o->uiBlogID = atoi(row[2]);
			strncpy(o->szBlogTitle, row[3], BLOG_TITLE_MAX_LENGTH);
			strncpy(o->szCreateTime, row[4], CREATE_TIME_MAX_LENGTH);

			o = (TBlog *)(((unsigned char *)o) + sizeof(TBlog));
		}
	}

	mysql_free_result(res);	
}

