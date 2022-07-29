#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <string>

using namespace std;
using namespace std::rel_ops;

namespace Ctriplus
{
    class object;        
    using var=object;

    enum OBJECT_TYPE{UNDEFIEND,BOOL,CHAR,INT,LONG_LONG,DOUBLE,LONG_DOUBLE,STRING,ARRAY,OBJECT,FUNCTION};
    using function=object (*)(object argument);

    class object
    {
        OBJECT_TYPE type{};
        bool value_bool;
        char value_char{};
        int value_int{};
        long long value_ll{};
        double value_double{};
        long double value_long_double{};
        string value_str{};
        function func;
        //void * ptr;
        std::shared_ptr<vector<object>> vec_ptr{};
        std::shared_ptr<map<string, object> > map_ptr{};
        

        void convertToArray(){
           type=OBJECT_TYPE::ARRAY;  
            vec_ptr= std::make_shared< vector<object>>(); 
            if(map_ptr){map_ptr->clear();}
        }
        void convertToObject(){type=OBJECT_TYPE::OBJECT; map_ptr= std::make_shared< map<string,object>>(); if(vec_ptr){vec_ptr->clear();} }

        public:
            object(){type=OBJECT_TYPE::UNDEFIEND;  }
            //object(undefined_class value):type{OBJECT_TYPE::UNDEFIEND} {}
            object(bool value):value_bool{value},type{OBJECT_TYPE::BOOL} {}
            object(char value):value_char{value},type{OBJECT_TYPE::CHAR} {}
            object(int value):value_int{value},type{OBJECT_TYPE::INT} {}
            object(long long value):value_ll{value},type{OBJECT_TYPE::LONG_LONG} {}
            object(double value):value_double{value},type{OBJECT_TYPE::DOUBLE} {}
            object(long double value):value_long_double{value},type{OBJECT_TYPE::LONG_DOUBLE} {}
            object(string value):value_str{value},type{OBJECT_TYPE::STRING} {}
            object(const char* value):value_str{string(value)},type{OBJECT_TYPE::STRING} {}
            object(function func):func{func},type{OBJECT_TYPE::FUNCTION} {}
            object(vector<object> vec):type{OBJECT_TYPE::ARRAY} {                
                convertToArray();
                for(const auto& item:vec){ push_back(item); cout<<endl<<item;}
            }
            // object(initializer_list<object> vec):type{OBJECT_TYPE::ARRAY} {
            //     convertToArray();
            //     for(const auto& item:vec){ push_back(item);}
            // }

            //copy constructor
            // object(const object &obj): type{obj.type},value_int{obj.value_int},vec_ptr{obj.vec_ptr}, map_ptr{obj.map_ptr} { 
            //     cout<<"in copy cons"; 
            // }
            //copy assignment operator
            // object& operator=(const object& right_hand_side){}

            bool isUndefined(){return (type==OBJECT_TYPE::UNDEFIEND)?true:false;}


            bool operator<(const object& obj)const{ return value_int<obj.value_int; }
            bool operator<(int val)const{ return value_int<val; }
            bool operator==(const object& obj)const{ return value_int==obj.value_int; }
            bool operator==(int value)const{ return value_int==value; }

            object operator+(const object& obj)const{
                return obj;
            }
            object& operator++(){value_int++; return *this;}
            object& operator[](size_t index){
                if (type!=OBJECT_TYPE::ARRAY){convertToArray();}
                return (*vec_ptr).at(index);
            }
            object& subscriptor(string name){
                if (type!=OBJECT_TYPE::OBJECT){convertToObject(); }
                return (*map_ptr)[name];
            }
            object& operator[](const char* name){return subscriptor(string(name) );}
            object& operator[](string name){return subscriptor(name); }

            operator int() const { return value_int; }
            operator double() const { return value_double; }

            object operator()(object argument) ;

            string toString(const string padding)const;
            friend std::ostream& operator<<(std::ostream& stream, const object& obj);

            object& push_back(object obj){
                if (type!=OBJECT_TYPE::ARRAY)
                {
                    convertToArray();
                    //throw runtime_error{ "object is not an array"};
                }
                vec_ptr->push_back(obj);
                return *this;
            }
            //void ttt(var a,var b,var c=undefined,var d=undefined){}
    };

     class JSON{  
        public:      
            static object parseR(string text,int ind=0);
            static string getWithoutWhiteSpace(string text);
        public:
            static object parse(string text);
    };

    class Console{
        public:
            void log(object obj1,object obj2=object(),object obj3=object(),object obj4=object(),object obj5=object(),object obj6=object(),object obj7=object(),object obj8=object(),object obj9=object(),object obj10=object(),object obj11=object(),object obj12=object(),object obj13=object());
            //template <typename... Ts>
            //void log(Ts... args);
    };
    extern Console console;

    void print();
    template <typename T> void print(const T& t);
    template <typename First, typename... Rest> void print(const First& first, const Rest&... rest);

    //inline bool operator<(const object& obj,int val)const{ return obj.value_int<val; }

    /////////   print    //////////
    // Variadic function
    void print();
    template <typename T, typename... Types>
    void print(T var1, Types... var2)
    {
        cout << var1 << " "; 
        print(var2...);
    }
    ////////////////////////////////

    
}

#endif