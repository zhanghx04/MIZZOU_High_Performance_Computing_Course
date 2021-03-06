#include <string>
#include "SLIC.h"

int main()
{
	int width(0), height(0);
	// unsigned int (32 bits) to hold a pixel in ARGB format as follows:
	// from left to right,
	// the first 8 bits are for the alpha channel (and are ignored)
	// the next 8 bits are for the red channel
	// the next 8 bits are for the green channel
	// the last 8 bits are for the blue channel
	unsigned int* pbuff = new UINT[sz];
	ReadImage(pbuff, width, height);//YOUR own function to read an image into the ARGB format

	//----------------------------------
	// Initialize parameters
	//----------------------------------
	int k = 200;//Desired number of superpixels.
	double m = 20;//Compactness factor. use a value ranging from 10 to 40 depending on your needs. Default is 10
	int* klabels = NULL;
	int numlabels(0);
	string filename = "yourfilename.jpg";
	string savepath = "yourpathname";
	//----------------------------------
	// Perform SLIC on the image buffer
	//----------------------------------
	SLIC segment;
	segment.DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels(pbuff, width, height, klabels, numlabels, k, m);
	// Alternately one can also use the function DoSuperpixelSegmentation_ForGivenStepSize() for a desired superpixel size
	//----------------------------------
	// Save the labels to a text file
	//----------------------------------
	segment.SaveSuperpixelLabels(klabels, width, height, filename, savepath);
	//----------------------------------
	// Draw boundaries around segments
	//----------------------------------
	segment.DrawContoursAroundSegments(pbuff, klabels, width, height, 0xff0000);
	//----------------------------------
	// Save the image with segment boundaries.
	//----------------------------------
	SaveSegmentedImageFile(pbuff, width, height);//YOUR own function to save an ARGB buffer as an image
	//----------------------------------
	// Clean up
	//----------------------------------
	if(pbuff) delete [] pbuff;
	if(klabels) delete [] klabels;

	return 0;
}