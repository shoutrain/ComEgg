#ifndef _C_VAR_H_
#define _C_VAR_H_

#include "CBase.h"

#include <string.h>
#include <string>

using namespace std;

typedef class CAutoVar : public CBase {
public:
    // Default constructor.
    CAutoVar() {
        memset(&_v, 0, sizeof(UValue));
        _offset = 0;
        _len = 0;
        _type = INVALID;
    }

    CAutoVar(const CAutoVar &value) {
        _type = value._type;

        if (STR == _type && value._v.str) {
            _len = (size_) (strlen(value._v.str) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, value._v.str, _len);
            _offset = 0;
        } else {
            _offset = value._offset;
            _len = value._len;
            memcpy(&_v, &value._v, sizeof(UValue));
        }
    }

    virtual ~CAutoVar() {
        clear();
    }

    // NORMAL_STYLE
    explicit CAutoVar(b_1 value) {
        _type = B_1;
        _v.b1 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(ub_1 value) {
        _type = UB_1;
        _v.ub1 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(b_2 value) {
        _type = B_2;
        _v.b2 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(ub_2 value) {
        _type = UB_2;
        _v.ub2 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(b_4 value) {
        _type = B_4;
        _v.b4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(ub_4 value) {
        _type = UB_4;
        _v.ub4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(b_8 value) {
        _type = B_8;
        _v.b8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(ub_8 value) {
        _type = UB_8;
        _v.ub8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(const b_1 *value) {
        if (value) {
            _type = P_B_1;
            _v.pb1 = (b_1 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const ub_1 *value) {
        if (value) {
            _type = P_UB_1;
            _v.pub1 = (ub_1 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const b_2 *value) {
        if (value) {
            _type = P_B_2;
            _v.pb2 = (b_2 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const ub_2 *value) {
        if (value) {
            _type = P_UB_2;
            _v.pub2 = (ub_2 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const b_4 *value) {
        if (value) {
            _type = P_B_4;
            _v.pb4 = (b_4 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const ub_4 *value) {
        if (value) {
            _type = P_UB_4;
            _v.pub4 = (ub_4 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const b_8 *value) {
        if (value) {
            _type = P_B_8;
            _v.pb8 = (b_8 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const ub_8 *value) {
        if (value) {
            _type = P_UB_8;
            _v.pub8 = (ub_8 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    // FLOAT_STYLE
    explicit CAutoVar(fb_4 value) {
        _type = FB_4;
        _v.fb4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(fb_8 value) {
        _type = FB_8;
        _v.fb8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(const fb_4 *value) {
        if (value) {
            _type = P_FB_4;
            _v.pfb4 = (fb_4 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    explicit CAutoVar(const fb_8 *value) {
        if (value) {
            _type = P_FB_8;
            _v.pfb8 = (fb_8 *) value;
            _len = 0;
            _offset = 0;
        } else {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }
    }

    // STRING_STYLE
    explicit CAutoVar(const ch_1 *value, const size_ n) {
        if (!value) {
            assert(0);
            logError("Invalid value in construct of CAutoVar");

            return;
        }

        if (0 == n) {
            _type = STR;
            _len = (size_) (strlen(value) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, value, _len);
            _offset = 0;
        } else {
            _type = P_STR;
            _v.pstr = (ch_1 *) value;
            _len = n;
            _offset = 0;
        }
    }

    explicit CAutoVar(const string &value) {
        if (value.empty()) {
            assert(0);
            logError("Invalid value in construct of CAutoVar");

            return;
        }

        _type = STR;
        _len = (size_) (value.length() + 1);
        _v.str = new ch_1[_len];
        memcpy(_v.str, value.data(), _len);
        _offset = 0;
    }

    // OBJECT_STYLE
    explicit CAutoVar(const obj_ value) {
        _type = OBJ;
        _v.obj = value;
        _len = 0;
        _offset = 0;
    }

    explicit CAutoVar(obj_ *value, size_ n_offset, size_ n = 0) {
        _offset = n_offset;
        _len = n;
        _type = P_OBJ;
        _v.pobj = value;
    }

    const CAutoVar &operator=(b_1 value) {
        if (INVALID == _type) {
            _type = B_1;
            _v.b1 = value;
        } else {
            switch (_type) {
                case B_1:
                    _v.b1 = value;
                    break;
                case P_B_1:
                    *_v.pb1 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_1 value) {
        if (INVALID == _type) {
            _type = UB_1;
            _v.ub1 = value;
        } else {
            switch (_type) {
                case UB_1:
                    _v.ub1 = value;
                    break;
                case P_UB_1:
                    *_v.pub1 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_2 value) {
        if (INVALID == _type) {
            _type = B_2;
            _v.b2 = value;
        } else {
            switch (_type) {
                case B_2:
                    _v.b2 = value;
                    break;
                case P_B_2:
                    *_v.pb2 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_2 value) {
        if (INVALID == _type) {
            _type = UB_2;
            _v.ub2 = value;
        } else {
            switch (_type) {
                case UB_2:
                    _v.ub2 = value;
                    break;
                case P_UB_2:
                    *_v.pub2 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_4 value) {
        if (INVALID == _type) {
            _type = B_4;
            _v.b4 = value;
        } else {
            switch (_type) {
                case B_4:
                    _v.b4 = value;
                    break;
                case P_B_4:
                    *_v.pb4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_4 value) {
        if (INVALID == _type) {
            _type = UB_4;
            _v.ub4 = value;
        } else {
            switch (_type) {
                case UB_4:
                    _v.ub4 = value;
                    break;
                case P_UB_4:
                    *_v.pub4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_8 value) {
        if (INVALID == _type) {
            _type = B_8;
            _v.b8 = value;
        } else {
            switch (_type) {
                case B_8:
                    _v.b8 = value;
                    break;
                case P_B_8:
                    *_v.pb8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_8 value) {
        if (INVALID == _type) {
            _type = UB_8;
            _v.ub8 = value;
        } else {
            switch (_type) {
                case UB_8:
                    _v.ub8 = value;
                    break;
                case P_UB_8:
                    *_v.pub8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(fb_4 value) {
        if (INVALID == _type) {
            _type = FB_4;
            _v.fb4 = value;
        } else {
            switch (_type) {
                case FB_4:
                    _v.fb4 = value;
                    break;
                case P_FB_4:
                    *_v.pfb4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(fb_8 value) {
        if (INVALID == _type) {
            _type = FB_8;
            _v.fb8 = value;
        } else {
            switch (_type) {
                case FB_8:
                    _v.fb8 = value;
                    break;
                case P_FB_8:
                    *_v.pfb8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_1 *value) {
        if (INVALID == _type) {
            _type = P_B_1;
            _v.pb1 = value;
        } else {
            switch (_type) {
                case B_1:
                    _v.b1 = *value;
                    break;
                case P_B_1:
                    _v.pb1 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_1 *value) {
        if (INVALID == _type) {
            _type = P_UB_1;
            _v.pub1 = value;
        } else {
            switch (_type) {
                case UB_1:
                    _v.ub1 = *value;
                    break;
                case P_UB_1:
                    _v.pub1 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_2 *value) {
        if (INVALID == _type) {
            _type = P_B_2;
            _v.pb2 = value;
        } else {
            switch (_type) {
                case B_2:
                    _v.b2 = *value;
                    break;
                case P_B_2:
                    _v.pb2 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_2 *value) {
        if (INVALID == _type) {
            _type = P_UB_2;
            _v.pub2 = value;
        } else {
            switch (_type) {
                case UB_2:
                    _v.ub2 = *value;
                    break;
                case P_UB_2:
                    _v.pub2 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_4 *value) {
        if (INVALID == _type) {
            _type = P_B_4;
            _v.pb4 = value;
        } else {
            switch (_type) {
                case B_4:
                    _v.b4 = *value;
                    break;
                case P_B_4:
                    _v.pb4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_4 *value) {
        if (INVALID == _type) {
            _type = P_UB_4;
            _v.pub4 = value;
        } else {
            switch (_type) {
                case UB_4:
                    _v.ub4 = *value;
                    break;
                case P_UB_4:
                    _v.pub4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(b_8 *value) {
        if (INVALID == _type) {
            _type = P_B_8;
            _v.pb8 = value;
        } else {
            switch (_type) {
                case B_8:
                    _v.b8 = *value;
                    break;
                case P_B_8:
                    _v.pb8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(ub_8 *value) {
        if (INVALID == _type) {
            _type = P_B_8;
            _v.pub8 = value;
        } else {
            switch (_type) {
                case UB_8:
                    _v.ub8 = *value;
                    break;
                case P_UB_8:
                    _v.pub8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(fb_4 *value) {
        if (INVALID == _type) {
            _type = P_FB_4;
            _v.pfb4 = value;
        } else {
            switch (_type) {
                case FB_4:
                    _v.fb4 = *value;
                    break;
                case P_FB_4:
                    _v.pfb4 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(fb_8 *value) {
        if (INVALID == _type) {
            _type = P_FB_8;
            _v.pfb8 = value;
        } else {
            switch (_type) {
                case FB_8:
                    _v.fb8 = *value;
                    break;
                case P_FB_8:
                    _v.pfb8 = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(const ch_1 *value) {
        if (!value) {
            assert(0);
            logError("Invalid value in construct of CAutoVar");
        }

        if (INVALID == _type) {
            _type = STR;
            _len = (size_) (strlen(value) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, value, _len);
        } else {
            switch (_type) {
                case STR: {
                    _DEL_ARR(_v.str);
                    _len = (size_) (strlen(value) + 1);
                    _v.str = new ch_1[_len];
                    memcpy(_v.str, value, _len);
                }
                    break;
                case P_STR: {
                    memset(_v.pstr, 0, _len);
                    strncpy(_v.pstr, value, _len);
                }
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(const obj_ value) {
        if (INVALID == _type) {
            _type = OBJ;
            _v.obj = value;
            _len = 0;
        } else {
            switch (_type) {
                case OBJ:
                    _v.obj = value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    const CAutoVar &operator=(const CAutoVar &value) {
        if (&value == this) {
            return *this;
        }

        if (INVALID == _type) {
            _type = value._type;

            if (STR == _type) {
                const ch_1 *psz = (const ch_1 *) value;

                _len = (size_) (strlen(psz) + 1);
                _v.str = new ch_1[_len];
                memcpy(_v.str, psz, _len);
            } else {
                _offset = value._offset;
                _len = value._len;
                memcpy(&_v, &value._v, sizeof(UValue));
            }
        } else if (INVALID == value._type) {
            if (P_OBJ == _type || P_STR == _type) {
                assert(0);
                logError("Invalid value in construct of CAutoVar");
            } else {
                clear();
            }
        } else if (REFERENCE_VARIABLE != (REFERENCE_VARIABLE & _type)
                && REFERENCE_VARIABLE != (REFERENCE_VARIABLE & value._type)) {
            switch (_type) {
                case B_1:
                    _v.b1 = (b_1) value;
                    break;
                case UB_1:
                    _v.ub1 = (ub_1) value;
                    break;
                case B_2:
                    _v.b2 = (b_2) value;
                    break;
                case UB_2:
                    _v.ub2 = (ub_2) value;
                    break;
                case B_4:
                    _v.b4 = (b_4) value;
                    break;
                case UB_4:
                    _v.ub4 = (ub_4) value;
                    break;
                case B_8:
                    _v.b8 = (b_8) value;
                    break;
                case UB_8:
                    _v.ub8 = (ub_8) value;
                    break;
                case FB_4:
                    _v.fb4 = (fb_4) value;
                    break;
                case FB_8:
                    _v.fb8 = (fb_8) value;
                    break;
                case STR: {
                    const ch_1 *psz = (const ch_1 *) value;

                    _DEL_ARR(_v.str);
                    _len = (size_) (strlen(psz) + 1);
                    _v.str = new ch_1[_len];
                    memcpy(_v.str, psz, _len);
                }
                    break;
                case OBJ:
                    _v.obj = (obj_) value;
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        } else if (REFERENCE_VARIABLE != (REFERENCE_VARIABLE & _type)
                && REFERENCE_VARIABLE == (REFERENCE_VARIABLE & value._type)) {
            switch (_type) {
                case B_1:
                    _v.b1 = (b_1) value;
                    break;
                case UB_1:
                    _v.ub1 = (ub_1) value;
                    break;
                case B_2:
                    _v.b2 = (b_2) value;
                    break;
                case UB_2:
                    _v.ub2 = (ub_2) value;
                    break;
                case B_4:
                    _v.b4 = (b_4) value;
                    break;
                case UB_4:
                    _v.ub4 = (ub_4) value;
                    break;
                case B_8:
                    _v.b8 = (b_8) value;
                    break;
                case UB_8:
                    _v.ub8 = (ub_8) value;
                    break;
                case FB_4:
                    _v.fb4 = (fb_4) value;
                    break;
                case FB_8:
                    _v.fb8 = (fb_8) value;
                    break;
                case STR: {
                    const ch_1 *psz = (const ch_1 *) value;

                    _DEL_ARR(_v.str);
                    _len = (size_) (strlen(psz) + 1);
                    _v.str = new ch_1[_len];
                    memcpy(_v.str, psz, _len);
                }
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        } else if (REFERENCE_VARIABLE == (REFERENCE_VARIABLE & _type)) {
            switch (_type) {
                case P_B_1:
                    *_v.pb1 = (b_1) value;
                    break;
                case P_UB_1:
                    *_v.pub1 = (ub_1) value;
                    break;
                case P_B_2:
                    *_v.pb2 = (b_2) value;
                    break;
                case P_UB_2:
                    *_v.pub2 = (ub_2) value;
                    break;
                case P_B_4:
                    *_v.pb4 = (b_4) value;
                    break;
                case P_UB_4:
                    *_v.pub4 = (ub_4) value;
                    break;
                case P_B_8:
                    *_v.pb8 = (b_8) value;
                    break;
                case P_UB_8:
                    *_v.pub8 = (ub_8) value;
                    break;
                case P_FB_4:
                    *_v.pfb4 = (fb_4) value;
                    break;
                case P_FB_8:
                    *_v.pfb8 = (fb_8) value;
                    break;
                case P_STR: {
                    const ch_1 *psz = (const ch_1 *) value;

                    memset(_v.pstr, 0, _len);
                    strncpy(_v.pstr, psz, _len);
                }
                    break;
                case P_OBJ: {
                    if (REFERENCE_VARIABLE == (REFERENCE_VARIABLE & value._type)
                            && _len == value._len && _type == value._type) {
                        memcpy(((ub_1 *) *_v.pobj) + _offset,
                                ((ub_1 *) *value._v.pobj) + value._offset, _len);
                    } else {
                        assert(0);
                        logError("Invalid value in construct of CAutoVar");
                    }
                }
                    break;
                default:
                    assert(0);
                    logError("Invalid value in construct of CAutoVar");
            }
        }

        return *this;
    }

    operator b_1() const {
        switch (_type) {
            case B_1:
                return (b_1) _v.b1;
            case UB_1:
                return (b_1) _v.ub1;
            case B_2:
                return (b_1) _v.b2;
            case UB_2:
                return (b_1) _v.ub2;
            case B_4:
                return (b_1) _v.b4;
            case UB_4:
                return (b_1) _v.ub4;
            case B_8:
                return (b_1) _v.b8;
            case UB_8:
                return (b_1) _v.ub8;
            case FB_4:
                return (b_1) _v.fb4;
            case FB_8:
                return (b_1) _v.fb8;
            case P_B_1:
                return (b_1) (*_v.pb1);
            case P_UB_1:
                return (b_1) (*_v.pub1);
            case P_B_2:
                return (b_1) (*_v.pb2);
            case P_UB_2:
                return (b_1) (*_v.pub2);
            case P_B_4:
                return (b_1) (*_v.pb4);
            case P_UB_4:
                return (b_1) (*_v.pub4);
            case P_B_8:
                return (b_1) (*_v.pb8);
            case P_UB_8:
                return (b_1) (*_v.pub8);
            case P_FB_4:
                return (b_1) (*_v.pfb4);
            case P_FB_8:
                return (b_1) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator ub_1() const {
        switch (_type) {
            case B_1:
                return (ub_1) _v.b1;
            case UB_1:
                return (ub_1) _v.ub1;
            case B_2:
                return (ub_1) _v.b2;
            case UB_2:
                return (ub_1) _v.ub2;
            case B_4:
                return (ub_1) _v.b4;
            case UB_4:
                return (ub_1) _v.ub4;
            case B_8:
                return (ub_1) _v.b8;
            case UB_8:
                return (ub_1) _v.ub8;
            case FB_4:
                return (ub_1) _v.fb4;
            case FB_8:
                return (ub_1) _v.fb8;
            case P_B_1:
                return (ub_1) (*_v.pb1);
            case P_UB_1:
                return (ub_1) (*_v.pub1);
            case P_B_2:
                return (ub_1) (*_v.pb2);
            case P_UB_2:
                return (ub_1) (*_v.pub2);
            case P_B_4:
                return (ub_1) (*_v.pb4);
            case P_UB_4:
                return (ub_1) (*_v.pub4);
            case P_B_8:
                return (ub_1) (*_v.pb8);
            case P_UB_8:
                return (ub_1) (*_v.pub8);
            case P_FB_4:
                return (ub_1) (*_v.pfb4);
            case P_FB_8:
                return (ub_1) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator b_2() const {
        switch (_type) {
            case B_1:
                return (b_2) _v.b1;
            case UB_1:
                return (b_2) _v.ub1;
            case B_2:
                return (b_2) _v.b2;
            case UB_2:
                return (b_2) _v.ub2;
            case B_4:
                return (b_2) _v.b4;
            case UB_4:
                return (b_2) _v.ub4;
            case B_8:
                return (b_2) _v.b8;
            case UB_8:
                return (b_2) _v.ub8;
            case FB_4:
                return (b_2) _v.fb4;
            case FB_8:
                return (b_2) _v.fb8;
            case P_B_1:
                return (b_2) (*_v.pb1);
            case P_UB_1:
                return (b_2) (*_v.pub1);
            case P_B_2:
                return (b_2) (*_v.pb2);
            case P_UB_2:
                return (b_2) (*_v.pub2);
            case P_B_4:
                return (b_2) (*_v.pb4);
            case P_UB_4:
                return (b_2) (*_v.pub4);
            case P_B_8:
                return (b_2) (*_v.pb8);
            case P_UB_8:
                return (b_2) (*_v.pub8);
            case P_FB_4:
                return (b_2) (*_v.pfb4);
            case P_FB_8:
                return (b_2) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator ub_2() const {
        switch (_type) {
            case B_1:
                return (ub_2) _v.b1;
            case UB_1:
                return (ub_2) _v.ub1;
            case B_2:
                return (ub_2) _v.b2;
            case UB_2:
                return (ub_2) _v.ub2;
            case B_4:
                return (ub_2) _v.b4;
            case UB_4:
                return (ub_2) _v.ub4;
            case B_8:
                return (ub_2) _v.b8;
            case UB_8:
                return (ub_2) _v.ub8;
            case FB_4:
                return (ub_2) _v.fb4;
            case FB_8:
                return (ub_2) _v.fb8;
            case P_B_1:
                return (ub_2) (*_v.pb1);
            case P_UB_1:
                return (ub_2) (*_v.pub1);
            case P_B_2:
                return (ub_2) (*_v.pb2);
            case P_UB_2:
                return (ub_2) (*_v.pub2);
            case P_B_4:
                return (ub_2) (*_v.pb4);
            case P_UB_4:
                return (ub_2) (*_v.pub4);
            case P_B_8:
                return (ub_2) (*_v.pb8);
            case P_UB_8:
                return (ub_2) (*_v.pub8);
            case P_FB_4:
                return (ub_2) (*_v.pfb4);
            case P_FB_8:
                return (ub_2) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator b_4() const {
        switch (_type) {
            case B_1:
                return (b_4) _v.b1;
            case UB_1:
                return (b_4) _v.ub1;
            case B_2:
                return (b_4) _v.b2;
            case UB_2:
                return (b_4) _v.ub2;
            case B_4:
                return (b_4) _v.b4;
            case UB_4:
                return (b_4) _v.ub4;
            case B_8:
                return (b_4) _v.b8;
            case UB_8:
                return (b_4) _v.ub8;
            case FB_4:
                return (b_4) _v.fb4;
            case FB_8:
                return (b_4) _v.fb8;
            case P_B_1:
                return (b_4) (*_v.pb1);
            case P_UB_1:
                return (b_4) (*_v.pub1);
            case P_B_2:
                return (b_4) (*_v.pb2);
            case P_UB_2:
                return (b_4) (*_v.pub2);
            case P_B_4:
                return (b_4) (*_v.pb4);
            case P_UB_4:
                return (b_4) (*_v.pub4);
            case P_B_8:
                return (b_4) (*_v.pb8);
            case P_UB_8:
                return (b_4) (*_v.pub8);
            case P_FB_4:
                return (b_4) (*_v.pfb4);
            case P_FB_8:
                return (b_4) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator ub_4() const {
        switch (_type) {
            case B_1:
                return (ub_4) _v.b1;
            case UB_1:
                return (ub_4) _v.ub1;
            case B_2:
                return (ub_4) _v.b2;
            case UB_2:
                return (ub_4) _v.ub2;
            case B_4:
                return (ub_4) _v.b4;
            case UB_4:
                return (ub_4) _v.ub4;
            case B_8:
                return (ub_4) _v.b8;
            case UB_8:
                return (ub_4) _v.ub8;
            case FB_4:
                return (ub_4) _v.fb4;
            case FB_8:
                return (ub_4) _v.fb8;
            case P_B_1:
                return (ub_4) (*_v.pb1);
            case P_UB_1:
                return (ub_4) (*_v.pub1);
            case P_B_2:
                return (ub_4) (*_v.pb2);
            case P_UB_2:
                return (ub_4) (*_v.pub2);
            case P_B_4:
                return (ub_4) (*_v.pb4);
            case P_UB_4:
                return (ub_4) (*_v.pub4);
            case P_B_8:
                return (ub_4) (*_v.pb8);
            case P_UB_8:
                return (ub_4) (*_v.pub8);
            case P_FB_4:
                return (ub_4) (*_v.pfb4);
            case P_FB_8:
                return (ub_4) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator b_8() const {
        switch (_type) {
            case B_1:
                return (b_8) _v.b1;
            case UB_1:
                return (b_8) _v.ub1;
            case B_2:
                return (b_8) _v.b2;
            case UB_2:
                return (b_8) _v.ub2;
            case B_4:
                return (b_8) _v.b4;
            case UB_4:
                return (b_8) _v.ub4;
            case B_8:
                return (b_8) _v.b8;
            case UB_8:
                return (b_8) _v.ub8;
            case FB_4:
                return (b_8) _v.fb4;
            case FB_8:
                return (b_8) _v.fb8;
            case P_B_1:
                return (b_8) (*_v.pb1);
            case P_UB_1:
                return (b_8) (*_v.pub1);
            case P_B_2:
                return (b_8) (*_v.pb2);
            case P_UB_2:
                return (b_8) (*_v.pub2);
            case P_B_4:
                return (b_8) (*_v.pb4);
            case P_UB_4:
                return (b_8) (*_v.pub4);
            case P_B_8:
                return (b_8) (*_v.pb8);
            case P_UB_8:
                return (b_8) (*_v.pub8);
            case P_FB_4:
                return (b_8) (*_v.pfb4);
            case P_FB_8:
                return (b_8) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator ub_8() const {
        switch (_type) {
            case B_1:
                return (ub_8) _v.b1;
            case UB_1:
                return (ub_8) _v.ub1;
            case B_2:
                return (ub_8) _v.b2;
            case UB_2:
                return (ub_8) _v.ub2;
            case B_4:
                return (ub_8) _v.b4;
            case UB_4:
                return (ub_8) _v.ub4;
            case B_8:
                return (ub_8) _v.b8;
            case UB_8:
                return (ub_8) _v.ub8;
            case FB_4:
                return (ub_8) _v.fb4;
            case FB_8:
                return (ub_8) _v.fb8;
            case P_B_1:
                return (ub_8) (*_v.pb1);
            case P_UB_1:
                return (ub_8) (*_v.pub1);
            case P_B_2:
                return (ub_8) (*_v.pb2);
            case P_UB_2:
                return (ub_8) (*_v.pub2);
            case P_B_4:
                return (ub_8) (*_v.pb4);
            case P_UB_4:
                return (ub_8) (*_v.pub4);
            case P_B_8:
                return (ub_8) (*_v.pb8);
            case P_UB_8:
                return (ub_8) (*_v.pub8);
            case P_FB_4:
                return (ub_8) (*_v.pfb4);
            case P_FB_8:
                return (ub_8) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator fb_4() const {
        switch (_type) {
            case B_1:
                return (fb_4) _v.b1;
            case UB_1:
                return (fb_4) _v.ub1;
            case B_2:
                return (fb_4) _v.b2;
            case UB_2:
                return (fb_4) _v.ub2;
            case B_4:
                return (fb_4) _v.b4;
            case UB_4:
                return (fb_4) _v.ub4;
            case B_8:
                return (fb_4) _v.b8;
            case UB_8:
                return (fb_4) _v.ub8;
            case FB_4:
                return (fb_4) _v.fb4;
            case FB_8:
                return (fb_4) _v.fb8;
            case P_B_1:
                return (fb_4) (*_v.pb1);
            case P_UB_1:
                return (fb_4) (*_v.pub1);
            case P_B_2:
                return (fb_4) (*_v.pb2);
            case P_UB_2:
                return (fb_4) (*_v.pub2);
            case P_B_4:
                return (fb_4) (*_v.pb4);
            case P_UB_4:
                return (fb_4) (*_v.pub4);
            case P_B_8:
                return (fb_4) (*_v.pb8);
            case P_UB_8:
                return (fb_4) (*_v.pub8);
            case P_FB_4:
                return (fb_4) (*_v.pfb4);
            case P_FB_8:
                return (fb_4) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator fb_8() const {
        switch (_type) {
            case B_1:
                return (fb_8) _v.b1;
            case UB_1:
                return (fb_8) _v.ub1;
            case B_2:
                return (fb_8) _v.b2;
            case UB_2:
                return (fb_8) _v.ub2;
            case B_4:
                return (fb_8) _v.b4;
            case UB_4:
                return (fb_8) _v.ub4;
            case B_8:
                return (fb_8) _v.b8;
            case UB_8:
                return (fb_8) _v.ub8;
            case FB_4:
                return (fb_8) _v.fb4;
            case FB_8:
                return (fb_8) _v.fb8;
            case P_B_1:
                return (fb_8) (*_v.pb1);
            case P_UB_1:
                return (fb_8) (*_v.pub1);
            case P_B_2:
                return (fb_8) (*_v.pb2);
            case P_UB_2:
                return (fb_8) (*_v.pub2);
            case P_B_4:
                return (fb_8) (*_v.pb4);
            case P_UB_4:
                return (fb_8) (*_v.pub4);
            case P_B_8:
                return (fb_8) (*_v.pb8);
            case P_UB_8:
                return (fb_8) (*_v.pub8);
            case P_FB_4:
                return (fb_8) (*_v.pfb4);
            case P_FB_8:
                return (fb_8) (*_v.pfb8);
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator const ch_1 *() const {
        switch (_type) {
            case STR:
                return _v.str;
            case P_STR:
                return _v.pstr;
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    operator const obj_() const {
        switch (_type) {
            case OBJ:
                return _v.obj;
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
                return 0;
        }
    }

    const size_ size() const {
        return _len;
    }

    void empty() {
        switch (_type) {
            case B_1:
                _v.b1 = 0;
                break;
            case UB_1:
                _v.ub1 = 0;
                break;
            case B_2:
                _v.b2 = 0;
                break;
            case UB_2:
                _v.ub2 = 0;
                break;
            case B_4:
                _v.b4 = 0;
                break;
            case UB_4:
                _v.ub4 = 0;
                break;
            case B_8:
                _v.b8 = 0;
                break;
            case UB_8:
                _v.ub8 = 0;
                break;
            case FB_4:
                _v.fb4 = 0;
                break;
            case FB_8:
                _v.fb8 = 0;
                break;
            case P_B_1:
                (*_v.pb1) = 0;
                break;
            case P_UB_1:
                (*_v.pub1) = 0;
                break;
            case P_B_2:
                (*_v.pb2) = 0;
                break;
            case P_UB_2:
                (*_v.pub2) = 0;
                break;
            case P_B_4:
                (*_v.pb4) = 0;
                break;
            case P_UB_4:
                (*_v.pub4) = 0;
                break;
            case P_B_8:
                (*_v.pb8) = 0;
                break;
            case P_UB_8:
                (*_v.pub8) = 0;
                break;
            case P_FB_4:
                (*_v.pfb4) = 0;
                break;
            case P_FB_8:
                (*_v.pfb8) = 0;
                break;
            case STR:
                memset(_v.str, 0, _len);
                break;
            case P_STR:
                memset(_v.pstr, 0, _len);
                break;
            case OBJ:
                _v.obj = null_v;
                break;
            case P_OBJ:
                if (_v.pobj && _len) {
                    memset(((ub_1 *) *_v.pobj) + _offset, 0, _len);
                } else {
                    assert(0);
                    logError("Wrong type of conversion of CAutoVar");
                }

                break;
            default:
                assert(0);
                logError("Wrong type of conversion of CAutoVar");
        }
    }

    evt_ getType() const {
        return _EVT(_type);
    }

    void clear() {
        if (STR == _type) {
            _DEL_ARR(_v.str);
        } else {
            memset(&_v, 0, sizeof(UValue));
        }

        _offset = 0;
        _len = 0;
        _type = INVALID;
    }

private:
    type_ _type;

    // Just valid as P_OBJ
    size_ _offset;

    // It's just valid when type is P_STR or STR or OBJ.
    // Default value is 0, it's the string's length + 1.
    size_ _len;

    union UValue {
        // NORMAL_STYLE
        b_1 *pb1;
        ub_1 *pub1;
        b_2 *pb2;
        ub_2 *pub2;
        b_4 *pb4;
        ub_4 *pub4;
        b_8 *pb8;
        ub_8 *pub8;

        b_1 b1;
        ub_1 ub1;
        b_2 b2;
        ub_2 ub2;
        b_4 b4;
        ub_4 ub4;
        b_8 b8;
        ub_8 ub8;

        // FLOAT_STYLE
        fb_4 fb4;
        fb_8 fb8;

        fb_4 *pfb4;
        fb_8 *pfb8;

        // STRING_STYLE
        ch_1 *str;
        ch_1 *pstr;

        // OBJECT_STYLE
        obj_ obj;
        obj_ *pobj;
    } _v;

    friend const CAutoVar operator-(const CAutoVar &value);

    friend const CAutoVar operator~(const CAutoVar &value);

    friend const b_4 operator!(const CAutoVar &value);

    friend const CAutoVar operator+(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator-(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator*(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator/(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator%(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator&(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator|(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const CAutoVar operator^(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator==(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator!=(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator>(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator>=(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator<(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator<=(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator&&(const CAutoVar &leftValue,
            const CAutoVar &rightValue);

    friend const b_4 operator||(const CAutoVar &leftValue,
            const CAutoVar &rightValue);
} v_;

#endif // _C_VAR_H_
