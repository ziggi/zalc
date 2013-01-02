/*
 *
 *     Copyright (C) 2012 ziggi
 *     Using GNU GPL v3 license
 *
 */

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include "config.h"

const int
	window_height = 180,
	window_width = 290,
	
	b_padding = 3,
	b_x = 20, b_y = 140,
	
	b_num_height = 24,
	b_num_width = 48,
	
	b_eq_height = b_num_height * 2 + b_padding,
	b_eq_width = 48,
	
	input_x = 20, input_y = 20,
	input_height = 30;

int inp_step = 0, dotted = 0;
long double first_num = 0;

char calc_op[2] = {0};
Fl_Input *input;


void ac_b_click()
{
	input->value("0");
	inp_step = 0;
	dotted = 0;
	calc_op[0] = 0;
}

int eq_b_click()
{
	if (inp_step == 0) {
		return 0;
	}
	int other_div = 0;
	long double result;
	long double second_num = atof(input->value());
	
	switch (calc_op[0]) {
		case '+': result = first_num + second_num; break;
		case '-': result = first_num - second_num; break;
		case '*': result = first_num * second_num; break;
		case '/':
			if (first_num == 0 && second_num == 0) {
				other_div = 1;
				input->value("nan");
			} else if (second_num == 0) {
				other_div = 1;
				input->value("inf");
			} else {
				result = first_num / second_num;
			}
			break;
	}
	if (other_div == 0) {
		char output[128];
		sprintf(output, "%Lf", result);
		input->value(output);
	}
	inp_step = 0;
	first_num = 0;
	return 1;
}

int num_b_click(Fl_Button *button, void* = 0)
{
	if (inp_step == 0 || inp_step == 2 || strcmp(input->value(), "0") == 0) {
		input->value("");
		inp_step++;
	}
	
	char str[128] = {0};
	strcat(str, input->value());
	strcat(str, button->label());
	input->value(str);
	return 1;
}

void do_b_click(Fl_Button *button, void* = 0)
{
	if (inp_step == 3) {
		eq_b_click();
	}
	first_num = atof(input->value());
	calc_op[0] = (char)*button->label();
	inp_step = 2;
	dotted = 0;
}

void dot_b_click(Fl_Button *button, void* = 0)
{
	if (inp_step == 0 || inp_step == 2) {
		input->value("0.");
		dotted = 1;
		inp_step = 1;
		return;
	}
	if (dotted != 1) {
		dotted = 1;
		char str[128] = {0};
		strcat(str, input->value());
		strcat(str, ".");
		input->value(str);
	}
}

int main(int argc, char **argv)
{
	Fl_Window *window = new Fl_Window(window_width, window_height);
	window->label("Zalc v"PACKAGE_VERSION);
	
	int button_x = b_x,
		button_y = b_y;
	
	// create dot button
	Fl_Button *button_dot = new Fl_Button(button_x + b_num_width + b_padding, button_y, b_num_width, b_num_height, ".");
	button_dot->callback((Fl_Callback*)dot_b_click);
	button_dot->box(FL_GTK_UP_BOX);
	
	// create digit button
	Fl_Button *num_b[10];
	//char buffer[20];
	for (int i = 0, k = 0; i < 10; i++) {
		if (i > 1) {
			button_x += b_padding + b_num_width;
		}
		if (i == 1 || ++k == 3) {
			k = 0;
			button_y -= b_num_height + b_padding;
			button_x = b_x;
		}
		
		num_b[i] = new Fl_Button(button_x, button_y, b_num_width, b_num_height);
		num_b[i]->callback((Fl_Callback*)num_b_click);
		num_b[i]->box(FL_GTK_UP_BOX);
		
		// does not work on fltk 1.3
		/*sprintf(buffer, "%d", j);
		num_b[i]->label(buffer);*/
	}
	num_b[0]->label("0");
	num_b[1]->label("1");
	num_b[2]->label("2");
	num_b[3]->label("3");
	num_b[4]->label("4");
	num_b[5]->label("5");
	num_b[6]->label("6");
	num_b[7]->label("7");
	num_b[8]->label("8");
	num_b[9]->label("9");
	
	// create doing button
	Fl_Button *do_b[4];
	button_x += b_padding + b_num_width;
	button_y = b_y;
	for (int i = 0; i < 4; i++) {
		do_b[i] = new Fl_Button(button_x, button_y, b_num_width, b_num_height);
		do_b[i]->callback((Fl_Callback*)do_b_click);
		do_b[i]->box(FL_GTK_UP_BOX);
		
		button_y -= b_num_height + b_padding;
	}
	do_b[0]->label("+");
	do_b[1]->label("-");
	do_b[2]->label("*");
	do_b[3]->label("/");
	
	// create ac button
	button_x += b_padding + b_num_width;
	
	button_y += b_num_height + b_padding;
	Fl_Button *button_ac = new Fl_Button(button_x, button_y, b_eq_width, b_eq_height, "AC");
	button_ac->callback((Fl_Callback*)ac_b_click);
	button_ac->box(FL_GTK_UP_BOX);
	
	// create eq button
	button_y += b_eq_height + b_padding;
	Fl_Button *button_eq = new Fl_Button(button_x, button_y, b_eq_width, b_eq_height, "=");
	button_eq->callback((Fl_Callback*)eq_b_click);
	button_eq->box(FL_GTK_UP_BOX);
	
	
	// create input
	input = new Fl_Input(input_x, input_y, window_width - (input_x * 2), input_height);
	input->box(FL_GTK_UP_BOX);
	input->textsize(18);
	input->readonly(1);
	input->value("0");
	
	
	window->end();
	window->show(argc, argv);
	return Fl::run();
}
