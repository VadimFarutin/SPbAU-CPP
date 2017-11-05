#include <stdio.h>

#include "scheme.h"
#include "rectangle.h"
#include "circle.h"


int main() {
	Scheme scheme(10);

	scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
	scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

	scheme.print_all_figures();

	Figure* found = scheme.is_inside_figure(5, 5);
	if (found != 0) {
			found->print();
	}
	else {
			printf("not found\n");
	}

	scheme.zoom_figure(1, 2);
	scheme.print_all_figures();
	scheme.remove_figure(1);
	scheme.print_all_figures();

	scheme.push_back_figure(new Rectangle(-1, -50, -50, 2, 2));
	scheme.push_back_figure(new Circle(3, 3, 1, 1, "small circle"));

	scheme.print_all_figures();
	scheme.move(3, 3, 3);
	scheme.print_all_figures();

	found = scheme.is_inside_figure(3, 4);
	if (found != 0) {
			found->print();
	}
	else {
			printf("not found\n");
	}

	scheme.zoom_figure(1, 2);
	scheme.zoom_figure(3, 20);
	scheme.remove_figure(1);
	scheme.remove_figure(2);
	scheme.print_all_figures();

	return 0;
}
