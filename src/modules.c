#include "string_vec.h"
#include "unicode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules.h"

char do_math(const char *restrict query, struct string_ref_vec filt) {
    char result[128] = "qalc -t -m 1000  \"";
    result[sizeof(result) - 1] = '\0'; // Ensure null termination
    strncat(result, query, sizeof(result) - 1);
    strncat(result, "\"", sizeof(result) - 1);
    // execute command
    FILE *fp = popen(result, "r");
    // extract String from FILE
    fgets(result, 50, fp);
    pclose(fp);
    // print result
    if (result != NULL) {
      // printf(result);
      char math_result[128] = "=";
      strncat(math_result, result, sizeof(math_result) - 1);
      string_ref_vec_add(&filt, utf8_normalize(result));
    }
}

bool math_result(char* suggestion) {
	// notification
	memmove(suggestion, suggestion+1, strlen(suggestion));
	char notfy[128] = "notify-send \"";
	strncat(notfy, suggestion, sizeof(notfy) - 1);
	strncat(notfy, "\"", sizeof(notfy) - 1);
	system(notfy);
	// copy
	char copy[128] = "wl-copy \"";
	strncat(copy, suggestion, sizeof(suggestion) - 1);
	strncat(copy, "\"", sizeof(notfy) - 1);
	system(copy);

    return true;
}

bool execute_module(char* suggestion) {
    switch (suggestion[0]) {
        case '=': return  math_result(suggestion);
        // add more modules
        default: return false;
    }
}

void add_moudle_suggestions(const char *restrict query, struct string_ref_vec filt) {
    do_math(query, filt);
    // add more modules
}
