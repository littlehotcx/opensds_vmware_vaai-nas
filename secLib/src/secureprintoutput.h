// Copyright 2019 The OpenSDS Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may
// not use this file except in compliance with the License. You may obtain
// a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#ifndef __SECUREPRINTOUTPUT_H__E950DA2C_902F_4B15_BECD_948E99090D9C
#define __SECUREPRINTOUTPUT_H__E950DA2C_902F_4B15_BECD_948E99090D9C

/* flag definitions */
enum{

FLAG_SIGN           = 0x00001,   
FLAG_SIGN_SPACE     = 0x00002,   
FLAG_LEFT           = 0x00004,   
FLAG_LEADZERO       = 0x00008,   
FLAG_LONG           = 0x00010,   
FLAG_SHORT          = 0x00020,   
FLAG_SIGNED         = 0x00040,   
FLAG_ALTERNATE      = 0x00080,   
FLAG_NEGATIVE       = 0x00100,   
FLAG_FORCE_OCTAL    = 0x00200,   
FLAG_LONG_DOUBLE    = 0x00400,   
FLAG_WIDECHAR       = 0x00800,   
FLAG_LONGLONG       = 0x01000,   
FLAG_CHAR           = 0x02000,   
FLAG_POINTER        = 0x04000,
FLAG_I64            = 0x08000,
FLAG_PTRDIFF        = 0x10000,
#ifdef COMPATIBLE_LINUX_FORMAT
FLAG_SIZE           = 0x20000,
FLAG_INTMAX         = 0x40000
#else
FLAG_SIZE           = 0x20000
#endif
};



/* character type values */
typedef enum _CHARTYPE
{
    CHAR_OTHER,                   /* character with no special meaning */
    CHAR_PERCENT,                 /* '%' */
    CHAR_DOT,                     /* '.' */
    CHAR_STAR,                    /* '*' */
    CHAR_ZERO,                    /* '0' */
    CHAR_DIGIT,                   /* '1'..'9' */
    CHAR_FLAG,                    /* ' ', '+', '-', '#' */
    CHAR_SIZE,                    /* 'h', 'l', 'L', 'N', 'F', 'w' */
    CHAR_TYPE                     /* type specifying character */
}CHARTYPE;

/* state definitions */
typedef enum _FMT_STATE
{
    STAT_NORMAL,           
    STAT_PERCENT,          
    STAT_FLAG,             
    STAT_WIDTH,            
    STAT_DOT,              
    STAT_PRECIS,           
    STAT_SIZE,             
    STAT_TYPE,             
    STAT_INVALID           
}FMT_STATE;

#define NUMSTATES ((int)STAT_INVALID + 1)

#ifdef STACK_SIZE_LESS_THAN_1K
#define BUFFERSIZE    256
#else
#define BUFFERSIZE    512
#endif

#define MAXPRECISION  BUFFERSIZE

#define BUFFERSIZE_LB 5120
#define MAXPRECISION_LB  BUFFERSIZE_LB

#ifndef MB_LEN_MAX
#define MB_LEN_MAX 5
#endif
#define CVTBUFSIZE (309+40)      /* # of digits in max. dp value + slop */
#define CVTBUFSIZE_LB (4932+40)

#define FIND_CHAR_CLASS(lookuptbl, c)  ((c) < _T(' ') || (c) > _T('z') ? CHAR_OTHER : (CHARTYPE)(lookuptbl[(c)-_T(' ')] & 0xF))             

#define FIND_NEXT_STATE(lookuptbl, charClass, state)  (FMT_STATE)((int)(lookuptbl[(int)(charClass) * NUMSTATES + (int)(state)]) >> 4)


typedef struct _SECUREC_XPRINTF_STREAM
{
    int _cnt;
    char* _ptr;
} SECUREC_XPRINTF_STREAM;


INT32T U64Div32(UINT32T uiDividendHigh,UINT32T uiDividendLow,UINT32T uiDivisor,UINT32T *puiQuotientHigh,UINT32T *puiQuotientLow,UINT32T *puiRemainder);/*lint !e129  !e101 !e132 !e131*/

//lint -esym(526, write_char_a*)                       
void write_char_a
(
    char ch,
    SECUREC_XPRINTF_STREAM* f,
    int* pnumwritten
);

//lint -esym(526, write_multi_char_a*)  
void write_multi_char_a
(
    char ch,
    int num,
    SECUREC_XPRINTF_STREAM* f,
    int* pnumwritten
);

//lint -esym(526, write_string_a*)  
void write_string_a
(
    char* string,
    int len,
    SECUREC_XPRINTF_STREAM* f,
    int* pnumwritten
);

//lint -esym(526, securec_output_s*)  
int securec_output_s
(
    SECUREC_XPRINTF_STREAM* stream,
    const char* format,
    va_list argptr
);

//lint -esym(526, securec_woutput_s*)  
int securec_woutput_s
(
    SECUREC_XPRINTF_STREAM* stream,
    const wchar_t* format,
    va_list argptr
);

#endif


