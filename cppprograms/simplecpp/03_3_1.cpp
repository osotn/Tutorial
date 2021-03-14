#include <simplecpp>
main_program{
	turtleSim();
	int i = 1;
	repeat(20){
		forward(i*10);
		right(90);
		wait(0.5);
		cout << i << endl;
		i++;
	}
	wait(10);
}
