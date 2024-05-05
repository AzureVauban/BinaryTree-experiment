#include "HiddenTests.h"
#include "LinkedList.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

template <typename T> class LinkedListUnitTest {
  typedef LINKEDLIST::Linked_List<T> Array;
  // The 'PRINTDEBUGLIST' function prints the size, maximum index, and elements
  // of a given linked list 'List'. It is used for debugging purposes.
  void PRINTDEBUGLIST(Array &List) {
    std::cout << "SIZE: " << List.size() << std::endl;
    std::cout << "MAX INDEX: " << List.size() - 1 << std::endl;

    std::cout << List << std::endl;
    std::cout << std::endl;
  }

  // This 'test_peek' function tests the 'peek' operation of a linked list by
  // comparing the first element of the list with an expected value. It returns
  // 'true' if the test passes and 'false' otherwise.
  bool test_peek(Array &List) {
    if (List.isempty()) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }
    T expectedList = List[0];
    return List.at(0) == expectedList;
  }

  // This 'test_infunction' function tests the insertion and duplicate value
  // checking operations of a linked list.It returns 'true' if a duplicate value
  // is found and 'false' otherwise.
  bool test_infunction(Array &List) {
    if (List.isempty() || List.size() == 0) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }
    const size_t ListSize = List.size();

    T targetvalue = List[randomBetween(0, ListSize - 1)];
    std::cout << "CHECKING TO SEE IF [" << targetvalue << "] IS A PRESENT VALUE"
              << std::endl;
    return List.in(targetvalue);
  }

  // The 'test_swap' function tests the 'swap' operation of a linked
  // list.It swaps two randomly chosen indices and verifies if the swap was
  // successful.The function returns 'true' if the test passes and
  // 'false' otherwise.
  bool test_swap(Array &List) {
    if (List.isempty() || List.size() == 0) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }

    if (List.size() == 1) {
      std::cout << "SKIPPING TEST BECAUSE LIST ONLY HAS 1 VALUE" << std::endl;
      return true;
    }
    std::vector<T> expectedList;
    const size_t ListSize = List.size();
    for (int i = 0; i < ListSize; i++) {
      expectedList.emplace_back(List[i]);
    }
    // random choosen two swap indicies
    int left = randomBetween(0, (ListSize / 2) - 1);
    int right = randomBetween(left, ListSize - 1);
    std::cout << "SWAPPING INDEX " << left << ":" << right << std::endl;
    std::cout << List << std::endl;
    List.swap(left, right);
    std::cout << List << std::endl;
    return List[left] == expectedList[right] &&
           List[right] == expectedList[left];
  }

  // The test_remove function is a template function that removes a randomly
  // chosen element from a given linked list. It then checks and returns whether
  // the value at the chosen index has changed, indicating successful removal.
  bool test_remove(Array &List) {
    if (List.isempty() || List.size() == 0) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }
    if (List.size() == 1) {
      List.remove(0);
      return List.isempty();
    }
    size_t chosen_index = randomBetween(0, List.size() - 1),
           preremovalsize = List.size();
    T chosen_value = List[chosen_index];
    std::cout << "REMOVING " << chosen_value << " AT " << chosen_index
              << std::endl;
    List.remove(chosen_index);
    std::cout << List << std::endl;
    // check if the value at the chosen index is the same as the chosen value
    int index_to_check = chosen_index - 1;
    if (index_to_check < 0) {
      index_to_check = 0;
    }
    return List[index_to_check] != chosen_value &&
           preremovalsize == List.size() + 1;
  }

  bool test_reverse(Array List) {
    std::cout << "PRE REVERSE:  " << List;
    // List.print_list(true);
    Array ReversedList = Copy(List);
    std::cout << "POST REVERSE: " << List;
    ReversedList.reverse();
    //! ReversedList.print_list(true);
    size_t n = List.size();
    for (size_t i = 0; i < n; i++) {
      if (List[i] != ReversedList[n - 1 - i]) {
        return false;
      }
    }
    return true;
  }

  bool test_clear(Array &List) {
    if (List.isempty()) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }
    size_t n = List.size();
    std::cout << "DELETING OF " << n << " VALUES" << std::endl;
    List.reverse();
    // List.print_list(true);
    std::cout << List << std::endl;
    List.clear();
    return List.isempty();
  }

public:
  void RunTests(Array &List, const size_t TESTCASE) {

    std::cout << "TESTCASE: " << TESTCASE << std::endl;
    for (int i = 0; i != 80; i++) {
      std::cout << '=';
    }

    std::cout << std::endl;
    PRINTDEBUGLIST(List);
    assert(test_peek(List));
    assert(test_infunction(List));
    assert(test_swap(List));
    assert(test_remove(List));
    // assert(test_reverse(List));
    assert(test_clear(List));
  }
  LinkedListUnitTest(Array &TList, size_t TESTCASE) {
    Array Test_Clone = LINKEDLIST::Copy(TList);
    RunTests(Test_Clone, TESTCASE);
  }
};

template <class Key, class Value> class HashMapUnitTest {
  // implement as a complete binary tree of buckets
  // the bucket is a linked list
  typedef HASHMAP::HashMap<Key, Value> HashMap;
  typedef LINKEDLIST::Linked_List<Key> TestKeys;
  typedef LINKEDLIST::Linked_List<Value> TestValues;
  size_t TESTCASE_NUM;
  // TEST FUNCTIONS
  bool test_echo() {
    std::cout << "NOT IMPLEMENTED YET" << std::endl;
    return true;
  }
  bool test_isempty(const HashMap &Map) { return Map.current_size == 0; }

  bool test_keyexists(HashMap &Map, Key &test_key) {
    // USE TEST KEY
    std::cout << "TESTING KEY: " << test_key << std::endl;
    const bool test_keyexists = Map.key_exists(test_key);
    if (!test_keyexists) {
      std::cout << "KEY \x1B[31m" << test_key << "\x1B[0m IS NOT IN THE MAP"
                << std::endl;
    } else {
      std::cout << "KEY \x1B[32m" << test_key << "\x1B[0m IS IN THE MAP"
                << std::endl;
    }
    return test_keyexists;
  }

  bool test_valueexists(HashMap &Map, Value &test_value) {
    // USE TEST VALUE
    std::cout << "TESTING KEY: " << test_value << std::endl;
    const bool test_valueexists = Map.value_exists(test_value);
    if (!test_valueexists) {
      std::cout << "VALUE \x1B[31m" << test_value
                << "\x1B[0m IS NOT IN THE MAP\n"
                << std::endl;
    } else {
      std::cout << "VALUE \x1B[32m" << test_value << "\x1B[0m IS IN THE MAP\n"
                << std::endl;
    }
    return test_valueexists;
  }

  bool test_insert(HashMap &Map, Key &test_key, Value &test_value) {
    const size_t oldMapsize = Map.current_size;
    Map.insert(test_key, test_value);
    bool test_success = oldMapsize < Map.current_size;
    if (!test_success) {
      std::cout << "FAILED TO INSERT {\x1B[33m" << test_key
                << "\x1B[0m:\x1B[36m" << test_value << "\x1B[0m}" << std::endl;
    }
    return test_success;
  }
  // TEST DRIVER
  void UnitTests(HashMap &Map, TestKeys &Keys, TestValues &Values,
                 size_t TESTCASE) {
    std::cout << "TESTCASE: " << TESTCASE << std::endl;
    for (int i = 0; i != 80; i++) {
      std::cout << '=';
    }
    std::cout << std::endl;
    std::cout << "KEYS: " << Keys << std::endl;
    std::cout << "VALUES: " << Values << std::endl;
    assert(test_isempty(Map));
    for (size_t index = 0; index < Keys.size(); index++) {
      assert(!test_keyexists(Map, Keys[index]));
    }
    for (size_t index = 0; index < Values.size(); index++) {
      assert(!test_valueexists(Map, Values[index]));
    }
    std::cout << std::endl;

    assert(!test_insert(Map, Keys[randomBetween(0, Keys.size() - 1)],
                        Values[randomBetween(0, Values.size() - 1)]));
  }

public:
  explicit HashMapUnitTest(HashMap Map, TestKeys &Keys, TestValues &Values,
                           const size_t TESTCASE) {
    TESTCASE_NUM = TESTCASE;
    // std::cout << Map << std::endl;
    std::cout << Map << std::endl;
    UnitTests(Map, Keys, Values, TESTCASE);
  };
  ~HashMapUnitTest() {}
};
int main() {
  const static int TESTCASES = 100;
  using namespace HASHMAP;

  for (size_t i = 0; i < TESTCASES; i++) {
    //break; //! SKIP THIS TEST
    LINKEDLIST::Linked_List<std::string> Fruits = GenerateRandomStringList(10);
    LinkedListUnitTest<std::string> mystringstests(Fruits, i);
  }

  for (size_t i = 0; i < TESTCASES; i++) {
    LINKEDLIST::Linked_List<std::string> testkeys =
        GenerateRandomStringList(20);
    LINKEDLIST::Linked_List<int> testvalues = GenerateIntList(20);

    HashMapUnitTest<std::string, int> hashMapUnitTest(
        HashMap<std::string, int>(), testkeys, testvalues, i);
  }
  std::cout << "TERMINATING PROCESS" << std::endl;
  return 0;
}