#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char* argv[]) {

	Point_<int> pt1(10, 20);    //int �� Point ����
	Point2f pt2(10.3f, 2.34f);   //���� ���� ������ ���� - float��  double �� ��� ���� ��������  ���� ����
	Point pt_i(50, 30);         //���� ���� int���� Point�� ���ǵǾ��ִ�.
	Point2i pt3 = pt1 + (Point2i)pt3;   //��Ģ���� ���� _ �ٸ� �ڷ����� ��� ����ȯ �ʿ�
	Point2d pt_d = (Point2d)(pt2 * 0.32);            //�� �������� ��� Point�� ��Į�� ������ �����ϳ� Point������ �Ұ�
													 //pt1 == pt_i ���� �� ���굵 ����
	cout << endl;
	cout << "pt1 = " << pt1 << endl;
	cout << "pt2 = " << pt2.x << " / " << pt2.y << endl;
	cout << "(pt1 = pt_i) ? -> " << (pt1 == pt_i) << endl;
	cout << "pt3 = " << pt3 << endl;
	cout << "pt_d = " << pt_d << endl;
	cout << "pt1 �� pt_i �� ����, ���� " << pt1.dot(pt_i) << " / " << pt1.cross(pt_i) << endl; //������ ���� ���� ����

	Point3i pt4(10, 20, 30);          //3���� �ڷ����� ��Ÿ���� ���� �ڷ��� �� point ���� ���� ������ ������.

	Size_<int> sz1(3, 4);            //�̹����� �簢���� ũ�⸦ �����ϴ� Ŭ����
	Size sz_i(4, 5);                 //point���� ���� ���������� �����Ͽ� ���� ����ȯ�� �����ϴ�
	Size2f sz2(3.2f, 1.2f);         //��, 3���� �ڷ����� ����.

	cout << endl;
	cout << "sz1.width = " << sz1.width << endl;        //���κ��� ���� width�� height �̴�.
	cout << "sz1.height = " << sz1.height << endl;
	cout << "sz1 ���� " << sz1.area() << endl;       //�� ���κ����� ���� ���̸� ���Ѵ�.
	cout << "sz2 + pt2 = " << sz2 + Size2f(pt2) << endl;    //Size�� Point�� ����ȯ�Ͽ� ���� ����

	Size r_sz(10, 20);

	Point r_pt1(0, 0), r_pt2(40, 80), r_pt3(30, 60);

	Rect rect1(10, 10, 30, 40);       //2���� �簢�� ������ ��Ÿ���� Ŭ����
	Rect rect2(r_pt1, r_pt2);       //Size�� Point�� Ȱ���� ������ �� �ִ�.
	Rect rect3(r_pt3, r_sz);

	cout << endl;
	cout << "Rect1 " << rect1 << endl;
	cout << "Rect2 " << rect2 << endl;
	cout << "Rect3 " << rect3 << endl;

	cout << endl;
	cout << "Rect1�� x = 40, y = 80 ��ŭ �����̵� " << rect1 + (Point)r_pt2 << endl;
	cout << "Rect2�� ������ǥ(���ʻ��)�� ������ǥ(�������ϴ�) " << "������ǥ : " << rect2.tl() << " / ������ǥ : " << rect2.br() << endl;
	cout << "Rect3�� ũ�� : " << rect3.size() << endl;
	cout << "Rect3�� ũ�⸦ 10x20��ŭ �ø��� " << rect3 + (Size)r_sz << endl;

	Vec2b v1(10, 10);                            //���� ������ ���� ���͸� ���� Ŭ����
	Vec3i v2(20, 30, 15);                        //Vec(���Ұ���)(���κ��� �ڷ���) ���� �����Ѵ�.
	Vec6f v3(2.3, 4.1, 3.6, 1.5, 2.3, 4.2);      //uchar = b / short = s / int = i / float = f / double = d  �̴�.
	Vec3d v4(3.2, 2.9, 1.0);
	Vec3i v5 = v2 + (Vec3i)v4;                   //����ȯ ���� ����

	Point3i pv1 = (Point3i)(v2 + (Vec3i)v4);     //Point_ Point3_ Scalar_ Ŭ������ ����ȯ ���갡��

	cout << endl;
	cout << "Vector 1 " << v1 << endl;
	cout << "Vector 2 * Vector 5 = " << v2.mul(v5) << endl;
	cout << "Vector 3�� ù��° ���� " << v3[0] << endl;
	cout << "Vector 3�� ������° ���� " << v3[5] << endl;
	cout << "Vector ���ҷ� �̷���� Point 1 " << pv1 << endl;

	Scalar_<int> red(0, 0, 255);                   // Scalar�� Vec<tp,4>���� �Ļ��� ���·� 4���� ���Ҹ� ������ �Ķ�,�ʷ�,����,������ ��Ÿ����.
	Scalar_<int> blue(255);                     //���ǵ��� ���� ���Ҵ� 0���� �����ȴ�.
	Scalar_<double> green(0, 255);
	Scalar_<float> black;                       // 4���� ��� �������� �ʴ´ٸ� ��� 0���� �����ȴ�.

	Vec3d red_vec(0, 0, 255);                      //Vec Ŭ���������� ��κ��� ������ �����ϴ�.

	Scalar violet = blue + (Scalar_<int>)red_vec;  //���� ���̴� Scalar_<double>�� Scalar�� ���ǵǾ��ִ�.
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

	Mat image(300, 500, CV_8UC1, Scalar(255));      //���
	Point2f cneter(250, 150), pts[4];               //�߾����� �� �������� ������ ����
	Size2f size(300, 100);                          //�簢���� ũ��
	RotatedRect rot_rect(cneter, size, 20);         //ȸ�� �簢�� ����
	Rect bount_rect = rot_rect.boundingRect();      //������ ȸ�� �簢���� �� �������� �����ϴ� �ּ�ũ�� �簢�� ����

	rectangle(image, bount_rect, Scalar(0), 1);     //���� ������ �簢�� �׸���
	circle(image, rot_rect.center, 1, Scalar(0), 2);   //���߾ӿ� ��(��) �׸���
	rot_rect.points(pts);                           //ȸ�� �簢���� ������ ��ȯ

	for (int i = 0; i < 4; i++) {                     //�������� ��(��)�� ������ ���̸� �մ� �� �׸���
		circle(image, pts[i], 4, Scalar(0), 1);
		line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);
	}

	imshow("ȸ�� �簢��", image);                        //�׷��� �簢�� �� �� ���
	waitKey(0);											//Ű �Է� ���

	cout << endl;
	cout << "OpenCV version - " << CV_VERSION << endl;
	return 0;
}