#include <iostream>


// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

template <typename T>
void flatten(const Array<T>& array, std::ostream& out) {
   for (int i = 0; i < array.size(); ++i) {
       out << array[i] << " ";
   }
}

template <typename T>
void flatten(const Array<Array<T>>& array, std::ostream& out) {
    for (int i = 0; i < array.size(); ++i) {
        flatten(array[i], out);
    }
}

//template <typename T>
//void traversingArray(const Array<T>& items, std::ostream& out) {
//    for (int i = 0; i < items.size(); i++) {
//        if (items[i].size()) {
//            traversingArray<typeid(items[i].name)>(items[i]);
//        }
//        else {
//            for (auto item: items) {
//                out << item;
//            }
//        }
//    }
//}