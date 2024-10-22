//
// Created by duhamel on 21/10/24.
//

#ifndef FONCTION_H
#define FONCTION_H
/**
* Class Fonction est la description de de fonction de type (A->A) A est le Type
*
*/
template<typename Type>
class Fonction {

        public:
        virtual ~Fonction() = default;
        /**
        * @brief copie la class et tous ces menbre
*/
        [[nodiscard]] virtual Fonction<Type>* copy()=0;

        /**
        * @brief rencoie le resultat de f(x)
*/
        [[nodiscard]] virtual Type evaluation(Type x) =0;
        /**
        * @brief
*/
        [[nodiscard]] virtual Fonction<Type>* derive()=0;

};
template<typename Type>
class Constant:public Fonction<Type> {
private:
        Type value;
        public:
        explicit Constant(Type value):value(value){}
        [[nodiscard]] Type evaluation(Type x) override {
                return value;
        }
        [[nodiscard]] Fonction<Type>* derive() override {
                return new Constant<Type>(Type(0));
        }
        [[nodiscard]] Fonction<Type>* copy() override {
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
class Variable:public Fonction<Type> {
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
class Addition:public Fonction<Type> {
        private:
        Fonction<Type>* first;
        Fonction<Type>* second;
        public:
        Addition(Fonction<Type> first,Fonction<Type> second):first(first),second(second){};
        [[nodiscard]] Type evaluation(Type x) override {
                return first->evaluation(x) + second->evaluation(x);
        }
        [[nodiscard]] Constant<Type>* derive() override {
                return new Addition<Type>(first->derive(), second->derive());
        }
        [[nodiscard]] Variable<Type>* copy() override {
                return new Addition<Type>(first->copy(), second->copy());
        }
        ~Addition() {
                delete first;
                delete second;
        }
};
template<typename Type>
class Mutplication:public Fonction<Type> {
        private:
        Fonction<Type>* first;
        Fonction<Type>* second;
        public:
        Mutplication(Fonction<Type> first,Fonction<Type> second):first(first),second(second){};
        ~Mutplication() {
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
class Power:public Fonction<Type> {
private:
        int exponent;
        Fonction<Type>* menber;
public:
        Power(Fonction<Type>* menber,int exponent):exponent(exponent),menber(menber){}

        [[nodiscard]] Type evaluation(Type x) override {
                return pow(x, exponent);
        }
        [[nodiscard]] Fonction<Type>* derive() override {
                return new Mutplication<Type>(menber->derive(), new Power<Type>(menber->copy(), exponent-1));
        }
        [[nodiscard]] Power<Type>* copy() override {
                return new Power<Type>(menber->copy(), exponent);
        }
};

#endif //FONCTION_H
