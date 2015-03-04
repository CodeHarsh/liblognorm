#ifndef LIBLOGNORM_STRING_BUFFER_H_INCLUDED
#define	LIBLOGNORM_STRING_BUFFER_H_INCLUDED
#include "json_compatibility.h"
/*
 * String buffer to work with es_str_t(libestr)
 */
typedef struct  {
    char **strs;
    int length;
    int size;
}string_buffer;

/*
 * returns a new instance of string_buffer
 * If fails return null
 */
string_buffer* get_string_buffer();

/*
 * print string buffer
 */
void print_string_buffer(string_buffer *str_buf);

/*
 * free the string buffer and assign to null
 */
void free_string_buffer(string_buffer** str_buf);

/*
 * Add new string pointer to string buffer returns current string buffer length
 */
int add_to_buffer (string_buffer* str_buf,char *str);

/*
 * get json object of string-buffer
 */
json_object* tags_json_object(string_buffer *str_buf);
#endif// end LIBLOGNORM_STRING_BUFFER_H_INCLUDED
