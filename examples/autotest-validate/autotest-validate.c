/**
* A simple file to validate your automated test setup for AESD
*/

#include "autotest-validate.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

/**
* @return true (as you may have guessed from the name)
*/
bool this_function_returns_true()
{
    return true;
}

/**
* @return false (as you may have guessed from the name)
*/
bool this_function_returns_false()
{
    return false;
}

/**
 * @return a string which contains the username you use for
 * git submissions.  This string should match the string in conf/username.txt
 */
const char *my_username()
{
    FILE *fp = fopen("conf/username.txt", "r");
    if (fp == NULL) {
        perror("Could not open conf/username.txt");
        return NULL;
    }

    static char *username;
    static size_t capacity;
    ssize_t bytes_read = getline(&username, &capacity, fp);

    if (ferror(fp)) {
        perror("Could not read conf/username.txt");
        fclose(fp);
        return NULL;
    }

    fclose(fp);

    if (bytes_read <= 0) {
        fprintf(stderr, "No username found in conf/username.txt\n");
        return NULL;
    }

    size_t start = 0;
    size_t end = (size_t)bytes_read;

    while (start < end && isspace((unsigned char)username[start])) {
        start++;
    }
    while (end > start && isspace((unsigned char)username[end - 1])) {
        end--;
    }

    if (start == end) {
        fprintf(stderr, "No username found in conf/username.txt\n");
        return NULL;
    }

    username[end] = '\0';
    if (start > 0) {
        memmove(username, username + start, end - start + 1);
    }

    return username;
}
