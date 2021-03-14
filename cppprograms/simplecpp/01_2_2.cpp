#include <simplecpp>
main_program{
	cout << "How many sides?";
	int nsides;
	cin >> nsides;
	turtleSim();
	repeat(nsides){
		repeat(5){
			forward(50.0/nsides);
			penUp();
			forward(50.0/nsides);
			penDown();
		}
		right(360.0/nsides);
		wait(0.5);
	}
	wait(10);
}
