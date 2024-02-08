#pragma once

namespace math {

	namespace Vectorize {

		template<template<int S, typename T> class Vec, int S, typename R, typename T>
		struct Functor1 {};

		template<template<int S, typename T> class Vec, typename R, typename T>
		struct Functor1<Vec, 2, R, T> {
			inline constexpr static Vec<2, T> call(R(*Func) (T x), const Vec<2, T>& v) {
				return Vec<2, T>(Func(v.x), Func(v.y));
			}
		};

		template<template<int S, typename T> class Vec, typename R, typename T>
		struct Functor1<Vec, 3, R, T> {
			inline constexpr static Vec<3, T> call(R(*Func) (T x), const Vec<3, T>& v) {
				return Vec<3, T>(Func(v.x), Func(v.y), Func(v.z));
			}
		};

		template<template<int S, typename T> class Vec, typename R, typename T>
		struct Functor1<Vec, 4, R, T> {
			inline constexpr static Vec<4, T> call(R(*Func) (T x), const Vec<4, T>& v) {
				return Vec<4, T>(Func(v.x), Func(v.y), Func(v.z), Func(v.w));
			}
		};


		template<template<int S, typename T> class Vec, int S, typename T>
		struct Functor2 {};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2<Vec, 2, T> {
			inline constexpr static Vec<2, T> call(T(*Func) (T a, T b), const Vec<2, T>& v1, const Vec<2, T>& v2) {
				return Vec<2, T>(Func(v1.x, v2.x), Func(v1.y, v2.y));
			}
		};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2<Vec, 3, T> {
			inline constexpr static Vec<3, T> call(T(*Func) (T a, T b), const Vec<3, T>& v1, const Vec<3, T>& v2) {
				return Vec<3, T>(Func(v1.x, v2.x), Func(v1.y, v2.y), Func(v1.z, v2.z));
			}
		};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2<Vec, 4, T> {
			inline constexpr static Vec<4, T> call(T(*Func) (T a, T b), const Vec<4, T>& v1, const Vec<4, T>& v2) {
				return Vec<4, T>(Func(v1.x, v2.x), Func(v1.y, v2.y), Func(v1.z, v2.z), Func(v1.w, v2.w));
			}
		};


		template<template<int S, typename T> class vec, int S, typename T>
		struct Functor2_vec_sca {};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2_vec_sca<Vec, 2, T> {
			inline constexpr static Vec<2, T> call(T(*Func) (T a, T b), const Vec<2, T>& a, T b) {
				return Vec<2, T>(Func(a.x, b), Func(a.y, b));
			}
		};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2_vec_sca<Vec, 3, T> {
			inline constexpr static Vec<3, T> call(T(*Func) (T a, T b), const Vec<3, T>& a, T b) {
				return Vec<3, T>(Func(a.x, b), Func(a.y, b), Func(a.z, b));
			}
		};

		template<template<int S, typename T> class Vec, typename T>
		struct Functor2_vec_sca<Vec, 4, T> {
			inline constexpr static Vec<4, T> call(T(*Func) (T a, T b), const Vec<4, T>& a, T b) {
				return Vec<4, T>(Func(a.x, b), Func(a.y, b), Func(a.z, b), Func(a.w, b));
			}
		};

	}

}