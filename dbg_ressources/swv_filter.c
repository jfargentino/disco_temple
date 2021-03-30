/*
 *   Copyright 2021 ENEGENO
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char ** argv) {
    int print_next = -1;
    int c = fgetc (stdin);
    while (c != EOF) {
        if (1) {
            if (isprint (c)) {
                c = fputc (c, stdout);
            }
        } else {
            if (print_next > 0) {
                c = fputc (c, stdout);
                print_next = 0;
            } else {
                switch (c) {
                    case 0x01:
                    print_next = 1;
                    break;
                    default:
                    break;
                }
            }
        }
        if (c != EOF) {
            c = fgetc (stdin);
        }
    }
    return EXIT_SUCCESS;
}

