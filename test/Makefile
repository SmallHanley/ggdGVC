PWD := $(shell pwd)

all:
	$(MAKE) -C ../lib/

test: all
	PYTHONPATH=../lib/ python3 -m pytest -v

visual:
	PYTHONPATH=../lib/ python3 visual_sample.py

benchmark:
	PYTHONPATH=../lib/ python3 benchmark.py

clean:
	rm -rf  __pycache__ .pytest_cache
	$(MAKE) -C ../lib/ clean
