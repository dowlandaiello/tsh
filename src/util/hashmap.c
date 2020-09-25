#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

/**
 * Returns a new stack-allocated HashMap.
 *
 * @return the new hashmap
 */
HashMap make_hashmap()
{
    return (HashMap) {};
}

/**
 * Calculates a hash code for the given key.
 *
 * @param key the key for which a hash code should be calculated
 *
 * @return
 */
unsigned long key_hash_code(char *key)
{
    // A proto-hashcode assigned to the key
    unsigned long hash_code = 0;

    for (char *curr = key; *curr != '\0'; curr++)
        hash_code = 128 * hash_code + *curr;

    return hash_code;
}

/**
 * Gets an entry forj the given key, provided that the key is contained in
 * the hashmap--if it is not, NULL is returned.
 *
 * @param map the HashMap from which the entry should be pulled
 * @param key the key of the entry that should be found
 *
 * @return a pointer to the entry
 */
Entry *entry_for_hashmap(HashMap *map, char *key)
{
    // Calculate a hash for the key
    unsigned long hash_code = key_hash_code(key);

    // Look through the bucket for an entry matching the key
    Entry *bucket = map->buckets[hash_code % NUM_BUCKETS].head;

    for (; bucket != NULL; bucket = bucket->next)
        if (strcmp(bucket->key, key) == 0)
            return bucket;

    return NULL;
}

/**
 * Determines whether or not the hashmap contains the given key.
 *
 * @param map the hashmap that may or may not contain the key
 * @param key the key to search for
 *
 * @return whether or not the hashmap contains the key
 */
int contains_key_hashmap(HashMap *map, char *key)
{
    return entry_for_hashmap(map, key) != NULL;
}

/**
 * Inserts a value into the hashmap under the corresponding key.
 *
 * @param key the key of the entry
 * @param value the value of the entry
 */
void put_hashmap(HashMap *map, char *key, char *value)
{
    Entry *existing_entry = entry_for_hashmap(map, key);
    if (existing_entry != NULL) {
        existing_entry->value = value;

        return;
    }

    // Calculate a hash for the key
    unsigned long hash_code = key_hash_code(key);

    // Find the bucket that the entry belongs in
    Entry **bkt_head_ptr = &map->buckets[hash_code % NUM_BUCKETS].head;

    // Allocate a new entry
    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = value;

    // If an entry exists in the bucket, make it the next
    if (*bkt_head_ptr != NULL) {
        new_entry->next = *bkt_head_ptr;    
    } 

    // Put the new entry in the bucket
    *bkt_head_ptr = new_entry;
}
