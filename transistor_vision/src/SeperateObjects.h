/*
 * SeperateObjects.h
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 */
#ifndef SEPERATEOBJECTS_H_
#define SEPERATEOBJECTS_H_

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>
#include <stdlib.h>


using namespace std;
using namespace cv;



class SeperateObjects {
private:
	Point get_corner_points (Rect boundBox);
public:

	SeperateObjects();
	virtual ~SeperateObjects();
	Mat1b BoundBox(Mat1b Binary, Mat1b origanal_image);

};

#endif /* SEPERATEOBJECTS_H_ */
