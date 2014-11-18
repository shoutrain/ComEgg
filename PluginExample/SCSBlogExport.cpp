#include "SCSBlogExport.h"

#include "CSCSBlog.h"

void RegisterUser(const unsigned char *pIn, unsigned int uiInSize,
				  unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.RegisterUser(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void VerifyUser(const unsigned char *pIn, unsigned int uiInSize,
				unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.VerifyUser(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void UpdateUserInfo(const unsigned char *pIn, unsigned int uiInSize,
					unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.UpdateUserInfo(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void GetUserInfo(const unsigned char *pIn, unsigned int uiInSize,
				 unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.GetUserInfo(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void AddBlog(const unsigned char *pIn, unsigned int uiInSize,
			 unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.AddBlog(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void AddComments(const unsigned char *pIn, unsigned int uiInSize,
				 unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.AddComments(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void GetBlog(const unsigned char *pIn, unsigned int uiInSize,
			 unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.GetBlog(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void GetBlogListByUser(const unsigned char *pIn, unsigned int uiInSize,
					   unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.GetBlogListByUser(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}

void GetBlogList(const unsigned char *pIn, unsigned int uiInSize,
				 unsigned char *&pOut, unsigned int &uiOutSize)
{
	CSCSBlog blog;

	if (!blog.Initialize())
		return;

	blog.GetBlogList(pIn, uiInSize, pOut, uiOutSize);
	
	blog.Uninitialize();	
}
