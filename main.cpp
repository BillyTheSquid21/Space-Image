#include <stdio.h>
#include <iostream>
#include "MetaRead.hpp"

int main()
{
	SpaceImage::ImageMeta meta = SpaceImage::ReadImage("test.png");
	for (int i = 0; i < meta.metaElements.size(); i++)
	{
		std::cout << meta.metaElements[i].keyword << " " << std::endl;
		std::cout << meta.metaElements[i].data << std::endl;
	}
	return 0;
}