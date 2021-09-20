#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, roi,clone;		//�̹����� �����ϱ� ���� Mat ����
int w=255, h=255;		//�ڸ� �̹����� ũ��

void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN) {	//���콺 Ŭ��
		img = clone.clone();		//������ �׷��� �簢���� ���ֱ� ���� ���ΰ�ħ

		if ((x + 128) >=512) x -= (x + 128) - 512;		//�簢���� �̹����� ��������� ���� ó��
		else if ((x - 128) <= 0) x -= (x - 128);
		if ((y + 128) >= 512) y -= (y + 128) - 512;
		else if ((y - 128) <= 0) y -= (y - 128);

		x -= 127;					//���콺�� Ŭ���� ������ �簢���� �߽������� �ϱ� ���� ó��
		y -= 127;
		Rect r(x,y,w,h);			//Ŭ���� ��ġ�� �߽����� �簢�� ����
		roi = img(r);				//Ŭ���� ��ġ�� �߽����� �� �簢����ŭ �̹����� �ڸ�
		resize(roi, roi, (size(roi) * 2));	//�ڸ� �̹����� 2�� Ȯ��
		imshow("Croping", roi);		//Ȯ���� �̹����� ȭ�鿡 ���

		rectangle(img,r,Scalar(0,255,0),2);	//���� �̹����� �簢�� ���
		imshow("Digital image processing", img);	//�簢���� �׷��� �̹��� ���
	}
	else if (event == EVENT_RBUTTONDOWN) {}
	else if (event == EVENT_MBUTTONDOWN) {}
	else if (event == EVENT_MOUSEMOVE) {}
}
int main()
{
	img = imread("Lenna.jpg", IMREAD_COLOR);	//�̹����� �ҷ���
	if (img.empty()) {				//�̹����� ������ ���� ó��
		cout << "������ ���� �� ����" << endl;
		return -1;
	}
	clone = img.clone();			//�̹��� ���ΰ�ħ�� ���� Ŭ�� ����
	imshow("Digital image processing", img);	//�ҷ��� �̹��� ȭ�鿡 ���

	setMouseCallback("Digital image processing", onMouse);	//���콺 Ŭ�� �Է�

	while (1) {						//Ű���� �Է� ó��
	int key = waitKey(0);
	if (key == 'q') break;			//q�� ������ ����
	else if (key == 's') {			//s�� ������ �ڸ� �̹����� ������ ��ġ�� ����
		imwrite("cropingLenna.jpg",roi);
		}
	}
	return 0;
}
