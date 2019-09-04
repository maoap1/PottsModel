#include <opencv2/opencv.hpp>
#include <map>

#include "Header.h"

using namespace cv;
using namespace std;

void SaveLatticePicture(string filename, uint8_t numberOfStates)
{
	uint8_t grid[latticeSize][latticeSize];
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			
			grid[i][j] = (uint8_t)((255 * lattice[i][j]) / numberOfStates);
		}
	}

	Mat image(latticeSize, latticeSize, CV_8UC1, grid);
	imwrite(filename, image);
}

void SaveLatticeWithoutWhite(string filename, uint8_t numberOfStates)
// Without BLACK??
{
	uint8_t grid[latticeSize][latticeSize];
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			grid[i][j] = (uint8_t)((255 * (lattice[i][j] + 1)) / (numberOfStates + 1));
		}
	}

	Mat image(latticeSize, latticeSize, CV_8UC1, grid);
	imwrite(filename, image);
}

void LoadLatticeFromFile(string filename, uint8_t numberOfStates)
{
	Mat image = imread(filename, CV_8UC1);
	map<uint8_t, uint8_t> dictionary;

	for (uint8_t i = 0; i < numberOfStates; i++)
	{
		dictionary[(uint8_t)((255 * i) / numberOfStates)] = i;
	}
	
	for (int i = 0; i < latticeSize; i++)
	{
		for (int j = 0; j < latticeSize; j++)
		{
			lattice[i][j] = dictionary[image.at<uint8_t>(i, j)];
		}
	}
	
}

void SaveLatticeRawPicture(string filename, uint8_t numberOfStates)
{
	Mat image(latticeSize, latticeSize, CV_8UC1, lattice);
	imwrite(filename, image);
}
