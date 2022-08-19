//////////////////////////////////////////////////////////////////////////
// TOD:  filename:   types.h
// 1.Using this head file for data-type defining,
//   Firstly make sure the type is defined
// 2.Example
//   1.Define a 8-bits variable : INT8 chVariable;
//   2.Define a 16-bits variable: INT16 snVariable;
//   3.Define a 32-bits variable: INT32 nVariable;
//   4.Define a 64-bits variable: INT64 llVariable;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//C Standards
//////////////////////////////////////////////////////////////////////////
#pragma once
#if defined(__STDC__)
# define PREDEF_STANDARD_C_1989
# if defined(__STDC_VERSION__)
#  define PREDEF_STANDARD_C_1990
#  if (__STDC_VERSION__ >= 199409L)
#   define PREDEF_STANDARD_C_1994
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define PREDEF_STANDARD_C_1999
#  endif
# endif
#endif

//////////////////////////////////////////////////////////////////////////
// Pre-C89 compilers do not recognize certain keywords. 
// Let the preprocessor remove those keywords for those compilers.
//////////////////////////////////////////////////////////////////////////
#if !defined(PREDEF_STANDARD_C_1989) && !defined(__cplusplus)
# define const
# define volatile
#endif

//////////////////////////////////////////////////////////////////////////
// Define 8-bits Integer, 16-bits Integer,32-bits Integer
// All compliant compilers that support Standard C/C++
// VC++����? Borland C++, Turb C++  those who support C89,but undefined __STDC__) 
//////////////////////////////////////////////////////////////////////////
#if defined(__STDC__) || defined(__cplusplus) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__TURBOC__)
#include <limits.h>
	// Defined 8 - bit Integer
	#if defined(UCHAR_MAX) && (UCHAR_MAX == 0xFF)
		typedef  signed char  INT8, *INT8_PTR; 
		typedef  unsigned char UINT8, *UINT8_PTR;
        #ifndef DEFINED_INT8
			#define DEFINED_INT8
		#endif
	#endif
	// Defined 16-bits Integer
	#if defined(USHRT_MAX) && (USHRT_MAX == 0xFFFF)
		typedef  short int  INT16, *INT16_PTR;
		typedef  unsigned short int UINT16, *UINT16_PTR;
		#ifndef DEFINED_INT16
		#define DEFINED_INT16
		#endif
	#elif defined(UINT_MAX) && (UINT_MAX == 0xFFFF)
		typedef  int  INT16, *INT16_PTR;
		typedef  unsigned int UINT16, *UINT16_PTR;
		#ifndef DEFINED_INT16
		#define DEFINED_INT16
		#endif	
	#endif
	// Defined 32-bits Integer
	#if defined(UINT_MAX) && (UINT_MAX == 0xFFFFFFFFUL)
		typedef int  INT32, *INT32_PTR;
		typedef unsigned int UINT32, *UINT32_PTR;
		#ifndef DEFINED_INT32
		#define DEFINED_INT32
		#endif
	#elif defined(ULONG_MAX) && (ULONG_MAX == 0xFFFFFFFFUL)
		typedef long int  INT32, *INT32_PTR;
		typedef unsigned long int UINT32, *UINT32_PTR;
		#ifndef DEFINED_INT32
		#define DEFINED_INT32
		#endif
	#endif
#endif

//////////////////////////////////////////////////////////////////////////
// Define 64-bits Integer
// Here Only support typical systems 
// such as GNU/Linux Windows UNIX Vxworks  BSD Solaris 
//////////////////////////////////////////////////////////////////////////

// GNU/Linux System 64-bits Integer
#if defined(__GNUC__) || defined(linux) ||defined(__linux)
	#if defined (__GLIBC_HAVE_LONG_LONG) || (defined(ULLONG_MAX) && (ULLONG_MAX == 0xFFFFFFFFFFFFFFFFUL)) || defined (PREDEF_STANDARD_C_1999)
		typedef  long long INT64, *INT64_PTR;
		typedef  unsigned long long UINT64, *UINT64_PTR;
		#ifndef DEFINE_INT64
		#define DEFINE_INT64
		#endif
	#endif
#endif

// Windows System 64-bits Integer
#if defined (WIN32) || defined (_WIN32)
	#if defined(_MSC_VER) || defined(__BORLANDC__)
		typedef __int64 INT64, *INT64_PTR;
		typedef unsigned __int64 UINT64, *UINT64_PTR;
		#ifndef DEFINE_INT64
		#define DEFINE_INT64
		#endif  
	#else
		typedef unsigned long long UINT64, *UINT64_PTR;
		typedef signed long long INT64, *INT64_PTR;
		#ifndef DEFINE_INT64
		#define DEFINE_INT64
		#endif
	#endif
#endif

// UNIX 
#if defined(unix) || defined(__unix__) || defined(__unix)
	# define PREDEF_PLATFORM_UNIX
#endif
#if defined(PREDEF_PLATFORM_UNIX)
	#include <unistd.h>
	#if defined(_XOPEN_VERSION)
		#if (_XOPEN_VERSION >= 3)
			#define PREDEF_STANDARD_XOPEN_1989
		#endif
        #if (_XOPEN_VERSION >= 4)
			#define PREDEF_STANDARD_XOPEN_1992
		#endif
		#if (_XOPEN_VERSION >= 4) && defined(_XOPEN_UNIX)
			#define PREDEF_STANDARD_XOPEN_1995
		#endif
		#if (_XOPEN_VERSION >= 500)
			#define PREDEF_STANDARD_XOPEN_1998
		#endif
		#if (_XOPEN_VERSION >= 600)
		#define PREDEF_STANDARD_XOPEN_2003
			typedef unsigned long long UINT64, *UINT64_PTR;
			typedef signed long long INT64, *INT64_PTR;
			#ifndef DEFINE_INT64
			#define DEFINE_INT64
			#endif
		#endif
	# endif
#endif
#ifdef UNICODE
#define __T(x) L##x
#else
#define __T(x) (x)
#endif

#define NULL 0