// Copyright (c) 2020 University of Lyon and CNRS (France).
// All rights reserved.
//
//The code is the implementation of our paper
//"PCQM: A Full-Reference Quality Metric for Colored 3D Point Clouds"
//Gabriel Meynet, Yana Nehme, Julie Digne, Guillaume Lavoué
//Presented at QoMEX 2020.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

/** @file */
#include <iostream>
// must be defined before pcqm.h
#define TINYPLY_IMPLEMENTATION
#include "pcqm.h"

/**
* \fn main(int argc, char** argv)
* \brief Entry point of the program
* \return EXIT_SUCCESS if the code executed successfuly.
*/
int main(int argc, char **argv)
{

	// Keep console open if false
	bool fast_quit = false;

	// PCQM params
	double RadiusCurvature = 0.004;
	int threshold_knnsearch = 20;
	double radius_factor = 2.0;

	if (argc < 3)
	{
		std::cerr << "Usage: "
				  << "REFERENCE.ply DISTORTED.ply (Options) (--fastquit || -fq) (-r radius)(-rx factor) "
					 "(-knn nb_point)"
				  << std::endl;
		return -1;
	}

	//As the code compute projection of regfile on reffile we have to inverse input to match paper description (R onto D)
	std::string reffile = argv[2];
	std::string regfile = argv[1];

	std::string inv_check = "";
	for (int i = 3; i < argc; ++i)
	{

		if (std::string(argv[i]) == "--fastquit" || std::string(argv[i]) == "-fq")
		{

			fast_quit = true;
			std::cout << "fast_quit set to : " << fast_quit << std::endl;
		}

		if (std::string(argv[i]) == "-r")
		{
			if (i + 1 < argc)
			{		 // Make sure we aren't at the end of argv!
				i++; // Increment 'i' so we don't get the argument as the next argv[i].
				RadiusCurvature = std::stod(std::string(argv[i]));
				std::cout << "Radius set to : " << RadiusCurvature << std::endl;
			}
			else
			{
				std::cerr << "-r option requires one argument." << std::endl;
				return -1;
			}
		}

		if (std::string(argv[i]) == "-knn")
		{
			if (i + 1 < argc)
			{ // Make sure we aren't at the end of argv!
				i++;
				threshold_knnsearch =
					std::stoi(std::string(argv[i])); // Increment 'i' so we don't get the argument as the next argv[i].

				std::cout << "threshold_knnsearch set to : " << threshold_knnsearch << std::endl;
			}
			else
			{
				std::cerr << "-knn option requires one argument." << std::endl;
				return -1;
			}
		}

		if (std::string(argv[i]) == "-rx")
		{
			if (i + 1 < argc)
			{ // Make sure we aren't at the end of argv!
				i++;
				radius_factor =
					std::stod(std::string(argv[i])); // Increment 'i' so we don't get the argument as the next argv[i].

				std::cout << "radius_factor set to : " << radius_factor << std::endl;
			}
			else
			{
				std::cerr << "-rx option requires one argument." << std::endl;
				return -1;
			}
		}
	}

	compute_pcqm(
		reffile,
		regfile,
		RadiusCurvature,
		threshold_knnsearch,
		radius_factor);

	if (!fast_quit)
	{
		std::cout << "Press enter to exit" << std::endl;
		std::getchar();
	}
	return EXIT_SUCCESS;
}
