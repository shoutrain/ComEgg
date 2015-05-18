#include "CXMLLoader.h"

ret_ CXMLLoader::GetLastName(const ch_1 *pszFullName, ch_1 *&sLastName)
{
#ifdef _DEBUG_
	if (!pszFullName)
		return (PARAMETER_NULL | PARAMETER_1);

	if (sLastName)
		return (PARAMETER_NOT_NULL | PARAMETER_2);
#endif

	sLastName = (ch_1 *)strrchr(pszFullName, '.');

#ifdef _DEBUG_
	if (!sLastName)
		return (FAILURE);
#endif

	sLastName++;

#ifdef _DEBUG_
	if ((sLastName - pszFullName) >= (b_4)strlen(pszFullName))
		return (FAILURE);
#endif

	return (SUCCESS);
}

ret_ CXMLLoader::GetFirstName(const ch_1 *pszFullName,
							  ch_1 *sFirstName,
							  size_ &nSize)
{
#ifdef _DEBUG_
	if (!pszFullName)
		return (PARAMETER_NULL | PARAMETER_1);

	if (!sFirstName)
		return (PARAMETER_NULL | PARAMETER_2);
#endif

	ch_1 *	sPos	= (ch_1 *)strchr(pszFullName, '.');
	size_	nLength = (size_)(sPos - pszFullName);

#ifdef _DEBUG_
	if (!sPos)
		return (FAILURE);

	if (nLength >= nSize)
		return (FAILURE);
#endif

	strncpy(sFirstName, pszFullName, nLength);
	sFirstName[nLength] = '\0';
	nSize				= nLength;

	return (SUCCESS);
}

ret_ CXMLLoader::GetDirection(const ch_1 *pszDirection, EDirection &Direction)
{
#ifdef _DEBUG_
	if (!pszDirection)
		return (PARAMETER_NULL | PARAMETER_1);
#endif

	if (0 == strcmp(pszDirection, "in"))
		Direction = DIRECTION_IN;
	else if (0 == strcmp(pszDirection, "out"))
		Direction = DIRECTION_OUT;
	else if (0 == strcmp(pszDirection, "all"))
		Direction = DIRECTION_ALL;
#ifdef _DEBUG_
	else
		return (TYPE_ERROR);
#endif

	return (SUCCESS);
}

ret_ CXMLLoader::GetFieldType(EFieldStyle Style, 
							  size_ nLength, 
							  bool_ bSign, 
							  EFieldType &Type)
{
	switch (Style)
	{
	case FIELD_NORMAL_STYLE:
		switch (nLength)
		{
		case 1:
			if (bSign)
				Type = FIELD_B_1_TYPE;
			else 
				Type = FIELD_UB_1_TYPE;

			break;
		case 2:
			if (bSign)
				Type = FIELD_B_2_TYPE;
			else 
				Type = FIELD_UB_2_TYPE;

			break;
		case 4:
			if (bSign)
				Type = FIELD_B_4_TYPE;
			else 
				Type = FIELD_UB_4_TYPE;

			break;
		case 8:
			if (bSign)
				Type = FIELD_B_8_TYPE;
			else 
				Type = FIELD_UB_8_TYPE;

			break;
		default:
			return (TYPE_ERROR);
		}

		break;
	case FIELD_FLOAT_STYLE:
		switch (nLength)
		{
		case 4:
			Type = FIELD_FB_4_TYPE;

			break;
		case 8:
			Type = FIELD_FB_8_TYPE;

			break;
		default:
			return (TYPE_ERROR);
		}

		break;
	case FIELD_STRING_STYLE:
		Type = FIELD_STR_TYPE;

		break;
	case FIELD_GROUP_STYLE:
		Type = FIELD_GROUP_TYPE;

		break;
	default:
		return (TYPE_ERROR);
	}

	return (SUCCESS);
}

ret_ CXMLLoader::GetUnitaryOperator(const ch_1 *pszOperator,
									EUnitaryCalculate &Calculate)
{
#ifdef _DEBUG_
	if (!pszOperator)
		return (PARAMETER_NULL | PARAMETER_1);
#endif

	if (0 == strcmp(pszOperator, "eql"))
		Calculate = UC_EQL;
	else if (0 == strcmp(pszOperator, "neg"))
		Calculate = UC_NEG;
	else if (0 == strcmp(pszOperator, "not"))
		Calculate = UC_NOT;
	else if (0 == strcmp(pszOperator, "obv"))
		Calculate = UC_OBV;
#ifdef _DEBUG_
	else
		return (PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif

	return (SUCCESS);
}

ret_ CXMLLoader::GetDualityOperator(const ch_1 *pszOperator,
									EDualityCalculate &Calculate)
{
#ifdef _DEBUG_
	if (!pszOperator)
		return (PARAMETER_NULL | PARAMETER_1);
#endif

	if (0 == strcmp(pszOperator, "add"))
		Calculate = EC_ADD;
	else if (0 == strcmp(pszOperator, "sub"))
		Calculate = EC_SUB;
	else if (0 == strcmp(pszOperator, "mul"))
		Calculate = EC_MUL;
	else if (0 == strcmp(pszOperator, "div"))
		Calculate = EC_DIV;
	else if (0 == strcmp(pszOperator, "mod"))
		Calculate = EC_MOD;
	else if (0 == strcmp(pszOperator, "and"))
		Calculate = EC_AND;
	else if (0 == strcmp(pszOperator, "or"))
		Calculate = EC_OR;
	else if (0 == strcmp(pszOperator, "xor"))
		Calculate = EC_XOR;
#ifdef _DEBUG_
	else
		return (PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif

	return (SUCCESS);
}

ret_ CXMLLoader::GetCompareOperator(const ch_1 *pszOperator,
									ECompareCalculate &Calculate)
{
#ifdef _DEBUG_
	if (!pszOperator)
		return (PARAMETER_NULL | PARAMETER_1);
#endif

	if (0 == strcmp(pszOperator, "eq"))
		Calculate = CC_EQ;
	else if (0 == strcmp(pszOperator, "gl"))
		Calculate = CC_GL;
	else if (0 == strcmp(pszOperator, "gt"))
		Calculate = CC_GT;
	else if (0 == strcmp(pszOperator, "ge"))
		Calculate = CC_GE;
	else if (0 == strcmp(pszOperator, "ls"))
		Calculate = CC_LS;
	else if (0 == strcmp(pszOperator, "le"))
		Calculate = CC_LE;
#ifdef _DEBUG_
	else
		return (PARAMETER_TYPE_ERROR | PARAMETER_1);
#endif

	return (SUCCESS);
}

