#ifndef VARIABLE_H
#define VARIABLE_H

#include "BaseType.h"
#include "ErrorCode.h"

#include <string.h>

#include <string>

using namespace std;

class variable
{
public:
	// Default constructor.
	variable()
	{
		memset(&v, 0, sizeof(unit_value));
		offset = 0;
		len = 0;
		type = INVALID;
	}

	~variable()
	{
		clear();
	}

	variable(const variable &value)
	{
		type = value.type;

		if (STR == type && value.v.str)
		{
			len = (size_)(strlen(value.v.str) + 1);
			v.str = new ch_1[len];
			memcpy(v.str, value.v.str, len);
			offset = 0;
		}
		else
		{
			offset = value.offset;
			len = value.len;
			memcpy(&v, &value.v, sizeof(unit_value));
		}
	}

	// NORMAL_STYLE
	explicit variable(b_1 value)
	{
		type = B_1;
		v.b1 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(ub_1 value)
	{
		type = UB_1;
		v.ub1 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(b_2 value)
	{
		type = B_2;
		v.b2 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(ub_2 value)
	{
		type = UB_2;
		v.ub2 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(b_4 value)
	{
		type = B_4;
		v.b4 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(ub_4 value)
	{
		type = UB_4;
		v.ub4 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(b_8 value)
	{
		type = B_8;
		v.b8 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(ub_8 value)
	{
		type = UB_8;
		v.ub8 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(const b_1 *p_value)
	{
		if (p_value)
		{
			type = P_B_1;
			v.p_b1 = (b_1 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const ub_1 *p_value)
	{
		if (p_value)
		{
			type = P_UB_1;
			v.p_ub1 = (ub_1 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const b_2 *p_value)
	{
		if (p_value)
		{
			type = P_B_2;
			v.p_b2 = (b_2 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const ub_2 *p_value)
	{
		if (p_value)
		{
			type = P_UB_2;
			v.p_ub2 = (ub_2 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const b_4 *p_value)
	{
		if (p_value)
		{
			type = P_B_4;
			v.p_b4 = (b_4 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const ub_4 *p_value)
	{
		if (p_value)
		{
			type = P_UB_4;
			v.p_ub4 = (ub_4 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const b_8 *p_value)
	{
		if (p_value)
		{
			type = P_B_8;
			v.p_b8 = (b_8 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const ub_8 *p_value)
	{
		if (p_value)
		{
			type = P_UB_8;
			v.p_ub8 = (ub_8 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	// FLOAT_STYLE
	explicit variable(fb_4 value)
	{
		type = FB_4;
		v.fb4 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(fb_8 value)
	{
		type = FB_8;
		v.fb8 = value;
		len = 0;
		offset = 0;
	}

	explicit variable(const fb_4 *p_value)
	{
		if (p_value)
		{
			type = P_FB_4;
			v.p_fb4 = (fb_4 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	explicit variable(const fb_8 *p_value)
	{
		if (p_value)
		{
			type = P_FB_8;
			v.p_fb8 = (fb_8 *)p_value;
			len = 0;
			offset = 0;
		}
		else
		{
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	// STRING_STYLE
	explicit variable(const ch_1 *psz_value, const size_ n)
	{
		if (!psz_value)
			throw VARIABLE_OPERATION_ERROR;

		if (0 == n)
		{
			type = STR;
			len = (size_)(strlen(psz_value) + 1);
			v.str = new ch_1[len];
			memcpy(v.str, psz_value, len);
			offset = 0;
		}
		else
		{
			type = P_STR;
			v.p_str = (ch_1 *)psz_value;
			len = n;
			offset = 0;
		}
	}

	explicit variable(const string &value)
	{
		if (value.empty())
			throw VARIABLE_OPERATION_ERROR;

		type = STR;
		len = (size_)(value.length() + 1);
		v.str = new ch_1[len];
		memcpy(v.str, value.data(), len);
		offset = 0;
	}

	// OBJECT_STYLE
	explicit variable(const obj_ value)
	{
		type = OBJ;
		v.obj = value;
		len = 0;
		offset = 0;
	}

	explicit variable(obj_ *p_value, size_ n_offset, size_ n = 0)
	{
		offset = n_offset;
		len = n;
		type = P_OBJ;
		v.p_obj = p_value;
	}

	evt_ get_type() const
	{
		return  _EVT(type);
	}

	const variable &operator =(b_1 value)
	{
		if (INVALID == type)
		{
			type = B_1;
			v.b1 = value;
		}
		else
		{
			switch (type)
			{
			case B_1:
				v.b1 = value;
				break;
			case P_B_1:
				*v.p_b1 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_1 value)
	{
		if (INVALID == type)
		{
			type = UB_1;
			v.ub1 = value;
		}
		else
		{
			switch (type)
			{
			case UB_1:
				v.ub1 = value;
				break;
			case P_UB_1:
				*v.p_ub1 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_2 value)
	{
		if (INVALID == type)
		{
			type = B_2;
			v.b2 = value;
		}
		else
		{
			switch (type)
			{
			case B_2:
				v.b2 = value;
				break;
			case P_B_2:
				*v.p_b2 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_2 value)
	{
		if (INVALID == type)
		{
			type = UB_2;
			v.ub2 = value;
		}
		else
		{
			switch (type)
			{
			case UB_2:
				v.ub2 = value;
				break;
			case P_UB_2:
				*v.p_ub2 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_4 value)
	{
		if (INVALID == type)
		{
			type = B_4;
			v.b4 = value;
		}
		else
		{
			switch (type)
			{
			case B_4:
				v.b4 = value;
				break;
			case P_B_4:
				*v.p_b4 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_4 value)
	{
		if (INVALID == type)
		{
			type = UB_4;
			v.ub4 = value;
		}
		else
		{
			switch (type)
			{
			case UB_4:
				v.ub4 = value;
				break;
			case P_UB_4:
				*v.p_ub4 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_8 value)
	{
		if (INVALID == type)
		{
			type = B_8;
			v.b8 = value;
		}
		else
		{
			switch (type)
			{
			case B_8:
				v.b8 = value;
				break;
			case P_B_8:
				*v.p_b8 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_8 value)
	{
		if (INVALID == type)
		{
			type = UB_8;
			v.ub8 = value;
		}
		else
		{
			switch (type)
			{
			case UB_8:
				v.ub8 = value;
				break;
			case P_UB_8:
				*v.p_ub8 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(fb_4 value)
	{
		if (INVALID == type)
		{
			type = FB_4;
			v.fb4 = value;
		}
		else
		{
			switch (type)
			{
			case FB_4:
				v.fb4 = value;
				break;
			case P_FB_4:
				*v.p_fb4 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(fb_8 value)
	{
		if (INVALID == type)
		{
			type = FB_8;
			v.fb8 = value;
		}
		else
		{
			switch (type)
			{
			case FB_8:
				v.fb8 = value;
				break;
			case P_FB_8:
				*v.p_fb8 = value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_1 *p_value)
	{
		if (INVALID == type)
		{
			type = P_B_1;
			v.p_b1 = p_value;
		}
		else
		{
			switch (type)
			{
			case B_1:
				v.b1 = *p_value;
				break;
			case P_B_1:
				v.p_b1 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_1 *p_value)
	{
		if (INVALID == type)
		{
			type = P_UB_1;
			v.p_ub1 = p_value;
		}
		else
		{
			switch (type)
			{
			case UB_1:
				v.ub1 = *p_value;
				break;
			case P_UB_1:
				v.p_ub1 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_2 *p_value)
	{
		if (INVALID == type)
		{
			type = P_B_2;
			v.p_b2 = p_value;
		}
		else
		{
			switch (type)
			{
			case B_2:
				v.b2 = *p_value;
				break;
			case P_B_2:
				v.p_b2 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_2 *p_value)
	{
		if (INVALID == type)
		{
			type = P_UB_2;
			v.p_ub2 = p_value;
		}
		else
		{
			switch (type)
			{
			case UB_2:
				v.ub2 = *p_value;
				break;
			case P_UB_2:
				v.p_ub2 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_4 *p_value)
	{
		if (INVALID == type)
		{
			type = P_B_4;
			v.p_b4 = p_value;
		}
		else
		{
			switch (type)
			{
			case B_4:
				v.b4 = *p_value;
				break;
			case P_B_4:
				v.p_b4 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_4 *p_value)
	{
		if (INVALID == type)
		{
			type = P_UB_4;
			v.p_ub4 = p_value;
		}
		else
		{
			switch (type)
			{
			case UB_4:
				v.ub4 = *p_value;
				break;
			case P_UB_4:
				v.p_ub4 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(b_8 *p_value)
	{
		if (INVALID == type)
		{
			type = P_B_8;
			v.p_b8 = p_value;
		}
		else
		{
			switch (type)
			{
			case B_8:
				v.b8 = *p_value;
				break;
			case P_B_8:
				v.p_b8 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(ub_8 *p_value)
	{
		if (INVALID == type)
		{
			type = P_B_8;
			v.p_ub8 = p_value;
		}
		else
		{
			switch (type)
			{
			case UB_8:
				v.ub8 = *p_value;
				break;
			case P_UB_8:
				v.p_ub8 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(fb_4 *p_value)
	{
		if (INVALID == type)
		{
			type = P_FB_4;
			v.p_fb4 = p_value;
		}
		else
		{
			switch (type)
			{
			case FB_4:
				v.fb4 = *p_value;
				break;
			case P_FB_4:
				v.p_fb4 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(fb_8 *p_value)
	{
		if (INVALID == type)
		{
			type = P_FB_8;
			v.p_fb8 = p_value;
		}
		else
		{
			switch (type)
			{
			case FB_8:
				v.fb8 = *p_value;
				break;
			case P_FB_8:
				v.p_fb8 = p_value;
				break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(const ch_1 *psz_value)
	{
		if (!psz_value)
			throw VARIABLE_OPERATION_ERROR;

		if (INVALID == type)
		{
			type = STR;
			len = (size_)(strlen(psz_value) + 1);
			v.str = new ch_1[len];
			memcpy(v.str, psz_value, len);
		}
		else
		{
			switch (type)
			{
			case STR:
			{
				_DEL_ARR(v.str);
				len = (size_)(strlen(psz_value) + 1);
				v.str = new ch_1[len];
				memcpy(v.str, psz_value, len);
			}
			break;
			case P_STR:
			{
				memset(v.p_str, 0, len);
				strncpy(v.p_str, psz_value, len);
			}
			break;
			default:
				throw VARIABLE_OPERATION_ERROR;
			}
		}

		return *this;
	}

	const variable &operator =(const obj_ value)
	{
		if (INVALID == type)
		{
			type = OBJ;
			v.obj = value;
			len = 0;
		}
		else
		{
			try
			{
				switch (type)
				{
				case OBJ:
					v.obj = value;
					break;
				default:
					throw VARIABLE_OPERATION_ERROR;
				}
			}
			catch (...)
			{
				throw;
			}
		}

		return *this;
	}

	const variable &operator =(const variable &value)
	{
		if (&value == this)
			return *this;

		if (INVALID == type)
		{
			type = value.type;

			if (STR == type)
			{
				const ch_1 *psz = (const ch_1 *)value;

				len = (size_)(strlen(psz) + 1);
				v.str = new ch_1[len];
				memcpy(v.str, psz, len);
			}
			else
			{
				offset = value.offset;
				len = value.len;
				memcpy(&v, &value.v, sizeof(unit_value));
			}
		}
		else if (INVALID == value.type)
		{
			if (P_OBJ == type || P_STR == type)
				throw VARIABLE_OPERATION_ERROR;
			else
				clear();
		}
		else if (REFERENCE_VARIABLE != (REFERENCE_VARIABLE & type) &&
				 REFERENCE_VARIABLE != (REFERENCE_VARIABLE & value.type))
		{
			try
			{
				switch (type)
				{
				case B_1:
					v.b1 = (b_1)value;
					break;
				case UB_1:
					v.ub1 = (ub_1)value;
					break;
				case B_2:
					v.b2 = (b_2)value;
					break;
				case UB_2:
					v.ub2 = (ub_2)value;
					break;
				case B_4:
					v.b4 = (b_4)value;
					break;
				case UB_4:
					v.ub4 = (ub_4)value;
					break;
				case B_8:
					v.b8 = (b_8)value;
					break;
				case UB_8:
					v.ub8 = (ub_8)value;
					break;
				case FB_4:
					v.fb4 = (fb_4)value;
					break;
				case FB_8:
					v.fb8 = (fb_8)value;
					break;
				case STR:
				{
					const ch_1 *psz = (const ch_1 *)value;

					_DEL_ARR(v.str);
					len = (size_)(strlen(psz) + 1);
					v.str = new ch_1[len];
					memcpy(v.str, psz, len);
				}
				break;
				case OBJ:
					v.obj = (obj_)value;
					break;
				default:
					throw VARIABLE_OPERATION_ERROR;
				}
			}
			catch (...)
			{
				throw;
			}
		}
		else if (REFERENCE_VARIABLE != (REFERENCE_VARIABLE & type) &&
				 REFERENCE_VARIABLE == (REFERENCE_VARIABLE & value.type))
		{
			try
			{
				switch (type)
				{
				case B_1:
					v.b1 = (b_1)value;
					break;
				case UB_1:
					v.ub1 = (ub_1)value;
					break;
				case B_2:
					v.b2 = (b_2)value;
					break;
				case UB_2:
					v.ub2 = (ub_2)value;
					break;
				case B_4:
					v.b4 = (b_4)value;
					break;
				case UB_4:
					v.ub4 = (ub_4)value;
					break;
				case B_8:
					v.b8 = (b_8)value;
					break;
				case UB_8:
					v.ub8 = (ub_8)value;
					break;
				case FB_4:
					v.fb4 = (fb_4)value;
					break;
				case FB_8:
					v.fb8 = (fb_8)value;
					break;
				case STR:
				{
					const ch_1 *psz = (const ch_1 *)value;

					_DEL_ARR(v.str);
					len = (size_)(strlen(psz) + 1);
					v.str = new ch_1[len];
					memcpy(v.str, psz, len);
				}
				break;
				default:
					throw VARIABLE_OPERATION_ERROR;
				}
			}
			catch (...)
			{
				throw;
			}
		}
		else if (REFERENCE_VARIABLE == (REFERENCE_VARIABLE & type))
		{
			try
			{
				switch (type)
				{
				case P_B_1:
					*v.p_b1 = (b_1)value;
					break;
				case P_UB_1:
					*v.p_ub1 = (ub_1)value;
					break;
				case P_B_2:
					*v.p_b2 = (b_2)value;
					break;
				case P_UB_2:
					*v.p_ub2 = (ub_2)value;
					break;
				case P_B_4:
					*v.p_b4 = (b_4)value;
					break;
				case P_UB_4:
					*v.p_ub4 = (ub_4)value;
					break;
				case P_B_8:
					*v.p_b8 = (b_8)value;
					break;
				case P_UB_8:
					*v.p_ub8 = (ub_8)value;
					break;
				case P_FB_4:
					*v.p_fb4 = (fb_4)value;
					break;
				case P_FB_8:
					*v.p_fb8 = (fb_8)value;
					break;
				case P_STR:
				{
					const ch_1 *psz = (const ch_1 *)value;

					memset(v.p_str, 0, len);
					strncpy(v.p_str, psz, len);
				}
				break;
				case P_OBJ:
				{
					if (REFERENCE_VARIABLE == (REFERENCE_VARIABLE & value.type)
						&& len == value.len 
						&& type == value.type)
					{
						memcpy(((ub_1 *)*v.p_obj) + offset, 
							   ((ub_1 *)*value.v.p_obj) + value.offset, 
							   len);
					}
					else
					{
						throw VARIABLE_OPERATION_ERROR;
					}
				}
				break;
				default:
					throw VARIABLE_OPERATION_ERROR;
				}
			}
			catch (...)
			{
				throw;
			}
		}

		return *this;
	}

	operator b_1() const
	{
		switch (type)
		{
		case B_1:
			return (b_1)v.b1;
		case UB_1:
			return (b_1)v.ub1;
		case B_2:
			return (b_1)v.b2;
		case UB_2:
			return (b_1)v.ub2;
		case B_4:
			return (b_1)v.b4;
		case UB_4:
			return (b_1)v.ub4;
		case B_8:
			return (b_1)v.b8;
		case UB_8:
			return (b_1)v.ub8;
		case FB_4:
			return (b_1)v.fb4;
		case FB_8:
			return (b_1)v.fb8;
		case P_B_1:
			return (b_1)(*v.p_b1);
		case P_UB_1:
			return (b_1)(*v.p_ub1);
		case P_B_2:
			return (b_1)(*v.p_b2);
		case P_UB_2:
			return (b_1)(*v.p_ub2);
		case P_B_4:
			return (b_1)(*v.p_b4);
		case P_UB_4:
			return (b_1)(*v.p_ub4);
		case P_B_8:
			return (b_1)(*v.p_b8);
		case P_UB_8:
			return (b_1)(*v.p_ub8);
		case P_FB_4:
			return (b_1)(*v.p_fb4);
		case P_FB_8:
			return (b_1)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator ub_1() const
	{
		switch (type)
		{
		case B_1:
			return (ub_1)v.b1;
		case UB_1:
			return (ub_1)v.ub1;
		case B_2:
			return (ub_1)v.b2;
		case UB_2:
			return (ub_1)v.ub2;
		case B_4:
			return (ub_1)v.b4;
		case UB_4:
			return (ub_1)v.ub4;
		case B_8:
			return (ub_1)v.b8;
		case UB_8:
			return (ub_1)v.ub8;
		case FB_4:
			return (ub_1)v.fb4;
		case FB_8:
			return (ub_1)v.fb8;
		case P_B_1:
			return (ub_1)(*v.p_b1);
		case P_UB_1:
			return (ub_1)(*v.p_ub1);
		case P_B_2:
			return (ub_1)(*v.p_b2);
		case P_UB_2:
			return (ub_1)(*v.p_ub2);
		case P_B_4:
			return (ub_1)(*v.p_b4);
		case P_UB_4:
			return (ub_1)(*v.p_ub4);
		case P_B_8:
			return (ub_1)(*v.p_b8);
		case P_UB_8:
			return (ub_1)(*v.p_ub8);
		case P_FB_4:
 			return (ub_1)(*v.p_fb4);
		case P_FB_8:
			return (ub_1)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator b_2() const
	{
		switch (type)
		{
		case B_1:
			return (b_2)v.b1;
		case UB_1:
			return (b_2)v.ub1;
		case B_2:
			return (b_2)v.b2;
		case UB_2:
			return (b_2)v.ub2;
		case B_4:
			return (b_2)v.b4;
		case UB_4:
			return (b_2)v.ub4;
		case B_8:
			return (b_2)v.b8;
		case UB_8:
			return (b_2)v.ub8;
		case FB_4:
			return (b_2)v.fb4;
		case FB_8:
			return (b_2)v.fb8;
		case P_B_1:
			return (b_2)(*v.p_b1);
		case P_UB_1:
			return (b_2)(*v.p_ub1);
		case P_B_2:
			return (b_2)(*v.p_b2);
		case P_UB_2:
			return (b_2)(*v.p_ub2);
		case P_B_4:
			return (b_2)(*v.p_b4);
		case P_UB_4:
			return (b_2)(*v.p_ub4);
		case P_B_8:
			return (b_2)(*v.p_b8);
		case P_UB_8:
			return (b_2)(*v.p_ub8);
		case P_FB_4:
			return (b_2)(*v.p_fb4);
		case P_FB_8:
			return (b_2)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator ub_2() const
	{
		switch (type)
		{
		case B_1:
			return (ub_2)v.b1;
		case UB_1:
			return (ub_2)v.ub1;
		case B_2:
			return (ub_2)v.b2;
		case UB_2:
			return (ub_2)v.ub2;
		case B_4:
			return (ub_2)v.b4;
		case UB_4:
			return (ub_2)v.ub4;
		case B_8:
			return (ub_2)v.b8;
		case UB_8:
			return (ub_2)v.ub8;
		case FB_4:
			return (ub_2)v.fb4;
		case FB_8:
			return (ub_2)v.fb8;
		case P_B_1:
			return (ub_2)(*v.p_b1);
		case P_UB_1:
			return (ub_2)(*v.p_ub1);
		case P_B_2:
			return (ub_2)(*v.p_b2);
		case P_UB_2:
			return (ub_2)(*v.p_ub2);
		case P_B_4:
			return (ub_2)(*v.p_b4);
		case P_UB_4:
			return (ub_2)(*v.p_ub4);
		case P_B_8:
			return (ub_2)(*v.p_b8);
		case P_UB_8:
			return (ub_2)(*v.p_ub8);
		case P_FB_4:
			return (ub_2)(*v.p_fb4);
		case P_FB_8:
			return (ub_2)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator b_4() const
	{
		switch (type)
		{
		case B_1:
			return (b_4)v.b1;
		case UB_1:
			return (b_4)v.ub1;
		case B_2:
			return (b_4)v.b2;
		case UB_2:
			return (b_4)v.ub2;
		case B_4:
			return (b_4)v.b4;
		case UB_4:
			return (b_4)v.ub4;
		case B_8:
			return (b_4)v.b8;
		case UB_8:
			return (b_4)v.ub8;
		case FB_4:
			return (b_4)v.fb4;
		case FB_8:
			return (b_4)v.fb8;
		case P_B_1:
			return (b_4)(*v.p_b1);
		case P_UB_1:
			return (b_4)(*v.p_ub1);
		case P_B_2:
			return (b_4)(*v.p_b2);
		case P_UB_2:
			return (b_4)(*v.p_ub2);
		case P_B_4:
			return (b_4)(*v.p_b4);
		case P_UB_4:
			return (b_4)(*v.p_ub4);
		case P_B_8:
			return (b_4)(*v.p_b8);
		case P_UB_8:
			return (b_4)(*v.p_ub8);
		case P_FB_4:
			return (b_4)(*v.p_fb4);
		case P_FB_8:
			return (b_4)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator ub_4() const
	{
		switch (type)
		{
		case B_1:
			return (ub_4)v.b1;
		case UB_1:
			return (ub_4)v.ub1;
		case B_2:
			return (ub_4)v.b2;
		case UB_2:
			return (ub_4)v.ub2;
		case B_4:
			return (ub_4)v.b4;
		case UB_4:
			return (ub_4)v.ub4;
		case B_8:
			return (ub_4)v.b8;
		case UB_8:
			return (ub_4)v.ub8;
		case FB_4:
			return (ub_4)v.fb4;
		case FB_8:
			return (ub_4)v.fb8;
		case P_B_1:
			return (ub_4)(*v.p_b1);
		case P_UB_1:
			return (ub_4)(*v.p_ub1);
		case P_B_2:
			return (ub_4)(*v.p_b2);
		case P_UB_2:
			return (ub_4)(*v.p_ub2);
		case P_B_4:
			return (ub_4)(*v.p_b4);
		case P_UB_4:
			return (ub_4)(*v.p_ub4);
		case P_B_8:
			return (ub_4)(*v.p_b8);
		case P_UB_8:
			return (ub_4)(*v.p_ub8);
		case P_FB_4:
			return (ub_4)(*v.p_fb4);
		case P_FB_8:
			return (ub_4)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator b_8() const
	{
		switch (type)
		{
		case B_1:
			return (b_8)v.b1;
		case UB_1:
			return (b_8)v.ub1;
		case B_2:
			return (b_8)v.b2;
		case UB_2:
			return (b_8)v.ub2;
		case B_4:
			return (b_8)v.b4;
		case UB_4:
			return (b_8)v.ub4;
		case B_8:
			return (b_8)v.b8;
		case UB_8:
			return (b_8)v.ub8;
		case FB_4:
			return (b_8)v.fb4;
		case FB_8:
			return (b_8)v.fb8;
		case P_B_1:
			return (b_8)(*v.p_b1);
		case P_UB_1:
			return (b_8)(*v.p_ub1);
		case P_B_2:
			return (b_8)(*v.p_b2);
		case P_UB_2:
			return (b_8)(*v.p_ub2);
		case P_B_4:
			return (b_8)(*v.p_b4);
		case P_UB_4:
			return (b_8)(*v.p_ub4);
		case P_B_8:
			return (b_8)(*v.p_b8);
		case P_UB_8:
			return (b_8)(*v.p_ub8);
		case P_FB_4:
			return (b_8)(*v.p_fb4);
		case P_FB_8:
			return (b_8)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator ub_8() const
	{
		switch (type)
		{
		case B_1:
			return (ub_8)v.b1;
		case UB_1:
			return (ub_8)v.ub1;
		case B_2:
			return (ub_8)v.b2;
		case UB_2:
			return (ub_8)v.ub2;
		case B_4:
			return (ub_8)v.b4;
		case UB_4:
			return (ub_8)v.ub4;
		case B_8:
			return (ub_8)v.b8;
		case UB_8:
			return (ub_8)v.ub8;
		case FB_4:
			return (ub_8)v.fb4;
		case FB_8:
			return (ub_8)v.fb8;
		case P_B_1:
			return (ub_8)(*v.p_b1);
		case P_UB_1:
			return (ub_8)(*v.p_ub1);
		case P_B_2:
			return (ub_8)(*v.p_b2);
		case P_UB_2:
			return (ub_8)(*v.p_ub2);
		case P_B_4:
			return (ub_8)(*v.p_b4);
		case P_UB_4:
			return (ub_8)(*v.p_ub4);
		case P_B_8:
			return (ub_8)(*v.p_b8);
		case P_UB_8:
			return (ub_8)(*v.p_ub8);
		case P_FB_4:
			return (ub_8)(*v.p_fb4);
		case P_FB_8:
			return (ub_8)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator fb_4() const
	{
		switch (type)
		{
		case B_1:
			return (fb_4)v.b1;
		case UB_1:
			return (fb_4)v.ub1;
		case B_2:
			return (fb_4)v.b2;
		case UB_2:
			return (fb_4)v.ub2;
		case B_4:
			return (fb_4)v.b4;
		case UB_4:
			return (fb_4)v.ub4;
		case B_8:
			return (fb_4)v.b8;
		case UB_8:
			return (fb_4)v.ub8;
		case FB_4:
			return (fb_4)v.fb4;
		case FB_8:
			return (fb_4)v.fb8;
		case P_B_1:
			return (fb_4)(*v.p_b1);
		case P_UB_1:
			return (fb_4)(*v.p_ub1);
		case P_B_2:
			return (fb_4)(*v.p_b2);
		case P_UB_2:
			return (fb_4)(*v.p_ub2);
		case P_B_4:
			return (fb_4)(*v.p_b4);
		case P_UB_4:
			return (fb_4)(*v.p_ub4);
		case P_B_8:
			return (fb_4)(*v.p_b8);
		case P_UB_8:
			return (fb_4)(*v.p_ub8);
		case P_FB_4:
			return (fb_4)(*v.p_fb4);
		case P_FB_8:
			return (fb_4)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator fb_8() const
	{
		switch (type)
		{
		case B_1:
			return (fb_8)v.b1;
		case UB_1:
			return (fb_8)v.ub1;
		case B_2:
			return (fb_8)v.b2;
		case UB_2:
			return (fb_8)v.ub2;
		case B_4:
			return (fb_8)v.b4;
		case UB_4:
			return (fb_8)v.ub4;
		case B_8:
			return (fb_8)v.b8;
		case UB_8:
			return (fb_8)v.ub8;
		case FB_4:
			return (fb_8)v.fb4;
		case FB_8:
			return (fb_8)v.fb8;
		case P_B_1:
			return (fb_8)(*v.p_b1);
		case P_UB_1:
			return (fb_8)(*v.p_ub1);
		case P_B_2:
			return (fb_8)(*v.p_b2);
		case P_UB_2:
			return (fb_8)(*v.p_ub2);
		case P_B_4:
			return (fb_8)(*v.p_b4);
		case P_UB_4:
			return (fb_8)(*v.p_ub4);
		case P_B_8:
			return (fb_8)(*v.p_b8);
		case P_UB_8:
			return (fb_8)(*v.p_ub8);
		case P_FB_4:
			return (fb_8)(*v.p_fb4);
		case P_FB_8:
			return (fb_8)(*v.p_fb8);
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator const ch_1 *() const
	{
		switch (type)
		{
		case STR:
			return v.str;
		case P_STR:
			return v.p_str;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	operator const obj_() const
	{
		switch (type)
		{
		case OBJ:
			return v.obj;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
/*
	operator const obj_ *() const
	{
		switch (type)
		{
		case P_OBJ:
			return v.p_obj;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}
*/
	const size_ size() const
	{
		return len;
	}

	void empty()
	{
		switch (type)
		{
		case B_1:
			v.b1 = 0;
			break;
		case UB_1:
			v.ub1 = 0;
			break;
		case B_2:
			v.b2 = 0;
			break;
		case UB_2:
			v.ub2 = 0;
			break;
		case B_4:
			v.b4 = 0;
			break;
		case UB_4:
			v.ub4 = 0;
			break;
		case B_8:
			v.b8 = 0;
			break;
		case UB_8:
			v.ub8 = 0;
			break;
		case FB_4:
			v.fb4 = 0;
			break;
		case FB_8:
			v.fb8 = 0;
			break;
		case P_B_1:
			(*v.p_b1) = 0;
			break;
		case P_UB_1:
			(*v.p_ub1) = 0;
			break;
		case P_B_2:
			(*v.p_b2) = 0;
			break;
		case P_UB_2:
			(*v.p_ub2) = 0;
			break;
		case P_B_4:
			(*v.p_b4) = 0;
			break;
		case P_UB_4:
			(*v.p_ub4) = 0;
			break;
		case P_B_8:
			(*v.p_b8) = 0;
			break;
		case P_UB_8:
			(*v.p_ub8) = 0;
			break;
		case P_FB_4:
			(*v.p_fb4) = 0;
			break;
		case P_FB_8:
			(*v.p_fb8) = 0;
			break;
		case STR:
			memset(v.str, 0, len);
			break;
		case P_STR:
			memset(v.p_str, 0, len);
			break;
		case OBJ:
			v.obj = null_v;
			break;
		case P_OBJ:
			if (v.p_obj && len)
				memset(((ub_1 *)*v.p_obj) + offset, 0, len);
			else
				throw VARIABLE_OPERATION_ERROR;

			break;
		default:
			throw VARIABLE_OPERATION_ERROR;
		}
	}

	void clear()
	{
		if (STR == type)
		{
			_DEL_ARR(v.str);
		}
		else
		{
			memset(&v, 0, sizeof(unit_value));
		}

		offset = 0;
		len = 0;
		type = INVALID;
	}

private:
	type_ type;

	// Just valid as P_OBJ
	size_ offset;

	// It's just valid when type is P_STR or STR or OBJ.
	// Default value is 0, it's the string's length + 1.
	size_ len;

	union unit_value
	{
		// NORMAL_STYLE
		b_1		*p_b1;
		ub_1	*p_ub1;
		b_2		*p_b2;
		ub_2	*p_ub2;
		b_4		*p_b4;
		ub_4	*p_ub4;
		b_8		*p_b8;
		ub_8	*p_ub8;

		b_1		b1;
		ub_1	ub1;
		b_2		b2;
		ub_2	ub2;
		b_4		b4;
		ub_4	ub4;
		b_8		b8;
		ub_8	ub8;

		// FLOAT_STYLE
		fb_4	fb4;
		fb_8	fb8;

		fb_4	*p_fb4;
		fb_8	*p_fb8;

		// STRING_STYLE
		ch_1 	*str;
		ch_1 	*p_str;

		// OBJECT_STYLE
		obj_	obj;
		obj_    *p_obj;
	} v;

	friend const variable operator -(const variable &value);
	friend const variable operator ~(const variable &value);

	friend const b_4 operator !(const variable &value);

	friend const variable operator +(const variable &left_value,
									 const variable &right_value);
	friend const variable operator -(const variable &left_value,
									 const variable &right_value);
	friend const variable operator *(const variable &left_value,
									 const variable &right_value);
	friend const variable operator /(const variable &left_value,
									 const variable &right_value);
	friend const variable operator %(const variable &left_value,
									 const variable &right_value);
	friend const variable operator &(const variable &left_value,
									 const variable &right_value);
	friend const variable operator |(const variable &left_value,
									 const variable &right_value);
	friend const variable operator ^(const variable &left_value,
									 const variable &right_value);

	friend const b_4 operator ==(const variable &left_value,
								 const variable &right_value);
	friend const b_4 operator !=(const variable &left_value,
								 const variable &right_value);
	friend const b_4 operator >(const variable &left_value,
								const variable &right_value);
	friend const b_4 operator >=(const variable &left_value,
								 const variable &right_value);
	friend const b_4 operator <(const variable &left_value,
								const variable &right_value);
	friend const b_4 operator <=(const variable &left_value,
								 const variable &right_value);

	friend const b_4 operator &&(const variable &left_value,
								 const variable &right_value);
	friend const b_4 operator ||(const variable &left_value,
								 const variable &right_value);
};

typedef variable v_;

#endif // VARIABLE_H
