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
	int sizeCounter;

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
		this->sizeCounter = 0;
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
		this->sizeCounter++;
	}

	void addToHead(int value) {
		this->head = new ListElement(value, head);
		this->sizeCounter++;
	}

	ListIterator* iterator() {
		return new ListIterator(this);
	}

	int size() {
		return this->sizeCounter;
	}

	void sort() {
		bool hasSwappes = true;
		int lastSortedElement = size() - 1;
		while (hasSwappes)
		{
			hasSwappes = false;
			ListElement* currentElement = head;
			ListElement* prevElement = head;
			for (int index = 0; index < lastSortedElement; index++)
			{
				if (currentElement->value > currentElement->next->value) {
					// обмен элементов местами
					ListElement* nextElement = currentElement->next;
					prevElement->next = currentElement->next;
					currentElement->next = currentElement->next->next;
					nextElement->next = currentElement;
					hasSwappes = true;

					// восстановление порядка предыдущий-текущий-следующий
					prevElement = nextElement;
					// восстановление головы
					if (currentElement == head) {
						head = nextElement;
					}
				}
				else 
				{
					prevElement = currentElement;
					currentElement = currentElement->next;
				}
			}
			lastSortedElement--;
		}
	}
};

int main()
{
	// создаем динамический связный список
	LinkedList* list = new LinkedList();
	list->addToEnd(5);
	list->addToEnd(2);
	list->addToEnd(3);
	list->addToEnd(1);
	list->addToEnd(4);

	list->sort();

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

