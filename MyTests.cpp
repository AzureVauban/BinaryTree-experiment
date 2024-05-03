#include "LinkedList.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// The 'randomBetween' function generates a random integer between two given
// integers 'a' and 'b'. It uses the Mersenne Twister algorithm for random
// number generation.
int randomBetween(int a, int b) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen); // generate numbers
}

// The 'CreateList' function generates a linked list of unique random
// integers. The size of the list is determined by the 'capacity' parameter.
LINKEDLIST::Linked_List<int> CreateIntList(const size_t, const int, const int);
template <typename T> class LinkedListUnitTest {
  typedef LINKEDLIST::Linked_List<T> Array;
  const static int TESTCASES = 1000;
  // The 'PRINTDEBUGLIST' function prints the size, maximum index, and elements
  // of a given linked list 'List'. It is used for debugging purposes.
  void PRINTDEBUGLIST(Array &List) {
    std::cout << "SIZE: " << List.size() << std::endl;
    std::cout << "MAX INDEX: " << List.size() - 1 << std::endl;

    List.print_list(true);
    std::cout << std::endl;
  }

  // This 'test_peek' function tests the 'peek' operation of a linked list by
  // comparing the first element of the list with an expected value. It returns
  // 'true' if the test passes and 'false' otherwise.
  bool test_peek(Array &List) {
    std::vector<T> expectedList;
    for (int i = 0; i < List.size(); i++) {
      expectedList.emplace_back(List[i]);
    }
    return List[0] == expectedList[0];
  }

  // This 'test_infunction' function tests the insertion and duplicate value
  // checking operations of a linked list.It returns 'true' if a duplicate value
  // is found and 'false' otherwise.
  bool test_infunction(Array &List) {
    const size_t ListSize = List.size();

    int targetvalue = List[randomBetween(0, ListSize - 1)];
    std::cout << "CHECKING TO SEE IF [" << targetvalue << "] IS A PRESENT VALUE"
              << std::endl;
    return List.in(targetvalue);
  }

  // The 'test_swap' function tests the 'swap' operation of a linked
  // list.It swaps two randomly chosen indices and verifies if the swap was
  // successful.The function returns 'true' if the test passes and
  // 'false' otherwise.
  bool test_swap(Array &List) {

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
    List.print_list(true);
    List.swap(left, right);
    List.print_list(true);
    return List[left] == expectedList[right] &&
           List[right] == expectedList[left];
  }

  // The test_remove function is a template function that removes a randomly
  // chosen element from a given linked list. It then checks and returns whether
  // the value at the chosen index has changed, indicating successful removal.
  bool test_remove(Array &List) {
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
    List.print_list(true);
    // check if the value at the chosen index is the same as the chosen value
    int index_to_check = chosen_index - 1;
    if (index_to_check < 0) {
      index_to_check = 0;
    }
    return List[index_to_check] != chosen_value &&
           preremovalsize == List.size() + 1;
  }

  bool test_reverse(Array List) {
    std::cout << "PRE REVERSE:  ";
    List.print_list(true);
    Array ReversedList = Copy(List);
    std::cout << "POST REVERSE: ";
    ReversedList.reverse();
    ReversedList.print_list(true);
    size_t n = List.size();
    for (size_t i = 0; i < n; i++) {
      if (List[i] != ReversedList[n - 1 - i]) {
        return false;
      }
    }
    return true;
  }

  bool test_clear(Array &List) {
    size_t n = List.size();
    std::cout << "DELETING OF " << n << " VALUES" << std::endl;
    List.reverse();
    List.print_list(true);
    List.clear();
    return List.isempty();
  }

public:
  void RunTests() {
    for (size_t t = 0; t <= TESTCASES; t++) {
      std::cout << "TESTCASE: " << t << std::endl;
      for (int i = 0; i != 80; i++) {
        std::cout << '=';
      }
      const int TESTSIZE = randomBetween(3, 20);

      Array List;
      for (int j = 0; j < TESTSIZE; j++) {
        int chosen_value = randomBetween(0, 1000);
        if (!List.in(chosen_value)) {
          List.insert(chosen_value);
        }
      }
      std::cout << std::endl;
      PRINTDEBUGLIST(List);
      assert(test_peek(List));
      assert(test_infunction(List));
      std::cout << std::endl;
      assert(test_swap(List));
      assert(test_remove(List));
      // assert(test_reverse(List));
      assert(test_clear(List));
    }
  }
};

template <class Key, class B> class HashMapUnitTest {
  // implement as a complete binary tree of buckets
  // the bucket is a linked list
  typedef JACKSONHASH::HashMap<Key, B> Value;
  size_t TESTCASE_NUM;
  // TEST FUNCTIONS
  bool test_echo() {
    std::cout << "NOT IMPLEMENTED YET" << std::endl;
    return true;
  }
  // TEST DRIVER
  void UnitTests(Value &value) { assert(test_echo()); }

public:
  HashMapUnitTest(Value &MapInstance, const size_t TESTCASE) {
    TESTCASE_NUM = TESTCASE;
    UnitTests(MapInstance);
  };
  ~HashMapUnitTest() {}
};
int main() {
  using namespace JACKSONHASH;
  // LinkedListUnitTest<int> mytests;
  // mytests.RunTests();
  HashMap<int, std::string> Map;
  std::ifstream file("../names.txt");
  std::string str;
  if (!file.is_open()) {
    std::cout << "Unable to open file.\n";
    return 1; // or exit(1);
  }
  while (std::getline(file, str)) {
    std::cout << "ADDING " << str << std::endl;
  }
    //Map.insert(0, str);

  HashMapUnitTest<int, std::string> hashMapUnitTest(Map, 0);
  std::cout << "TERMINATING PROCESS" << std::endl;
  return 0;
}

LINKEDLIST::Linked_List<int> CreateIntList(const size_t capacity = 10,
                                           const int min = 0,
                                           const int max = 10) {
  std::vector<int> values;
  LINKEDLIST::Linked_List<int> intArray;
  for (int i = 0; i < capacity; i++) {
    int chosen_value = randomBetween(min, max);
    bool value_exists = false;
    for (int j = 0; j < values.size(); j++) {
      if (values.at(j) == chosen_value) {
        value_exists = true;
        break;
      }
    }
    if (!value_exists) {
      values.emplace_back(chosen_value);
      intArray.insert(chosen_value);
    }
  }
  return intArray;
}
