from typing import *

from numpy import float64

#lets learn about datatypes in python

#Basic data types: int, float, str, bool
integer_var : int = 10
float_var : float = 10.5
string_var : str = "Hello, World!"
boolean_var : bool = True

pi : float64 = float64(3.141592653589793) #using numpy float64 type

#in case of string, what is the difference between single quote and double quote?
single_quote_str : str = 'Hello'
double_quote_str : str = "World"
#There is no difference in terms of data type, both are strings
#You can use single quotes inside double quotes and vice versa
mixed_str : str = "It's a beautiful day!"
#or
mixed_str2 : str = 'He said, "Hello!"'



#Complex data types: List, Tuple, Set, Dict
list_var : List[int] = [1, 2, 3, 4, 5]
#list is a mutable ordered collection of items, can contain duplicates
tuple_var : Tuple[str, int] = ("Age", 25)
#tuple is an immutable ordered collection of items, can contain duplicates
set_var : Set[str] = {"apple", "banana", "cherry"}
#Set is an unordered collection of unique items, no duplicates
dict_var : Dict[str, int] = {"one": 1, "two": 2, "three": 3}
#Dict is a collection of key-value pairs, keys are unique

#methods of each data type
list_var.append(6)  # List method
tuple_length : int = len(tuple_var)  # Tuple method
set_var.add("date")  # Set method
dict_var["four"] = 4  # Dict method

#can you mutate data?
list_var[0] = 10  # Yes, lists are mutable
#set_var[0] = "avocado"  # No, sets are unordered and do not support indexing
#tuple_var[0] = "Name"  # No, tuples are immutable
dict_var["one"] = 11  # Yes, dictionaries are mutable

#let's use type() function to check data types
print(type(integer_var))  # <class 'int'>
print(type(float_var))    # <class 'float'>
print(type(tuple_var))    # <class 'tuple'>
print(type(set_var))      # <class 'set'>
print(type(dict_var))     # <class 'dict'>
print(type(3 + 4.5j))  # <class 'complex'>
print(type(None))     # <class 'NoneType'>
print(type((1+1j)*(1-1j)), (1+1j)*(1-1j))  # <class 'complex'>


