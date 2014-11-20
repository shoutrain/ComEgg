#include "CAutoVar.h"

const CAutoVar operator -(const CAutoVar &value) {
	switch (value._type) {
	case B_1:
		return CAutoVar((b_1) -value._v.b1);
	case B_2:
		return CAutoVar((b_2) -value._v.b2);
	case B_4:
		return CAutoVar((b_4) -value._v.b4);
	case B_8:
		return CAutoVar((b_8) -value._v.b8);
	case FB_4:
		return CAutoVar((fb_4) -value._v.fb4);
	case FB_8:
		return CAutoVar((fb_8) -value._v.fb8);
	case P_B_1:
		return CAutoVar((b_1) -(*value._v.pb1));
	case P_B_2:
		return CAutoVar((b_2) -(*value._v.pb2));
	case P_B_4:
		return CAutoVar((b_4) -(*value._v.pb4));
	case P_B_8:
		return CAutoVar((b_8) -(*value._v.pb8));
	case P_FB_4:
		return CAutoVar((fb_4) -(*value._v.pfb4));
	case P_FB_8:
		return CAutoVar((fb_8) -(*value._v.pfb8));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator ~(const CAutoVar &value) {
	switch (value._type) {
	case B_1:
		return CAutoVar(~value._v.b1);
	case UB_1:
		return CAutoVar(~value._v.ub1);
	case B_2:
		return CAutoVar(~value._v.b2);
	case UB_2:
		return CAutoVar(~value._v.ub2);
	case B_4:
		return CAutoVar(~value._v.b4);
	case UB_4:
		return CAutoVar(~value._v.ub4);
	case B_8:
		return CAutoVar(~value._v.b8);
	case UB_8:
		return CAutoVar(~value._v.ub8);
	case P_B_1:
		return CAutoVar(~(*value._v.pb1));
	case P_UB_1:
		return CAutoVar(~(*value._v.pub1));
	case P_B_2:
		return CAutoVar(~(*value._v.pb2));
	case P_UB_2:
		return CAutoVar(~(*value._v.pub2));
	case P_B_4:
		return CAutoVar(~(*value._v.pb4));
	case P_UB_4:
		return CAutoVar(~(*value._v.pub4));
	case P_B_8:
		return CAutoVar(~(*value._v.pb8));
	case P_UB_8:
		return CAutoVar(~(*value._v.pub8));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const b_4 operator !(const CAutoVar &value) {
	switch (value._type) {
	case B_1:
		return 0 == value._v.b1 ? true_v : false_v;
	case UB_1:
		return 0 == value._v.ub1 ? true_v : false_v;
	case B_2:
		return 0 == value._v.b2 ? true_v : false_v;
	case UB_2:
		return 0 == value._v.ub2 ? true_v : false_v;
	case B_4:
		return 0 == value._v.b4 ? true_v : false_v;
	case UB_4:
		return 0 == value._v.ub4 ? true_v : false_v;
	case B_8:
		return 0 == value._v.b8 ? true_v : false_v;
	case UB_8:
		return 0 == value._v.ub8 ? true_v : false_v;
	case FB_4:
		return 0 == value._v.fb4 ? true_v : false_v;
	case FB_8:
		return 0 == value._v.fb8 ? true_v : false_v;
	case STR:
		return 0 == strlen(value._v.str) ? true_v : false_v;
	case OBJ:
		return null_v == value._v.obj ? true_v : false_v;
	case P_B_1:
		return 0 == *value._v.pb1 ? true_v : false_v;
	case P_UB_1:
		return 0 == *value._v.pub1 ? true_v : false_v;
	case P_B_2:
		return 0 == *value._v.pb2 ? true_v : false_v;
	case P_UB_2:
		return 0 == *value._v.pub2 ? true_v : false_v;
	case P_B_4:
		return 0 == *value._v.pb4 ? true_v : false_v;
	case P_UB_4:
		return 0 == *value._v.pub4 ? true_v : false_v;
	case P_B_8:
		return 0 == *value._v.pb8 ? true_v : false_v;
	case P_UB_8:
		return 0 == *value._v.pub8 ? true_v : false_v;
	case P_FB_4:
		return 0 == *value._v.pfb4 ? true_v : false_v;
	case P_FB_8:
		return 0 == *value._v.pfb8 ? true_v : false_v;
	case P_STR:
		return null_v == strlen(value._v.pstr) ? true_v : false_v;
	case P_OBJ:
		return null_v == *value._v.pobj ? true_v : false_v;
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const CAutoVar operator +(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	if (OBJ == leftValue._type) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type;

	if (STR == _EVT(leftValue._type)) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) + ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) + ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) + ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) + ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) + ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) + ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) + ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) + ((ub_8) rightValue));
	case FB_4:
		return CAutoVar(((fb_4) leftValue) + ((fb_4) rightValue));
	case FB_8:
		return CAutoVar(((fb_8) leftValue) + ((fb_8) rightValue));
	case STR: {
		string str((const ch_1 *) leftValue);

		str += (const ch_1 *) rightValue;

		return CAutoVar(str);
	}
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator -(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	if (OBJ == leftValue._type || STR == _EVT(leftValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) - ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) - ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) - ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) - ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) - ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) - ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) - ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) - ((ub_8) rightValue));
	case FB_4:
		return CAutoVar(((fb_4) leftValue) - ((fb_4) rightValue));
	case FB_8:
		return CAutoVar(((fb_8) leftValue) - ((fb_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator *(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	if (OBJ == leftValue._type || STR == _EVT(leftValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) * ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) * ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) * ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) * ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) * ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) * ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) * ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) * ((ub_8) rightValue));
	case FB_4:
		return CAutoVar(((fb_4) leftValue) * ((fb_4) rightValue));
	case FB_8:
		return CAutoVar(((fb_8) leftValue) * ((fb_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

}

const CAutoVar operator /(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	if (OBJ == leftValue._type || STR == _EVT(leftValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) / ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) / ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) / ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) / ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) / ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) / ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) / ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) / ((ub_8) rightValue));
	case FB_4:
		return CAutoVar(((fb_4) leftValue) / ((fb_4) rightValue));
	case FB_8:
		return CAutoVar(((fb_8) leftValue) / ((fb_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator %(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (NORMAL_STYLE != _STYLE(leftValue._type)
			|| NORMAL_STYLE != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) % ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) % ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) % ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) % ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) % ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) % ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) % ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) % ((ub_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator &(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (NORMAL_STYLE != _STYLE(leftValue._type)
			|| NORMAL_STYLE != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) & ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) & ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) & ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) & ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) & ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) & ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) & ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) & ((ub_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator |(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (NORMAL_STYLE != _STYLE(leftValue._type)
			|| NORMAL_STYLE != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) | ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) | ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) | ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) | ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) | ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) | ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) | ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) | ((ub_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const CAutoVar operator ^(const CAutoVar &leftValue,
		const CAutoVar &rightValue) {
	if (NORMAL_STYLE != _STYLE(leftValue._type)
			|| NORMAL_STYLE != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}

	type_ type =
	_LEN(leftValue._type) >= _LEN(rightValue._type) ?
			leftValue._type : rightValue._type;

	switch (_EVT(type)) {
	case B_1:
		return CAutoVar(((b_1) leftValue) ^ ((b_1) rightValue));
	case UB_1:
		return CAutoVar(((ub_1) leftValue) ^ ((ub_1) rightValue));
	case B_2:
		return CAutoVar(((b_2) leftValue) ^ ((b_2) rightValue));
	case UB_2:
		return CAutoVar(((ub_2) leftValue) ^ ((ub_2) rightValue));
	case B_4:
		return CAutoVar(((b_4) leftValue) ^ ((b_4) rightValue));
	case UB_4:
		return CAutoVar(((ub_4) leftValue) ^ ((ub_4) rightValue));
	case B_8:
		return CAutoVar(((b_8) leftValue) ^ ((b_8) rightValue));
	case UB_8:
		return CAutoVar(((ub_8) leftValue) ^ ((ub_8) rightValue));
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return CAutoVar();
	}
}

const b_4 operator ==(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type) || OBJ == leftValue._type) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) == ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) == ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) == ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) == ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) == ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) == ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) == ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) == ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) == ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) == ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) == 0;
	case OBJ:
		return ((const obj_) leftValue) == ((const obj_) rightValue);
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator !=(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type) || OBJ == leftValue._type) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) != ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) != ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) != ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) != ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) != ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) != ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) != ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) != ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) != ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) != ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) != 0;
	case OBJ:
		return ((const obj_) leftValue) != ((const obj_) rightValue);
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator >(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	if (OBJ == leftValue._type) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type)) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) > ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) > ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) > ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) > ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) > ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) > ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) > ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) > ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) > ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) > ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) > 0;
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator >=(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	if (OBJ == leftValue._type) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type)) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) >= ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) >= ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) >= ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) >= ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) >= ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) >= ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) >= ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) >= ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) >= ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) >= ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) >= 0;
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator <(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	if (OBJ == leftValue._type) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type)) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) < ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) < ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) < ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) < ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) < ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) < ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) < ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) < ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) < ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) < ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) < 0;
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator <=(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	if (OBJ == leftValue._type) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type)) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) <= ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) <= ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) <= ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) <= ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) <= ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) <= ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) <= ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) <= ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) <= ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) <= ((fb_8) rightValue);
	case STR:
		return strcmp((const ch_1 *) leftValue, (const ch_1 *) rightValue) <= 0;
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator &&(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type) || OBJ == leftValue._type) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) && ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) && ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) && ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) && ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) && ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) && ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) && ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) && ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) && ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) && ((fb_8) rightValue);
	case STR:
		return strlen((const ch_1 *) leftValue)
				&& strlen((const ch_1 *) rightValue);
	case OBJ:
		return ((const obj_) leftValue) && ((const obj_) rightValue);
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}

const b_4 operator ||(const CAutoVar &leftValue, const CAutoVar &rightValue) {
	if (_STYLE(leftValue._type) != _STYLE(rightValue._type)) {
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}

	type_ type;

	if (STR == _EVT(leftValue._type) || OBJ == leftValue._type) {
		type = leftValue._type;
	} else {
		type = _LEN(leftValue._type) >= _LEN(rightValue._type) ?
				leftValue._type : rightValue._type;
	}

	switch (_EVT(type)) {
	case B_1:
		return ((b_1) leftValue) || ((b_1) rightValue);
	case UB_1:
		return ((ub_1) leftValue) || ((ub_1) rightValue);
	case B_2:
		return ((b_2) leftValue) || ((b_2) rightValue);
	case UB_2:
		return ((ub_2) leftValue) || ((ub_2) rightValue);
	case B_4:
		return ((b_4) leftValue) || ((b_4) rightValue);
	case UB_4:
		return ((ub_4) leftValue) || ((ub_4) rightValue);
	case B_8:
		return ((b_8) leftValue) || ((b_8) rightValue);
	case UB_8:
		return ((ub_8) leftValue) || ((ub_8) rightValue);
	case FB_4:
		return ((fb_4) leftValue) || ((fb_4) rightValue);
	case FB_8:
		return ((fb_8) leftValue) || ((fb_8) rightValue);
	case STR:
		return strlen((const ch_1 *) leftValue)
				|| strlen((const ch_1 *) rightValue);
	case OBJ:
		return ((const obj_) leftValue) || ((const obj_) rightValue);
	default:
		assert(0);
		logError("Invalid parameter in operator of CAutoVar");
		return 0;
	}
}
