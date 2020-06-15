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
	: m_head(nullptr), m_size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
	this->m_size = copyList.m_size;
	if (this->m_size == 0) {
		this->m_head = nullptr;
		return;
	}

	this->m_head = new Node(copyList.m_head->value);

	Node* currentNode = this->m_head;
	Node* currentCopyNode = copyList.m_head;

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
	this->m_size = bufList.m_size;
	this->m_head = bufList.m_head;

	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->m_size = moveList.m_size;
	this->m_head = moveList.m_head;

	moveList.m_size = 0;
	moveList.m_head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(m_head);
	this->m_size = moveList.m_size;
	this->m_head = moveList.m_head;

	moveList.m_size = 0;
	moveList.m_head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(m_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->m_size) {
		assert(pos >= this->m_size);
	}

	Node* bufNode = this->m_head;
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
	else if (pos > this->m_size) {
		assert(pos > this->m_size);
	}

	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->m_head;
		for (size_t i = 0; i < pos - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++m_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void LinkedList::pushBack(const ValueType& value)
{
	if (m_size == 0) {
		pushFront(value);
		return;
	}
	insert(m_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	m_head = new Node(value, m_head);
	++m_size;
}

void LinkedList::remove(const size_t pos)
{
	if (pos == 0) {
		Node* removeNode = this->m_head;
		this->m_head = m_head->next;

		delete removeNode;
		m_size--;
	}
	else {
		Node* bufNode = this->m_head;

		for (size_t i = 0; i < pos - 1; ++i)
			bufNode = bufNode->next;

		Node* removeNode = bufNode->next;
		bufNode->next = removeNode->next;
		delete removeNode;
		m_size--;
	}

}

void LinkedList::removeNextNode(Node* node)
{
	node->removeNext();
}

long long int LinkedList::findIndex(const ValueType& index_value) const
{
	Node* bufNode = this->m_head;

	for (int i = 0; i < m_size; ++i)
	{
		if (index_value == bufNode->value)
			return i;
		else
			bufNode = bufNode->next;
	}
	
	return 0;
}

LinkedList::Node* LinkedList::findNode(const ValueType& index_value) const
{
	Node* bufNode = this->m_head;

	for (int i = 0; i < m_size; ++i)
	{
		if (index_value == bufNode->value)
			return bufNode;
		else
			bufNode = bufNode->next;
	}
	return nullptr;
}

void LinkedList::reverse()
{
	Node* reversedNode = nullptr;

	while (this->m_head != nullptr)
	{
		Node* temp = m_head->next;
		m_head->next = reversedNode;
		reversedNode = m_head;
		m_head = temp;
	}
	m_head = reversedNode;
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
	return m_size;
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
