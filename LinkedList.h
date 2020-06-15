#ifndef LINKEDLIST_H
#define LINKEDLIST_H


typedef double ValueType;

class LinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr); //  конструктор определения объекта типа LinkedList.
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node* next;
	};

public:
	////
	LinkedList();
	LinkedList(const LinkedList& copyList);
	LinkedList& operator=(const LinkedList& copyList);

	LinkedList(LinkedList&& moveList) noexcept;
	LinkedList& operator=(LinkedList&& moveList) noexcept;

	~LinkedList();
	////

	// доступ к значению элемента по индексу
	const ValueType& operator[](const size_t pos) const;
	ValueType& operator[](const size_t pos);
	// доступ к узлу по индексу
	LinkedList::Node* getNode(const size_t pos) const;

	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value);
	// вставка элемента после узла, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);
	// вставка в конец (О(n))
	void pushBack(const ValueType& value);
	// вставка в начало (О(1))
	void pushFront(const ValueType& value);

	// удаление
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	LinkedList reverse() const;			// получение нового списка (для константных объектов)
	LinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;
private:
	Node* m_head;
	size_t	m_size;

	void forceNodeDelete(Node* node);
};

#endif 