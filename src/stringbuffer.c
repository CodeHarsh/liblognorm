#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringbuffer.h"

/*
 * returns a new instance of string_buffer
 * If fails return null
 */
string_buffer* get_string_buffer()
{
	string_buffer *str_buf=NULL;
	str_buf = (string_buffer *) calloc(1,sizeof(string_buffer));
	str_buf->strs=0;
	str_buf->length=0;
	str_buf->size=0;
	return str_buf;
}

/*
 * print buffer
 */
void print_string_buffer(string_buffer *str_buf)
{
	int i =0;
	for(i=0;i<str_buf->length;i++)
	{
		fprintf(stderr,"%s\n",str_buf->strs[i]);
	}
}

/*
 * free the string buffer and assign to null
 */
void free_string_buffer(string_buffer* str_buf)
{
	if(str_buf)
	{
		int i =0;
		int count=0;
		for(i=0;i < (str_buf->length);i++)
		{
			count++;
			free(str_buf->strs[i]);
		}
		str_buf->strs=0;
		str_buf->length=0;
		str_buf->size=0;
		free(str_buf);
	}
}

/*
 * create and add string in buffer
 */
static inline int create_add_string_buf(string_buffer* str_buf,char *str)
{
	char *cstr = 0;
	cstr = calloc((strlen(str) + 1),sizeof(char));
	if(cstr==NULL)
	{
		free_string_buffer(str_buf);
		return 0;
	}
	strcpy(cstr,str);
	str_buf->strs[str_buf->length]= cstr;
	str_buf->length++;
	return str_buf->length;
}

/*
 * Add new string pointer to string buffer returns current string buffer length
 */
int add_to_buffer (string_buffer* str_buf,char *str)
{
	int sizeIncrease =1;
	if(str_buf->length + 1 < str_buf->size )
	{
		return create_add_string_buf(str_buf,str);
	}
	else
	{
		char** tmp = (char**)realloc(str_buf->strs,(str_buf->size + sizeIncrease) * sizeof(char*));
		if(tmp!=NULL)
		{
			str_buf->strs = tmp;
			str_buf->size+=sizeIncrease;
			return create_add_string_buf(str_buf,str);
		}
		else
		{
			free_string_buffer(str_buf);
			return 0;
		}
	}
}

/*
 * get json object of string-buffer
 */
json_object* tags_json_object(string_buffer *str_buf)
{
	struct json_object *tagBucket = NULL;
	if((tagBucket = json_object_new_array())== NULL)
	{
		return NULL;
	}
	int i =0;
	for(i=0;i<str_buf->length;i++)
	{
		struct json_object *tag;
		if((tag = json_object_new_string(str_buf->strs[i]))==NULL)
		{
			json_object_put(tagBucket);
			return NULL;
		}
		json_object_array_add(tagBucket, tag);
	}
	return tagBucket;

}
