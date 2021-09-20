#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main() {
	Mat input, origin;

	input = imread("C:\\Users\\허성민\\Desktop\\과제\\20년도1학기\\디지털 영상처리\\seam_carving\\seam_result.jpg");
	if (!input.data) { cout << "Image Not Found" << endl; return -1; }
	
	input.convertTo(input, CV_8UC3);
	
	Mat gray, sobel_x, sobel_y, e_map;
	cvtColor(input, gray, COLOR_BGR2GRAY);
	Sobel(gray, sobel_x, CV_8UC1, 1, 0);
	Sobel(gray, sobel_y, CV_8UC1, 0, 1);
	e_map = abs(sobel_x) + abs(sobel_y);
	
	Mat seam_map(e_map.rows, e_map.cols, CV_8UC1, Scalar(255));
	int min = 0;
	for (int i = 1; i < e_map.rows; i++) {
		for (int j = 0; j < e_map.cols; j++) {
			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i, j - 1) && e_map.at<uchar>(i + 1, j - 1) > e_map.at<uchar>(i, j - 1))
				min = e_map.at<uchar>(i, j - 1);

			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i + 1, j - 1) && e_map.at<uchar>(i, j - 1) > e_map.at<uchar>(i + 1, j - 1))
				min = e_map.at<uchar>(i + 1, j - 1);

			if (e_map.at<uchar>(i, j - 1) > e_map.at<uchar>(i - 1, j - 1) && e_map.at<uchar>(i + 1, j - 1) > e_map.at<uchar>(i - 1, j - 1))
				min = e_map.at<uchar>(i - 1, j - 1);

			seam_map.at<uchar>(i, j) = e_map.at<uchar>(i, j) + min;
		}
	}
	
	vector<int> seam_line;
	int min_pixel = 999, pixel_x = -1;

	for (int i = 0; i < seam_map.cols; i++) {
		if (min_pixel > seam_map.at<uchar>(seam_map.rows - 1, i)) {
			min_pixel = seam_map.at<uchar>(seam_map.rows - 1, i);
			pixel_x = i;
		}
	}

	int seam_pixel = pixel_x;

	for (int j = seam_map.rows - 1; j >= 0; j--) {
		seam_line.push_back(seam_pixel);
		if (j == 0) break;

		if (seam_map.at<uchar>(j,pixel_x - 1) > seam_map.at<uchar>(j, pixel_x) && seam_map.at<uchar>(j, pixel_x + 1) > seam_map.at<uchar>(j, pixel_x))
			seam_pixel = pixel_x;

		if (seam_map.at<uchar>(j, pixel_x) > seam_map.at<uchar>(j, pixel_x - 1) && seam_map.at<uchar>(j, pixel_x + 1) > seam_map.at<uchar>(j, pixel_x - 1))
			seam_pixel = pixel_x - 1;

		if (seam_map.at<uchar>(j, pixel_x - 1) > seam_map.at<uchar>(j, pixel_x + 1) && seam_map.at<uchar>(j, pixel_x - 1) > seam_map.at<uchar>(j, pixel_x + 1))
			seam_pixel = pixel_x + 1;
	}
	reverse(seam_line.begin(), seam_line.end());

	Mat seam_carving(input.rows, input.cols-1, CV_8UC3);

	for (int i = 0; i < seam_carving.rows; i++) {
		for (int j = 0; j < seam_carving.cols-1; j++) {
			seam_carving.at<Vec3b>(i, j) = i < seam_line[i] ? input.at<Vec3b>(i, j) : input.at<Vec3b>(i, j + 1);
		}
	}

	imwrite("C:\\Users\\허성민\\Desktop\\과제\\20년도1학기\\디지털 영상처리\\seam_carving\\seam_result.jpg", seam_carving);
	imshow("result", seam_carving);
	
	waitKey(0);
	return 0;
}
