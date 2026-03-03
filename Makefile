allc: clean build run
all: build run

clean:
	clear
	rm -rf cmake-build-debug

build: 
	cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
	cmake --build cmake-build-debug -j

run:
	./cmake-build-debug/RasterizerEngine


n: clean
	nvim


# GIT HELPER

MESSAGE = .

push: clean add commit
	git push

add:
	git add .

commit:
	git commit -a -m "$(MESSAGE)"
