#include "variable.h"

const variable operator -(const variable &value)
{
	switch (value.type)
	{
	case B_1:
		return variable((b_1)-value.v.b1);
	case B_2:
		return variable((b_2)value.v.b2);
	case B_4:
		return variable((b_4)-value.v.b4);
	case B_8:
		return variable((b_8)-value.v.b8);
	case FB_4:
		return variable((fb_4)-value.v.fb4);
	case FB_8:
		return variable((fb_8)-value.v.fb8);
	case P_B_1:
		return variable((b_1)-(*value.v.p_b1));
	case P_B_2:
		return variable((b_2)-(*value.v.p_b2));
	case P_B_4:
		return variable((b_4)-(*value.v.p_b4));
	case P_B_8:
		return variable((b_8)-(*value.v.p_b8));
	case P_FB_4:
		return variable((fb_4)-(*value.v.p_fb4));
	case P_FB_8:
		return variable((fb_8)-(*value.v.p_fb8));
	default:
		throw VARIABLE_OPERATION_ERROR;
	}
}

const variable operator ~(const variable &value)
{
	switch (value.type)
	{
	case B_1:
		return variable(~value.v.b1);
	case UB_1:
		return variable(~value.v.ub1);
	case B_2:
		return variable(~value.v.b2);
	case UB_2:
		return variable(~value.v.ub2);
	case B_4:
		return variable(~value.v.b4);
	case UB_4:
		return variable(~value.v.ub4);
	case B_8:
		return variable(~value.v.b8);
	case UB_8:
		return variable(~value.v.ub8);
	case P_B_1:
		return variable(~(*value.v.p_b1));
	case P_UB_1:
		return variable(~(*value.v.p_ub1));
	case P_B_2:
		return variable(~(*value.v.p_b2));
	case P_UB_2:
		return variable(~(*value.v.p_ub2));
	case P_B_4:
		return variable(~(*value.v.p_b4));
	case P_UB_4:
		return variable(~(*value.v.p_ub4));
	case P_B_8:
		return variable(~(*value.v.p_b8));
	case P_UB_8:
		return variable(~(*value.v.p_ub8));
	default:
		throw VARIABLE_OPERATION_ERROR;
	}
}

const b_4 operator !(const variable &value)
{
	switch (value.type)
	{
	case B_1:
		return 0 == value.v.b1 ? true_v : false_v;
	case UB_1:
		return 0 == value.v.ub1 ? true_v : false_v;
	case B_2:
		return 0 == value.v.b2 ? true_v : false_v;
	case UB_2:
		return 0 == value.v.ub2 ? true_v : false_v;
	case B_4:
		return 0 == value.v.b4 ? true_v : false_v;
	case UB_4:
		return 0 == value.v.ub4 ? true_v : false_v;
	case B_8:
		return 0 == value.v.b8 ? true_v : false_v;
	case UB_8:
		return 0 == value.v.ub8 ? true_v : false_v;
	case FB_4:
		return 0 == value.v.fb4 ? true_v : false_v;
	case FB_8:
		return 0 == value.v.fb8 ? true_v : false_v;
	case STR:
		return 0 == strlen(value.v.str) ? true_v : false_v;
	case OBJ:
		return null_v == value.v.obj ? true_v : false_v;
	case P_B_1:
		return 0 == *value.v.p_b1 ? true_v : false_v;
	case P_UB_1:
		return 0 == *value.v.p_ub1 ? true_v : false_v;
	case P_B_2:
		return 0 == *value.v.p_b2 ? true_v : false_v;
	case P_UB_2:
		return 0 == *value.v.p_ub2 ? true_v : false_v;
	case P_B_4:
		return 0 == *value.v.p_b4 ? true_v : false_v;
	case P_UB_4:
		return 0 == *value.v.p_ub4 ? true_v : false_v;
	case P_B_8:
		return 0 == *value.v.p_b8 ? true_v : false_v;
	case P_UB_8:
		return 0 == *value.v.p_ub8 ? true_v : false_v;
	case P_FB_4:
		return 0 == *value.v.p_fb4 ? true_v : false_v;
	case P_FB_8:
		return 0 == *value.v.p_fb8 ? true_v : false_v;
	case P_STR:
		return null_v == strlen(value.v.p_str) ? true_v : false_v;
	case P_OBJ:
		return null_v == *value.v.p_obj ? true_v : false_v;
	default:
		throw VARIABLE_OPERATION_ERROR;
	}
}

const variable operator +(const variable &left_value, 
						  const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type)
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type))
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	+ ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	+ ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	+ ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	+ ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	+ ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	+ ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	+ ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	+ ((ub_8)right_value));
		case FB_4:
			return variable(((fb_4)left_value)	+ ((fb_4)right_value));
		case FB_8:
			return variable(((fb_8)left_value)	+ ((fb_8)right_value));
		case STR:
			{
				string str((const ch_1 *)left_value);

				str += (const ch_1 *)right_value;

				return variable(str);
			}
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator -(const variable &left_value, 
						  const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type || STR == _EVT(left_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	- ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	- ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	- ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	- ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	- ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	- ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	- ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	- ((ub_8)right_value));
		case FB_4:
			return variable(((fb_4)left_value)	- ((fb_4)right_value));
		case FB_8:
			return variable(((fb_8)left_value)	- ((fb_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator *(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type || STR == _EVT(left_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	* ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	* ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	* ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	* ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	* ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	* ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	* ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	* ((ub_8)right_value));
		case FB_4:
			return variable(((fb_4)left_value)	* ((fb_4)right_value));
		case FB_8:
			return variable(((fb_8)left_value)	* ((fb_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator /(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type || STR == _EVT(left_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	/ ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	/ ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	/ ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	/ ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	/ ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	/ ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	/ ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	/ ((ub_8)right_value));
		case FB_4:
			return variable(((fb_4)left_value)	/ ((fb_4)right_value));
		case FB_8:
			return variable(((fb_8)left_value)	/ ((fb_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator %(const variable &left_value, const variable &right_value)
{
	if (NORMAL_STYLE != _STYLE(left_value.type) ||
		NORMAL_STYLE != _STYLE(right_value.type))
	{
		throw VARIABLE_OPERATION_ERROR;
	}

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	% ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	% ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	% ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	% ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	% ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	% ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	% ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	% ((ub_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator &(const variable &left_value, const variable &right_value)
{
	if (NORMAL_STYLE != _STYLE(left_value.type) ||
		NORMAL_STYLE != _STYLE(right_value.type))
	{
		throw VARIABLE_OPERATION_ERROR;
	}

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	& ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	& ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	& ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	& ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	& ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	& ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	& ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	& ((ub_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator |(const variable &left_value, const variable &right_value)
{
	if (NORMAL_STYLE != _STYLE(left_value.type) ||
		NORMAL_STYLE != _STYLE(right_value.type))
	{
		throw VARIABLE_OPERATION_ERROR;
	}

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	| ((b_1)right_value));
		case UB_1:
			return variable(((ub_1)left_value)	| ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	| ((b_2)right_value));
		case UB_2:
			return variable(((ub_2)left_value)	| ((ub_2)right_value));
		case B_4:
			return variable(((b_4)left_value)	| ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	| ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	| ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	| ((ub_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const variable operator ^(const variable &left_value, const variable &right_value)
{
	if (NORMAL_STYLE != _STYLE(left_value.type) ||
		NORMAL_STYLE != _STYLE(right_value.type))
	{
		throw VARIABLE_OPERATION_ERROR;
	}

	type_ type = _LEN(left_value.type) >= _LEN(right_value.type) 
		? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return variable(((b_1)left_value)	^ ((b_1)right_value));
		case UB_1:	
			return variable(((ub_1)left_value)	^ ((ub_1)right_value));
		case B_2:
			return variable(((b_2)left_value)	^ ((b_2)right_value));
		case UB_2:	
			return variable(((ub_2)left_value)	^ ((ub_2)right_value));
		case B_4:	
			return variable(((b_4)left_value)	^ ((b_4)right_value));
		case UB_4:
			return variable(((ub_4)left_value)	^ ((ub_4)right_value));
		case B_8:
			return variable(((b_8)left_value)	^ ((b_8)right_value));
		case UB_8:
			return variable(((ub_8)left_value)	^ ((ub_8)right_value));
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}


const b_4 operator ==(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type) || OBJ == left_value.type)
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)		== ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)		== ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)		== ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)		== ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)		== ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)		== ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)		== ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)		== ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)		== ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)		== ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) == 0;
		case OBJ:
			return ((const obj_)left_value)	== ((const obj_)right_value);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator !=(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type) || OBJ == left_value.type)
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	!= ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	!= ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	!= ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	!= ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	!= ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	!= ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	!= ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	!= ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	!= ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	!= ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) != 0;
		case OBJ:
			return ((const obj_)left_value) != ((const obj_)right_value);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator >(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type)
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type))
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	> ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	> ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	> ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	> ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	> ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	> ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	> ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	> ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	> ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	> ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) > 0;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator >=(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type)
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type))
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	>= ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	>= ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	>= ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	>= ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	>= ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	>= ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	>= ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	>= ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	>= ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	>= ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) >= 0;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator <(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type)
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type))
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	< ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	< ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	< ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	< ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	< ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	< ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	< ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	< ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	< ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	< ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) < 0;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator <=(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	if (OBJ == left_value.type)
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type))
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	<= ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	<= ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	<= ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	<= ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	<= ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	<= ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	<= ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	<= ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	<= ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	<= ((fb_8)right_value);
		case STR:
			return strcmp((const ch_1 *)left_value,
						  (const ch_1 *)right_value) <= 0;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}


const b_4 operator &&(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type) || OBJ == left_value.type)
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)	&& ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)	&& ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)	&& ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)	&& ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)	&& ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)	&& ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)	&& ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)	&& ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)	&& ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)	&& ((fb_8)right_value);
		case STR:
			return strlen((const ch_1 *)left_value) 
				&& strlen((const ch_1 *)right_value);
		case OBJ:
			return ((const obj_)left_value) && ((const obj_)right_value);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}

const b_4 operator ||(const variable &left_value, const variable &right_value)
{
	if (_STYLE(left_value.type) != _STYLE(right_value.type))
		throw VARIABLE_OPERATION_ERROR;

	type_ type;
	
	if (STR == _EVT(left_value.type) || OBJ == left_value.type)
		type = left_value.type;
	else
		type = _LEN(left_value.type) >= _LEN(right_value.type) 
			? left_value.type : right_value.type;

	try
	{
		switch (_EVT(type))
		{
		case B_1:
			return ((b_1)left_value)				|| ((b_1)right_value);
		case UB_1:
			return ((ub_1)left_value)				|| ((ub_1)right_value);
		case B_2:
			return ((b_2)left_value)				|| ((b_2)right_value);
		case UB_2:
			return ((ub_2)left_value)				|| ((ub_2)right_value);
		case B_4:
			return ((b_4)left_value)				|| ((b_4)right_value);
		case UB_4:
			return ((ub_4)left_value)				|| ((ub_4)right_value);
		case B_8:
			return ((b_8)left_value)				|| ((b_8)right_value);
		case UB_8:
			return ((ub_8)left_value)				|| ((ub_8)right_value);
		case FB_4:
			return ((fb_4)left_value)				|| ((fb_4)right_value);
		case FB_8:
			return ((fb_8)left_value)				|| ((fb_8)right_value);
		case STR:
			return strlen((const ch_1 *)left_value)	
				|| strlen((const ch_1 *)right_value);
		case OBJ:
			return ((const obj_)left_value)			|| ((const obj_)right_value);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
	catch (...)
	{
		throw;
	}
}
