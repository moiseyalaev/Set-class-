#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

using ItemType = std::string;

class Set
{
public:
  Set();
  ~Set();
  Set(const Set &other);
  Set &operator=(const Set &rhs);
  int size() const;
  bool empty() const;
  bool insert(const ItemType &value); 
  bool erase(const ItemType &value);
  bool contains(const ItemType &value) const;
  bool get(int i, ItemType &value) const;
  void swap(Set &other);
  void dump() const;

private:
  struct Node
  {
    ItemType val;
    Node *next;
    Node *prev;
  };

  Node *head;
};

void unite(const Set &s1, const Set &s2, Set &result);
void subtract(const Set &s1, const Set &s2, Set &result);

#endif