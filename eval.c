#include "types.h"
#include "array.h"
#include <stdio.h>
#include <math.h>

DEFINE_ARRAY(char, string);
DEFINE_SLICE(char, string);

double
double_from_string_slice(string_slice str) {
	if(str.size == 0) {
		return NAN;
	}
	bool negative = str.data[0] == '-';
	int exponent = 0;
	u8_array numbers = {};
	bool decimal = false;
	for(int i = negative; i < str.size; i++) {
		if(str.data[i] == '.' && decimal == false) {
			exponent = i - 1;
			decimal = true;
		} else {
			if(str.data[i] < '0' || str.data[i] > '9') {
				array_free(&numbers);
				return NAN;
			}
			array_push(&numbers, str.data[i] - '0');
		}
	}
	if(!decimal){
		exponent = numbers.size - 1;
	}
	double result = 0;
	for(int i = 0; i < numbers.size; i++) {
		result += numbers.data[i]*pow(10,exponent);
		exponent--;
	}
	array_free(&numbers);
	if(negative) {
		return -result;
	}
	return result;
}

//Order	Operator:
//2	^
//1	*,/
//0	+,-
double
eval(string_slice expression, int order) {
	string_slice slice_a = {};
	string_slice slice_b = {};
	switch(order) {
		case 0:
			for(int i = expression.size - 1; i >= 0; i--)
			{
				if(expression.data[i] == '+' || expression.data[i] == '-') {
					slice_a.data = expression.data;
					slice_a.size = i;
					slice_b.data = &expression.data[i+1];
					slice_b.size = expression.size - (i+1);
					if(expression.data[i] == '+') {
						return eval(slice_a, 0) + eval(slice_b, 0);
					} else if(i != 0 && expression.data[i-1] >= '0' && expression.data[i-1] <= '9') {
						return eval(slice_a, 0) - eval(slice_b, 0);
					}
				}
			}
		case 1:
			for(int i = expression.size - 1; i >= 0; i--)
			{
				if(expression.data[i] == '*' || expression.data[i] == '/') {
					slice_a.data = expression.data;
					slice_a.size = i;
					slice_b.data = &expression.data[i+1];
					slice_b.size = expression.size - (i+1);
					if(expression.data[i] == '*') {
						return eval(slice_a, 1) * eval(slice_b, 1);
					} else {
						return eval(slice_a, 1) / eval(slice_b, 1);
					}
				}
			}
		case 2:
			for(int i = 0; i < expression.size; i++)
			{
				if(expression.data[i] == '^') {
					slice_a.data = expression.data;
					slice_a.size = i;
					slice_b.data = &expression.data[i+1];
					slice_b.size = expression.size - (i+1);
					return pow(eval(slice_a, 2),  eval(slice_b, 2));
				}
			}
		default: return double_from_string_slice(expression);
	}
}

int
main(int argc, char *argv[]) {
	if(argc < 2) {
		return 1;
	}
	int i = 0;
	char c = argv[1][i];
	string_array input = {};
	while(c != '\0') {
		array_push(&input, c);
		i++;
		c = argv[1][i];
	}
	string_slice input_slice = {};
	input_slice.data = input.data;
	input_slice.size = input.size;
	double output = eval(input_slice, 0);
	array_push(&input, '\0');
	printf("%s = %.10g\n", input.data, output);
	array_free(&input);
}
