#include "../catch/catch.hpp"
#include "circularList.h"

template <class T> bool testTailPointsToHead(CircularList<T> *l) {
  Node<T> *head = l->getLeader();

  // If the list is empty tail won't point to head.
  if (!head) {
    return true;
  }

  Node<T> *currentNode = head;
  bool tailPointsBackToHead = false;

  while (currentNode && currentNode->next) {
    if (currentNode->next != head) {
      currentNode = currentNode->next;
    } else {
      tailPointsBackToHead = true;
      break;
    }
  }

  return tailPointsBackToHead;
}

template <class T>

/** This does not capture printf **/
void captureDisplay(CircularList<T> *ll, ostringstream &output) {
  // http://stackoverflow.com/questions/4810516/c-redirecting-stdout

  // Redirect cout to our output stream
  output.str("");

  streambuf *oldCoutBuffer = cout.rdbuf();
  cout.rdbuf(output.rdbuf());
  cout << flush;

  // Capture output
  cout << *ll;

  // Reset cout
  cout.rdbuf(oldCoutBuffer);
}

TEST_CASE("testing CircularList<int> insert", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  REQUIRE(testTailPointsToHead(ll) == true);

  ll->insert(1, 2);
  REQUIRE(testTailPointsToHead(ll) == true);

  ll->insert(2, 3);
  REQUIRE(testTailPointsToHead(ll) == true);

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());

  REQUIRE(testTailPointsToHead(ll) == true);
  delete ll;
}

TEST_CASE("testing CircularList<string> insert", "[task2]") {
  CircularList<std::string> *ll = new CircularList<std::string>();
  ll->insert(0, "AAA");
  REQUIRE(testTailPointsToHead(ll) == true);

  ll->insert(1, "BBB");
  REQUIRE(testTailPointsToHead(ll) == true);

  ll->insert(2, "CCC");
  REQUIRE(testTailPointsToHead(ll) == true);

  ostringstream result;
  result << "[AAA,BBB,CCC]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());

  REQUIRE(testTailPointsToHead(ll) == true);
  delete ll;
}

TEST_CASE("testing CircularList<int> remove index 0", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(1, 2);
  ll->insert(2, 3);

  int data = ll->remove(0);

  REQUIRE(data == 1);

  ostringstream result;
  result << "[2,3]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);

  delete ll;
}

TEST_CASE("testing CircularList<int> remove tail", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(1, 2);
  ll->insert(2, 3);

  int data = ll->remove(2);

  REQUIRE(data == 3);

  ostringstream result;
  result << "[1,2]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);

  delete ll;
}

TEST_CASE("testing CircularList<int> remove inbetween", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(1, 2);
  ll->insert(2, 3);

  int data = ll->remove(1);

  REQUIRE(data == 2);

  ostringstream result;
  result << "[1,3]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);

  delete ll;
}

TEST_CASE("testing CircularList<int> remove multiple inbetween", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(1, 2);
  ll->insert(2, 3);
  ll->insert(3, 4);
  ll->insert(4, 5);
  ll->insert(5, 6);

  int data = ll->remove(1);

  REQUIRE(data == 2);

  ostringstream result;
  result << "[1,3,4,5,6]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());

  data = ll->remove(3);
  REQUIRE(data == 5);
  // "[1,3,4,6]"

  data = ll->remove(1);
  REQUIRE(data == 3);

  result.str("");
  result << "[1,4,6]";

  output.str("");
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);

  delete ll;
}

TEST_CASE("testing CircularList<string> remove multiple inbetween", "[task2]") {
  CircularList<std::string> *ll = new CircularList<std::string>();
  ll->insert(0, "1");
  ll->insert(1, "2");
  ll->insert(2, "3");
  ll->insert(3, "4");
  ll->insert(4, "5");
  ll->insert(5, "6");

  std::string data = ll->remove(1);

  REQUIRE(data == "2");

  ostringstream result;
  result << "[1,3,4,5,6]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());

  data = ll->remove(3);
  REQUIRE(data == "5");
  // "[1,3,4,6]"

  data = ll->remove(1);
  REQUIRE(data == "3");

  result.str("");
  result << "[1,4,6]";

  output.str("");
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);

  delete ll;
}

TEST_CASE("testing CircularList<int> remove all", "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(0, 2);
  ll->insert(0, 3);

  ll->remove(0);
  ll->remove(0);
  ll->remove(0);

  ostringstream result;
  result << "[]";

  ostringstream output;
  captureDisplay(ll, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll) == true);
}

TEST_CASE("testing CircularList<int> remove invalid index from non empty list",
          "[task2]") {
  CircularList<int> *ll = new CircularList<int>();
  ll->insert(0, 1);
  ll->insert(0, 2);
  ll->insert(0, 3);

  string result = "invalid index";
  string thrownResult = "";
  bool thrown = false;
  bool found = false;

  try {
    ll->remove(3);

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
  }

  REQUIRE(thrown == true);
  REQUIRE(thrownResult == result);

  try {
    ll->remove(-1);

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
  }

  REQUIRE(thrown == true);
  REQUIRE(thrownResult == result);
  REQUIRE(testTailPointsToHead(ll) == true);
}

TEST_CASE("testing CircularList<int> remove invalid index from empty list",
          "[task2]") {
  CircularList<int> *ll = new CircularList<int>();

  string result = "empty structure";
  string thrownResult = "";
  bool thrown = false;

  try {
    ll->remove(5);

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
  }

  REQUIRE(thrown == true);
  REQUIRE(thrownResult == result);
}

TEST_CASE("testing CircularList<int> append two lists", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  CircularList<int> *ll2 = new CircularList<int>();

  ll2->insert(0, 4);
  ll2->insert(1, 5);
  ll2->insert(2, 6);

  CircularList<int> ll3 = (*ll1 + *ll2);

  ostringstream result;
  result << "[1,2,3,4,5,6]";

  ostringstream output;
  captureDisplay(&ll3, output);

  REQUIRE(output.str() == result.str());

  REQUIRE(testTailPointsToHead(&ll3) == true);
}

TEST_CASE("testing CircularList<int> assignment operator", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  CircularList<int> *ll2 = new CircularList<int>();
  ll2->insert(0, 9);

  ll2 = ll1;

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll2, output);

  REQUIRE(output.str() == result.str());
  REQUIRE(testTailPointsToHead(ll2) == true);
}

TEST_CASE("testing CircularList<int> get leader", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  int data = ll1->getLeader()->data;

  REQUIRE(data == 1);
  REQUIRE(testTailPointsToHead(ll1) == true);
}

TEST_CASE("testing CircularList<int> clear function", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  ll1->clear();

  ostringstream result;
  result << "[]";

  ostringstream output;
  captureDisplay(ll1, output);

  REQUIRE(output.str() == result.str());
}

TEST_CASE("testing CircularList<int> [] operator", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  int data0 = (*ll1)[0];
  int data1 = (*ll1)[1];
  int data2 = (*ll1)[2];

  REQUIRE(data0 == 1);
  REQUIRE(data1 == 2);
  REQUIRE(data2 == 3);
  REQUIRE(testTailPointsToHead(ll1) == true);
}

TEST_CASE("testing CircularList<int> invalid [] operator", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  string result = "invalid index";
  string thrownResult = "";
  bool thrown = false;
  bool found = false;

  try {
    int data = (*ll1)[4];

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
    std::transform(thrownResult.begin(), thrownResult.end(),
                   thrownResult.begin(), ::tolower);
  }

  REQUIRE(thrown == true);

  if (thrownResult.find(result) != std::string::npos) {
    found = true;
  }

  REQUIRE(found == true);
}

TEST_CASE("testing CircularList<int> get function", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  int data = ll1->get(2);

  REQUIRE(data == 3);

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll1, output);

  REQUIRE(output.str() == result.str());

  REQUIRE(testTailPointsToHead(ll1) == true);
}

TEST_CASE("testing CircularList<int> invalid get index", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  string result = "invalid index";
  string thrownResult = "";
  bool thrown = false;
  bool found = false;

  try {
    int data = ll1->get(3);

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
    std::transform(thrownResult.begin(), thrownResult.end(),
                   thrownResult.begin(), ::tolower);
  }

  REQUIRE(thrown == true);

  if (thrownResult.find(result) != std::string::npos) {
    found = true;
  }

  REQUIRE(found == true);
}

TEST_CASE("testing CircularList<int> get from an empty list", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  string result = "empty structure";
  string thrownResult = "";
  bool thrown = false;
  bool found = false;

  try {
    int data = ll1->get(-3);

  } catch (const char *s) {
    thrown = true;
    thrownResult = string(s);
  }

  REQUIRE(thrown == true);
  REQUIRE(thrownResult == result);
}

TEST_CASE("testing CircularList<int> inbetween insert", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll1, output);

  REQUIRE(output.str() == result.str());

  ll1->insert(1, 99);

  result.str("");
  result << "[1,99,2,3]";

  output.str("");
  captureDisplay(ll1, output);

  REQUIRE(output.str() == result.str());

  ll1->insert(2, 88);

  result.str("");
  result << "[1,99,88,2,3]";

  output.str("");
  captureDisplay(ll1, output);

  REQUIRE(output.str() == result.str());
}

TEST_CASE("testing CircularList<int> copy constructor", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  CircularList<int> *ll2 = new CircularList<int>(*ll1);

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll2, output);

  REQUIRE(output.str() == result.str());
}

TEST_CASE("testing CircularList<int> clone function", "[task2]") {
  CircularList<int> *ll1 = new CircularList<int>();

  ll1->insert(0, 1);
  ll1->insert(1, 2);
  ll1->insert(2, 3);

  CircularList<int> *ll2 = ll1->clone();

  ostringstream result;
  result << "[1,2,3]";

  ostringstream output;
  captureDisplay(ll2, output);

  REQUIRE(output.str() == result.str());
}
template <class T> string getOutput(CircularList<T> list) {
  stringstream out("");
  out.flush();
  out << list;
  return out.str();
}

SCENARIO("SLL Tests") {

  GIVEN("an empty char SLL list") {
    CircularList<char> list;
    stringstream output("");

    THEN("the output should display correctly") {
      output << list;
      REQUIRE(output.str() == "[]");
    }

    THEN("cloning should work properly") {
      CircularList<char> *cloneList = list.clone();
      list.clear();
      output << *cloneList;
      REQUIRE(output.str() == "[]");
    }

    WHEN("a single item is added") {
      list.insert(0, 'a');

      THEN("the output should display correctly") {
        output << list;
        REQUIRE(output.str() == "[a]");
      }

      THEN("cloning should work properly") {
        CircularList<char> *cloneList = list.clone();
        list.clear();
        output << *cloneList;
        REQUIRE(output.str() == "[a]");
      }

      THEN("the correct out of bounds error should be thrown") {
        try {
          list.insert(5, 'a');
        } catch (const char *e) {
          REQUIRE(e == "invalid index");
        }
      }

      WHEN("another item is added") {
        list.insert(1, 'b');

        THEN("the output should display correctly") {
          output << list;
          REQUIRE(output.str() == "[a,b]");
        }

        WHEN("the list is cleared") {
          list.clear();

          THEN("the correct output should be displayed") {
            output << list;
            REQUIRE(output.str() == "[]");
          }
        }

        WHEN("an item is added to the back of the list (size())") {
          list.insert(2, 'c');
          output << list;
          REQUIRE(output.str() == "[a,b,c]");
        }
      }
    }
  }
}

SCENARIO("Testing SLL duplication") {
  GIVEN("a SLL") {
    CircularList<char> list;

    list.insert(0, 'c');
    list.insert(0, 'b');
    list.insert(0, 'a');

    stringstream output("");

    WHEN("cloning with items should have same itemes") {
      output << list;
      REQUIRE(output.str() == "[a,b,c]");
      output.str("");

      CircularList<char> *cloneList = list.clone();
      output << *cloneList;
      REQUIRE(output.str() == "[a,b,c]");
      output.str("");

      THEN("when clearing the original, the cloned should not change") {
        CircularList<char> *cloneList = list.clone();

        list.clear();
        output << list;
        REQUIRE(output.str() == "[]");
        output.str("");

        output << *cloneList;
        REQUIRE(output.str() == "[a,b,c]");
        output.str("");
      }
    }
  }
}

SCENARIO("Testing the '+' operator") {
  GIVEN("two singly linked lists") {
    CircularList<char> list1;
    CircularList<char> list2;

    list1.insert(0, 'a');
    list1.insert(1, 'b');
    list1.insert(2, 'c');

    list2.insert(0, 'd');
    list2.insert(1, 'e');
    list2.insert(2, 'f');

    stringstream output("");

    THEN("output should be correct") {
      output << list1 << list2;
      REQUIRE(output.str() == "[a,b,c][d,e,f]");
    }

    WHEN("the two lists are added together") {
      CircularList<char> newList = (list1 + list2);

      THEN("the new list's output should be correct") {
        output << newList;
        REQUIRE(output.str() == "[a,b,c,d,e,f]");
      }

      THEN("the output should not change if the original lists are cleared") {
        list1.clear();
        list2.clear();
        output << newList;
        REQUIRE(output.str() == "[a,b,c,d,e,f]");
      }
    }
  }
}

SCENARIO("testing [] operator and remove") {
  GIVEN("a linked list") {
    CircularList<char> list1;

    list1.insert(0, 'a');
    list1.insert(1, 'b');
    list1.insert(2, 'c');

    THEN("the [] operators should behave correctly") {
      REQUIRE(list1[0] == 'a');
      REQUIRE(list1[1] == 'b');
      REQUIRE(list1[2] == 'c');

      REQUIRE_THROWS(list1[-1]);
      REQUIRE_THROWS(list1[3]);
    }

    THEN("removing elements should work") {
      char letter;

      letter = list1.remove(0);
      REQUIRE(getOutput(list1) == "[b,c]");
      REQUIRE(letter == 'a');

      letter = list1.remove(1);
      REQUIRE(getOutput(list1) == "[b]");
      REQUIRE(letter == 'c');

      letter = list1.remove(0);
      REQUIRE(getOutput(list1) == "[]");
      REQUIRE(letter == 'b');
    }
  }
}
