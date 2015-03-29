/*!
 * \file IWorkable.h
 * \brief Interface of workers which are used by threads.
 *
 *
 *
 * \author Rafael Gu(shoutrain.goo@gmail.com)
 * \version 1.0.0
 * \date 2/15/2015
 */

#ifndef SRC_COMMON_IWORKABLE_H_
#define SRC_COMMON_IWORKABLE_H_

class IWorkable {
public:
	// only for avoiding warning
	virtual ~IWorkable() {
	}

	virtual bool_ working() = 0;
};

#endif /* SRC_COMMON_IWORKABLE_H_ */
