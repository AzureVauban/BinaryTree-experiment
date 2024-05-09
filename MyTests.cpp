#include "HiddenTests.h"
#include "LinkedList.h"
#include "Queue.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <float.h>
#include <iostream>
#include <string>

template <typename Rvalue>
Rvalue choose_random(const LINKEDLIST::Linked_List<Rvalue> &RList) {
  return RList.at(randomBetween(0, RList.size() - 1));
}
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
    if (List.isempty() /*|| List.size() == 0*/) {
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

template <class Key, class Value> class AssociativeArrayUnitTest {
  typedef ASSOCIATIVEARRAY::AssociativeArray<Key, Value> Array;
  typedef LINKEDLIST::Linked_List<Key> TestKeys;
  typedef LINKEDLIST::Linked_List<Value> TestValues;

  bool test_isempty(const Array &Array) { return Array.size() == 0; }
  bool test_keyexists(Array &Array, Key &test_key,
                      const bool debugout = false) {
    // USE TEST KEY
    if (debugout)
      std::cout << "TESTING KEY: " << test_key << std::endl;
    const bool test_keyexists = Array.key_exists(test_key);
    if (!test_keyexists && debugout) {
      std::cout << "KEY \x1B[31m" << test_key << "\x1B[0m IS NOT IN THE MAP"
                << std::endl;
    } else {
      if (debugout) {
        std::cout << "KEY \x1B[32m" << test_key << "\x1B[0m IS IN THE MAP"
                  << std::endl;
      }
    }
    return test_keyexists;
  }

  bool test_valueexists(Array &Array, Value &test_value,
                        const bool debugout = false) {
    // USE TEST VALUE
    if (debugout)
      std::cout << "TESTING VALUE: " << test_value << std::endl;
    const bool test_valueexists = Array.value_exists(test_value);
    if (!test_valueexists && debugout) {
      std::cout << "VALUE \x1B[31m" << test_value
                << "\x1B[0m IS NOT IN THE MAP\n"
                << std::endl;
    } else {
      if (debugout) {
        std::cout << "VALUE \x1B[32m" << test_value << "\x1B[0m IS IN THE MAP\n"
                  << std::endl;
      }
    }
    return test_valueexists;
  }

  bool test_insert(Array &Array, const Key test_key, const Value test_value,
                   const bool debugout = false) {
    const size_t oldArraysize = Array.size();
    Array.insert(test_key, test_value);
    bool test_success = oldArraysize < Array.size();
    if (!test_success && debugout) {
      std::cout << "FAILED TO INSERT      {\x1B[30m" << test_key
                << "\x1B[0m:\x1B[31m" << test_value << "\x1B[0m}" << std::endl;
    } else {
      if (debugout) {
        std::cout << "SUCCESSFULLY INSERTED {\x1B[30m" << test_key
                  << "\x1B[0m:\x1B[32m" << test_value << "\x1B[0m}"
                  << std::endl;
      }
    }
    return test_success;
  }
  bool test_isfull(Array &Array, TestKeys &Keys, TestValues &Values,
                   const bool debugout = false) {
    while (!Array.isfull()) {
      if (debugout) {
        std::cout << Array << std::endl;
      }
      // std::cout << "CURRENT SIZE: " << Array.size() << std::endl;
      // std::cout << "DESIRED SIZE: " <<  << std::endl;
      if (Array.isfull()) {
        std::cout << "ARRAY IS FULL...RESIZING TO " << Array.size() * 2
                  << std::endl;
        Array.resize(Array.size() * 2);
      }
      test_insert(Array, choose_random(Keys), choose_random(Values));
    }
    const bool test_sucess = Array.isfull();
    if (test_sucess && debugout) {
      std::cout << "ARRAY IS FULL:\x1B[32m " << Array.size() << "\x1B[0m"
                << std::endl;
    } else {
      if (debugout) {
        std::cout << "ARRAY IS NOT FULL:\x1B[31m " << Array.size() << "\x1B[0m"
                  << std::endl;
      }
    }
    return test_sucess;
  }
  bool test_remove(Array &Array, const Key key, const bool debugoutput) {
    if (Array.isempty()) {
      std::cout << "LIST IS EMPTY, SKIPPING TEST" << std::endl;
      return true;
    }
    if (!Array.key_exists(key)) {
      std::cout << "KEY DOES NOT EXIST IN ARRAY, SKIPPING TEST" << std::endl;
      return true;
    }
    if (Array.size() == 1) {
      Array.remove(key);
      return Array.isempty();
    }
    bool test_success = true;
    std::cout << "NOT IMPLEMENTED\n";
    return test_success;
  }

  bool test_resize(Array &Array, const bool decreasesize = false,
                   const bool debugout = false) {
    // const bool isfull = Map.isfull(); only for debug
    if (decreasesize) {
      std::cout << "ATTEMPTING TO DECREASE THE SIZE OF ARRAY\n";
    } else {
      std::cout << "ATTEMPTING TO INCREASE THE SIZE OF ARRAY\n";
    }
    const size_t old_capacity = Array.capacity();
    size_t new_capacity = old_capacity;
    if (decreasesize) {
      new_capacity /= 2;
      // expected_capacity = new_capacity - 1;
    } else {
      new_capacity *= 2.5;
      new_capacity += 1;
      // expected_capacity = new_capacity + 1;
    }
    const size_t expected_capacity = new_capacity;
    Array.resize(new_capacity);
    // new_capacity = Map.capacity();
    bool test_success = false;
    if (decreasesize) {
      test_success = Array.capacity() < old_capacity;
    } else {
      test_success = Array.capacity() > old_capacity;
    }
    if (test_success && debugout) {

      std::cout << "SUCCESSFULLY RESIZED FROM " << old_capacity
                << " TO \x1B[30m" << expected_capacity << "\x1B[0m"
                << std::endl;
    } else {
      if (debugout) {
        std::cout << "FAILED TO RESIZE FROM " << old_capacity << " TO \x1B[30m"
                  << expected_capacity << "\x1B[0m" << std::endl;
      }
    }
    return test_success;
  }

  void UnitTests(Array &Array, TestKeys &Keys, TestValues &Values,
                 size_t TESTCASE) {
    std::cout << "TESTCASE: " << TESTCASE << std::endl;
    for (int i = 0; i != 80; i++) {
      std::cout << '=';
    }
    std::cout << std::endl;
    std::cout << "VALUES: " << Values << std::endl;
    std::cout << "KEYS: " << Keys << std::endl;
    assert(test_isempty(Array));
    for (size_t index = 0; index < Keys.size(); index++) {
      assert(!test_keyexists(Array, Keys[index]));
    }
    for (size_t index = 0; index < Values.size(); index++) {
      assert(!test_valueexists(Array, Values[index]));
    }
    assert(test_insert(Array, choose_random(Keys), choose_random(Values)));
    assert(test_isfull(Array, Keys, Values));
    assert(test_resize(Array, false, true)); // resize to larger
    std::cout << std::endl;
    std::cout << "SIZE:     " << Array.size() << std::endl
              << "CAPACITY: " << Array.capacity() << std::endl;
    std::cout << Array << std::endl;
    std::cout << std::endl;
    assert(test_resize(Array, true, true)); // resize to smaller'
    Array.shrink_to_fit();
    std::cout << Array << std::endl;
    Array.clear();
    std::cout << Array << std::endl;
    assert(Array.isempty());
  }

public:
  explicit AssociativeArrayUnitTest(Array &Map, TestKeys &Keys,
                                    TestValues &Values, const size_t TESTCASE) {
    UnitTests(Map, Keys, Values, TESTCASE);
  }
  ~AssociativeArrayUnitTest() {}
};

template <class Value> class QueueUnitTest {
  typedef LINKEDQUEUE::Queue<Value> Queue;
  typedef LINKEDLIST::Linked_List<Value> TestValuesList;

  bool test_isempty(const Queue &Test) {
    bool test_successful = Test.isEmpty();
    if (test_successful) {
      std::cout << "QUEUE IS EMPTY" << std::endl;
    } else {
      std::cout << "QUEUE HAS A SIZE OF " << Test.Size() << std::endl;
    }
    return test_successful;
  }
  bool test_enqueue(Queue &Test, const Value value) {
    bool test_successful = true;
    size_t old_size = Test.Size();
    // std::cout << "QUEUE: " << Test << std::endl;
    Test.enqueue(value);
    test_successful = Test.Size() == old_size + 1 && Test.value_exists(value);
    if (test_successful) {
      std::cout << " SUCCESSFULLY ENQUEUED " << value << std::endl;
    } else {
      std::cout << "WAS UNABLE TO ENQUEUE " << value << std::endl;
    }
    std::cout << "QUEUE: " << Test << std::endl << std::endl;
    return test_successful;
  }
  bool test_dequeue(Queue &Test) {
    if (Test.isEmpty()) {
      std::cout << "TEST QUEUE IS EMPTY, SKIPPING TEST\n";
      return true;
    }
    const Value dequeue_value = Test.Peek();
    std::cout << "QUEUE: " << Test << std::endl;
    size_t old_size = Test.Size();
    Test.dequeue();
    bool test_successful = Test.Size() == old_size - 1;
    if (test_successful) {
      std::cout << "SUCCESSFULLY DEQUEUED " << dequeue_value
                << " FROM THE QUEUE" << std::endl;
    } else {
      std::cout << "UNABLE TO SUCCESSFULLY DEQUEUED " << dequeue_value
                << "FROM THE QUEUE" << std::endl;
    }
    // std::cout << "QUEUE: " << Test << std::endl;
    return test_successful;
  }
  bool test_clear(Queue &Test) {
    std::cout << "CLEARING QUEUE OF " << Test.Size() << " VALUES" << std::endl;
    std::cout << "QUEUE: " << Test << std::endl;
    Test.clear();
    bool test_successful = Test.isEmpty();
    if (test_successful) {
      std::cout << "SUCCESSFULLY EMPTIED THE QUEUE" << std::endl;
    } else {
      std::cout << "UNABLE TO EMPTY THE QUEUE" << std::endl;
    }
    return test_successful;
  }

public:
  void runtest(Queue &Test, const TestValuesList &List) {
    assert(test_isempty(Test));
    for (int i = 0; i < randomBetween(0, List.size()); i++) {
      assert(test_enqueue(Test, choose_random(List)));
    }
    assert(test_dequeue(Test));
    assert(test_clear(Test));
  }

  explicit QueueUnitTest(Queue &Test, const TestValuesList &Values,
                         const size_t TESTCASE) {
    std::cout << "TESTCASE: " << TESTCASE << std::endl;
    for (int i = 0; i != 80; i++) {
      std::cout << '=';
    }
    std::cout << std::endl;
    runtest(Test, Values);
    std::cout << std::endl;
  }
};
// template <class Key, class Value> class HashMapUnitTest {
//   // implement as a complete binary tree of buckets
//   // the bucket is a linked list
//   typedef HASHMAP::HashMap<Key, Value> HashMap;
//   typedef LINKEDLIST::Linked_List<Key> TestKeys;
//   typedef LINKEDLIST::Linked_List<Value> TestValues;
//   size_t TESTCASE_NUM;
//
//   // TEST FUNCTIONS
//   bool test_echo() {
//     std::cout << "NOT IMPLEMENTED YET" << std::endl;
//     return true;
//   }
//   bool test_isempty(const HashMap &Map) { return Map.current_size == 0; }
//
//   bool test_keyexists(HashMap &Map, Key &test_key) {
//     // USE TEST KEY
//     std::cout << "TESTING KEY: " << test_key << std::endl;
//     const bool test_keyexists = Map.key_exists(test_key);
//     if (!test_keyexists) {
//       std::cout << "KEY \x1B[31m" << test_key << "\x1B[0m IS NOT IN THE MAP"
//                 << std::endl;
//     } else {
//       std::cout << "KEY \x1B[32m" << test_key << "\x1B[0m IS IN THE MAP"
//                 << std::endl;
//     }
//     return test_keyexists;
//   }
//
//   bool test_valueexists(HashMap &Map, Value &test_value) {
//     // USE TEST VALUE
//     std::cout << "TESTING KEY: " << test_value << std::endl;
//     const bool test_valueexists = Map.value_exists(test_value);
//     if (!test_valueexists) {
//       std::cout << "VALUE \x1B[31m" << test_value
//                 << "\x1B[0m IS NOT IN THE MAP\n"
//                 << std::endl;
//     } else {
//       std::cout << "VALUE \x1B[32m" << test_value << "\x1B[0m IS IN THE
//       MAP\n"
//                 << std::endl;
//     }
//     return test_valueexists;
//   }
//
//   bool test_insert(HashMap &Map, Key &test_key, Value &test_value) {
//     const size_t currentSize = Map.size();
//     Map.insert(test_key, test_value);
//     bool test_success = currentSize < Map.size();
//     if (!test_success) {
//       std::cout << "FAILED TO INSERT {\x1B[33m" << test_key
//                 << "\x1B[0m:\x1B[36m" << test_value << "\x1B[0m}" <<
//                 std::endl;
//     } else {
//       std::cout << "SUCCESSFULLY INSERTED {\x1B[32m" << test_key
//                 << "\x1B[0m:\x1B[32m" << test_value << "\x1B[0m}" <<
//                 std::endl;
//     }
//     return test_success;
//   }
//   // TEST DRIVER
//   void UnitTests(HashMap &Map, TestKeys &Keys, TestValues &Values,
//                  size_t TESTCASE) {
//     std::cout << "TESTCASE: " << TESTCASE << std::endl;
//     for (int i = 0; i != 80; i++) {
//       std::cout << '=';
//     }
//     std::cout << std::endl;
//     std::cout << "KEYS: " << Keys << std::endl;
//     std::cout << "VALUES: " << Values << std::endl;
//     assert(test_isempty(Map));
//     for (size_t index = 0; index < Keys.size(); index++) {
//       assert(!test_keyexists(Map, Keys[index]));
//     }
//     for (size_t index = 0; index < Values.size(); index++) {
//       assert(!test_valueexists(Map, Values[index]));
//     }
//     std::cout << std::endl;
//
//     assert(test_insert(Map, Keys[randomBetween(0, Keys.size() - 1)],
//                        Values[randomBetween(0, Values.size() - 1)]));
//     while (Map.current_size != 1) {
//       // int randint = randomBetween(0, int(Keys.size() - 5));
//       Key chosen_key = choose_random(Keys);
//       Value chosen_value = choose_random(Values);
//       Map.insert(chosen_key, chosen_value);
//     }
//     std::cout << Map << std::endl;
//   }
//
// public:
//   explicit HashMapUnitTest(HashMap Map, TestKeys &Keys, TestValues &Values,
//                            const size_t TESTCASE) {
//     TESTCASE_NUM = TESTCASE;
//     std::cout << Map << std::endl;
//     UnitTests(Map, Keys, Values, TESTCASE);
//   };
//   ~HashMapUnitTest() {}
// };

int main() {
  const static int TESTCASES = 5000;
  // using namespace HASHMAP;

  for (size_t i = 0; i < TESTCASES; i++) {
    break; //! COMMENT OUT TO ENABLE TEST
    LINKEDLIST::Linked_List<std::string> Fruits = GenerateRandomStringList(10);
    LinkedListUnitTest<std::string> mystringstests(Fruits, i);
  }

  for (size_t i = 0; i < TESTCASES; i++) {
    break; //! COMMENT OUT TO ENABLE TEST
    LINKEDLIST::Linked_List<std::string> strings = GenerateRandomStringList(50);
    LINKEDLIST::Linked_List<int> numbers = GenerateIntList(100);
    ASSOCIATIVEARRAY::AssociativeArray<std::string, int> Array(
        randomBetween(5, 10));
    // ASSOCIATIVEARRAY::AssociativeArray<std::string, int>()
    AssociativeArrayUnitTest<std::string, int> myTests(Array, strings, numbers,
                                                       i);
  }
  for (size_t i = 0; i < TESTCASES; i++) {
    // break; //! COMMENT OUT TO ENABLE TEST
    LINKEDLIST::Linked_List<int> numbers = GenerateIntList(25);
    LINKEDQUEUE::Queue<int> NumsQueue;
    QueueUnitTest<int> myQueueTests(NumsQueue, numbers, i);
  }
  std::cout << "TERMINATING PROCESS" << std::endl;
  return 0;
}
