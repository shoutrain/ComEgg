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
#include "../Logic/COptReadFile.h"
#include "../Logic/COptSaveFile.h"
#include "../Logic/COptDeleteFile.h"
#include "../Logic/COptSplit.h"
#include "../Logic/COptDie.h"
#include "../Logic/COptShowWindow.h"
#include "../Logic/COptWaitMessage.h"
#include "../Logic/COptAlert.h"
#include "../Logic/COptEnable.h"
#include "../Logic/COptAddItem.h"
#include "../Logic/CProgram.h"

#include "../Logic/CExpNot.h"
#include "../Logic/CExpAnd.h"
#include "../Logic/CExpOr.h"
#include "../Logic/CExpVarUnitary.h"
#include "../Logic/CExpVarDuality.h"

#include "../Data/CVarSolidDefined.h"
#include "../Data/CVarGroupDefined.h"
#include "../Data/CVarNetwork.h"
#include "../Data/CVarInterface.h"

#include "../Protocols/CProtocolManager.h"
#include "../UI/CUIManager.h"
#include "../Network/CNetworkManager.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif

#include "auto_xerces_str.h"

const ub_4 ENVIRONMENT_PATH_LENGTH		= 128;

const ch_1 DEFAULT_ENVIRONMENT_PATH[]	= "./Environment/";
const ch_1 PROTOCOL_XML_FILE[]			= "protocol.xml";
const ch_1 NETWORK_XML_FILE[]			= "network.xml";
const ch_1 UI_XML_FILE[]				= "interface.xml";
const ch_1 ACTIONS_XML_FILE[]			= "actions.xml";

const ch_1 SIGN_UNBOUNDED[]				= "unbounded";

const ch_1 SOLID_VARIABLE[]				= "solid_variable";
const ch_1 INTERFACE_VARIABLE[]			= "interface_variable";
const ch_1 GROUP_VARIABLE[]				= "group_variable";
const ch_1 NETWORK_VARIABLE[]			= "network_variable";

#endif // XML_PARSER_COMMON_H
