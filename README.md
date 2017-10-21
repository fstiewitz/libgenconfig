# libgenconfig
Small C parser for simple config files

## Example

    # comments span the entire line
    my-option = 1
    # name is everything until "="
    my-other option = 2
    # minus whitespaces before/after the name:
       hello world    =    good   bye
    # means key "hello world" is value "good   bye"

```c
#include "genconfig.h"
#include<stdio.h>

int main(int argc, char **argv)
{
    struct genconfig_tree_t *tree;
    if(genconfig_from_fd(stdin, &tree))
        return 1;
    // search option
    const char *s = genconfig_string(tree, "my-option");
    if(s) {
        printf("%s = %s\n", argv[i], s);
    } else {
        printf("%s undefined\n", argv[i]);
    }
    // iterate over all config values
    for(struct genconfig_item_list_t *t = tree->list; t; t = t->next) {
        printf("%s = %s\n", t->name, t->value);
    }
    // clean up
    genconfig_free(tree);
    return 0;
}
```

## Documentation

```c
struct genconfig_item_list_t {
    const char* name;
    const char* value;
    struct genconfig_item_list_t *next;
};

struct genconfig_tree_t {
    const char* path;
    struct genconfig_item_list_t *list;
};

// 0 on success, >0 on error
int genconfig_from_file(const char* path, struct genconfig_tree_t **item);
int genconfig_from_fd(FILE *fd, struct genconfig_tree_t **item);
void genconfig_free(struct genconfig_tree_t *item);
const char* genconfig_string(struct genconfig_tree_t *item, const char* name);
// error codes
#define GENCONFIG_ERR_FILE 1 // error in fopen or fgets
#define GENCONFIG_ERR_MALLOC 2 // error in malloc
```
