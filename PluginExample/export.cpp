#include "export.h"
#include "CBlog.h"

void registerUser(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init()) {
		return;
	}

	blog.registerUser(in, inSize, out, outSize);
	blog.deinit();
}

void verifyUser(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init()) {
		return;
	}

	blog.verifyUser(in, inSize, out, outSize);
	blog.deinit();
}

void updateUserInfo(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init()) {
		return;

	blog.updateUserInfo(in, inSize, out, outSize);

	blog.deinit();
}

void getUserInfo(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.getUserInfo(in, inSize, out, outSize);

	blog.deinit();
}

void addBlog(const unsigned char *in, unsigned int inSize, unsigned char *&out,
		unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.addBlog(in, inSize, out, outSize);

	blog.deinit();
}

void addComments(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.addComments(in, inSize, out, outSize);

	blog.deinit();
}

void getBlog(const unsigned char *in, unsigned int inSize, unsigned char *&out,
		unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.getBlog(in, inSize, out, outSize);

	blog.deinit();
}

void getBlogListByUser(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.getBlogListByUser(in, inSize, out, outSize);

	blog.deinit();
}

void getBlogList(const unsigned char *in, unsigned int inSize,
		unsigned char *&out, unsigned int &outSize) {
	CBlog blog;

	if (!blog.init())
		return;

	blog.getBlogList(in, inSize, out, outSize);

	blog.deinit();
}
