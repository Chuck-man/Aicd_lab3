#include "Image.cpp"

#pragma once

template <>
class Image<bool> {
private:
	size_t _l, _w;
	vector<vector<bool>> _px;

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

	Image(size_t l, size_t w, bool value) {
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
	}

	Image(const Image& another) = default;

	~Image() = default;

	Image& operator =(const Image& v) = default;

	auto begin() const { return _px.begin(); }

	auto end() const { return _px.end(); }

	bool& operator()(size_t l, size_t w) {
		if (l < 0 || l > _l || w < 0 || w > _w) throw std::out_of_range("invalid index");
		//return _px[l][w];
	}

	Image operator+(const Image& obj) {
		if (_l != obj._l || _w != obj._w) throw std::logic_error("size mismatch");
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] || obj._px[i][j];
			}
		}
		return temp_px;
	}

	Image operator*(const Image& obj) const {
		if (_l != obj._l || _w != obj._w) throw std::logic_error("size mismatch");
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] && obj._px[i][j];
			}
		}
		return temp_px;
	}

	Image operator+(const bool value) {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] || value;
			}
		}
		return temp_px;
	}

	friend Image operator+(const bool value, const Image& obj) {
		Image temp_px(obj);
		for (size_t i = 0; i < obj._l; i++) {
			for (size_t j = 0; j < obj._w; j++) {
				temp_px(i, j) = obj._px[i][j] || value;
			}
		}
		return temp_px;
	}

	friend Image operator*(const bool value, const Image& obj) {
		Image temp_px(obj);
		for (size_t i = 0; i < obj._l; i++) {
			for (size_t j = 0; j < obj._w; j++) {
				temp_px(i, j) = obj._px[i][j] && value;
			}
		}
		return temp_px;
	}

	Image operator*(const bool value) {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = _px[i][j] && value;
			}
		}
		return temp_px;
	}

	Image operator!() {
		Image temp_px(*this);
		for (size_t i = 0; i < _l; i++) {
			for (size_t j = 0; j < _w; j++) {
				temp_px(i, j) = !_px[i][j];
			}
		}
		return temp_px;
	}

	friend std::ostream& operator<<(std::ostream& out, const Image& obj) {
		for (auto i : obj) {
			for (auto j : i) {
				if (j)
					out << "\t" << "1";
				else out << "\t" << ".";
			}
			out << "\n";
		}
		system("pause");
		return out;
	}

	friend double fullness(const Image& obj) {
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

	Image creating_rectangle(size_t x1, size_t y1, size_t x2, size_t y2) {
		if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) throw std::logic_error("coordinates mismatch");
		size_t i = x1, j = y1;
		if (_px[i][j] != true) {
			while (i < x2) {
				_px[i][j] = true;
				++i;
			}
			while (j < y2) {
				_px[i][j] = true;
				++j;
			}
			while (i >= x1) {
				_px[i][j] = true;
				--i;
			}
			while (j >= y1) {
				_px[i][j] = true;
				--j;
			}
			return *this;
		}
	}
};