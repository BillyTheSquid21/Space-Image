#include <stdio.h>
#include <iostream>
#include <SpaceImage.hpp>

int main()
{
	SpaceImage::ImageMeta meta = SpaceImage::ReadImage("torterra2.png");
	for (int i = 0; i < meta.metaElements.size(); i++)
	{
		std::cout << meta.metaElements[i].keyword << " " << std::endl;
		std::cout << meta.metaElements[i].data << std::endl;
	}
	return 0;
}
