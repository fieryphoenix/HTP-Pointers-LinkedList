// LinkedList.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>

using namespace std;

struct LinkedList {
private:
	// элемент в списке. каждый элемент хранит значение и указатель на следующий элемент
	struct ListElement {
		int value;
		ListElement *next;

		ListElement(int& value, ListElement *next) {
			this->value = value;
			this->next = next;
		}
	};

	ListElement* head;
	int size;

public:
	// проходчик по списку. умеет сообщать есть ли следующее значение и возвращать текущее
	struct ListIterator {
	private:
		LinkedList *list;
		ListElement* current;

	public:
		ListIterator(LinkedList *list) {
			this->list = list;
			this->current = list->head;
		}

		bool hasNext() {
			return this->current != NULL;
		}

		int next() {
			int value = this->current->value;
			this->current = current->next;
			return value;
		}
	};

	LinkedList() {
		this->head = NULL;
		this->size = 0;
	}

	// переопределяем удаление списка - необходимо очистить память, выделенную под каждый элемент
	~LinkedList() {
		ListElement* element = head;
		while (element != NULL) {
			ListElement* next = element->next;
			delete element;
			element = next;
		}
	}

	void addToEnd(int value) {
		ListElement* newElement = new ListElement(value, NULL);
		if (head == NULL) {
			head = newElement;
		}

		ListElement* lastElement = head;
		while (lastElement->next != NULL) {
			lastElement = lastElement->next;
		}

		if (newElement != head) {
			lastElement->next = newElement;
		}
	}

	ListIterator* iterator() {
		return new ListIterator(this);
	}
};

int main()
{
	// создаем динамический связный список
	LinkedList* list = new LinkedList();
	list->addToEnd(10);
	list->addToEnd(4);

	// проходим по связному списку и выводим значения
	LinkedList::ListIterator* iterator = list->iterator();
	while (iterator->hasNext()) {
		cout << iterator->next() << endl;
	}

	// очищаем память
	delete iterator;
	delete list; 

	system("pause");
	return 0;
}

