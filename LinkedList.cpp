#include <iostream>
#include <cassert>
#include "LinkedList.h"



LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList()
	: _head(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	LinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;

	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

//ValueType& LinkedList::operator[](const size_t pos) const
//{
//	return getNode(pos)->value;
//}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for(size_t i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
	if (pos == 0) {
		Node* removeNode = this->_head;
		this->_head = _head->next;

		delete removeNode;
		_size--;
	}
	else {
		Node* bufNode = this->_head;

		for (size_t i = 0; i < pos - 1; ++i)
			bufNode = bufNode->next;

		Node* removeNode = bufNode->next;
		bufNode->next = removeNode->next;
		delete removeNode;
		_size--;
	}

}

void LinkedList::removeFront()
{
	Node* removeNode = this->_head;
	this->_head = _head->next;

	delete removeNode;
	_size--;

}

void LinkedList::removeBack()
{
	remove(_size - 1);
}

void LinkedList::removeNextNode(Node* node)
{
	node->removeNext();
}

long long int LinkedList::findIndex(const ValueType& index_value) const
{
	Node* bufNode = this->_head;

	for (int i = 0; i < _size; ++i)
	{
		if (index_value == bufNode->value)
			return i;
		else
			bufNode = bufNode->next;
	}
	std::cout << "error" << "\n";
	return 0;
}

LinkedList::Node* LinkedList::findNode(const ValueType& index_value) const
{
	Node* bufNode = this->_head;

	for (int i = 0; i < _size; ++i)
	{
		if (index_value == bufNode->value)
			return bufNode;
		else
			bufNode = bufNode->next;
	}
	std::cout << "error";
	return nullptr;
}

void LinkedList::reverse()
{
	Node* reversedNode = nullptr;

	while (this->_head != nullptr)
	{
		Node* temp = _head->next;
		_head->next = reversedNode;
		reversedNode = _head;
		_head = temp;
	}
	_head = reversedNode;
}


LinkedList LinkedList::reverse() const
{
	LinkedList reversedList = (*this);
	reversedList.reverse();
	return LinkedList();
}

LinkedList LinkedList::getReverseList() const
{
	LinkedList reversedList(*this);
	reversedList.reverse();
	return LinkedList();
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
