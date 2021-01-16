//
// Created by daniel on 15.01.2021.
//

#include "include/Task4.h"
#include <iostream>


Task4::Task4(cimg_library::CImg<unsigned char>* img)
		:img(img),img_transformed(512)
{
	for (int y = 0; y < WIDTH; y++)
	{
		img_transformed[y].resize(HEIGHT);
	}
}



void Task4::transform_row(int row_number, unsigned char* first_pixel,
		std::array<std::array<std::complex<double>, WIDTH>, HEIGHT>& img_output)
{
	for (int k = 0; k<img->width(); k++)
	{
			//-j*2*pi*k/N
		double row_coefficient = -2 * M_PI * k / img->width();

		std::complex<double> transformed_pixel;
		auto* pixel = first_pixel;
		for (int n = 0; n < WIDTH; n++)
		{
			transformed_pixel += std::polar((double)*pixel, row_coefficient * n);
			pixel++;
		}

		img_output[k][row_number] = transformed_pixel;
	}
}
void Task4::transform_row(int row_number, std::complex<double>* first_pixel)
{
	for (int k = 0; k<img->width(); k++)
	{
		//-j*2*pi*k/N
		double row_coefficient = -2 * M_PI * k / img->width();

		std::complex<double> transformed_pixel;
		auto* pixel = first_pixel;
		for (int n = 0; n < WIDTH; n++)
		{
			std::complex<double> tmp(0,row_coefficient*n);
			transformed_pixel += *pixel * std::exp(tmp);
			pixel++;
		}

		img_transformed[k][row_number] = transformed_pixel;
	}
}


void Task4::DFT()
{
	std::array<std::array<std::complex<double>,WIDTH>,HEIGHT> img_tmp;
	for (int y = 0; y<img->height(); y++)
	{
		transform_row(y, img->data(0, y), img_tmp);
		{
			using namespace std;
			cout<<img_tmp[0][y]<<";";
			//cout<<".";
		}
	}
	for (int y = 0; y<img->height(); y++)
	{
		transform_row(y,&img_tmp[y][0]);
		{
			using namespace std;
			//cout<<img_transformed[0][y]<<",";
			cout<<",";
		}
	}

	print_spatial_domain();
}

void Task4::print_spatial_domain()
{

	cimg_library::CImg<double> new_img(HEIGHT,WIDTH);

	for(int y = 0 ; y<512 ; y++)
		for(int x = 0 ; x<512 ; x++)
		{
			new_img(x,y)=log10(abs(img_transformed[x][y]));
		}
	new_img.display();

	//auto* data = img_transformed.begin();
	//for(auto & pixel : *img)
	//{
	//	pixel=log10(std::abs(*data));
	//}
}

/*

void Task4::transform_col(int row_number)
{
	unsigned new_col;

	if (row_number < WIDTH / 2)
		new_col = row_number + WIDTH / 2;
	else
		new_col = row_number - WIDTH / 2;

for (int k = 0; k < HEIGHT / 2; k++)
	{
		//-j*2*pi*k/N
		double row_coefficient = -2 * M_PI * k / HEIGHT;
		std::complex<double> transformed_pixel = 0.0;

		int n = 0;

		for (auto& pixel : img_transformed_shifted[row_number])
		{
			transformed_pixel += pixel * std::exp(row_coefficient * n);
		}
		img_transformed[k + 512 / 2][new_col] = transformed_pixel;
	}
	for (int k = HEIGHT / 2; k < HEIGHT; k++)
	{
		//-j*2*pi*k/N
		double row_coefficient = -2 * M_PI * k / HEIGHT;
		std::complex<double> transformed_pixel = 0.0;

		int n = 0;

		for (auto& pixel : img_transformed_shifted[row_number])
		{
			transformed_pixel += pixel * pixel * std::exp(row_coefficient * n);
		}
		img_transformed[k - 512 / 2][new_col] = transformed_pixel;
	}
}
*/
