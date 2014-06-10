////////////////////////////
//rcp_buffer
//The simple FIFO binaly data buffer.
//by Kent-Na

struct rcp_buffer{
	//Allocated memory pointer
    //Address between (front) and (back-1) are allocated.
	void *front;
	void *back;
	//Active data pointer. 
    //Value between (*begin) and (*end-1) are filled with meaningful data..
	void *begin;
	void *end;
};

//////
//Init and deinit
void rcp_buffer_init(struct rcp_buffer *buffer, size_t len);
void rcp_buffer_deinit(struct rcp_buffer *buffer);

/////
//Sanity check(For debug)
//Print error message into STDOUT when something wrong.
void rcp_buffer_verify(struct rcp_buffer *buffer);

/////////
//Buffer status

//Return 1 if buffer has no data. Otherwise, return 0.
int rcp_buffer_is_empty(struct rcp_buffer *buffer);

//Return 1 if buffer has no space. Call rcp_buffer_cleanup may freeup 
//extra space.
int rcp_buffer_has_no_space(struct rcp_buffer *buffer);

//Return 1 if buffer filled with  data. Otherwise, return 0.
int rcp_buffer_is_full(struct rcp_buffer *buffer);

///////////
//Buffer data

void *rcp_buffer_data(struct rcp_buffer *buffer);
void *rcp_buffer_data_end(struct rcp_buffer *buffer);
size_t rcp_buffer_data_size(struct rcp_buffer *buffer);


//Copy data from front of buffer into memory where 2nd arg pointed,
//and remove it.
//Return value:
//	Return 0 if succeeded operation. Othrewise, return -1 in case of 
//	the error like insufficient data in the buffer.
int  rcp_buffer_consume(struct rcp_buffer *buffer, void* data, size_t len);

//Remove data from buffer.
//Return value:
//  Pointer to just consumed data. It will stay valid until callilng 
//  rcp_buffer_crean_up or rcp_buffer_deinit.
void* rcp_buffer_consumed(struct rcp_buffer *buffer, size_t len);
void rcp_buffer_consumed_at(struct rcp_buffer *buffer, void* ptr);
void rcp_buffer_consumed_all(struct rcp_buffer *buffer);


///////////
//Buffer space

//rcp_buffer_space
//Return value:
//  Pointer to available space in buffer.
void *rcp_buffer_space(struct rcp_buffer *buffer);

//rcp_buffer_space_size
//Return value:
//  Size of available space in buffer.
size_t rcp_buffer_space_size(struct rcp_buffer *buffer);

//rcp_buffer_supply
//Push data into buffer.
//Parameters:
//  buffer: Target buffer.
//  data  : Pointer to data.
//  len   : Length of data in byte.
//Return value:
//  Return -1 when buffer doesn't have enough space. In this case, 
//  data will not push into the buffer at all.
//  Return 0 when successfully push data into buffer.
int rcp_buffer_supply(struct rcp_buffer *buffer, 
		const void* data, size_t len);

void* rcp_buffer_supplied(struct rcp_buffer *buffer, size_t len);

void rcp_buffer_cleanup(struct rcp_buffer *buffer);
