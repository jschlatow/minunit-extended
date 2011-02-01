/**
 * 
 * \file          minunit_ext.h
 * \brief         JTN002 - MinUnit -- a minimal unit testing framework for C
 *
 *                This is an extended version of MinUnit.
 *                (see http://www.jera.com/techinfo/jtns/jtn002.html)
 *
 * \author        Johannes Schlatow <johannes.schlatow@googlemail.com>
 */

/*
 * Configuration:
 *
 * You should modify the MU_PRINT_* macros to map to your preferred output functions.
 * E.g. you might want to use printf.
 *
 */

/* Usage example:
 *
 * // test functions
 * static MU_RET test_1() {
 *   MU_ASSERT("This will fail", 0==1);
 *   return MU_NULL;
 * }
 *
 * static MU_RET test_2() {
 *   MU_ASSERT("This will succeed", true);
 *   return MU_NULL;
 * }
 *
 * // you can specify tests that serves as 
 * //  init or cleanup functions
 * static MU_RET init() {
 *   // [...]
 * }
 *
 * static MU_RET cleanup() {
 *   // [...]
 * }
 *
 * // defining a suite
 * MU_RET my_test_suite() {
 *   mu_tests_run = 0;
 *   mu_tests = 4;
 *
 *   MU_RUN_TEST(init);
 *
 *   MU_RUN_TEST(test_1);
 *   MU_RUN_TEST(test_2);
 *
 *   MU_RUN_TEST(cleanup);
 *   return MU_NULL;
 * }
 *
 * int main() {
 *   MU_RET result = my_test_suite();
 *   if (result != MU_NULL) {
 *     printf("%s\n", result);
 *   } else {
 *     printf("ALL TESTS PASSED\n");
 *   }
 *
 *   printf("Tests run: %d of %d\n", mu_tests_run, mu_tests);
 *
 *   return mu_tests-mu_tests_run;
 * }
 *
 */
 
#ifndef MINUNIT_H
#define MINUNIT_H

/// default return value
#define MU_NULL     NULL

/// return type
#define MU_RET      char*

/// enable/disable output of succeeded tests and assertions
#ifdef MU_PRINT
	#define MU_PRINT_ERROR(msg)   DEBUG_PRINT(DEBUG_LEVEL_ERROR,   msg)
	#define MU_PRINT_INFO(msg)    DEBUG_PRINT(DEBUG_LEVEL_INFO,    msg)
	#define MU_PRINT_VERBOSE(msg) DEBUG_PRINT(DEBUG_LEVEL_VERBOSE, msg)
#else
	#define MU_PRINT_ERROR(msg)
	#define MU_PRINT_INFO(msg)
	#define MU_PRINT_VERBOSE(msg)
#endif

/// helpers
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__":"TOSTRING(__LINE__)

/// classic assertion, use within tests
#define MU_ASSERT(message, test)  do { if (!(test)) { \
	                                     return "Assertion failed: \""message"\" ("#test")\n" \
	                                    		 "            in "AT"\n"; \
                                       } else MU_PRINT_VERBOSE("Assertion ok: \""message"\" ("#test")\n"); } \
	                              while (0)

/// assert and print output directly; use within bg threads
#define MU_ASSERT_PRINT(message, test) do { if (!(test)) { \
                                              MU_PRINT_ERROR("Assertion failed: \""message"\" ("#test")\n" \
	                                    		 "            in "AT"\n"); \
											} else MU_PRINT_VERBOSE("Assertion ok: \""message"\" ("#test")\n"); } \
                                       while (0)

/// run a test function
//// remark: the do-while construct might be surprising; this is a standard C idiom
////         for writing a macro that contains multiple statements.
#define MU_RUN_TEST(test)         do { char *message = test(); \
                                       if (message) return message; \
                                       MU_PRINT_INFO("Test ok: \""#test"\"\n"); \
	                                   mu_tests_run++; } \
                                  while (0)

/// test counter
extern int mu_tests_run;
/// total number of tests
extern int mu_tests;

#endif
