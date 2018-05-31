#pragma once
#ifndef TEST_H
#define TEST_H

#include <stdio.h>

int (*test_rand)();

#define rand(...)\
	test_rand()

#endif /*TEST_H*/