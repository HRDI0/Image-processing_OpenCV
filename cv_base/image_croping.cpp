#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, roi,clone;		//이미지를 저장하기 위한 Mat 변수
int w=255, h=255;		//자를 이미지의 크기

void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN) {	//마우스 클릭
		img = clone.clone();		//기존의 그려진 사각형을 없애기 위한 새로고침

		if ((x + 128) >=512) x -= (x + 128) - 512;		//사각형이 이미지를 벗어났을때를 위한 처리
		else if ((x - 128) <= 0) x -= (x - 128);
		if ((y + 128) >= 512) y -= (y + 128) - 512;
		else if ((y - 128) <= 0) y -= (y - 128);

		x -= 127;					//마우스로 클릭한 지점을 사각형의 중심점으로 하기 위한 처리
		y -= 127;
		Rect r(x,y,w,h);			//클릭한 위치를 중심으로 사각형 생성
		roi = img(r);				//클릭한 위치를 중심으로 한 사각형만큼 이미지를 자름
		resize(roi, roi, (size(roi) * 2));	//자른 이미지를 2배 확대
		imshow("Croping", roi);		//확대한 이미지를 화면에 출력

		rectangle(img,r,Scalar(0,255,0),2);	//기존 이미지에 사각형 출력
		imshow("Digital image processing", img);	//사각형이 그려진 이미지 출력
	}
	else if (event == EVENT_RBUTTONDOWN) {}
	else if (event == EVENT_MBUTTONDOWN) {}
	else if (event == EVENT_MOUSEMOVE) {}
}
int main()
{
	img = imread("Lenna.jpg", IMREAD_COLOR);	//이미지를 불러옴
	if (img.empty()) {				//이미지가 없을때 에러 처리
		cout << "영상을 읽을 수 없음" << endl;
		return -1;
	}
	clone = img.clone();			//이미지 새로고침을 위한 클론 생성
	imshow("Digital image processing", img);	//불러온 이미지 화면에 출력

	setMouseCallback("Digital image processing", onMouse);	//마우스 클릭 입력

	while (1) {						//키보드 입력 처리
	int key = waitKey(0);
	if (key == 'q') break;			//q를 누르면 종료
	else if (key == 's') {			//s를 누르면 자른 이미지를 지정된 위치에 저장
		imwrite("cropingLenna.jpg",roi);
		}
	}
	return 0;
}
