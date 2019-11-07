/*
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src, dst;
const char* input_title = "input image";
const char* output_title = "demo";
int main(int argc, char** argv) {
	src = imread("E:/photo/segment.jpg", 1);
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow(input_title, WINDOW_AUTOSIZE);
	namedWindow(output_title, WINDOW_AUTOSIZE);

	imshow(input_title, src);
	cvtColor(src, src, COLOR_BGR2GRAY);
	cornerHarris(src, dst, 2, 3, 0.01);
	threshold(dst, dst, 0.00001, 255, THRESH_BINARY);
	imshow(output_title, dst);

	waitKey(0);
	return 0;
}
*/
/*带滚动条*/
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

const char* title1 = "窗口1";
const char* title2 = "窗口2";

Mat srcImg, srcImg1, grayImg;
int thresh = 30;
int max_thresh = 175;

void on_CornerHarris(int, void*);

int main(int argc, char** argv) {
	srcImg = imread("E:/photo/chessboard.jpg", 1);
	if (!srcImg.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow(title1, WINDOW_AUTOSIZE);
	namedWindow(title2, WINDOW_AUTOSIZE);

	//imshow("原始图", srcImg);

	srcImg1 = srcImg.clone();
	cvtColor(srcImg1, grayImg, COLOR_BGR2GRAY);

	createTrackbar("Threshold:", title1, &thresh, max_thresh, on_CornerHarris);
	on_CornerHarris(0, 0);

	waitKey(0);
	return 0;
}

void on_CornerHarris(int, void*) {
	Mat dstImg;
	Mat normImg;
	Mat scaledImg;

	dstImg = Mat::zeros(srcImg.size(), CV_32FC1);
	srcImg1 = srcImg.clone();

	cornerHarris(grayImg, dstImg, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImg, normImg, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImg, scaledImg);

	/*绘制*/
	for (int j = 0; j < normImg.rows; j++) {
		for (int i = 0; i < normImg.cols; i++) {
			if ((int)normImg.at<float>(j, i) > thresh + 80) {
				circle(srcImg1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(srcImg1, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow(title1, srcImg1);
	imshow(title2, scaledImg);
}