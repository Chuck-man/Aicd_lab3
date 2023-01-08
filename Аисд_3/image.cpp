#include<iostream>
#include<stdexcept>
#include<iomanip>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#pragma once

template <typename T>
class Image {
private:
	size_t _l, _w;
	vector<vector<T>>  _px;

public:
	Image() : _l(0), _w(0) {
		_px.resize(_w);
		for (size_t i = 0; i < _w; ++i)
		{
			_px[i].resize(_l);
		}
		for (size_t i = 0; i < _w; i++) {
			for (size_t j = 0; j < _l; j++)
			{
				_px[i][j] = 0;
			}
		}
	}

	Image(size_t l, size_t w, T value) {
		if (l <= 0 || w <= 0) throw std::logic_error("incorrect image sizes");
		_l = l;
		_w = w;
		_px.resize(_w);
		for (size_t i = 0; i < _w; ++i)
		{
			_px[i].resize(_l);
		}
		for (size_t i = 0; i < _w; i++) {
			for (size_t j = 0; j < _l; j++)
			{
				_px[i][j] = value;
			}
		}
		/*_px = new T * [_l];
		for (size_t i = 0; i < _l; i++) {
			_px[i] = new T[_w];
		}
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				_px[i][j] = value;
			}
		}*/
	}

	Image(const Image<T>& another) = default;

	~Image() = default;

	Image& operator =(const Image& v) = default;

	auto begin() const { return _px.begin(); }

	auto end() const { return _px.end(); }

	T& operator()(size_t l, size_t w) {
		if (l < 0 || l > _l || w < 0 || w > _w) throw std::out_of_range("invalid index");
		return _px[l][w];
	}

	Image<T> operator+(const Image<T>& obj) {
		if (_l != obj._l || _w != obj._w) throw std::logic_error("size mismatch");
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] + obj._px[i][j];
			}
		}
		return temp_px;
	}

	Image<T> operator*(const Image<T>& obj) const {
		if (_l != obj._l || _w != obj._w) throw std::logic_error("size mismatch");
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] * obj._px[i][j];
			}
		}
		return temp_px;
	}

	Image<T> operator+(const T& value) {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] + value;
			}
		}
		return temp_px;
	}

	friend Image<T> operator+(const T& value, const Image<T>& obj) {
		Image temp_px(obj);
		for (size_t i = 0; i < obj._l; i++) {
			for (size_t j = 0; j < obj._w; j++) {
				temp_px(i, j) = obj._px[i][j] + value;
			}
		}
		return temp_px;
	}

	friend Image<T> operator*(const T& value, const Image<T>& obj) {
		Image temp_px(obj);
		for (size_t i = 0; i < obj._l; i++) {
			for (size_t j = 0; j < obj._w; j++) {
				temp_px(i, j) = obj._px[i][j] * value;
			}
		}
		return temp_px;
	}

	Image<T> operator*(const T& value) {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] * value;
			}
		}
		return temp_px;
	}

	Image operator!() {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] - 2 * _px[i][j];
			}
		}
		return temp_px;
	}

	friend std::ostream& operator<<(std::ostream& out, const Image<T>& obj) {
		for (auto i : obj) {
			for (auto j : i) {
				out << std::fixed << std::setprecision(2);
				out << j << '\t';
			}
			out << "\n";
		}
		system("pause");
		return out;
	}

	friend double fullness(const Image<T>& obj) {
		double empty = 1, full = 0;
		for (size_t i = 0; i < obj._l; i++) {
			for (size_t j = 0; j < obj._w; j++) {
				empty++;
				if (obj._px[i][j]) {
					full++;
				}
			}
		}
		return full / empty;
	}

	Image<T> creating_rectangle(size_t x1, size_t y1, size_t x2, size_t y2) {
		if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) throw std::logic_error("coordinates mismatch");
		size_t i = x1, j = y1;
		if (_px[i][j] != 0) {
			while (i < x2) {
				_px[i][j] = 0;
				++i;
			}
			while (j < y2) {
				_px[i][j] = 0;
				++j;
			}
			while (i >= x1) {
				_px[i][j] = 0;
				--i;
			}
			while (j >= y1) {
				_px[i][j] = 0;
				--j;
			}
			return *this;
		}
	}
};