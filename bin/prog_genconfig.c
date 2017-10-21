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

int main(int argc, char **argv)
{
    struct genconfig_tree_t *tree;
    if(genconfig_from_fd(stdin, &tree))
        return 1;
    if(argc > 1) {
        for(int i = 1; i < argc; ++i) {
            const char *s = genconfig_string(tree, argv[i]);
            if(s) {
                printf("%s = %s\n", argv[i], s);
            } else {
                printf("%s undefined\n", argv[i]);
            }
        }
    } else {
        for(struct genconfig_item_list_t *t = tree->list; t; t = t->next) {
            printf("%s = %s\n", t->name, t->value);
        }
    }
    genconfig_free(tree);
    return 0;
}
