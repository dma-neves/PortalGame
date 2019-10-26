CPPC=g++ -std=c++11

launcher: Launcher/launcher.cpp
	$(CPPC) Launcher/launcher.cpp -o launcher.out
