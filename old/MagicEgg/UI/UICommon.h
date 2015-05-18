#ifndef UI_COMMON_H
#define UI_COMMON_H

#include "../Logic/CProgram.h"

#include <string.h>

#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/Input.h>
#include <fltk/MultiLineInput.h>
#include <fltk/SecretInput.h>
#include <fltk/Browser.h>
#include <fltk/Button.h>
#include <fltk/ask.h>
#include <fltk/run.h>

const ub_4 WINDOW_NAME_LENGTH = VARIABLE_NAME_LENGTH;
const ub_4 WINDOW_TITLE_LENGTH = VARIABLE_NAME_LENGTH;

enum EWindowType
{
	WINDOW_CONTAINER,
	
	WINDOW_LABEL,
	WINDOW_TEXT,
	WINDOW_TABLE,
	WINDOW_BUTTON
};

#endif 
