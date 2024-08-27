#include<fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
using namespace std;

class Matrix
{
private:
	int width, height;
	vector<vector<int>> data;


public:
	Matrix(int width, int height, int initialValue = 0) {
		if (width <= 0 || height <= 0) {
			throw runtime_error("矩阵为空，无意义");
		}
		this->width = width;
		this->height = height;
		data.resize(height, vector<int>(width, initialValue));


	}
	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}
	void setPixel(int x, int y, int value) {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			throw runtime_error("Pixel coordinates are out of range.");

		}
		data[y][x] = value;
	}

	int getPixel(int x, int y) {
		return data[y][x];
	}


	void print() {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				cout << data[y][x] << "        ";
			}
			cout << endl;
		}
	}

	void save(Matrix& matrix, string code) {
		ofstream file;
		if (!file.is_open()) {
			throw runtime_error("Faile ");
		}
		try {
			for (int y = 0; y < matrix.getHeight(); ++y) {
				for (int x = 0; x < matrix.getWidth(); ++x) {
					file << matrix.getPixel(x, y);
					if (x < matrix.getWidth() - 1) {
						file << ",";
					}
				}
				file << endl;
			}
		}
		catch (exception& e) {
			throw;
		}

		file.close();
	}

	void read(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			throw runtime_error("无法打开文件以读取矩阵");
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string item;
			vector<int> row;

			while (getline(ss, item, ',')) {
				try {
					int value = stoi(item);
					row.push_back(value);
				}
				catch (const invalid_argument& e) {
					throw runtime_error("文件包含非整数数据");
				}
				catch (const out_of_range& e) {
					throw runtime_error("文件中的数据超出了int的范围");
				}
			}

			if (!row.empty()) {
				data.push_back(row);
			}
		}

		if (data.empty()) {
			throw runtime_error("文件是空的或格式不正确");
		}

		file.close();
	}

	void print1() {
		for (const auto& row : data) {
			for (int value : row) {
				cout << value << " ";
			}
			cout << endl;
		}
	}

	//二值化
	void Binarization() {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cout << ((char)data[y][x] == 0 ? '.' : 'o')<<"  ";
			}
			cout << endl;
		}
	}

	//阈值化
	void Binary(int THR) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (data[y][x] <= THR)
					data[y][x] = 0;
				cout << data[y][x]<<"  ";
			}
			cout << endl;
		}
	}
	//翻转
	void fz() {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width / 2; ++x) {
				// 交换左右对称的像素值  
				swap(data[y][x], data[y][width - 1 - x]);
			}
		}
	}

	//旋转
	void xz90() {
		// 首先，保存原始矩阵的尺寸  
		int originalWidth = width;
		int originalHeight = height;

		// 交换宽度和高度  
		swap(width, height);

		// 创建一个新的矩阵来存储旋转后的结果  
		vector<vector<int>> rotatedData(height, vector<int>(width, 0));

		  
		for (int y = 0; y < originalHeight; ++y) {
			for (int x = 0; x < originalWidth; ++x) {
				// 旋转后的坐标映射：(x, y) -> (originalHeight - 1 - y, x)  
				rotatedData[x][originalHeight - 1 - y] = data[y][x];
			}
		}

		// 更新内部数据  
		data = rotatedData;
	}

};


int main() {
	Matrix matrix(5, 7, 100);

	matrix.setPixel(0, 0, 0);
	for (int i = 1; i < 5; i++) {
		matrix.setPixel(i, 0, 255);
		matrix.setPixel(i, 6, 255);
	}
	for (int i = 1; i < 7; i++) {
		matrix.setPixel(0, i, 255);
		matrix.setPixel(4, i, 255);
	}
	


	try {
		matrix.read( "C:\\Users\\16840\\OneDrive\\dg\\Project0\\Project0\\matrix1.csv");
		matrix.print1();
		
	}
	catch (exception e) {
		cerr << "Exception caught: " << e.what() << endl;

	}

}
