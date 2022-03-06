#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

//using namespace std;
class Timer
{
private:
    int time;
public:
    Timer();
    virtual ~Timer();
    void start();
    int end();
};
Timer::Timer()
{
    time = 0;
}

Timer::~Timer()
{
}
void Timer::start() {
    time = clock();
}
int Timer::end() {
    time = clock() - time;
    return time;
}
class Object
{
protected:
    std::string class_name;
public:
    std::string get_class_name() {
        return class_name;
    }
    Object();
    virtual ~Object();
};
Object::Object()
{
    class_name = "Object";
}

Object::~Object()
{
    printf("~Object() ");

}
class Point : public Object {
private:
    int x; int y;
public:
    Point() {
        x = 0;
        y = 0;
        class_name = "Point";
    };
    Point(int x, int y) {
        this->x = x;
        this->y = y;
        class_name = "Point";
    };
    Point(Point& p) {
        this->x = p.x;
        this->y = p.y;
        class_name = "Point";
    };
    ~Point() {
        printf("~Point() ");
    };
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    void add(int x, int y) {
        this->x = this->x + x;
        this->y = this->y + y;
    }
};
class Section : public Object
{
public:
    Section();
    Section(Point* p1, Point* p2);
    Section(Section* sec);
    ~Section();
    double lenght() {
        return sqrt((this->p2->getx() - this->p1->getx()) * (this->p2->getx() - this->p1->getx()) - ((this->p2->gety() - this->p1->gety()) * (this->p2->gety() - this->p1->gety())));
    }
protected:
    Point* get_f();
    Point* get_l();
private:
    Point* p1;
    Point* p2;
};
class Circle : public Point
{
public:
    Circle();
    Circle(int x, int y, int r);
    ~Circle();
    void set_radius(int r) {
        this->radius = r;
    }
private:
    int radius;
};
class Ellipsis : public Object
{
public:
    Ellipsis();
    ~Ellipsis();

private:
    Point* p1;
    Point* p2;
    Point* p3;
};

Ellipsis::Ellipsis()
{
    class_name = "Ellipsis";
    p1 = new Point();
    p2 = new Point();
    p3 = new Point();
}

Ellipsis::~Ellipsis()
{
    printf("~Ellipsis() ");
    delete p1;
    delete p2;
    delete p3;
}
Circle::Circle() :Point()
{
    class_name = "Circle";
    radius = 0;
}
Circle::Circle(int x, int y, int r) : Point(x, y)
{
    class_name = "Circle";
    if (r >= 0) {
        radius = r;
    }
    else {
        radius = 0;
    }
}

Circle::~Circle()
{
    printf("~Circle() ");
}
Section::Section()
{
    class_name = "Section";
    p1 = new Point();
    p2 = new Point();
}

Section::Section(Point* p1, Point* p2)
{
    class_name = "Section";
    (this->p1) = p1;
    (this->p2) = p2;
}
Point* Section::get_f() {
    return p1;
}
Point* Section::get_l() {
    return p2;
}
Section::Section(Section* sec)
{
    class_name = "Section";
    p1 = sec->get_f();
    p2 = sec->get_l();
}

Section::~Section()
{
    printf("~Section() ");
    delete p1;
    delete p2;
}
struct node
{
    Object* ptr;
    int id;
    node* left;
    node* right;
    node() {
        ptr = NULL;
    }
    node(Object*& obj) {
        ptr = obj;
    };
    ~node() {
        printf("\n ~node id = %d ", id);
    }
};
class Storage
{
private:
    node* first;
    //node* last;
public:
    node* get_first();
    node* get_last();
    node* get_element(int i);
    int size();
    int amount_elements(int size);
    int amount_elements();
    void set_object(int i, Object* obj);
    void del_element(int i);
    void del_object(int i);
    void add_element(Object* obj);
    void add_element(int i, Object* obj);
    Object* get_object(int i);
    void show();
    node* next(node* element);
    node* prev(node* element);
    Storage();
    Storage(int k);
    Storage(Object* obj);
    ~Storage();
};
Object* Storage::get_object(int i) {
    return (this->get_element(i))->ptr;
};
Storage::Storage()
{
    first = new node;
    first->left = first;
    first->right = first;
    first->id = 0;
}
Storage::Storage(Object* obj) {
    //printf("\nstorage()\n%d\n%d", &first, &last);
    first = new node(obj);
    first->left = first;
    first->right = first;
    first->id = 0;
    //last = new node;
    //first->left = last;
    //last->right = first;
    //last->left = first;
    //first->right = last;
    //int l = 0;

    //*(first->left) = *last;
    //*(last->right) = *first;
    //*(last->left) = *first;
    //*(first->right) = *last;
    //first->id = 0;
    //last->id = 1;
}
Storage::Storage(int k) {
    first = new node;
    first->left = first;
    first->right = first;
    first->id = 0;
    node* element = first;
    while (k - 1 > 0) {
        element->right = new node();
        element->right->left = element;
        element->right->id = element->id + 1;
        element = element->right;
        k--;
    }
    element->right = first;
    first->left = element;
}
Storage::~Storage()
{
    int size = this->size();
    node* element = first;
    node* del_element = element;
    Object* obj;
    while (size - 1 > 0) {
        size--;
        del_element = element;
        element = element->right;
        obj = del_element->ptr;
        if (obj != NULL) {
            delete obj;
        }
        delete del_element;
    }
    obj = element->ptr;
    if (obj != NULL) {
        delete obj;
    }
    delete element;
}
//возвращает первый элемент
node* Storage::get_first() {
    return first;
};
//возвращает следующий элемент
node* Storage::next(node* element) {
    return element->right;
}
//возвращает предыдущий элемент
node* Storage::prev(node* element) {
    return element->left;
}
//возвращает последний элемент
node* Storage::get_last() {
    return this->prev(first);
};
//возвращает размер хранилища
int Storage::size() {
    int i = 1;
    while (this->get_element(i)->id != 0) {
        i++;
    }
    return i;
}
//возвращает количество элементов в хранилище
int Storage::amount_elements(int size) {
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (this->get_element(i)->ptr != NULL) {
            k++;
        }
    }
    return k;
}
int Storage::amount_elements() {
    return this->amount_elements(this->size());
}
void Storage::del_element(int i) {

    int size = this->size();
    if (i <= size) {
        if (size == 0) {

        }
        else if (size == 1) {
            first->ptr = NULL;
        }
        else {
            node* element = this->get_element(i);
            if (element->ptr != NULL) {
                delete element->ptr;
                element->ptr = NULL;
            }
            while (element->right->id != 0) {
                element->ptr = element->right->ptr;
                element = element->right;
            }
            element->left->right = element->right;
            element->right->left = element->left;
            delete element;
        }
    }
    //node* element = this->get_element(i);
    //int size = this->storage_size();
    //if (size <= 1) {
    //    element->ptr = NULL;
    //}
    //else if (i == 0) {
    //    element->ptr = element->right->ptr;
    //    del_element(i + 1);
    //}
    //else if (i < size) {
    //    element->right->left = element->left;
    //    element->left->right = element->right;
    //    node* next_element = element->right;
    //    delete element;
    //    while (next_element->id != 0) {
    //        next_element->id--;
    //        next_element = next_element->right;
    //    }
    //}
}
void Storage::del_object(int i) {
    int size = this->size();
    node* element = this->get_element(i);
    if (i <= size) {
        Object* obj = element->ptr;
        if (obj != NULL) {
            delete obj;
        };
        element->ptr = NULL;
    }
}
//функция для вывода информации о хранилище
void Storage::show() {
    int storage_size = this->size();
    int amount_elements = this->amount_elements(storage_size);
    printf("[=Storage-info============================================================================]\n");
    printf("| Элементы внутри хранилища:\n");
    node* element = first;
    Object* obj;
    int id = 0;
    std::string s;
    for (int i = 0; i < storage_size; i++) {
        obj = element->ptr;
        id = element->id;
        if (id / 10 == 0) {
            printf("| %d    | ", id);
        }
        else if (id / 100 == 0) {
            printf("| %d   | ", id);
        }
        else if (id / 1000 == 0) {
            printf("| %d  | ", id);
        }
        else {
            printf("| %d | ", id);
        }
        if (obj != NULL) {
            Point* p = dynamic_cast<Point*>(obj);
            Circle* c = dynamic_cast<Circle*>(obj);
            Ellipsis* e = dynamic_cast<Ellipsis*>(obj);
            Section* sec = dynamic_cast<Section*>(obj);
            s = (element->ptr)->get_class_name();
            std::cout << s;
            if ((p != NULL) && (c == NULL)) {
                printf("    ");
            }
            else if (c != NULL) {
                printf("   ");

            }
            else if (e != NULL) {
                printf(" ");
            }
            else if (sec != NULL) {
                printf("  ");
            }

        }
        else {
            printf("         ");
        }
        element = element->right;
        if ((i + 1) % 5 == 0) {
            printf("|\n");
        }
    }
    //Section 1
    //Point 3 
    //Circle 2
    //Ellipsis 0

    printf("\n[=========================================================================================]");
    printf("\n| Размер хранилища: %d\n| Элементов в хранилище: %d\n", storage_size, amount_elements);
    printf("[=========================================================================================]\n");
}
//возвращает элемент под id = i
node* Storage::get_element(int i) {
    node* element = first;
    while (i > 0) {
        element = element->right;
        i--;
    }
    return element;
};
//меняет объект под id = i на новый
void Storage::set_object(int i, Object* obj) {
    node* element = this->get_element(i);
    if (element->ptr != NULL) {
        delete element->ptr;
    }
    element->ptr = obj;
}
//добавляет новый элемент
void Storage::add_element(int i, Object* obj) {
    node* new_element = this->get_element(i);
    if (new_element->ptr != NULL) {
        node* next_element = new node(new_element->ptr);
        new_element->ptr = obj;

        next_element->right = new_element->right;
        next_element->left = new_element;
        new_element->right->left = next_element;
        new_element->right = next_element;
        next_element->id = new_element->id + 1;
        next_element = next_element->right;
        while (next_element->id != 0) {
            next_element->id++;
            next_element = next_element->right;
        }
    }
    else {
        new_element->ptr = obj;
    }
    //node* element = this->get_element(i);
    //if (element->ptr != NULL) {
    //    node* prev_element = element->left;
    //    node* next_element = element;
    //    node* new_element = new node(obj);
    //    new_element->right = next_element;
    //    new_element->left = prev_element;
    //    prev_element->right = new_element;
    //    next_element->left = next_element;
    //    new_element->id = element->id;
    //    element->id++;
    //    element = element->right;
    //    while (element->id!= 0) {
    //        element->id++;
    //        element = element->right;
    //    }
    //}
    //else {
    //    element->ptr = obj;
    //}
};
void Storage::add_element(Object* obj) {
    if (first->ptr == NULL) {
        first->ptr = obj;
    }
    else {
        node* element = first->right;
        while ((element->ptr != NULL) && (element->id != 0)) {
            element = element->right;
        }
        if (element->ptr == NULL) {
            element->ptr = obj;
        }
        else if ((element->ptr != NULL) && (element->id == 0)) {
            node* last_element = first->left;
            node* new_element = new node(obj);
            new_element->right = first;
            new_element->left = last_element;
            last_element->right = new_element;
            first->left = new_element;
            new_element->id = last_element->id + 1;
        }
    }
    /*int i = 0;
    int size = this->storage_size();
    node* element = first;

    while ((i < size)&&(element->ptr!=NULL)) {
        element = element->right;
        i++;
    }
    if (element->ptr == NULL) {
        element->ptr = obj;
        return;
    }
    else {
        while ((element->ptr != NULL) && (element->id != size - 1)) {
            element = element->right;
        }
        add_element(size - 1, obj);
    }*/

    //add_element(element->id, obj);

    //if (first->ptr == NULL) {
    //  first->ptr = obj;
    //}
    //else {
    //    node* prev_last_element = this->get_last();
    //    node* new_element = new node(obj);
    //    prev_last_element->right = new_element;
    //    new_element->left = prev_last_element;
    //    new_element->right = first;
    //    first->left = new_element;
    //    new_element->id = prev_last_element->id + 1;
    //}
    //if (first->ptr == NULL) {
    //    first->ptr = obj;
    //
    //}
    //else {
    //    node* left_element = (this->last)->left;
    //    node* new_element = new node(obj);
    //    (this->last)->left = new_element;
    //    new_element->right = this->last;
    //    new_element->left = left_element;
    //    left_element->right = new_element;
    //    new_element->id = last->id;
    //    last->id++;
    //}
};

int randomizer(int min, int max) {
    time_t sec;
    sec = time(NULL);
    int r = (rand() * sec) % (max - min) + min;
    return r;
}
int randomizer(int max) {
    return randomizer(0, max);
}
Object* create_rand_obj() {
    int v = randomizer(4);
    switch (v)
    {
    case 0: {
        int x = randomizer(-10, 10);
        int y = randomizer(-10, 10);
        return new Point(x, y);
        break; }
    case 1: {
        return new Section();
        break;
    }
    case 2: {
        int x = randomizer(-10, 10);
        int y = randomizer(-10, 10);
        int r = randomizer(-10, 10);
        return new Circle(x, y, r);
        break;
    }
    case 3: {
        return new Ellipsis();
        break;
    }
    default: {
        return NULL;
        break;
    }
    }
}
void rand_obj_method(Object* obj) {
    Point* p = dynamic_cast<Point*>(obj);
    if (p != NULL) {
        if (randomizer(2) % 2 == 0) {
            int x = randomizer(-10, 10);
            int y = randomizer(-10, 10);
            p->add(x, y);
            printf("add(%d,%d)\n", x, y);
        }
        else {
            int x = randomizer(-10, 10);
            int y = randomizer(-10, 10);
            p->set(x, y);
            printf("set(%d,%d)\n", x, y);
        }

    }
    Circle* c = dynamic_cast<Circle*>(obj);
    if (c != NULL) {
        int r = randomizer(10);
        if (randomizer(2) % 2 == 0) {
            c->set_radius(r);
            printf(" set_radius(%d)\n", r);
        }
        else {
            int x = randomizer(-10, 10);
            int y = randomizer(-10, 10);
            c->set(x, y);
        }
    }
    Ellipsis* e = dynamic_cast<Ellipsis*>(obj);
    if (e != NULL) {
        std::cout << "get_class_name() " << e->get_class_name() << "\n";
    }
    Section* sec = dynamic_cast<Section*>(obj);
    if (sec != NULL) {
        if (randomizer(2) % 2 == 0) {
            printf("sec->lenght = %d.0\n", sec->lenght());
        }
        else {
            std::cout << "get_class_name() " << sec->get_class_name() << "\n";
        }
    }

}
void test(Storage* massive, int amount) {
    int i = 0;
    int v = 0;
    int size = massive->size();
    int k = 0;
    Object* obj;
    while (i < amount) {
        v = randomizer(5);
        //Object* obj = create_rand_obj();
        switch (v)
        {
        case 0:
            obj = create_rand_obj();
            massive->add_element(obj);
            std::cout << "\nadd_element(" << obj->get_class_name() << ")\n";
            //(*massive).show();

            break;
        case 1:
            size = massive->size();
            k = randomizer(size);
            std::cout << "\ndel_element(" << k << ")\n";
            massive->del_element(k);
            //(*massive).show();
            break;
        case 2:
            obj = create_rand_obj();
            size = massive->size();
            k = randomizer(size);
            massive->set_object(k, obj);
            std::cout << "\nset_object(" << k << "," << obj->get_class_name() << ")\n";
            //(*massive).show();
            break;
        case 3:
            size = massive->size();
            k = randomizer(size);
            massive->del_object(k);
            std::cout << "\ndel_object(" << k << ")\n";
            //(*massive).show();
            break;
        case 4:
            size = massive->size();
            k = randomizer(size);
            obj = massive->get_object(k);
            if (obj != NULL) {
                std::cout << "\nrand_obj_method " << obj->get_class_name() << " ";
                rand_obj_method(obj);
            }
            else {
                printf("get_object(%d)=null", k);
            }
            //(*massive).show();
            break;
        default:
            break;
        }
        i++;
    }
}
int main() {
    int time;
    setlocale(LC_ALL, "Russian");
    Storage* massive = new Storage(10);
    (*massive).show();
    int v;
    int i = 0;
    for (int i = 0; i < massive->size(); i++) {
        massive->add_element(create_rand_obj());
    }
    (*massive).show();
    printf("\nМассив из 10 элементов создан.\nНажмите чтобы начать тест из 100 случайных методов.\n");
    _getch();
    Timer clock;
    clock.start();
    test(massive, 100);
    float sec1 = clock.end() / 1000;
    massive->show();
    printf("\nТест завершён.\nВремя работы программы: %.3f\n", sec1);
    printf("\n\nНажмите чтобы начать тест из 1000 случайных методов\n");
    _getch();
    clock.start();
    test(massive, 1000);
    float sec2 = clock.end() / 1000;
    massive->show();
    printf("\nТест завершён.\nВремя работы программы: %.3f\n", sec2);
    printf("\n\nНажмите чтобы начать тест из 10000 случайных методов\n");
    _getch();
    clock.start();
    test(massive, 10000);
    float sec3 = clock.end() / 1000;
    massive->show();
    printf("\nТест завершён.\nВремя работы программы: %.3f\n", sec3);
    _getch();

    delete massive;
    return 0;
}