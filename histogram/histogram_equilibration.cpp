#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, gray_img, gray_result, result, img_histogram1, img_histogram2, img_histogram_r, img_histogram_g, img_histogram_b, img_histogram_or, img_histogram_og, img_histogram_ob;

void color_histogram(Mat& input) {
	int histogram_cr[256] = { 0, };				//������׷� ���
	int histogram_cg[256] = { 0, };
	int histogram_cb[256] = { 0, };

	for (int y = 0; y < input.rows; y++)
	{
		for (int x = 0; x < input.cols; x++)
		{
			int value_r = input.at<Vec3b>(y, x)[2];
			histogram_cr[value_r] += 1;
			int value_g = input.at<Vec3b>(y, x)[1];
			histogram_cg[value_g] += 1;
			int value_b = input.at<Vec3b>(y, x)[0];
			histogram_cb[value_b] += 1;
		}
	}
	int cumulative_r[256] = { 0, };			//���� ������׷� ���
	int cumulative_g[256] = { 0, };			//���� ������׷� ���
	int cumulative_b[256] = { 0, };			//���� ������׷� ���
	int sum_r = 0;
	int sum_g = 0;
	int sum_b = 0;

	for (int i = 1; i < 256; i++)
	{
		sum_r += histogram_cr[i];
		cumulative_r[i] = sum_r;
		sum_g += histogram_cg[i];
		cumulative_g[i] = sum_g;
		sum_b += histogram_cb[i];
		cumulative_b[i] = sum_b;
	}

	float normalized_histogram_r[256] = { 0.0, };		//����ȭ �� ����������׷� ���
	float normalized_histogram_g[256] = { 0.0, };
	float normalized_histogram_b[256] = { 0.0, };
	int image_size = input.rows * input.cols;

	for (int i = 0; i < 256; i++)
	{
		normalized_histogram_r[i] = cumulative_r[i] / (float)image_size;
		normalized_histogram_g[i] = cumulative_g[i] / (float)image_size;
		normalized_histogram_b[i] = cumulative_b[i] / (float)image_size;
	}

	result = Mat(input.rows, input.cols, CV_8UC3);			//��� ���� ������׷� ���
	int histogram_r[256] = { 0, };
	int histogram_g[256] = { 0, };
	int histogram_b[256] = { 0, };
	for (int y = 0; y < input.rows; y++)
	{
		for (int x = 0; x < input.cols; x++)
		{
			result.at<Vec3b>(y, x)[2] = normalized_histogram_r[input.at<Vec3b>(y, x)[2]] * 255;
			histogram_r[result.at<Vec3b>(y, x)[2]] += 1;
			result.at<Vec3b>(y, x)[1] = normalized_histogram_g[input.at<Vec3b>(y, x)[1]] * 255;
			histogram_g[result.at<Vec3b>(y, x)[1]] += 1;
			result.at<Vec3b>(y, x)[0] = normalized_histogram_b[input.at<Vec3b>(y, x)[0]] * 255;
			histogram_b[result.at<Vec3b>(y, x)[0]] += 1;
		}
	}
	img_histogram_or = Mat(300, 300, CV_8UC3, Scalar(0));			//������׷� ���
	img_histogram_og = Mat(300, 300, CV_8UC3, Scalar(0));
	img_histogram_ob = Mat(300, 300, CV_8UC3, Scalar(0));

	img_histogram_r = Mat(300, 300, CV_8UC3, Scalar(0));
	img_histogram_g = Mat(300, 300, CV_8UC3, Scalar(0));
	img_histogram_b = Mat(300, 300, CV_8UC3, Scalar(0));

	int max1 = -1;
	for (int i = 0; i < 256; i++)
		if (max1 < histogram_cr[i]) max1 = histogram_cr[i];

	int max2 = -1;
	for (int i = 0; i < 256; i++)
		if (max2 < histogram_cg[i]) max2 = histogram_cg[i];

	int max3 = -1;
	for (int i = 0; i < 256; i++)
		if (max3 < histogram_cb[i]) max3 = histogram_cb[i];

	int max4 = -1;
	for (int i = 0; i < 256; i++)
		if (max4 < histogram_r[i]) max4 = histogram_r[i];

	int max5 = -1;
	for (int i = 0; i < 256; i++)
		if (max5 < histogram_g[i]) max5 = histogram_g[i];

	int max6 = -1;
	for (int i = 0; i < 256; i++)
		if (max6 < histogram_b[i]) max6 = histogram_b[i];

	for (int i = 0; i < 256; i++)
	{
		int histo_or = 300 * histogram_cr[i] / (float)max1;
		int cumulative_histo_or = 300 * cumulative_r[i] / (float)cumulative_r[255];

		line(img_histogram_or, Point(i + 10, 300), Point(i + 10, 300 - histo_or), Scalar(0, 0, 255));

		int histo_og = 300 * histogram_cg[i] / (float)max2;
		int cumulative_histo_og = 300 * cumulative_g[i] / (float)cumulative_g[255];

		line(img_histogram_og, Point(i + 10, 300), Point(i + 10, 300 - histo_og), Scalar(0, 255, 0));

		int histo_ob = 300 * histogram_cb[i] / (float)max3;
		int cumulative_histo_ob = 300 * cumulative_b[i] / (float)cumulative_b[255];

		line(img_histogram_ob, Point(i + 10, 300), Point(i + 10, 300 - histo_ob), Scalar(255, 0, 0));
		////////////////////////////////////////////////////////////////////////////////////////////////
		int histo_r = 300 * histogram_r[i] / (float)max4;

		int cumulative_histo_r = 300 * histogram_r[i] / (float)histogram_r[255];

		line(img_histogram_r, Point(i + 10, 300), Point(i + 10, 300 - histo_r), Scalar(0, 0, 255));

		int histo_g = 300 * histogram_g[i] / (float)max5;
		int cumulative_histo_g = 300 * histogram_g[i] / (float)histogram_g[255];

		line(img_histogram_g, Point(i + 10, 300), Point(i + 10, 300 - histo_g), Scalar(0, 255, 0));

		int histo_b = 300 * histogram_b[i] / (float)max6;
		int cumulative_histo_b = 300 * histogram_b[i] / (float)histogram_b[255];

		line(img_histogram_b, Point(i + 10, 300), Point(i + 10, 300 - histo_b), Scalar(255, 0, 0));
	}
	imshow("�÷� �Է� ����", input);
	imshow("�÷� ��� ����", result);
	imshow("RED ��Ȱȭ ������׷�", img_histogram_r);
	imshow("GREEN ��Ȱȭ ������׷�", img_histogram_g);
	imshow("BLUE ��Ȱȭ ������׷�", img_histogram_b);
	imshow("RED ������׷�", img_histogram_or);
	imshow("GREEN ������׷�", img_histogram_og);
	imshow("BLUE ������׷�", img_histogram_ob);
}

void gray_histogram(Mat& input) {
	int histogram[256] = { 0, };				//������׷� ���

	for (int y = 0; y < input.rows; y++)
	{
		for (int x = 0; x < input.cols; x++)
		{
			int value = input.at<uchar>(y, x);
			histogram[value] += 1;
		}
	}
	int cumulative[256] = { 0, };			//���� ������׷� ���
	int sum = 0;

	for (int i = 1; i < 256; i++)
	{
		sum += histogram[i];
		cumulative[i] = sum;
	}

	float normalized_histogram[256] = { 0.0, };		//����ȭ �� ����������׷� ���
	int image_size = input.rows * input.cols;

	for (int i = 0; i < 256; i++)
	{
		normalized_histogram[i] = cumulative[i] / (float)image_size;
	}

	gray_result = Mat(input.rows, input.cols, CV_8UC1);			//��� ���� ������׷� ���
	int histogram2[256] = { 0, };
	for (int y = 0; y < input.rows; y++)
	{
		for (int x = 0; x < input.cols; x++)
		{
			gray_result.at<uchar>(y, x) = normalized_histogram[input.at<uchar>(y, x)] * 255;
			histogram2[gray_result.at<uchar>(y, x)] += 1;
		}
	}

	img_histogram1 = Mat(300, 300, CV_8UC1, Scalar(0));			//������׷� ���
	img_histogram2 = Mat(300, 300, CV_8UC1, Scalar(0));

	int max = -1;
	for (int i = 0; i < 256; i++)
		if (max < histogram[i]) max = histogram[i];

	int max2 = -1;
	for (int i = 0; i < 256; i++)
		if (max2 < histogram2[i]) max2 = histogram2[i];

	for (int i = 0; i < 256; i++)
	{
		int histo = 300 * histogram[i] / (float)max;
		int cumulative_histo = 300 * cumulative[i] / (float)cumulative[255];

		line(img_histogram1, Point(i + 10, 300), Point(i + 10, 300 - histo), Scalar(255, 255, 255));


		int histo2 = 300 * histogram2[i] / (float)max2;
		int cumulative_histo2 = 300 * histogram2[i] / (float)histogram2[255];

		line(img_histogram2, Point(i + 10, 300), Point(i + 10, 300 - histo2), Scalar(255, 255, 255));
	}

	imshow("��� �Է� ����", input);
	imshow("��� ��� ����", gray_result);
	imshow("��� �Է� ������׷�", img_histogram1);
	imshow("��� ��Ȱȭ ������׷�", img_histogram2);
}

int main()
{
	gray_img = imread("Lenna.jpg", IMREAD_GRAYSCALE);	//�̹����� �ҷ���
	img = imread("Lenna.jpg", IMREAD_COLOR);
	if (gray_img.empty()) {				//�̹����� ������ ���� ó��
		cout << "������ ���� �� ����" << endl;
		return -1;
	}
	if (img.empty()) {				//�̹����� ������ ���� ó��
		cout << "������ ���� �� ����" << endl;
		return -1;
	}

	gray_histogram(gray_img);
	color_histogram(img);

	while (1) {						//Ű���� �Է� ó��
		int key = waitKey(0);
		if (key == 'q') break;			//q�� ������ ����
	}
	return 0;
}