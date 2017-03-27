#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cache.h"


extern uns64 cycle_count; // You can use this as timestamp for LRU

////////////////////////////////////////////////////////////////////
// ------------- DO NOT MODIFY THE INIT FUNCTION -----------
////////////////////////////////////////////////////////////////////

Cache  *cache_new(uns64 size, uns64 assoc, uns64 linesize, uns64 repl_policy){

   Cache *c = (Cache *) calloc (1, sizeof (Cache));
   c->num_ways = assoc;
   c->repl_policy = repl_policy;

   if(c->num_ways > MAX_WAYS){
     printf("Change MAX_WAYS in cache.h to support %llu ways\n", c->num_ways);
     exit(-1);
   }

   // determine num sets, and init the cache
   c->num_sets = size/(linesize*assoc);
   c->sets  = (Cache_Set *) calloc (c->num_sets, sizeof(Cache_Set));

   return c;
}

////////////////////////////////////////////////////////////////////
// ------------- DO NOT MODIFY THE PRINT STATS FUNCTION -----------
////////////////////////////////////////////////////////////////////

void    cache_print_stats    (Cache *c, char *header){
  double read_mr =0;
  double write_mr =0;

  if(c->stat_read_access){
    read_mr=(double)(c->stat_read_miss)/(double)(c->stat_read_access);
  }

  if(c->stat_write_access){
    write_mr=(double)(c->stat_write_miss)/(double)(c->stat_write_access);
  }

  printf("\n%s_READ_ACCESS    \t\t : %10llu", header, c->stat_read_access);
  printf("\n%s_WRITE_ACCESS   \t\t : %10llu", header, c->stat_write_access);
  printf("\n%s_READ_MISS      \t\t : %10llu", header, c->stat_read_miss);
  printf("\n%s_WRITE_MISS     \t\t : %10llu", header, c->stat_write_miss);
  printf("\n%s_READ_MISSPERC  \t\t : %10.3f", header, 100*read_mr);
  printf("\n%s_WRITE_MISSPERC \t\t : %10.3f", header, 100*write_mr);
  printf("\n%s_DIRTY_EVICTS   \t\t : %10llu", header, c->stat_dirty_evicts);

  printf("\n");
}



////////////////////////////////////////////////////////////////////
// Note: the system provides the cache with the line address
// Return HIT if access hits in the cache, MISS otherwise 
// Also if mark_dirty is TRUE, then mark the resident line as dirty
// Update appropriate stats
////////////////////////////////////////////////////////////////////

Flag    cache_access(Cache *c, Addr lineaddr, uns mark_dirty){
  Flag outcome=MISS;

  // Your Code Goes Here

  uns64 cache_line_num = lineaddr % (c->num_sets);
  uns64 cache_tag_num = lineaddr >> (int) (log(c->num_sets)/log(2));
  
  for (int i = 0; i < (c->num_ways); i++){
    if (c->sets->line[i]->tag == cache_tag_num){
      outcome = HIT;
    }
  }
  
  return outcome;
}

////////////////////////////////////////////////////////////////////
// Note: the system provides the cache with the line address
// Install the line: determine victim using repl policy (LRU/RAND)
// copy victim into last_evicted_line for tracking writebacks
////////////////////////////////////////////////////////////////////

void    cache_install(Cache *c, Addr lineaddr, uns mark_dirty){
  
  // Your Code Goes Here
  // Note: You can use cycle_count as timestamp for LRU

  uns64 victim_set_num = lineaddr % (c->num_sets);
  uns64 line_tag_num = lineaddr >> (log(c->num_sets)/log(2));
  if (c->repl_policy == RAND){
    uns64 victim_way_num = rand()%(c->num_ways);
    c->last_evicted_line = c->sets->line[victim_way_num];
    c->sets->line[victim_way_num] = line_tag_num;
  }else if (c->repl_policy == LRU) {
    for (int i = 0; i < (c->num_ways); i++){
      int 
      if (c->sets->line[i]->tag == cache_tag_num){
        outcome = HIT;
      }
  }
  }
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


