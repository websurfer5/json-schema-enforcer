# Copyright 2018 Jeffrey Kintscher <websurfer@surf2c.net>
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

AC_PREQ(2.69)
AC_INIT([json-schema-enforcer], 0.1-alpha, [websurfer@surf2c.net])
AC_COPYRIGHT([Copyright 2018 Jeffrey Kintscher <websurfer@surf2c.net>])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.15 subdir-objects foreign tar-ustar])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/progs/json-schema-tool.cc])
AC_GNU_SOURCE

LT_INIT
AC_LANG([C++])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC_C_O
AC_PROG_CXX_C_O
AX_CXX_COMPILE_STDCXX_11
AM_PROG_LEX
FLEX=${LEX}
AX_PROG_FLEX_VERSION([2.6.0], [flex_cxxflags="-Wno-error=unused-function"], [flex_cxxflags="-Wno-error=sign-compare -Wno-error=unused-function -Wno-deprecated-register"])
AC_SUBST([FLEX_CXXFLAGS], [${flex_cxxflags}])
AC_PATH_PROG([BISON],[bison])
AX_PROG_BISON_VERSION([3.0.0], [AC_SUBST([YACC], [$BISON])], [AC_MSG_ERROR(bison 3.1.0 or newer is required)])
AC_PROG_LN_S
AC_PROG_MKDIR_P

AX_BOOST_BASE([1.58.0], [], AC_MSG_ERROR(boost 1.58 or newer is required))
AX_BOOST_UNIT_TEST_FRAMEWORK

AM_SILENT_RULES([yes])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
