# Space Image
Lightweight functions for retreival of image metadata

# Usage
- Include the "SpaceImage.hpp" header in your project 
- Create an instance of the "ImageMeta" struct from the "SpaceImage" namespace
- Call "ReadImage(const char* path)" with the path to the file to retrieve the metadata (only currently functions with PNG)

# ImageMeta Struct
The main ImageMeta struct contains basic image fields:
- width
- height
- bitdepth
- colorType

In addition it contains a std::vector of keyword and data pairs which gives the field title and the char/string representation of the data contained in the field

# Example
```
#include "SpaceImage.hpp"

//Takes all metadata from image
//Prints out the data type keyword and the char/string representation of the data
SpaceImage::ImageMeta meta = SpaceImage::ReadImage("test.png");
for (int i = 0; i < meta.metaElements.size(); i++)
{
    std::cout << meta.metaElements[i].keyword << " " << std::endl;
    std::cout << meta.metaElements[i].data << std::endl;
}
```
