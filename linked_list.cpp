#include <iostream>


template<typename T>
struct node {
	T data;
	node* next;

	node(T data = T(), node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};



template<typename T>
class iterator {
	node<T>* m_node;
public:
	iterator(node<T>* n) : m_node(n) {}

	// Проверка на равенство
	bool operator==(const iterator<T>& other) {
		return this->m_node == other.m_node;
	}

	// Проверка на неравенство
	bool operator!=(const iterator<T>& other) {
		return !operator==(other);
	}

	// Получение значения текущего узла
	T operator*() {
		if (m_node) {
			return m_node->data;
		} // Иначе достигнут конец списка. Уместно возбудить исключение
		return T();
	}

	// Переход к следующему узлу
	void operator++() {
		if (m_node) {
			m_node = m_node->next;
		}
	}

};



template<typename T>
class list {
	node<T>* head;
	int counter;
public:

	list();
	~list();

	void push_back(T);	//добавление нового узла в конец списка

	void pop_front();		//удаление первого узла из списка, реализовал для более быстрого clear

	void pop_back();		//удаление последнего элемента списка

	int size();				//количество элементов в списке

	void clear();			//полная очистка списка

	bool is_empty();		//проверка на то, пуст ли список

	void erase(int);		//удаление узла по заданному индексу (начиная от 0)

	T& operator[](const int);				//доступ к значению по индексу, жаль что скорости как у вектора не добиться

	const list& operator=(const list&);		//полное копирование элементов другого списка

	node<T>* begin();
	node<T>* end();
	
};





void main() {
	list<int> a;
	
	a.push_back(44);
	a.push_back(4);
	a.push_back(2);

	for (iterator<int> it = a.begin(); it != a.end(); ++it)
		std::cout << *it << std::endl;
	
	
}


//Реализация всех методов, конструкторов, деструкторов и перегрузок


template<typename T>
node<T>* list<T>::begin() {
	return head;
}

template<typename T>
node<T>* list<T>::end() {
	return nullptr;
}
template<typename T>
list<T>::list() {
	counter = 0;
	head = nullptr;
}

template<typename T>
list<T>::~list()
{
	clear();
}


template<typename T>
void list<T>::push_back(T data)
{
	if (!head) head = new node<T>(data);

	else {
		node<T>* current = head;
		while (current->next) current = current->next;
		current->next = new node<T>(data);
	}
	++counter;
}

template<typename T>
void list<T>::pop_front()
{
	node<T>* temp = head;
	head = head->next;
	delete temp;
	--counter;
}

template<typename T>
void list<T>::pop_back()
{
	node<T>* temp = head;
	for (int i = 0; i < counter - 1; ++i)
		temp = temp->next;
	delete temp;

	--counter;
}

template<typename T>
int list<T>::size()
{
	return counter;
}

template<typename T>
T& list<T>::operator[](const int index)
{
	int i = 0;
	node<T>* current = head;
	while (current) {
		if (i == index) return current->data;
		current = current->next;
		++i;
	}
}

template<typename T>
const list<T>& list<T>::operator=(const list<T>& second)
{
	clear();
	node<T>* temp = second.head;

	while (temp) {
		push_back(temp->data);
		temp = temp->next;
	}

	return *this;
}

template<typename T>
void list<T>::clear()
{
	while (counter) pop_front();
}

template<typename T>
bool list<T>::is_empty()
{
	return !counter;
}

template<typename T>
void list<T>::erase(int index)
{
	if (index == 0)
		pop_front();
	else {
		node<T>* previous = head;
		for (int i = 0; i < index - 1; ++i)
			previous = previous->next;

		node<T>* temp = previous->next;
		previous->next = temp->next;
		delete temp;
		--counter;
	}
}


