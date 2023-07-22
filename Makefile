pyphone:
	g++ \
		-O3 \
		-Wall \
		-shared \
		-std=c++17 \
		-fvisibility=hidden \
		-fPIC $$(python3 -m pybind11 --includes) \
		-l phonenumber \
		pyphone.cpp \
		-o pyphone$$(python3-config --extension-suffix)
