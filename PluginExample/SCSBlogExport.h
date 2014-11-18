#ifndef SCS_BLOG_EXPORT_H
#define SCS_BLOG_EXPORT_H

extern "C"
{
	void RegisterUser(const unsigned char *pIn, unsigned int uiInSize,
					  unsigned char *&pOut, unsigned int &uiOutSize);
	void VerifyUser(const unsigned char *pIn, unsigned int uiInSize,
					unsigned char *&pOut, unsigned int &uiOutSize);
	void UpdateUserInfo(const unsigned char *pIn, unsigned int uiInSize,
						unsigned char *&pOut, unsigned int &uiOutSize);
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
}

#endif // SCS_BLOG_EXPORT_H

