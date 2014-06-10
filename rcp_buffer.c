#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rcp_buffer.h"

void rcp_buffer_init(struct rcp_buffer *buffer, size_t len)
{
	buffer->front = malloc(len);
	buffer->back = buffer->front + len;
	buffer->begin = buffer->front;
	buffer->end = buffer->front;
}

void rcp_buffer_deinit(struct rcp_buffer *buffer)
{
	free(buffer->front);
}

void rcp_buffer_verify(struct rcp_buffer *buffer)
{
	if (buffer->end > buffer->back){
		printf("buffer over run!!!\n");
	}
	if (buffer->begin > buffer->end){
		printf("undefined data used!!!\n");
	}
}

int rcp_buffer_is_empty(struct rcp_buffer *buffer){
    if (buffer->begin == buffer->end) return 1;
    else return 0;
}
int rcp_buffer_has_no_space(struct rcp_buffer *buffer){
    if (buffer->end == buffer->back) return 1;
    else return 0;
}
int rcp_buffer_is_full(struct rcp_buffer *buffer){
    if (rcp_buffer_has_no_space(buffer) && buffer->begin == buffer->front) 
        return 1;
    else 
        return 0;
}

void *rcp_buffer_data(struct rcp_buffer *buffer)
{
	return buffer->begin;
}

void *rcp_buffer_data_end(struct rcp_buffer *buffer)
{
	return buffer->end;
}

size_t rcp_buffer_data_size(struct rcp_buffer *buffer)
{
	return buffer->end - buffer->begin;
}

void *rcp_buffer_space(struct rcp_buffer *buffer)
{
	return buffer->end;
}

size_t rcp_buffer_space_size(struct rcp_buffer *buffer)
{
	return  buffer->back - buffer->end;
}

void* rcp_buffer_supplied(struct rcp_buffer *buffer, size_t len)
{
	void*o = buffer->end;
	buffer->end += len;	
	rcp_buffer_verify(buffer);
	return o;
}

int rcp_buffer_supply(struct rcp_buffer *buffer, 
		const void* data, size_t len)
{
	if (rcp_buffer_space_size(buffer)<len)
		return -1;//Not enough space
	memcpy(buffer->end, data, len);
	rcp_buffer_supplied(buffer, len);
    return 0;
}

int  rcp_buffer_consume(struct rcp_buffer *buffer, void* data, size_t len){
	if (rcp_buffer_data_size(buffer)<len)
		return 0;
	memcpy(data, buffer->begin, len);
	rcp_buffer_consumed(buffer, len);
    return 0;
}
void* rcp_buffer_consumed(struct rcp_buffer *buffer, size_t len)
{
	void* o = buffer->begin;
	buffer->begin += len;
	rcp_buffer_verify(buffer);
	return o;
}

void rcp_buffer_consumed_at(struct rcp_buffer *buffer, void* ptr)
{
	buffer->begin = ptr;
	rcp_buffer_verify(buffer);
}

void rcp_buffer_consumed_all(struct rcp_buffer *buffer)
{
	buffer->begin = buffer->end;
	rcp_buffer_verify(buffer);
}

void rcp_buffer_cleanup(struct rcp_buffer *buffer)
{
	if (buffer->begin == buffer->end){
		//Buffer is empty.
		buffer->begin = buffer->front;
		buffer->end = buffer->front;
		return;
	}

	if (buffer->begin != buffer->front){
		size_t remain = buffer->end - buffer->begin;
		memmove(buffer->front, buffer->begin, remain);
		buffer->begin = buffer->front;
		buffer->end = buffer->front + remain;
	}
}

