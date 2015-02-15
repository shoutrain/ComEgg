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

#ifndef _I_WORKABLE_H_
#define _I_WORKABLE_H_

class IWorkable {
public:
    // only for avoiding warning
    virtual ~IWorkable() {
    }

    virtual bool_ working() = 0;
};

#endif // _I_WORKABLE_H_
