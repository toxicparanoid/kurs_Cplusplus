//подключаем макросы catch2
#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include <cstdint>

////проверяемая функция
//uint32_t factorial( uint32_t number ) {
//    return number <= 1 ? number : factorial(number-1) * number;
//}

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    //проверка
    bool Empty() { return m_size == 0; }

    //проверка
    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    //проверка
    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};


//юнит-тест
TEST_CASE( "List Testing") {
    List a;
    SECTION("Function PushBack") {
        INFO("Some of the elements didn't add");
        a.PushBack(1);
        CHECK(a.Size() == 1);
        a.PushBack(2);
        a.PushBack(3);
        a.PopBack();
        CHECK(a.Size() == 2);
        a.PushBack(5);
        CHECK(a.Size() == 3);
    }

    SECTION("Function PushFront") {
        INFO("Some of the elements didn't add");
        a.PushFront(5);
        a.PopFront();
        CHECK(a.Size() == 0);
        a.PushFront(3);
        a.PushFront(2);
        CHECK(a.Size() == 2);
        a.PopBack();
        CHECK(a.Size() == 1);
    }

    SECTION("Function PopBack") {
        a.PushFront(1);
        a.PushFront(2);
        a.PopFront();
        a.PopBack();
        CHECK(a.Size() == 0);
        /*a.PopBack();
        CHECK(a.Size() == 0);*/   //тест не пройдет проверку и будет выведено list is empty
    }
    
    SECTION("Function PopFront") {
        a.PushBack(1);
        a.PushBack(2);
        a.PopFront();
        a.PushBack(3);
        a.PopBack();
        a.PopFront();
        CHECK(a.Size() == 0);
        /*a.PopFront();
        CHECK(a.Size() == 0);*/   //тест не пройдет проверку и будет выведено list is empty
    }
}