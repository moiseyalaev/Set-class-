#include "Set.h"
#include <iostream>

Set::Set()
{
  head = nullptr;
}

Set::~Set()
{
  Node *ptr = head; // start the transversing at the first interesting node

  while (ptr != nullptr) // loop until reached full circle back to dummy node
  {
    Node *tempNext = ptr->next; // save next node in temp Node ptr
    delete ptr;                 // delete curr node
    ptr = tempNext;             // update ptr node to next node using temp
  }
}

Set::Set(const Set &other)
{
  head = nullptr;

  int len = other.size(); // get length of other

  for (int i = 0; i < len; i++) // loop through other's Set
  {
    ItemType curr;
    other.get(i, curr); // get value of the other node

    insert(curr); // insert that value into a new node
  }
}

Set &Set::operator=(const Set &rhs) // weird header
{
  if (this != &rhs) // dont do anything is this and rhs's pointer are the same
  {
    Set temp(rhs); // copy construct
    swap(temp);    // swap
  }

  return *this;
}

int Set::size() const
{
  Node *ptr = head; //start loop at head
  int count = 0;

  while (ptr != nullptr) //go until ptr is null
  {
    count++;         // increment
    ptr = ptr->next; // move ptr to next node
  }

  return count;
}

bool Set::empty() const
{
  return size() == 0;
}

bool Set::insert(const ItemType &value)
{
  if (contains(value)) // if the value already exsists, return false
    return false;

  // create a new Node with a val = value
  Node *curr = new Node;
  curr->val = value;

  if (head == nullptr) // set is empty
  {
    // add first element in Set
    curr->next = head;
    curr->prev = nullptr;
    head = curr;
  }
  else if (value < head->val) // first element is greater than curr's val
  {
    // add to front of Set
    curr->next = head;
    curr->prev = nullptr;
    head->prev = curr;
    head = curr;
  }
  else // curr's position is somewhere after the first element
  {
    Node *ptr = head;

    while (ptr->next != nullptr) // loop until ptr->next is null
    {
      if (value < ptr->val) // if ptr->val goes after value then break
        break;

      ptr = ptr->next;
    }

    if (value > ptr->val) // if value is the last thing in the set
    {
      // add value to end of the Set
      curr->next = nullptr;
      curr->prev = ptr;
      ptr->next = curr;
    }
    else
    {
      //add value to middle of Set
      ptr->prev->next = curr;
      curr->next = ptr;
      curr->prev = ptr->prev;
      ptr->prev = curr;
    }
  }

  return true;
}

bool Set::erase(const ItemType &value)
{
  if (!contains(value)) // if value doesn't exsist, return false
    return false;

  if (size() == 1) // if te size is 1
  {
    // delete the only present element
    delete head;
    head = nullptr;
    return true;
  }

  Node *ptr = head;

  while (ptr->next != nullptr) // loop until the ptr is the last node
  {
    if (ptr->val == value) // if value is found in the Set then break
      break;

    ptr = ptr->next;
  }

  if (ptr == head) // if node of interest is the first node
  {
    // adjust the pointers at the front of the Set
    head = ptr->next;
    head->prev = nullptr;
  }
  else if (ptr->next == nullptr) // if node of interest is the last node
  {
    ptr->prev->next = nullptr; // adjust the pointeres at the end of the Set
  }
  else // if node of interest is in the middle
  {
    // adjust the pointers in the middle of the Set
    ptr->prev->next = ptr->next;
    ptr->prev->next->prev = ptr->prev;
  }

  delete ptr; // delete the node whose pointers were adjusted
  return true;
}

bool Set::contains(const ItemType &value) const
{
  bool doesContain = false; // assume value not in Set

  Node *ptr = head; //start transversing from the head

  while (ptr != nullptr) // loop through all the nodes
  {
    if (ptr->val == value) // update doesContain to if value is found in the Set
      doesContain = true;

    ptr = ptr->next;
  }

  return doesContain; //return if the value was found
}

bool Set::get(int i, ItemType &value) const
{
  if (i < 0 || i >= size()) // if i is out of bound return false
    return false;

  Node *ptr = head; // start looping at the head

  while (i > 0) // loop until ith element in Set is found since the Set is already sorted
  {
    i--;
    ptr = ptr->next;
  }

  value = ptr->val; //update value to the ith element

  return true;
}

void Set::swap(Set &other)
{
  // swap head pointers of this and other
  Node *temp = head;
  head = other.head;
  other.head = temp;
}

void Set::dump() const
{
  const Node *ptr = head;
  while (ptr != nullptr)
  {
    std::cerr << ptr->val << ", ";
    ptr = ptr->next;
  }

  std::cerr << "Done! \n";
}

void unite(const Set &s1, const Set &s2, Set &result)
{
  if (!result.empty()) // if the set isn't empty
  {
    for (int i = 0; i < result.size();) // loop through result and erase every element
    {
      // get the element we want to erase, and then erase it
      ItemType temp;
      result.get(i, temp);
      result.erase(temp);
    }
  }

  int len1 = s1.size();
  for (int i = 0; i < len1; i++) //loop through s1
  {
    // add the items in s1 to result
    ItemType temp;
    s1.get(i, temp);
    result.insert(temp);
  }

  int len2 = s2.size();
  for (int i = 0; i < len2; i++) //loop through s2
  {
    //add the items in s2 to result
    ItemType temp;
    s2.get(i, temp);
    result.insert(temp);
  }
}

void subtract(const Set &s1, const Set &s2, Set &result)
{
  if (!result.empty()) // if the set isn't empty
  {
    for (int i = 0; i < result.size();) // loop through result and erase every element
    {
      // get the element we want to erase, and then erase it
      ItemType temp;
      result.get(i, temp);
      result.erase(temp);
    }
  }

  int len = s1.size();
  for (int i = 0; i < len; i++) // loop through s1
  {
    // get the element from s1 we want to inspect
    ItemType temp;
    s1.get(i, temp);
    if (!s2.contains(temp)) // if the element is not included in s2
      result.insert(temp);  // then insert it into result
  }
}
