#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>			// 문자열 출력 라이브러리
#include <vector> 			// 벡터 라이브러리
#include <random>			// 랜덤 라이브러리
#include <fstream>			// 파일 입출력 라이브러리
#include <sstream>			// 문자열 스트림 라이브러리
#include <chrono>			// 시간 라이브러리
#include <array>			// 배열 라이브러리
#include <memory>			// 스마트 포인터 라이브러리
#include <unordered_map>	// 해시맵 라이브러리

#include "Utils.h"
#include "Logger.h"

constexpr GLint WINDOW_W = 600;
constexpr GLint WINDOW_H = 600;

constexpr int FPS = 60;
constexpr int FRAME_TIME_MS = 1000 / FPS;
