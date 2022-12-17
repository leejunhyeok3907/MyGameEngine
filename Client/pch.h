#pragma once

#include <windows.h>
#include <wchar.h>

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;

#include <string>
using std::string;
using std::wstring;

#define _USE_MATH_DEFINES
#include <math.h>

#include <assert.h>

//vs설치도중 개발도구에 포함되어있기때문에
//라이브러리 사용시에 절대경로를 입력해줄 필요가 없음.
#pragma comment(lib, "Msimg32.lib")

#include "define.h"
#include "struct.h"
#include "function.h"