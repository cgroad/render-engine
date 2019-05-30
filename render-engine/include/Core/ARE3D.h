#pragma once

#ifndef DLLEXP
#define DLLEXP extern "C" __declspec(dllexport)
#endif

DLLEXP bool areInit();