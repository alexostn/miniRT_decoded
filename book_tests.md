If you will always use TEST_ASSERT in such a way that it is the only statement in its if/else branch, or if you will always use curly braces, then you can manage without do-while(0).

c
#define TEST_ASSERT_SIMPLE(condition, message) \
{ \
    printf("  - %s: ", message); \
    if (condition) { \
        printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "\n"); \
    } else { \
        printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET "\n"); \
    } \
}
The problem with this approach is:

c
if (some_condition)
    TEST_ASSERT_SIMPLE(cond, "msg"); // This will expand to: if (some_condition) { ... };
else // <-- This 'else' branch will become a syntax error!
    do_something_else();