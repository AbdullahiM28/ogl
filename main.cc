#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <chrono>
#include "window.h"


class hash_pair { // lifted from geeksforgeeks
	public:
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = std::hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

int main() {
	float speed = 3; // determines have fast the block drops

	OGL_Window w(600, 600); // width, height
	// GLFWwindow *window = w.getWindow();

	int x = 0;
	while (true) {
			// #### glClearColour(red, green, blue, opaqueness)
		using namespace std::chrono;
		auto start = steady_clock::now();
		// wait speed amount of seconds
		w.drawTriangle(5,5, Colors::BLACK);
        while (duration_cast<seconds>(steady_clock::now() - start).count() < speed) {}

		if (x % 5 == 0) {
			w.chooseClearColor(Colors::BLUE);
			w.drawRectangle(5, 5, Colors::WHITE);
		} else if (x % 5 == 1) {
			w.chooseClearColor(Colors::GREEN);
			w.drawRectangle(5, 5, Colors::BLACK);
		} else if (x % 5 == 2) {
			w.chooseClearColor(Colors::RED);
			w.drawRectangle(5, 5, Colors::WHITE);
		} else if (x % 5 == 3) {
			w.chooseClearColor(Colors::BLACK);
			w.drawRectangle(5, 5, Colors::WHITE);
		} else {
			w.chooseClearColor(Colors::WHITE);
			w.drawRectangle(5, 5, Colors::BLACK);
		}

		// wait speed amount of seconds
		start = steady_clock::now();
        while (duration_cast<seconds>(steady_clock::now() - start).count() < speed) {}
		// w.drawRectangle(5, 5, Colors::PURPLE);

		
		std::cout << x << std::endl;
		x++;
		if (x == 10) {
			break;
		}
	}
	return 0;	
}
