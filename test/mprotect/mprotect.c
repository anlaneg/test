#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>

typedef struct ht
{
	int et_size ;
	int entity_size;
	char* et;
	char* protect_begin;
	int protect_length;
} ht_t;

char* ht_get_entity_by_id(ht_t*hash_table,int id)
{
	assert(hash_table->et_size > id);
	return hash_table->et + (hash_table->entity_size * id);
}

static void et_make_freelist(ht_t*hash_table)
{
    uint32_t idx = 1;
 
     assert(hash_table);
 
     assert(hash_table->et_size >863);
     assert((hash_table->entity_size*863) > 4096);

     //1.get special_entity_address_begin
     char*special_entity_address_begin=(char*)ht_get_entity_by_id(hash_table,863);
     char*special_entity_page_address_begin= (char*)(((uintptr_t)special_entity_address_begin) & (~(4096-1)));
     char*special_entity_page_address_end  = special_entity_page_address_begin + 4096;

     //2.what is the first entity id
     assert(special_entity_page_address_end >= special_entity_address_begin);
     for(idx = 863;idx <=hash_table->et_size;++idx)
     {
	     char*et = (char*)ht_get_entity_by_id(hash_table,idx);
	     if(et>special_entity_page_address_end)
	     {
		     break;
	     }
     }
     assert(idx < hash_table->et_size);

     //3.protect the memory zone for [special_entity_page_address_begin,special_entity_page_address_end]
     if(mprotect(special_entity_page_address_begin,4096, PROT_READ)==0)
     {
    		printf("Protect memory zone [%p,%p] success\n",special_entity_page_address_begin,special_entity_page_address_end);
		hash_table->protect_begin = special_entity_page_address_begin;
		hash_table->protect_length = 4096;
     }
     else
     {
	     printf("Protect memory zone [%p,%p] error,errno=%d,error message is %s\n",
    				special_entity_page_address_begin,special_entity_page_address_end,
    				errno,strerror(errno));
    		*((uint32_t*)0)=0;
     }

}


int main(int argc,char**argv)
{
	ht_t fdb_table;
	ht_t* fdb = &fdb_table;
	fdb->entity_size = 88;
	fdb->et_size = 4096;

	char*pro1 = malloc(fdb->entity_size*fdb->et_size);
	fdb->et = malloc(fdb->entity_size*fdb->et_size);
	char*pro = malloc(fdb->entity_size*fdb->et_size);
	printf("pro1 %p pro %p\n",pro1,pro);

	et_make_freelist(fdb);
#if 0
	if(mprotect(fdb->protect_begin,4096, PROT_READ|PROT_WRITE)==0)
	{
		printf("Unprotect memory zone [%p,%p] success\n",fdb->protect_begin,(char*)((uintptr_t)fdb->protect_begin + 4096));
		
	}
	else
	{
		printf("Unprotect memory zone [%p,%p] error,errno=%d,error message is %s\n",fdb->protect_begin,(char*)((uintptr_t)fdb->protect_begin + 4096),errno,strerror(errno));
		*((uint32_t*)0)=0;
	}
#endif
#if 0
	//free fdb->et
	printf("Try free %p \n",fdb->et);
	free(fdb->et);
#endif
	//must ok
	char* ok = ht_get_entity_by_id(fdb,4);
	printf("Try access %p [ok]\n",ok);
	*ok = 1;


	//must die
	char* error = ht_get_entity_by_id(fdb,863);
	printf("Try access %p [die]\n",error);
	*error = 1;//must 11 signal 

	//free fdb->et
	printf("Try free %p \n",fdb->et);
	free(fdb->et);


	return 0;
}
