#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void colorTransfer(const Mat& input1, Mat& input2)
{														//�Էµ� �̹����� lab ��ȯ�Ѵ�.
	Mat labinput, labouput;
	cvtColor(input1, labinput, COLOR_BGR2Lab);
	cvtColor(input2, labouput, COLOR_BGR2Lab);
	labinput.convertTo(labinput, CV_32FC3);					//������ 32FC3 �������� ��ȯ�Ѵ�.
	labouput.convertTo(labouput, CV_32FC3);

	Scalar meaninput, stdinput, meanoutput, stdoutput;		//�Է� ������ ��հ� ǥ�������� ä�κ��� mean( )�� std( )�� ����Ѵ�.
	meanStdDev(labinput, meaninput, stdinput);
	meanStdDev(labouput, meanoutput, stdoutput);

	vector<Mat> inputsplit, outputsplit;					//ä���� �и��Ѵ�.
	split(labinput, inputsplit);
	split(labouput, outputsplit);
															//������ ä�κ��� ����� �����Ѵ�.
	outputsplit[0] -= meanoutput[0];
	outputsplit[1] -= meanoutput[1];
	outputsplit[2] -= meanoutput[2];

	outputsplit[0] = stdoutput[0] / stdinput[0] * outputsplit[0];
	outputsplit[1] = stdoutput[1] / stdinput[0] * outputsplit[1];
	outputsplit[2] = stdoutput[2] / stdinput[0] * outputsplit[2];

	outputsplit[0] += meaninput[0];
	outputsplit[1] += meaninput[1];
	outputsplit[2] += meaninput[2];
														//������ 8UC1 �������� ��ȯ�Ѵ�.
	outputsplit[0].convertTo(outputsplit[0], CV_8UC1);
	outputsplit[1].convertTo(outputsplit[1], CV_8UC1);
	outputsplit[2].convertTo(outputsplit[2], CV_8UC1);

	merge(outputsplit, input2);							//�и��� ä�ε��� �����Ѵ�.

	cvtColor(input2, input2, COLOR_Lab2BGR);			// lab���� rgb�� �ٽ� ��ȯ�Ѵ�.
}
int main(int argc, char** argv)
{
	Mat input1, input2, input2_origin;
	input1 = imread("color_transfer\\b.jpg");
	input2 = imread("color_transfer\\a.jpg");
	input2_origin = input2.clone();

	if (input1.empty() || input2.empty())
	{
		cout << "FILE NOT FOUND" << endl;
		return -1;
	}

	colorTransfer(input1, input2);
	imwrite("color_transfer\\result.jpg", input2);
	imshow("input1", input1);
	imshow("input2", input2_origin);
	imshow("result", input2);
	waitKey(0);
	return 0;
}