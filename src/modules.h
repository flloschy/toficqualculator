#ifndef MODULES_H
#define MODULES_H

char do_math(const char *restrict query, struct string_ref_vec filt);
bool math_result(char* suggestion);
bool execute_module(char* suggestion);
void add_moudle_suggestions(const char *restrict query, struct string_ref_vec filt);

#endif /* MODULES_H */
