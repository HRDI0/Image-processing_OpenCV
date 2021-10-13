#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include<cstdlib>
#include<ctime>



using namespace std;
using namespace cv;

int pre_seam = -1;

void get_e_map(Mat& input, Mat& output) {	//에너지 맵 구성

	Mat gray, sobel_x, sobel_y;
	cvtColor(input, gray, COLOR_BGR2GRAY);
	
	Sobel(gray, sobel_x, CV_64F, 1, 0);
	Sobel(gray, sobel_y, CV_64F, 0, 1);

	magnitude(sobel_x, sobel_y, output);	//벡터 크기 계산

	double min, max, z;	
	minMaxLoc(output, &min, &max);
	z = (1 / max) * 255;
	output = output * z;
	output.convertTo(output, CV_8U);
	
}

void find_seam_line(Mat& e_map, vector<int>& seam_line) {	//에너지 맵 구성 / decrese seam_line 찾기

	Mat seam_map(e_map.rows, e_map.cols, CV_8UC1, Scalar(255));
	int min = 0;
	for (int i = 1; i < e_map.rows; i++) {
		for (int j = 0; j < e_map.cols; j++) {
			if (e_map.at<uchar>(i - 1, j) > e_map.at<uchar>(i - 1, j - 1) && e_map.at<uchar>(i - 1, j + 1) > e_map.at<uchar>(i - 1, j - 1))
				min = e_map.at<uchar>(i - 1, j - 1);

			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i - 1, j + 1) && e_map.at<uchar>(i - 1, j) > e_map.at<uchar>(i - 1, j + 1))
				min = e_map.at<uchar>(i - 1, j + 1);

			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i - 1, j) && e_map.at<uchar>(i - 1, j + 1) > e_map.at<uchar>(i - 1, j))
				min = e_map.at<uchar>(i - 1, j);

			seam_map.at<uchar>(i, j) = e_map.at<uchar>(i, j) + min;
		}
	}

	int min_pixel = 999, pixel_x = -1;
	for (int i = 0; i < seam_map.cols; i++) {
		if (min_pixel > seam_map.at<uchar>(seam_map.rows - (seam_map.rows - 3), i)) {
			min_pixel = seam_map.at<uchar>(seam_map.rows - (seam_map.rows - 3), i);
			pixel_x = i;
		}
	}

	int seam_pixel = pixel_x;
	for (int j = seam_map.rows - 1; j >= 0; j--) {
		seam_line.push_back(seam_pixel);
		if (j == 0) break;

		if (seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel) && seam_map.at<uchar>(j, seam_pixel + 1) > seam_map.at<uchar>(j, seam_pixel))
			seam_pixel = seam_pixel;

		if (seam_map.at<uchar>(j, seam_pixel) > seam_map.at<uchar>(j, seam_pixel - 1) && seam_map.at<uchar>(j, seam_pixel + 1) > seam_map.at<uchar>(j, seam_pixel - 1))
			seam_pixel = seam_pixel - 1;

		if (seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel + 1) && seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel + 1))
			seam_pixel = seam_pixel + 1;
	}
	reverse(seam_line.begin(), seam_line.end());
}

void find_add_seam_line(Mat& e_map, vector<int>& seam_line) {  //에너지 맵 구성 / increse seam_line 찾기 
	srand((unsigned int)time(NULL));
	int num = rand();

	Mat seam_map(e_map.rows, e_map.cols, CV_8UC1, Scalar(255));
	int min = 0;
	for (int i = 1; i < e_map.rows; i++) {
		for (int j = 0; j < e_map.cols; j++) {
			if (e_map.at<uchar>(i - 1, j) > e_map.at<uchar>(i - 1, j - 1) && e_map.at<uchar>(i - 1, j + 1) > e_map.at<uchar>(i - 1, j - 1))
				min = e_map.at<uchar>(i - 1, j - 1);

			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i - 1, j + 1) && e_map.at<uchar>(i - 1, j) > e_map.at<uchar>(i - 1, j + 1))
				min = e_map.at<uchar>(i - 1, j + 1);

			if (e_map.at<uchar>(i - 1, j - 1) > e_map.at<uchar>(i - 1, j) && e_map.at<uchar>(i - 1, j + 1) > e_map.at<uchar>(i - 1, j))
				min = e_map.at<uchar>(i - 1, j);

			seam_map.at<uchar>(i, j) = e_map.at<uchar>(i, j) + min;
		}
	}

	int min_pixel = 999, pixel_x = -1;
	for (int i = 0; i < seam_map.cols; i++) {
		if (i != pre_seam) {
			if (min_pixel > seam_map.at<uchar>(num % seam_map.rows, i)) {
				min_pixel = seam_map.at<uchar>(num % seam_map.rows, i);
				pixel_x = i;
			}
		}
		i += 30;
	}
	pre_seam = pixel_x;

	int seam_pixel = pixel_x;
	for (int j = seam_map.rows - 1; j >= 0; j--) {
		seam_line.push_back(seam_pixel);
		if (j == 0) break;

		if (seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel) && seam_map.at<uchar>(j, seam_pixel + 1) > seam_map.at<uchar>(j, seam_pixel))
			seam_pixel = seam_pixel;

		if (seam_map.at<uchar>(j, seam_pixel) > seam_map.at<uchar>(j, seam_pixel - 1) && seam_map.at<uchar>(j, seam_pixel + 1) > seam_map.at<uchar>(j, seam_pixel - 1))
			seam_pixel = seam_pixel - 1;

		if (seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel + 1) && seam_map.at<uchar>(j, seam_pixel - 1) > seam_map.at<uchar>(j, seam_pixel + 1))
			seam_pixel = seam_pixel + 1;
	}
	reverse(seam_line.begin(), seam_line.end());
}

void seam_remove(Mat& input, Mat& output, vector<int>& seam_line) {		//remove seam line
	
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols - 1; j++) {
			output.at<Vec3b>(i, j) = j < seam_line[i] ? input.at<Vec3b>(i, j) : input.at<Vec3b>(i, j + 1);
		}
	}
}

void seam_add(Mat& input, Mat& output, vector<int>& seam_line) { //add seam line
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols + 1; j++) {
			output.at<Vec3b>(i, j) = j < seam_line[i] ? input.at<Vec3b>(i, j) : input.at<Vec3b>(i, j - 1);
		}
	}
}

void seam_remove_carving(Mat& input) {			//seam remove carving

	Mat e_map, result(input.rows,input.cols - 1,CV_8UC3);
	vector<int> seam_line_remove;

	get_e_map(input, e_map);
	find_seam_line(e_map, seam_line_remove);
	seam_remove(input, result, seam_line_remove);

	input = result;
}

void seam_add_carving(Mat& input) {				//seam add carving

	Mat e_map, result(input.rows, input.cols + 1, CV_8UC3);
	vector<int> seam_line_add;

	get_e_map(input, e_map);
	find_add_seam_line(e_map, seam_line_add);
	seam_add(input, result, seam_line_add);
	input = result;
}


int main() {

	Mat input, origin;
	input = imread("D:/WorkSpace/OpenCV/repos/OpenCV/OpenCV/seam_caving/seam_result.jpg");
	if (!input.data) { cout << "Image Not Found" << endl; return -1; }

	namedWindow("resize_seam_carving",WINDOW_NORMAL);
	resizeWindow("resize_seam_carving", input.cols, input.rows);

	imshow("resize_seam_carving", input);

	while (true) {										//wasd 로 이미지 조정
		int keycode = waitKey();
		switch (keycode)
		{
		case 's':
			rotate(input, input, ROTATE_90_CLOCKWISE);
			seam_remove_carving(input);
			rotate(input, input, ROTATE_90_COUNTERCLOCKWISE);
			imshow("resize_seam_carving", input);
			resizeWindow("resize_seam_carving", input.cols, input.rows);
			break;
		case 'w':
			rotate(input, input, ROTATE_90_CLOCKWISE);
			seam_add_carving(input);
			rotate(input, input, ROTATE_90_COUNTERCLOCKWISE);
			imshow("resize_seam_carving", input);
			resizeWindow("resize_seam_carving", input.cols, input.rows);
			break;
		case 'a':
			seam_remove_carving(input);
			imshow("resize_seam_carving", input);
			resizeWindow("resize_seam_carving", input.cols, input.rows);
			break;
		case 'd':
			seam_add_carving(input);
			imshow("resize_seam_carving", input);
			resizeWindow("resize_seam_carving", input.cols, input.rows);
			break;
		case 'q':
			exit(1);
			break;
		}
	}

	return 0;
}
