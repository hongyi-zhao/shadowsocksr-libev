/*
 * Copyright (c) 2014, Dustin Lundquist <dustin@null-ptr.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H

/*
https://groups.google.com/g/comp.unix.shell/c/QZpbj_8IZz8/m/n_RA7gHrBQAJ
https://groups.google.com/g/comp.lang.c/c/7qAMmeDUFvY/m/v24yB3eiBAAJ
When reading complex declarations, start by finding the leftmost
identifier and work your way out, remembering the following rules:

T *ap[N]; // ap is an array of pointer to T
T (*pa)[N]; // pa is a pointer to an array of T
T *fp(); // fp is a function returning pointer to T
T (*pf)(); // pf is a pointer to a function returning T

T const *p; // p is a pointer to const T
const T *p; // same as above

T * const p; // p is a const pointer to T

Apply these rules recursively to any function parameters. Given that,
this declaration breaks down as

parse_packet -- parse_packet
(*const parse_packet) -- is a const pointer to

(*const parse_packet)( ) -- function taking
(*const parse_packet)( ) -- unnamed parameter
(*const parse_packet)( * ) -- is a pointer to
(*const parse_packet)(const char * ) -- const char
(*const parse_packet)(const char *,
) -- unnamed parameter
(*const parse_packet)(const char *,
size_t ) -- is a size_t
(*const parse_packet)(const char *,
size_t,
) -- unnamed parameter
(*const parse_packet)(const char *,
size_t,
* ) -- is a pointer to
(*const parse_packet)(const char *,
size_t,
** ) -- a pointer to
(*const parse_packet)(const char *,
size_t,
char ** ) -- char
int (*const parse_packet)(const char *,
size_t,
char ** ) -- returning int

In plain English, parse_packet is a const pointer to a function taking
three arguments of type const char *, size_t, and char **, and returning
an int. 

http://unixwiz.net/techtips/reading-cdecl.html
https://cdecl.org/
*/

typedef struct protocol {
    const int default_port;
    int(*const parse_packet)(const char *, size_t, char **);
} protocol_t;

#endif
