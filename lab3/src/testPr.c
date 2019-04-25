#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>

#include"find_min_max.c"

void testRevertString(void) {
 
  

 // RevertString(simple_string);
  //CU_ASSERT_STRING_EQUAL_FATAL(simple_string, "olleH");

  //RevertString(str_with_spaces);
  //CU_ASSERT_STRING_EQUAL_FATAL(str_with_spaces, "secaps htiw gnirtS");

  //RevertString(str_with_odd_chars_num);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_with_odd_chars_num, "cba");

  //RevertString(str_with_even_chars_num);
  //CU_ASSERT_STRING_EQUAL_FATAL(str_with_even_chars_num, "dcba");
 
 // RevertString(str_test1);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test1, "321");
  
 // RevertString(str_test2);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test2, "cba");
  
  //RevertString(str_test3);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test3, "123");
  
  CU_PASS("ok");
  
}

void testRevertString3(void) {
   int array_size =3;
   int *array = malloc(array_size * sizeof(int));
 // RevertString(str_test1);
  
  //CU_ASSERT_STRING_EQUAL_FATAL(str_test1, "321");
  
 // RevertString(str_test2);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test2, "cba");
  
 // RevertString(str_test3);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test3, "123");
 GetMinMax(array,0,array_size);
 CU_ASSERT_STRING_EQUAL_FATAL("","");
  
}


void testRevertString5(void) {
    char* str_test3="ok";
   int array_size =5;
   int *array = malloc(array_size * sizeof(int));
   array={2,4,5,6,7};
 // RevertString(str_test1);
  
  //CU_ASSERT_STRING_EQUAL_FATAL(str_test1, "321");
  
 // RevertString(str_test2);
 // CU_ASSERT_STRING_EQUAL_FATAL(str_test2, "cba");
  
 // RevertString(str_test3);
  
 GetMinMax(array,0,array_size);
 CU_ASSERT_STRING_EQUAL_FATAL("2323", "123");
}

int main() {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite", NULL, NULL);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
  if ((NULL == CU_add_test(pSuite, "test of find minmax function",
                           testRevertString3))) {
                               
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  if ((NULL == CU_add_test(pSuite, "test of find minmax function2",
                           testRevertString5))) {
                               
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}