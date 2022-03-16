BUILD_DIR=build
REPORT_DIR=${BUILD_DIR}/report

.PHONY: all

coverage: tests
	lcov -t "${BUILD_DIR}/tests/test_subnet" -o coverage.info -c -d ${BUILD_DIR}/subnet_lib/
	genhtml -o ${BUILD_DIR}/report coverage.info

tests: build
	${BUILD_DIR}/tests/test_subnet

build:
	rm -rf build/
	cmake -B build/
	cmake --build build

docker:
	# sudo docker build . -f Dockerfile -t task1
	docker run -v ~/CLionProjects/vk_task1:/home/project -it task1:latest

check:
	./linters/run.sh
