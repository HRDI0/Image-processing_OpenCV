#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char* argv[]) {

	Point_<int> pt1(10, 20);    //int 형 Point 변수
	Point2f pt2(10.3f, 2.34f);   //위와 같은 형태의 변수 - float과  double 형 모두 같은 형식으로  선언 가능
	Point pt_i(50, 30);         //자주 쓰는 int형은 Point로 정의되어있다.
	Point2i pt3 = pt1 + (Point2i)pt3;   //사칙연산 가능 _ 다른 자료형일 경우 형변환 필요
	Point2d pt_d = (Point2d)(pt2 * 0.32);            //단 곱연산의 경우 Point와 스칼라 연산은 가능하나 Point끼리는 불가
													 //pt1 == pt_i 같은 비교 연산도 가능
	cout << endl;
	cout << "pt1 = " << pt1 << endl;
	cout << "pt2 = " << pt2.x << " / " << pt2.y << endl;
	cout << "(pt1 = pt_i) ? -> " << (pt1 == pt_i) << endl;
	cout << "pt3 = " << pt3 << endl;
	cout << "pt_d = " << pt_d << endl;
	cout << "pt1 과 pt_i 의 내적, 외적 " << pt1.dot(pt_i) << " / " << pt1.cross(pt_i) << endl; //내적과 외적 연산 가능

	Point3i pt4(10, 20, 30);          //3차원 자료형을 나타내기 위한 자료형 위 point 형과 같은 성질을 가진다.

	Size_<int> sz1(3, 4);            //이미지나 사각형의 크기를 규정하는 클래스
	Size sz_i(4, 5);                 //point형과 내부 변수구조가 동일하여 서로 형변환이 가능하다
	Size2f sz2(3.2f, 1.2f);         //단, 3차원 자료형은 없다.

	cout << endl;
	cout << "sz1.width = " << sz1.width << endl;        //내부변수 명은 width와 height 이다.
	cout << "sz1.height = " << sz1.height << endl;
	cout << "sz1 넓이 " << sz1.area() << endl;       //두 내부변수를 곱해 넓이를 구한다.
	cout << "sz2 + pt2 = " << sz2 + Size2f(pt2) << endl;    //Size와 Point를 형변환하여 연산 가능

	Size r_sz(10, 20);

	Point r_pt1(0, 0), r_pt2(40, 80), r_pt3(30, 60);

	Rect rect1(10, 10, 30, 40);       //2차원 사각형 정보를 나타내는 클래스
	Rect rect2(r_pt1, r_pt2);       //Size와 Point를 활용해 선언할 수 있다.
	Rect rect3(r_pt3, r_sz);

	cout << endl;
	cout << "Rect1 " << rect1 << endl;
	cout << "Rect2 " << rect2 << endl;
	cout << "Rect3 " << rect3 << endl;

	cout << endl;
	cout << "Rect1를 x = 40, y = 80 만큼 평행이동 " << rect1 + (Point)r_pt2 << endl;
	cout << "Rect2의 시작좌표(왼쪽상단)와 종료좌표(오른쪽하단) " << "시작좌표 : " << rect2.tl() << " / 종료좌표 : " << rect2.br() << endl;
	cout << "Rect3의 크기 : " << rect3.size() << endl;
	cout << "Rect3의 크기를 10x20만큼 늘리기 " << rect3 + (Size)r_sz << endl;

	Vec2b v1(10, 10);                            //원소 개수가 작은 벡터를 위한 클래스
	Vec3i v2(20, 30, 15);                        //Vec(원소갯수)(내부변수 자료형) 으로 선언한다.
	Vec6f v3(2.3, 4.1, 3.6, 1.5, 2.3, 4.2);      //uchar = b / short = s / int = i / float = f / double = d  이다.
	Vec3d v4(3.2, 2.9, 1.0);
	Vec3i v5 = v2 + (Vec3i)v4;                   //형변환 연산 가능

	Point3i pv1 = (Point3i)(v2 + (Vec3i)v4);     //Point_ Point3_ Scalar_ 클래스로 형변환 연산가능

	cout << endl;
	cout << "Vector 1 " << v1 << endl;
	cout << "Vector 2 * Vector 5 = " << v2.mul(v5) << endl;
	cout << "Vector 3의 첫번째 원소 " << v3[0] << endl;
	cout << "Vector 3의 여섯번째 원소 " << v3[5] << endl;
	cout << "Vector 원소로 이루어진 Point 1 " << pv1 << endl;

	Scalar_<int> red(0, 0, 255);                   // Scalar는 Vec<tp,4>에서 파생된 형태로 4개의 원소를 가지며 파랑,초록,빨강,투명도를 나타낸다.
	Scalar_<int> blue(255);                     //정의되지 않은 원소는 0으로 설정된다.
	Scalar_<double> green(0, 255);
	Scalar_<float> black;                       // 4개의 모두 정의하지 않는다면 모두 0으로 설정된다.

	Vec3d red_vec(0, 0, 255);                      //Vec 클래스에서의 대부분의 연산이 가능하다.

	Scalar violet = blue + (Scalar_<int>)red_vec;  //자주 쓰이는 Scalar_<double>은 Scalar로 정의되어있다.
	Scalar yellow = green + (Scalar)red_vec;

	cout << endl;
	cout << "red : " << red[0] << ", " << red[1] << ", " << red[2] << ", " << red[3] << endl;
	cout << "blue : " << blue << endl;
	cout << "green : " << green << endl;
	cout << "black : " << black << endl;
	cout << "white : " << (Scalar)black + (Scalar)red + green + (Scalar)blue << endl;
	cout << "red_vec : " << red_vec << endl;
	cout << "violet : " << violet << endl;
	cout << "yellow : " << yellow << endl;

	Mat image(300, 500, CV_8UC1, Scalar(255));      //행렬
	Point2f cneter(250, 150), pts[4];               //중앙점과 네 꼭짓점을 저장할 변수
	Size2f size(300, 100);                          //사각형의 크기
	RotatedRect rot_rect(cneter, size, 20);         //회전 사각형 선언
	Rect bount_rect = rot_rect.boundingRect();      //생성된 회전 사각형의 네 꼭짓점은 포함하는 최소크기 사각형 생성

	rectangle(image, bount_rect, Scalar(0), 1);     //위에 생성한 사각형 그리기
	circle(image, rot_rect.center, 1, Scalar(0), 2);   //정중앙에 점(원) 그리기
	rot_rect.points(pts);                           //회전 사각형의 꼭짓점 반환

	for (int i = 0; i < 4; i++) {                     //꼭짓점에 점(원)과 각각의 사이를 잇는 선 그리기
		circle(image, pts[i], 4, Scalar(0), 1);
		line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);
	}

	imshow("회전 사각형", image);                        //그려진 사각형 과 원 출력
	waitKey(0);											//키 입력 대기

	cout << endl;
	cout << "OpenCV version - " << CV_VERSION << endl;
	return 0;
}