#ifndef GEOMETRICTOOLS_H_
#define GEOMETRICTOOLS_H_

#include <array>

namespace GeometricTools {
	constexpr std::array<float, 3 * 2> UnitTriangle2D = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};

	constexpr std::array<float, 4 * 2> UnitSquare2D = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	constexpr std::array<float, 8 * 3> UnitCube3D = {
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};

	constexpr std::array<unsigned int, 6 * 6> UnitCubeTopology = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		0, 1, 5, 5, 4, 0,
		3, 2, 6, 6, 7, 3,
		1, 5, 6, 6, 2, 1,
		4, 0, 3, 3, 7, 4
	};

	constexpr std::array<float, 3 * 24 * 2> UnitCube3D24WNormals = {
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.5f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.5f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.5f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -0.5f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -0.5f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -0.5f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -0.5f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -0.5f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.5f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.5f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f
	};

	constexpr std::array<unsigned int, 6 * 3 * 2> UnitCube3DTopologyTriangles24 = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 9, 11, 10,
		12, 13, 14, 13, 15, 14,
		16, 17, 18, 17, 18, 19,
		20, 21, 22, 20, 23, 22
	};
	/**
	template<int x, int y>
	constexpr std::array<float, 2 * (x + 1) * (y + 1)> UnitGridGeometry2D() {
		std::array<float, 2 * (x + 1) * (y + 1)> arr;
		int k = 0;
		for (int i = 0; i <= x; ++i) {
			for (int j = 0; j <= y; ++j) {
				arr[k++] = i * 1.0f / x - 0.5f;
				arr[k++] = j * 1.0f / y - 0.5f;
			}
		}
		return arr;
	}*/

	template<int x, int y>
	constexpr std::array<float, 2 * 4 * x * y> UnitGridGeometry2D() {
		std::array<float, 2 * 4 * x * y> arr;
		int k = 0;
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				arr[k++] = i * 1.0f / x - 0.5f;
				arr[k++] = j * 1.0f / y - 0.5f;
				arr[k++] = (i + 1) * 1.0f / x - 0.5f;
				arr[k++] = j * 1.0f / y - 0.5f;
				arr[k++] = (i + 1) * 1.0f / x - 0.5f;
				arr[k++] = (j + 1) * 1.0f / y - 0.5f;
				arr[k++] = i * 1.0f / x - 0.5f;
				arr[k++] = (j + 1) * 1.0f / y - 0.5f;
			}
		}
	}
	/**
	template<int x, int y>
	constexpr std::array<unsigned int, 6 * x * y> UnitGridTopologyTriangles() {
		std::array<unsigned int, 6 * x * y> arr;
		int k = 0;
		for (int i = 0; i < x * (y + 1); ++i) {
			if (i % (y + 1) == y) continue;
			int a = i;
			int b = a + 1;
			int c = b + y;
			int d = c + 1;
			arr[k++] = a;
			arr[k++] = b;
			arr[k++] = c;
			arr[k++] = c;
			arr[k++] = d;
			arr[k++] = b;
		}
		return arr;
	}*/

	template<int x, int y>
	constexpr std::array<unsigned int, 6 * x * y> UnitGridTopologyTriangles() {
		std::array<unsigned int, 6 * x * y> arr;
		int k = 0;
		for (int i = 0; i < x * y; ++i) {
			int a = 4 * i;
			int b = a + 1;
			int c = b + 1;
			int d = c + 1;
			arr[k++] = a;
			arr[k++] = b;
			arr[k++] = c;
			arr[k++] = c;
			arr[k++] = d;
			arr[k++] = a;
		}
		return arr;
	}
	/**
	template<unsigned int X, unsigned int Y>
	constexpr std::array<float, (X + 1)* (Y + 1)* (2 + 2)> UnitGridGeometry2DWTCoords()
	{
		std::array<float, (X + 1)* (Y + 1)* (2 + 2)> arr;
		int k = 0;
		for (int i = 0; i <= X; ++i) {
			for (int j = 0; j <= Y; ++j) {
				arr[k++] = i * 1.0f / X - 0.5f;
				arr[k++] = j * 1.0f / Y - 0.5f;
				arr[k++] = i * 1.0f / X;
				arr[k++] = j * 1.0f / Y;
			}
		}
		return arr;
	}*/

	template<unsigned int x, unsigned int y>
	constexpr std::array<float, 4 * 4 * x * y> UnitGridGeometry2DWTCoords() {
		std::array<float, 4 * 4 * x * y> arr;
		int k = 0;
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				arr[k++] = i * 1.0f / x - 0.5f;
				arr[k++] = j * 1.0f / y - 0.5f;
				arr[k++] = i * 1.0f / x;
				arr[k++] = j * 1.0f / x;

				arr[k++] = (i + 1) * 1.0f / x - 0.5f;
				arr[k++] = j * 1.0f / y - 0.5f;
				arr[k++] = (i + 1) * 1.0f / x;
				arr[k++] = j * 1.0f / y;

				arr[k++] = (i + 1) * 1.0f / x - 0.5f;
				arr[k++] = (j + 1) * 1.0f / y - 0.5f;
				arr[k++] = (i + 1) * 1.0f / x;
				arr[k++] = (j + 1) * 1.0f / y;

				arr[k++] = i * 1.0f / x - 0.5f;
				arr[k++] = (j + 1) * 1.0f / y - 0.5f;
				arr[k++] = i * 1.0f / x;
				arr[k++] = (j + 1) * 1.0f / y;
			}
		}
		return arr;
	}
}

#endif