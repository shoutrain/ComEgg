#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "CBase.h"

#include <cassert>
#include <cstring>

// Data _type signs and masks
const unsigned int UNSIGNED_SIGN = 0x00001000;
const unsigned int LEGNTH_MASK = 0x0000000f;
const unsigned int UDT_MASK = 0x000000f0;
const unsigned int RDT_MASK = 0x0000ffff;
const unsigned int POINTER_SIGN = 0x00010000;

#define __is_unsigned(TYPE) \
    ((TYPE) & UNSIGNED_SIGN)
#define __len(TYPE) \
    ((TYPE) & LEGNTH_MASK)
#define __udt(TYPE) \
    ((TYPE) & UDT_MASK)
#define __rdt(TYPE) \
    ((rdt_)((TYPE) & RDT_MASK))
#define __is_pointer(TYPE) \
    ((TYPE) & POINTER_SIGN)

typedef enum UserDataType {
    NORMAL_TYPE = 0x00000010,
    FLOAT_TYPE = 0x00000020,
    STRING_TYPE = 0x00000030,
    OBJECT_TYPE = 0x00000040
} udt_;

typedef enum RunningDataType {
    INVALID = 0x00000000,

    B_1 = 0x00000001 | NORMAL_TYPE,
    UB_1 = B_1 | UNSIGNED_SIGN,
    B_2 = 0x00000002 | NORMAL_TYPE,
    UB_2 = B_2 | UNSIGNED_SIGN,
    B_4 = 0x00000004 | NORMAL_TYPE,
    UB_4 = B_4 | UNSIGNED_SIGN,
    B_8 = 0x00000008 | NORMAL_TYPE,
    UB_8 = B_8 | UNSIGNED_SIGN,

    FB_4 = 0x00000004 | FLOAT_TYPE,
    FB_8 = 0x00000008 | FLOAT_TYPE,

    STR = 0x00000000 | STRING_TYPE,

    OBJ = 0x00000000 | OBJECT_TYPE
} rdt_;

typedef enum RunningDataTypeForPointer {
    P_B_1 = POINTER_SIGN | B_1,
    P_UB_1 = POINTER_SIGN | UB_1,
    P_B_2 = POINTER_SIGN | B_2,
    P_UB_2 = POINTER_SIGN | UB_2,
    P_B_4 = POINTER_SIGN | B_4,
    P_UB_4 = POINTER_SIGN | UB_4,
    P_B_8 = POINTER_SIGN | B_8,
    P_UB_8 = POINTER_SIGN | UB_8,

    P_FB_4 = POINTER_SIGN | FB_4,
    P_FB_8 = POINTER_SIGN | FB_8,

    P_STR = POINTER_SIGN | STR,

    P_OBJ = POINTER_SIGN | OBJ,
} prdt_;

class Variable: public CBase {
public:
    Variable() {
        memset(&_v, 0, sizeof(unit_value));
        _offset = 0;
        _len = 0;
        _type = INVALID;
    }

    ~Variable() {
        clear();
    }

    Variable(const Variable &value) {
        _type = value._type;

        if (STR == _type && value._v.str) {
            _len = (size_) (strlen(value._v.str) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, value._v.str, _len);
            _offset = 0;
        } else {
            _offset = value._offset;
            _len = value._len;
            memcpy(&_v, &value._v, sizeof(unit_value));
        }
    }

    explicit Variable(b_1 value) {
        _type = B_1;
        _v.b1 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(ub_1 value) {
        _type = UB_1;
        _v.ub1 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(b_2 value) {
        _type = B_2;
        _v.b2 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(ub_2 value) {
        _type = UB_2;
        _v.ub2 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(b_4 value) {
        _type = B_4;
        _v.b4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(ub_4 value) {
        _type = UB_4;
        _v.ub4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(b_8 value) {
        _type = B_8;
        _v.b8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(ub_8 value) {
        _type = UB_8;
        _v.ub8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const b_1 *pValue) {
        assert(null_v != pValue);

        _type = P_B_1;
        _v.pb1 = (b_1 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const ub_1 *pValue) {
        assert(null_v != pValue);

        _type = P_UB_1;
        _v.pub1 = (ub_1 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const b_2 *pValue) {
        assert(null_v != pValue);

        _type = P_B_2;
        _v.pb2 = (b_2 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const ub_2 *pValue) {
        assert(null_v != pValue);

        _type = P_UB_2;
        _v.pub2 = (ub_2 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const b_4 *pValue) {
        assert(null_v != pValue);

        _type = P_B_4;
        _v.pb4 = (b_4 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const ub_4 *pValue) {
        assert(null_v != pValue);

        _type = P_UB_4;
        _v.pub4 = (ub_4 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const b_8 *pValue) {
        assert(null_v != pValue);

        _type = P_B_8;
        _v.pb8 = (b_8 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const ub_8 *pValue) {
        assert(null_v != pValue);

        _type = P_UB_8;
        _v.pub8 = (ub_8 *) pValue;
        _len = 0;
        _offset = 0;
    }

    // FLOAT_STYLE
    explicit Variable(fb_4 value) {
        _type = FB_4;
        _v.fb4 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(fb_8 value) {
        _type = FB_8;
        _v.fb8 = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const fb_4 *pValue) {
        assert(null_v != pValue);

        _type = P_FB_4;
        _v.pfb4 = (fb_4 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const fb_8 *pValue) {
        assert(null_v != pValue);

        _type = P_FB_8;
        _v.pfb8 = (fb_8 *) pValue;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(const ch_1 *pszValue, const size_ n) {
        assert(null_v != pszValue);

        if (0 == n) {
            _type = STR;
            _len = (size_) (strlen(pszValue) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, pszValue, _len);
            _offset = 0;
        } else {
            _type = P_STR;
            _v.pstr = (ch_1 *) pszValue;
            _len = n;
            _offset = 0;
        }
    }

    explicit Variable(const obj_ value) {
        _type = OBJ;
        _v.obj = value;
        _len = 0;
        _offset = 0;
    }

    explicit Variable(obj_ *pValue, size_ nOffset, size_ n = 0) {
        _offset = nOffset;
        _len = n;
        _type = P_OBJ;
        _v.pobj = pValue;
    }

    rdt_ rdt() const {
        return __rdt(_type) ;
    }

    const Variable &operator =(b_1 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_1 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_2 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_2 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_4 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_4 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_8 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_8 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(fb_4 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(fb_8 value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_1 *pValue) {
        if (INVALID == _type) {
            _type = P_B_1;
            _v.pb1 = pValue;
        } else {
            switch (_type) {
            case B_1:
                _v.b1 = *pValue;
                break;
            case P_B_1:
                _v.pb1 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_1 *pValue) {
        if (INVALID == _type) {
            _type = P_UB_1;
            _v.pub1 = pValue;
        } else {
            switch (_type) {
            case UB_1:
                _v.ub1 = *pValue;
                break;
            case P_UB_1:
                _v.pub1 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_2 *pValue) {
        if (INVALID == _type) {
            _type = P_B_2;
            _v.pb2 = pValue;
        } else {
            switch (_type) {
            case B_2:
                _v.b2 = *pValue;
                break;
            case P_B_2:
                _v.pb2 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_2 *pValue) {
        if (INVALID == _type) {
            _type = P_UB_2;
            _v.pub2 = pValue;
        } else {
            switch (_type) {
            case UB_2:
                _v.ub2 = *pValue;
                break;
            case P_UB_2:
                _v.pub2 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_4 *pValue) {
        if (INVALID == _type) {
            _type = P_B_4;
            _v.pb4 = pValue;
        } else {
            switch (_type) {
            case B_4:
                _v.b4 = *pValue;
                break;
            case P_B_4:
                _v.pb4 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_4 *pValue) {
        if (INVALID == _type) {
            _type = P_UB_4;
            _v.pub4 = pValue;
        } else {
            switch (_type) {
            case UB_4:
                _v.ub4 = *pValue;
                break;
            case P_UB_4:
                _v.pub4 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(b_8 *pValue) {
        if (INVALID == _type) {
            _type = P_B_8;
            _v.pb8 = pValue;
        } else {
            switch (_type) {
            case B_8:
                _v.b8 = *pValue;
                break;
            case P_B_8:
                _v.pb8 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(ub_8 *pValue) {
        if (INVALID == _type) {
            _type = P_B_8;
            _v.pub8 = pValue;
        } else {
            switch (_type) {
            case UB_8:
                _v.ub8 = *pValue;
                break;
            case P_UB_8:
                _v.pub8 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(fb_4 *pValue) {
        if (INVALID == _type) {
            _type = P_FB_4;
            _v.pfb4 = pValue;
        } else {
            switch (_type) {
            case FB_4:
                _v.fb4 = *pValue;
                break;
            case P_FB_4:
                _v.pfb4 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(fb_8 *pValue) {
        if (INVALID == _type) {
            _type = P_FB_8;
            _v.pfb8 = pValue;
        } else {
            switch (_type) {
            case FB_8:
                _v.fb8 = *pValue;
                break;
            case P_FB_8:
                _v.pfb8 = pValue;
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(const ch_1 *pszValue) {
        assert(null_v != pszValue);

        if (INVALID == _type) {
            _type = STR;
            _len = (size_) (strlen(pszValue) + 1);
            _v.str = new ch_1[_len];
            memcpy(_v.str, pszValue, _len);
        } else {
            switch (_type) {
            case STR: {
                __del(_v.str);
                _len = (size_) (strlen(pszValue) + 1);
                _v.str = new ch_1[_len];
                memcpy(_v.str, pszValue, _len);
            }
                break;
            case P_STR: {
                memset(_v.pstr, 0, _len);
                strncpy(_v.pstr, pszValue, _len);
            }
                break;
            default:
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(const obj_ value) {
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
                assert(false_v);
                break;
            }
        }

        return *this;
    }

    const Variable &operator =(const Variable &value) {
        if (&value == this)
            return *this;

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
                memcpy(&_v, &value._v, sizeof(unit_value));
            }
        } else if (INVALID == value._type) {
            if (P_OBJ == _type || P_STR == _type) {
                assert(false_v);
            } else {
                clear();
            }
        } else if (POINTER_SIGN != (POINTER_SIGN & _type)
                && POINTER_SIGN != (POINTER_SIGN & value._type)) {
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

                __del(_v.str);
                _len = (size_) (strlen(psz) + 1);
                _v.str = new ch_1[_len];
                memcpy(_v.str, psz, _len);
            }
                break;
            case OBJ:
                _v.obj = (obj_) value;
                break;
            default:
                assert(false_v);
                break;
            }
        } else if (POINTER_SIGN != (POINTER_SIGN & _type)
                && POINTER_SIGN == (POINTER_SIGN & value._type)) {
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

                __del(_v.str);
                _len = (size_) (strlen(psz) + 1);
                _v.str = new ch_1[_len];
                memcpy(_v.str, psz, _len);
            }
                break;
            default:
                assert(false_v);
                break;
            }
        } else if (POINTER_SIGN == (POINTER_SIGN & _type)) {
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
                if (POINTER_SIGN == (POINTER_SIGN & value._type)
                        && _len == value._len && _type == value._type) {
                    memcpy(((ub_1 *) *_v.pobj) + _offset,
                            ((ub_1 *) *value._v.pobj) + value._offset, _len);
                } else {
                    assert(false_v);
                }
            }
                break;
            default:
                assert(false_v);
                break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
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
            assert(false_v);
            break;
        }
    }

    operator const ch_1 *() const {
        switch (_type) {
        case STR:
            return _v.str;
        case P_STR:
            return _v.pstr;
        default:
            assert(false_v);
            break;
        }
    }

    operator const obj_() const {
        switch (_type) {
        case OBJ:
            return _v.obj;
        default:
            assert(false_v);
            break;
        }
    }

    const size_ size() const {
        return _len;
    }

    none_ empty() {
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
                assert(false_v);
                break;
            }
            break;
        default:
            assert(false_v);
            break;
        }
    }

    none_ clear() {
        if (STR == _type) {
            __del(_v.str);
        } else {
            memset(&_v, 0, sizeof(unit_value));
        }

        _offset = 0;
        _len = 0;
        _type = INVALID;
    }

private:
    type_ _type;

    // Just valid as P_OBJ
    size_ _offset;

    // It's just valid when _type is P_STR or STR or OBJ.
    // Default value is 0, it's the string's _length + 1.
    size_ _len;

    union unit_value {
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

        fb_4 fb4;
        fb_8 fb8;

        fb_4 *pfb4;
        fb_8 *pfb8;

        ch_1 *str;
        ch_1 *pstr;

        obj_ obj;
        obj_ *pobj;
    } _v;

    friend const Variable operator -(const Variable &value);
    friend const Variable operator ~(const Variable &value);

    friend const b_4 operator !(const Variable &value);

    friend const Variable operator +(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator -(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator *(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator /(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator %(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator &(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator |(const Variable &leftValue,
            const Variable &rightValue);
    friend const Variable operator ^(const Variable &leftValue,
            const Variable &rightValue);

    friend const b_4 operator ==(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator !=(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator >(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator >=(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator <(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator <=(const Variable &leftValue,
            const Variable &rightValue);

    friend const b_4 operator &&(const Variable &leftValue,
            const Variable &rightValue);
    friend const b_4 operator ||(const Variable &leftValue,
            const Variable &rightValue);
};

typedef Variable v_;

#endif // VARIABLE_H_
