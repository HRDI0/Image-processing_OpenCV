#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float distance(int x, int y, int i, int j) {
	return float(sqrt(pow(x - i, 2) + pow(y - j, 2)));
}

double gaussian(float x, double sigma) {

	return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * pow(sigma, 2));
}

void start(Mat& source, Mat r_Image, int x, int y, int size, double sigmapq, double sigmai) {
	double result[3];
	double wP[3];
	double w[3];
	double gi[3];
	double gs[3];
	int n_x = 0;
	int n_y = 0;

	for (int c = 0; c < 3; c++) {

		result[c] = 0;
		wP[c] = 0;
		w[c] = 0;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				n_x = x - ((size / 2) - i);
				n_y = y - ((size / 2) - j);

				gi[c] = gaussian(source.at<Vec3b>(n_x, n_y)[c] - source.at<Vec3b>(x, y)[c], sigmapq);
				gs[c] = gaussian(distance(x, y, n_x, n_y), sigmai);
				w[c] = gi[c] * gs[c];

				result[c] = result[c] + source.at<Vec3b>(n_x, n_y)[c] * w[c];

				wP[c] = wP[c] + w[c];
			}
		}

		result[c] = result[c] / wP[c];
		r_Image.at<Vec3b>(x, y)[c] = result[c];
	}

}

Mat myFilter(Mat& source, int size, double sigmapq, double sigmai) {
	Mat temp;
	source.copyTo(temp);

	for (int i = 2; i < source.rows - 2; i++) {
		for (int j = 2; j < source.cols - 2; j++) {
			start(source, temp, i, j, size, sigmapq, sigmai);
		}
	}
	return temp;
}

int main() {
	Mat src;
	Mat r_Image;
	Mat g_x, g_y;
	Mat	a_g_x,a_g_y;
	Mat r_g;
	Mat plus_g;

	src = imread("Lenna_256.jpg", 1);
	
	if (!src.data) {
		return -1;
	}

	imshow("origin", src);
	
	Sobel(src, g_x, CV_16S, 1, 0, 3);
	Sobel(src, g_y, CV_16S, 0, 1, 3);
	convertScaleAbs(g_x, a_g_x);
	convertScaleAbs(g_y, a_g_y);
	addWeighted(a_g_x, 0.5, a_g_y, 0.5, 0, r_g);

	r_Image = myFilter(src, 10, 20.0, 20.0);
	imshow("result", r_Image);
	imshow("gradient", r_g);
	
	addWeighted(r_Image, 1, r_g, 0.5, 0, plus_g);
	imshow("plus image", plus_g);

	waitKey(0);

	return 0;

}