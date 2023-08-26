#include <iostream>
using namespace std;
template<class T>
class Stack
{
	template<class T> // Внутренняя структура
	struct Node
	{
		T data;
		Node<T>* next;
	};
	Node<T>* head; // Указатель на голову списка
	unsigned int size; // Размер стека

	// Для получения копии стека во внутренние данные
	void Copy(Node<T>* _head)
	{
		//проверка
		if(_head == nullptr)
			return;
			
		//Доп переменные
		Node<T>* p = _head; //Указатель на вершину стека
		bool f_first = true;
		Node<T>* p2 = nullptr;
		Node<T>* p3 = nullptr;

		//Цикл обхода стека
		size = 0; //кол-во элементов в стеке 
		while (p != nullptr)
		{
			//Выделяем память в заполняем её (чем-то)
			try
			{
				p2 = new Node<T>;
				p2->data = p->data;
				p2->next = nullptr;
				
				//проверка добавляется ли превый элемент
				if (f_first) 
				{
					// если добавился
					head = p2;
					p3 = p2;
					f_first = false;
				}
				else
				{
					//Если добавился не первый то устанвить указатель next
					p3->next = p2;
					p3 = p3->next;
				}
				size++;

				//переход на новый элемент
				p = p->next;
			}
			catch (bad_alloc e)
			{
				cout << e.what();
			}
		}
	}

	//Метод для освобожниеня памяти
	void Free()
	{
		//Указатель на вершину стека
		Node<T>* p = head;
		// Обход стека и освобождение памяти 
		while (p != nullptr)
		{
			head = head->next;
			delete p;
			p = head;
			size--; //так и не понял нужна она или нет.
		}
	}
public:
	//Создать пустой стек
	Stack()
	{
		head = nullptr;
		size = 0;
	}

	//Добавить элемент в стек
	void Push(T item)
	{
		try 
		{
			//Если первый элемент
			if (size == 0)
			{
				head = new Node<T>;
				head->next = nullptr;
				head->data = item;
			}
			else
			{
				//Если не первый элемент
				//Создаем новую ячейку и заполняем её
				Node<T>* p2 = new Node<T>;
				p2->data = item;
				p2->next = nullptr;

				//Направить указатели
				p2->next = head;
				head = p2;
			}
			//Увеличить количество элементов в стеке
			size++;
		}
		catch (bad_alloc e)
		{
			cout << e.what();
		}
	}

	// Вытянуть элемент из стека
		T Pop()
	{
		// 1. Проверка
		if (size == 0)
			return 0;

		// 2. Запомнить элемент, который будет возвращаться
		T item = head->data;

		// 3. Установить дополнительный указатель на вершину
		Node<T>* p = head;

		// 4. Переместить вершину
		head = head->next;

		// 5. Освободить память, выделенную под вершину стека
		delete p;

		// 6. Уменьшить количество элементов в стека
		size--;

		// 7. Вернуть элемент
		return item;
	}

		// Вывод стека на экран
		void Show(string msg)
		{
			Node<T>* p = head;
			cout << msg << " => ";
			while (p != nullptr)
			{
				cout << p->data << "  ";
				p = p->next;
			}
			cout << endl;
		}

		// Освобождение памяти - деструктор
		~Stack()
		{
			Free();
		}

		// Возвращает true, если стек пуст
		bool IsEmpty()
		{
			return size == 0;
		}

		// Вернуть размер стека
		int Size() const { return size; }

		// Конструктор копирования this<=obj
		Stack(const Stack<T>& obj)
		{
			// Обойти стек obj и сделать копию
			Copy(obj.head);
		}

		// Оператор присваивания копированием
		Stack<T>& operator=(const Stack<T>& obj)
		{
			if (this != &obj)
			{
				if (size > 0)
					Free();
				Copy(obj.head);
			}
			return *this;
		}
};

int main()
{
	Stack<int> S1;
	Stack<int> S3;
	S3 = S1;

	if (S3.IsEmpty())
		cout << "+";
	else
		cout << "-";

	S1.Push(10);
	S1.Push(15);
	S1.Push(20);
	cout << S1.Size() << endl;
	S1.Show("S1");

	Stack<int> S2 = S1;
	S2.Show("S2");

	S3 = S2;
	S3.Show("S3");

	if (S3.IsEmpty())
		cout << "+";
	else
		cout << "-";
}
