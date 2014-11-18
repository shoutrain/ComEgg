#ifndef XML_PARSER_COMMON_H
#define XML_PARSER_COMMON_H

#include "../Logic/COptEmpty.h"
#include "../Logic/COptUnitaryCalculate.h"
#include "../Logic/COptDualityCalculate.h"
#include "../Logic/COptConfigGroup.h"
#include "../Logic/CProgramIf.h"
#include "../Logic/CProgramWhile.h"
#include "../Logic/COptContinue.h"
#include "../Logic/COptBreak.h"
#include "../Logic/COptBlock.h"
#include "../Logic/COptSend.h"
#include "../Logic/COptForward.h"
#include "../Logic/COptGetAddress.h"
#include "../Logic/COptRegister.h"
#include "../Logic/COptUnregister.h"
#include "../Logic/COptSearch.h"
#include "../Logic/COptGetUsage.h"
#include "../Logic/COptNetworkWakeUp.h"
#include "../Logic/COptNetworkSleep.h"
#include "../Logic/COptReadFile.h"
#include "../Logic/COptSaveFile.h"
#include "../Logic/COptDeleteFile.h"
#include "../Logic/COptUseModule.h"
#include "../Logic/COptSplit.h"
#include "../Logic/COptDie.h"
#include "../Logic/CProgram.h"

#include "../Logic/CExpNot.h"
#include "../Logic/CExpAnd.h"
#include "../Logic/CExpOr.h"
#include "../Logic/CExpVarUnitary.h"
#include "../Logic/CExpVarDuality.h"

#include "../Data/CVarSolidDefined.h"
#include "../Data/CVarGroupDefined.h"
#include "../Data/CVarNetwork.h"
#include "../Data/CVarModule.h"

#include "../Protocols/CProtocolManager.h"
#include "../Modules/CModuleManager.h"
#include "../Network/CNetworkManager.h"
#include "../Transactions/CTransactionManager.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif

#include "auto_xerces_str.h"

const ub_4 ENVIRONMENT_PATH_LENGTH		= 128;

const ch_1 DEFAULT_ENVIRONMENT_PATH[]	= "./Environment/";
const ch_1 MODULE_XML_FILE[]			= "module.xml";
const ch_1 NETWORK_XML_FILE[]			= "network.xml";
const ch_1 INTERFACE_XML_FILE[]			= "interfaces.xml";
const ch_1 TRANSACION_XML_FILE[]		= "transactions.xml";
const ch_1 XML_FILE_EXTENSION[]			= ".xml";

const ch_1 SIGN_UNBOUNDED[]				= "unbounded";

const ch_1 SOLID_VARIABLE[]				= "solid_variable";
const ch_1 GROUP_VARIABLE[]				= "group_variable";
const ch_1 NETWORK_VARIABLE[]			= "network_variable";

#endif // XML_PARSER_COMMON_H
