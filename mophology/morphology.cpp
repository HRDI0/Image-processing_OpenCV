#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat binary_im = imread("im.jpg",IMREAD_GRAYSCALE);		//���� �׷��̽����� �̹���
	if (!binary_im.data) {
		cout << "Not Found File" << endl;
		return -1;
	}
	imshow("image", binary_im);

	threshold(binary_im, binary_im, 180,255, THRESH_BINARY_INV);	//���� �̹��� ����ȭ
	imshow("binary_image", binary_im);

	Mat kernel = getStructuringElement(MORPH_CROSS, Size(3,3));		//Ŀ�� 1	CROSS 3 X 3
	Mat kernel2 = getStructuringElement(MORPH_CROSS, Size(3,2));	//Ŀ�� 2	CROSS 3 X 2
	Mat kernel3 = getStructuringElement(MORPH_RECT, Size(2,2));		//Ŀ�� 3	RECT  2 X 2	

	Mat result_im;													//�̹������� "ó��ó��" ���ڸ� ����� ����
	erode(binary_im, result_im, kernel);

	for (int i = 0; i < 4; i++) {
		dilate(result_im, result_im, kernel2);
		for (int j = 0; j < 2; j++) {
			erode(result_im, result_im, kernel2);
		}
	}
	
	imshow("result_image", result_im);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Mat result_im2;													//��ü ���ȭ �̹������� "ó��ó��" ���ڸ� ������ ����ũ �̹��� ����
	erode(binary_im, result_im2, kernel);

	for (int i = 0; i < 2; i++) {
		dilate(result_im2, result_im2, kernel);
		for(int j = 0; j <3; j++) erode(result_im2, result_im2, kernel3);
	}
	erode(result_im2, result_im2, kernel);
	erode(result_im2, result_im2, kernel3);

	for (int i = 0; i < 20; i++) {
		dilate(result_im2, result_im2, kernel);
	}

	imshow("result_image2", result_im2);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Mat skel(result_im.size(), CV_8UC1, Scalar(0));					// "ó��ó��" ���ڸ� ���ȭ
	Mat temp, eroded;

	while (countNonZero(result_im)) {
		erode(result_im, eroded, kernel);
		dilate(eroded, temp, kernel);
		subtract(result_im, temp, temp);
		bitwise_or(skel, temp, skel);
		eroded.copyTo(result_im);
	}

	imshow("skel_img", skel);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Mat skel2(result_im.size(), CV_8UC1, Scalar(0));			// ��ü ����ȭ �̹��� ���ȭ
	Mat temp2, eroded2;										
	erode(binary_im, binary_im, kernel);
	while (countNonZero(binary_im)) {
		erode(binary_im, eroded2, kernel);
		dilate(eroded2, temp2, kernel);
		subtract(binary_im, temp2, temp2);
		bitwise_or(skel2, temp2, skel2);
		eroded2.copyTo(binary_im);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	subtract(skel2, result_im2, skel2);						// ��ü �̹��� ���ȭ �̹������� "ó��ó��" ���ڸ� �����
	imshow("skel_img2", skel2);

	add(skel, skel2, skel);									// ���� �۾��� ���� ����ȭ ����̹����� ������ "ó��ó��" ���� ���ȭ �̹����� �ռ�
	imshow("skel_img3", skel);

	waitKey(0);
	return 0;
}
