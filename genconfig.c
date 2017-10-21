// Copyright (c) 2017 Fabian Stiewitz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "genconfig.h"

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

int split_line(char *buffer, char **name, char **val)
{
    while((buffer[0] != '\0') && ((buffer[0] == '\t') || (buffer[0] == ' '))) {
        buffer = buffer + 1;   // skip leading whitespace
    }
    if(buffer[0] == '\0') return 1; // is invalid line (treated as comment)
    if(buffer[0] == '#') return 2; // is comment
    *name = buffer;
    while((buffer[0] != '\0') && (buffer[0] != '=')) {
        buffer = buffer + 1;   // skip name until '='
    }
    if(buffer[0] == '\0') return 1; // is invalid line (treated as comment)
    char *save = buffer;
    while((*(buffer - 1) == ' ') || (*(buffer - 1) == '\t')) {
        buffer = buffer - 1;   // go back to first non-whitespace
    }
    buffer[0] = '\0'; // set delimiter
    buffer = save + 1; // reset
    while((buffer[0] != '\0') && ((buffer[0] == '\t') || (buffer[0] == ' '))) {
        buffer = buffer + 1;   // skip leading whitespace
    }
    if(buffer[0] == '\0') return 1; // is invalid line (treated as comment)
    *val = buffer;
    while((buffer[0] != '\0') && (buffer[0] != '\n')) {
        buffer = buffer + 1;   // skip value until NULL or '\n'
    }
    while((*(buffer - 1) == ' ') || (*(buffer - 1) == '\t')) {
        buffer = buffer - 1;   // go back to first non-whitespace
    }
    buffer[0] = '\0'; // set delimiter
    return 0;
}

int genconfig_from_file(const char* path, struct genconfig_tree_t **item)
{
    assert(path);
    int err = 0;
    FILE *fd = fopen(path, "r");
    if(fd == NULL)
        return GENCONFIG_ERR_FILE;
    if((err = genconfig_from_fd(fd, item)) != 0)
        goto onerr;
    (*item)->path = path;
    fclose(fd);
    return 0;
onerr:
    fclose(fd);
    return err;
}

int genconfig_from_fd(FILE *fd, struct genconfig_tree_t **item)
{
    assert(fd);
    struct genconfig_tree_t *head = NULL;
    struct genconfig_item_list_t *list = NULL;
    char buffer[BUFSIZ];
    char *name;
    char *val;
    char *t;

    head = (struct genconfig_tree_t*)malloc(sizeof(struct genconfig_tree_t));
    if(head == NULL) return GENCONFIG_ERR_MALLOC;
    head->path = NULL;
    head->list = NULL;

check:
    if(fgets(buffer, BUFSIZ, fd)) {
        switch(split_line(buffer, &name, &val)) {
        case 0:
            list = (struct genconfig_item_list_t*)malloc(sizeof(struct genconfig_item_list_t));
            if(list == NULL) {
                genconfig_free(head);
                return GENCONFIG_ERR_MALLOC;
            }
            list->next = head->list;

            t = malloc(strlen(name) + 1);
            if(t == NULL) {
                free(list);
                genconfig_free(head);
                return GENCONFIG_ERR_MALLOC;
            }
            strcpy(t, name);
            list->name = t;

            t = malloc(strlen(val) + 1);
            if(t == NULL) {
                free((char*)list->name);
                free(list);
                genconfig_free(head);
                return GENCONFIG_ERR_MALLOC;
            }
            strcpy(t, val);
            list->value = t;

            head->list = list;
            break;
        }
        goto check;
    }
    *item = head;
    if(ferror(fd)) return GENCONFIG_ERR_FILE;
    return 0;
}

void genconfig_free(struct genconfig_tree_t *tree)
{
    assert(tree);
    struct genconfig_item_list_t *t;
    while(tree->list) {
        t = tree->list;
        tree->list = tree->list->next;
        free((char*)t->name);
        free((char*)t->value);
        free(t);
    }
    free(tree);
}

const char *genconfig_string(struct genconfig_tree_t *item, const char* name)
{
    assert(item);
    assert(name);
    struct genconfig_item_list_t *t = item->list;
    while(t) {
        if(strcmp(t->name, name) == 0)
            return t->value;
        t = t->next;
    }
    return NULL;
}
