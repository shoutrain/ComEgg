#ifndef _I_WORKABLE_H_
#define _I_WORKABLE_H_

class IWorkable {
public:
    virtual ~IWorkable() {
    } // to anone_ waring

    virtual bool_ working() = 0;
};

#endif // _I_WORKABLE_H_
