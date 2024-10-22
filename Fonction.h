//
// Created by duhamel on 21/10/24.
//

#ifndef FONCTION_H
#define FONCTION_H
/**
* Class Function est la description de de fonction de type (A->A) A est le Type
*
*/
template<typename Type>
class Function {

        public:
        virtual ~Function() = default;
        /**
        * @brief copie la class et tous ces menbre
*/
        [[nodiscard]] virtual Function<Type>* copy()=0;

        /**
        * @brief rencoie le resultat de f(x)
*/
        [[nodiscard]] virtual Type evaluation(Type x) =0;
        /**
        * @brief return a new function* that it is
*/
        [[nodiscard]] virtual Function<Type>* derive()=0;
        [[nodiscard]] friend Function<Type>* operator+(Function<Type>* f1, Function<Type>* f2);

};
template<typename Type>
class Constant:public Function<Type> {
private:
        Type value;
        public:
        explicit Constant(Type value):value(value){}
        [[nodiscard]] Type evaluation(Type x) override {
                return value;
        }
        [[nodiscard]] Function<Type>* derive() override {
                return new Constant<Type>(Type(0));
        }
        [[nodiscard]] Function<Type>* copy() override {
                return new Constant<Type>(value);
        }
        [[nodiscard]] Type getValue() {
                return value;
        }
        void setValue(Type value) {
                this->value = value;
        }
};
template<typename Type>
class Variable:public Function<Type> {
public:
        [[nodiscard]] Type evaluation(Type x) override {
                return x;
        }
        [[nodiscard]] Constant<Type>* derive() override {
                return new Constant<Type>(Type(1));
        }
        [[nodiscard]] Variable<Type>* copy() override {
                return new Variable<Type>(Type(0));
        }

};

template<typename Type>
class Addition:public Function<Type> {
        private:
        Function<Type>* first;
        Function<Type>* second;
        public:
        Addition(Function<Type> first,Function<Type> second):first(first),second(second){};
        [[nodiscard]] Type evaluation(Type x) override {
                return first->evaluation(x) + second->evaluation(x);
        }
        [[nodiscard]] Constant<Type>* derive() override {
                return new Addition<Type>(first->derive(), second->derive());
        }
        [[nodiscard]] Variable<Type>* copy() override {
                return new Addition<Type>(first->copy(), second->copy());
        }
        ~Addition() override{
                delete first;
                delete second;
        }
};
template<typename Type>
class Mutplication:public Function<Type> {
        private:
        Function<Type>* first;
        Function<Type>* second;
        public:
        Mutplication(Function<Type> first,Function<Type> second):first(first),second(second){};
        ~Mutplication() override{
                delete first;
                delete second;
        }
        [[nodiscard]] Type evaluation(Type x) override {
                return first->evaluation(x) * second->evaluation(x);
        }
        [[nodiscard]] Constant<Type>* derive() override {
                return new Addition<Type>(new Mutplication<Type>(first-derive(),second->copy()),
                        Mutplication<Type>(first->copy(),second->derive()));
        }
        [[nodiscard]] Variable<Type>* copy() override {
                return new Mutplication<Type>(first->copy(), second->copy());
        }
};
template<typename Type>
class Power:public Function<Type> {
private:
        int exponent;
        Function<Type>* menber;
public:
        Power(Function<Type>* menber,int exponent):exponent(exponent),menber(menber){}

        [[nodiscard]] Type evaluation(Type x) override {
                return pow(x, exponent);
        }
        [[nodiscard]] Function<Type>* derive() override {
                return new Mutplication<Type>(menber->derive(), new Power<Type>(menber->copy(), exponent-1));
        }
        [[nodiscard]] Power<Type>* copy() override {
                return new Power<Type>(menber->copy(), exponent);
        }
};
template<typename Type>
Function<Type> operator+(Function<Type>* f1,Function<Type>* f2 ) {
        return new Addition<Type>(f1->copy(),f2->copy());
}

#endif //FONCTION_H
