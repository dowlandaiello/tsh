#define NUM_BUCKETS 53

/**
 * An entry in a hashmap bucket.
 */
typedef struct Entry {
    /* The key of the entry */
    char *key;

    /* The value of the entry */
    char *value;

    /* The next entry */
    struct Entry *next;
} Entry;

/**
 * A bucket in a hashmap.
 */
typedef struct Bucket {
    /* The next bucket */
    Entry *head;
} Bucket;

/**
 * A hashmap.
 */
typedef struct HashMap {
    /* The buckets stored in the hashmap */
    Bucket buckets[NUM_BUCKETS];

    /* The number of entries in the hashmap */
    unsigned long n_entries;
} HashMap;

/**
 * Returns a new stack-allocated HashMap.
 *
 * @return the new hashmap
 */
HashMap make_hashmap();

/**
 * Gets an entry forj the given key, provided that the key is contained in
 * the hashmap--if it is not, NULL is returned.
 *
 * @param map the HashMap from which the entry should be pulled
 * @param key the key of the entry that should be found
 *
 * @return a pointer to the entry
 */
Entry *entry_for_hashmap(HashMap *map, char *key);

/**
 * Determines whether or not the hashmap contains the given key.
 *
 * @param map the hashmap that may or may not contain the key
 * @param key the key to search for
 *
 * @return whether or not the hashmap contains the key
 */
int contains_key_hashmap(HashMap *map, char *key);

/**
 * Inserts a value into the hashmap under the corresponding key.
 *
 * @param map the HashMap from which the entry should be pulled
 * @param key the key of the entry
 * @param value the value of the entry
 */
void put_hashmap(HashMap *map, char *key, char *value);
