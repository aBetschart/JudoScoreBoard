/*
 * Stack.h
 *
 *  Created on: 19.05.2015
 *      Author: rbondere
 */

#ifndef STACK_H_
#define STACK_H_

template<typename ElemType, int size = 10>
class Stack
{
public:
    Stack():
        top(0), error(false)
{
}
    // Default-Konstruktor

    void push(const ElemType& e)
    {
        error = top == size;
        if (!error)
        {
            elems[top] = e;
            ++top;
        }
    }
    // legt ein Element auf den Stack, falls der Stack noch nicht voll ist
    // wasError() gibt Auskunft, ob push() erfolgreich war

    ElemType pop()
    {
        error = top == 0;
        if (!error)
        {
            --top;
        }
        return elems[top];
    }
    // nimmt ein Element vom Stack, falls der Stack nicht leer ist
    // wasError() gibt Auskunft, ob pop() erfolgreich war

    const ElemType& peek() const
    {
        error = top == 0;
        return elems[top - 1];
    }
    // liest das oberste Element vom Stack, falls der Stack nicht leer ist
    // wasError() gibt Auskunft, ob peek() erfolgreich war

    bool isEmpty() const
    {
        return top == 0;
    }
    // return: true: Stack ist leer
    //         false: sonst

    bool wasError() const
    {
        return error;
    }
    // return: true: Operation war fehlerhaft
    //         false: sonst

private:
    ElemType elems[size]; // Speicher fuer Speicherung des Stacks
    int top;              // Arrayindex des naechsten freien Elements
    mutable bool error;   // true: Fehler passiert; false: sonst
    // mutable: auch const-Methoden koennen dieses Attribut setzen
};

#endif // STACK_H_
