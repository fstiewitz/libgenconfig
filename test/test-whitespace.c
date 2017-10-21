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
#include<string.h>

#ifndef TESTDATAPATH
#define TESTDATAPATH "test-data.good"
#endif

int main()
{
    struct genconfig_tree_t *tree = NULL;
    const char *test;
    if(genconfig_from_file(TESTDATAPATH, &tree)) {
        printf("test-data.good not found\n");
        return 1;
    }
    if((test = genconfig_string(tree, "test field 1"))) {
        if(strcmp(test, "test value1") != 0) {
            printf("test output (testvalue1 check): '%s'\n", test);
            goto fail;
        }
    } else {
        printf("testvalue1 check failed\n");
        goto fail;
    }
    if((test = genconfig_string(tree, "test field 2"))) {
        if(strcmp(test, "test value2") != 0) {
            printf("test output (testvalue2 check): '%s'\n", test);
            goto fail;
        }
    } else {
        printf("testvalue2 check failed\n");
        goto fail;
    }
    if((test = genconfig_string(tree, "testfield0")))
        goto fail;
    genconfig_free(tree);
    return 0;
fail:
    genconfig_free(tree);
    return 1;
}
