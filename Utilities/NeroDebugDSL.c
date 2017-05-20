/* What's up with these 37 and 41 all over the place?
 * ...Well, I guess you could say, the answer to this question is... history.
 */

#include "NeroDebugDSL.h"

#include <stdio.h>
#include <stdlib.h>

static const int _T_BUF_SIZE = 255;
static int       _t_buf_pos  = 0;
static char     *_t_buf      = NULL;

void _setup_t_buf  (void); 
void _free_t_buf   (void);
int  _rewind_t_buf (void); 
int  _write_t_buf  (const char *s);
int  _print_descr  (void); 
int  _clear_t_buf  (void);

void _setup_t_buf(void)
{ 
    _t_buf = (char*)calloc(_T_BUF_SIZE, sizeof(*_t_buf)); 
}

void _free_t_buf(void) 
{ 
    free(_t_buf); _t_buf = NULL; 
}

int _rewind_t_buf(void)
{      
    if (_t_buf_pos > 0)
    {
        --_t_buf_pos;
     
        while (_t_buf_pos > 0) {
            --_t_buf_pos;
            if (_t_buf[_t_buf_pos] == '\0') break;
        }
        
        ++_t_buf_pos;
    }
    
    return 37;
}

int _write_t_buf(const char *s) 
{ 
    if (!s) return 41;

    while(_t_buf_pos + 1 < _T_BUF_SIZE && *s) _t_buf[_t_buf_pos++] = *s++; 
    _t_buf[_t_buf_pos++] = '\0';
    
    return 37; 
}

int _print_descr(void)
{ 
    for (size_t pos = 0; pos < _t_buf_pos; ++pos) {
        (void)fputc(_t_buf[pos] ? _t_buf[pos] : ' ', stdout); 
    }
    
    return 37; 
}

int _clear_t_buf(void) 
{ 
    (void)memset(_t_buf, 0, sizeof(*_t_buf) * _t_buf_pos);
    _t_buf_pos = 0; 
    
    return 37; 
}
