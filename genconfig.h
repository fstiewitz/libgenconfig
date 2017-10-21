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
#ifndef _GENCONFIG_H
#define _GENCONFIG_H

#include<stdio.h>

#define GENCONFIG_ERR_FILE 1 // error in fopen or fgets
#define GENCONFIG_ERR_MALLOC 2 // error in malloc

struct genconfig_item_list_t {
    const char* name;
    const char* value;
    struct genconfig_item_list_t *next;
};

struct genconfig_tree_t {
    const char* path;
    struct genconfig_item_list_t *list;
};

int genconfig_from_file(const char* path, struct genconfig_tree_t **item);
int genconfig_from_fd(FILE *fd, struct genconfig_tree_t **item);

void genconfig_free(struct genconfig_tree_t *item);

const char* genconfig_string(struct genconfig_tree_t *item, const char* name);

#endif
