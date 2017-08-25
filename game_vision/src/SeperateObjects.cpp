/*
 * SeperateObjects.cpp
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 *
 *      Separate objects/regions in an image and draw bounded boxes around them in the original captured image frame.
 */

#include "SeperateObjects.h"
//#include <vector>
//#include <stdlib.h>

//using namespace std;
//RNG rng(12345);
SeperateObjects::SeperateObjects() {

	std::cout<<"identyfying objects in seperate objects class"<<endl;

}

SeperateObjects::~SeperateObjects() {

}

/**
	 *****************************************************************************************
	 *  @brief      identify objects and get their X and Y coordinates in the image frame
	 *
	 *  @usage      draw boxes around each object/region,
	 *  			create a vector of seperated objects/regions7
	 *  			get coordinates of each object/region
	 *
	 *
	 *  @param      Binary image
	 *  @param      grayscale image
	 *  @param      Original (non- processed) image frame
	 *  @param      indicate which directory to save separated object/regions images (only effective is last parameter is set to "true"). 0 = darkworld/non-contrasted binary image; 1 = lightworld/contrasted binary image
	 *  @param      vector which will hold x coordinates of each object/region
	 *  @param      vector which will hold y coordinates of each object/region
	 *  @param 		true = save separated objects/regions in directory of your choice
	 *
	 *  @return     vector of object/regions
	 ****************************************************************************************/

vector <Mat>  SeperateObjects::BoundBox(Mat Binary, Mat origanal_image,Mat& Original_image_clone, int world_number, vector<int>& x_coordinate, vector<int>& y_coordinate, bool save_image_result)
{
	//bounded box will be draw on this copy of the original image instead
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//find contours
	findContours(Binary, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	 /// Get the moments(weighted average of image pixels intensities )
	  vector<Moments> mu(contours.size());
	  for( uint32_t i = 0; i < contours.size(); i++ )
	     { mu[i] = moments( contours[i], false ); }

	  ///  Get the mass centres:
	    vector<Point2f> mc( contours.size() );
	    for( uint32_t i = 0; i < contours.size(); i++ )
	       { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

	//Approximate contours to polygons + get bounding rects
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	//region of interest
	vector<Mat> roi(contours.size());
	//get image coordinate;
	vector<int> x2_coordinate ( contours.size() );
	vector<int> y2_coordinate ( contours.size() );


	//character length for roi filename to be saved in separate folder
	char file [100];
	int lock_dark_file = 0 ;
	int lock_light_file = 0;

	for(uint32_t i = 0; i < contours.size(); i++)
	{

		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);

		boundRect[i] = boundingRect(Mat(contours_poly[i]));

		x2_coordinate[i] = ((boundRect[i].x + boundRect[i].width) / 2);
		y2_coordinate[i] = ((boundRect[i].y + boundRect[i].height) / 2);

		Scalar color( rand()&255, rand()&255, rand()&255 );
		rectangle (Original_image_clone, boundRect[i].tl(), boundRect[i].br(), color, 2,8,0);

		// Crop the original image to the defined ROI
	    roi[i] = origanal_image(boundRect[i]);
	    //save regions of interest into a folder
	    if ( save_image_result == true)
	    {
			if (world_number == 0)
			{
				if (lock_dark_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects/trasistor_vision_darkworld_images/*");lock_dark_file++; }
				sprintf(file,"../game_vision/cloudbank_images/objects/trasistor_vision_darkworld_images/Image%d.jpg",i);
			}
			else if(world_number == 1)
			{
				if (lock_light_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects/trasistor_vision_lightworld_images/*");lock_light_file++; }
				sprintf(file,"../game_vision/cloudbank_images/objects/trasistor_vision_lightworld_images/Image%d.jpg",i);
			}

			imwrite(file,roi[i]);
		}


	}
	x_coordinate = x2_coordinate;
	y_coordinate = y2_coordinate;



	return roi;
}

