/*!
 * \file IWorkable.h
 * \brief Interface of workers which are used by threads.
 *
 *
 *
 * \author Rafael Gu(shoutrain.goo@gmail.com)
 * \version 1.0.1
 * \date 3/29/2015
 */

#ifndef SRC_COMMON_IWORKABLE_H_
#define SRC_COMMON_IWORKABLE_H_

class IWorkable {
public:
	virtual bool_ working() = 0;

protected:
	IWorkable() {
	}

	virtual ~IWorkable() {
	}

};

#endif /* SRC_COMMON_IWORKABLE_H_ */
