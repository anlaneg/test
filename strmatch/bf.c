
static inline char* bf_find_match_loc(char*src,uint32_t offset)
{
	uint32_t i ;
	if(!src)
	{
		return NULL;
	}

	for(i = 0 ; i < offset && *src ; ++i)
	{
		src ++;
	}

	if(i == offset)
	{
		return src;
	}

	return NULL;
}

uint32_t bf_match(char*src,char*substr)
{	
	uint32_t i , j ,k ;
	uint32_t src_length;
	uint32_t substr_length ;

	src_length = strlen(src);
	substr_length = strlen(substr);

	for( i = 0 ,k = 0,j = 0 ; i + k < src_length && j < substr_length;)
	{
		if(src[i+k] == substr[j])
		{
			k ++ ;
			j ++ ;
			continue;
		}
		i ++ ;
		j = 0 ;
		k = 0 ;
	}

	if( j == substr_length )
	{
		return i;
	}
	return -1;

}
uint32_t bf_match(char*src,char*substr,uint32_t offset)
{
	assert(src && substr);
	if(!(src = bf_find_match_loc(src,offset)))
	{
		return -1;
	}

	return bf_match(src,substr);
}
