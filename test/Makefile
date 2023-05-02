PWD := $(shell pwd)

all:
	$(MAKE) -C ../lib/

test: all
	PYTHONPATH=../lib/ python3 -m pytest -v

clean:
	rm -rf  __pycache__ .pytest_cache
	$(MAKE) -C ../lib/ clean
